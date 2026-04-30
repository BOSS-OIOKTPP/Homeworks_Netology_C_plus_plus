#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("Поисковик"));

    m_configPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));
    m_dbManager = std::make_unique<DbManager>(m_configPath);
    ui->showResultsButton->setEnabled(false);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->queryEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchClicked);
    connect(ui->showResultsButton, &QPushButton::clicked, this, &MainWindow::onShowResultsClicked);
    connect(ui->refreshWordsButton, &QPushButton::clicked, this, &MainWindow::onRefreshWordsClicked);

    if (!initializeDatabase()) {
        ui->searchButton->setEnabled(false);
        ui->refreshWordsButton->setEnabled(false);
        return;
    }

    onRefreshWordsClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchClicked()
{
    const QStringList queryWords = parseQueryWords(ui->queryEdit->text());
    if (queryWords.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("Некорректный запрос"),
                             QStringLiteral("Введите от 1 до 4 слов (длина каждого 4..32 символа)."));
        return;
    }

    QString errorMessage;
    QList<QPair<QString, int>> results;
    if (!searchDocuments(queryWords, &results, &errorMessage)) {
        QMessageBox::critical(this, QStringLiteral("Ошибка поиска"), errorMessage);
        return;
    }

    m_lastResults = results;
    ui->showResultsButton->setEnabled(true);

    ui->searchOutput->clear();
    ui->searchOutput->appendPlainText(QStringLiteral("Запрос: %1").arg(queryWords.join(' ')));

    if (m_lastResults.isEmpty()) {
        ui->searchOutput->appendPlainText(QStringLiteral("Результатов не найдено."));
    } else {
        ui->searchOutput->appendPlainText(
            QStringLiteral("Найдено документов: %1. Нажмите кнопку «Показать найденные документы».")
                .arg(m_lastResults.size()));
    }
}

void MainWindow::onShowResultsClicked()
{
    ui->searchOutput->clear();
    if (m_lastResults.isEmpty()) {
        ui->searchOutput->appendPlainText(QStringLiteral("Результатов не найдено."));
        return;
    }

    ui->searchOutput->appendPlainText(QStringLiteral("Найденные документы и релевантность:"));
    for (const auto &item : m_lastResults) {
        ui->searchOutput->appendPlainText(QStringLiteral("- %1 (релевантность: %2)")
                                              .arg(normalizePathForLog(item.first))
                                              .arg(item.second));
    }
}

void MainWindow::onRefreshWordsClicked()
{
    QString errorMessage;
    QList<QPair<QString, int>> wordsStat;
    if (!loadWordsStatistic(&wordsStat, &errorMessage)) {
        QMessageBox::critical(this, QStringLiteral("Ошибка чтения словаря"), errorMessage);
        return;
    }

    ui->wordsOutput->clear();
    if (wordsStat.isEmpty()) {
        ui->wordsOutput->appendPlainText(QStringLiteral("Словарь пуст."));
        return;
    }

    for (const auto &item : wordsStat) {
        ui->wordsOutput->appendPlainText(QStringLiteral("%1 : %2").arg(item.first).arg(item.second));
    }
}

bool MainWindow::initializeDatabase()
{
    QString errorMessage;
    if (!m_dbManager->connectToDatabase(&errorMessage)) {
        QMessageBox::critical(this, QStringLiteral("Ошибка БД"),
                              QStringLiteral("Не удалось подключиться к БД: %1").arg(errorMessage));
        return false;
    }

    bool tablesAlreadyExist = false;
    if (!m_dbManager->createTables(&tablesAlreadyExist, &errorMessage)) {
        QMessageBox::critical(this, QStringLiteral("Ошибка БД"),
                              QStringLiteral("Не удалось проверить/создать таблицы: %1").arg(errorMessage));
        return false;
    }

    return true;
}

QString MainWindow::normalizePathForLog(const QString &path) const
{
    return QDir::fromNativeSeparators(path);
}

QStringList MainWindow::parseQueryWords(const QString &queryText) const
{
    const QString normalized = queryText.toLower();
    const QStringList rawTokens = normalized.split(QRegularExpression(QStringLiteral("[^\\p{L}\\p{N}]+")),
                                                   Qt::SkipEmptyParts);

    QStringList result;
    for (const QString &token : rawTokens) {
        if (token.length() <= 3 || token.length() > 32) {
            continue;
        }
        if (!result.contains(token)) {
            result.append(token);
        }
        if (result.size() == 4) {
            break;
        }
    }
    return result;
}

bool MainWindow::searchDocuments(const QStringList &queryWords,
                                 QList<QPair<QString, int>> *results,
                                 QString *errorMessage)
{
    if (results == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан контейнер результатов.");
        }
        return false;
    }

    results->clear();

    QStringList placeholders;
    for (int i = 0; i < queryWords.size(); ++i) {
        placeholders << QStringLiteral(":w%1").arg(i);
    }

    const QString sql = QStringLiteral(
        "SELECT d.path, SUM(dw.frequency) AS relevance "
        "FROM documents d "
        "JOIN document_words dw ON dw.document_id = d.id "
        "JOIN words w ON w.id = dw.word_id "
        "WHERE w.word IN (%1) "
        "GROUP BY d.id, d.path "
        "HAVING COUNT(DISTINCT w.word) = :words_count "
        "ORDER BY relevance DESC, d.path "
        "LIMIT 10;")
                            .arg(placeholders.join(QStringLiteral(",")));

    QSqlQuery query(m_dbManager->database());
    query.prepare(sql);
    for (int i = 0; i < queryWords.size(); ++i) {
        query.bindValue(QStringLiteral(":w%1").arg(i), queryWords.at(i));
    }
    query.bindValue(QStringLiteral(":words_count"), queryWords.size());

    if (!query.exec()) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    while (query.next()) {
        const QString path = query.value(0).toString();
        const int relevance = query.value(1).toInt();
        results->append(qMakePair(path, relevance));
    }

    return true;
}

bool MainWindow::loadWordsStatistic(QList<QPair<QString, int>> *wordsStat, QString *errorMessage)
{
    if (wordsStat == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан контейнер статистики.");
        }
        return false;
    }

    wordsStat->clear();

    QSqlQuery query(m_dbManager->database());
    const QString sql =
        QStringLiteral("SELECT w.word, COALESCE(SUM(dw.frequency), 0) AS total_frequency "
                       "FROM words w "
                       "LEFT JOIN document_words dw ON dw.word_id = w.id "
                       "GROUP BY w.id, w.word "
                       "HAVING COALESCE(SUM(dw.frequency), 0) > 0 "
                       "ORDER BY total_frequency DESC, w.word;");

    if (!query.exec(sql)) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    while (query.next()) {
        wordsStat->append(qMakePair(query.value(0).toString(), query.value(1).toInt()));
    }

    return true;
}

