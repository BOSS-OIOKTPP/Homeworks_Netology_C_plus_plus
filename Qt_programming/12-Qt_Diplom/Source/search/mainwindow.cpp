#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlError>
#include <QSqlQuery>

// Инициализирует окно поисковика, подключает обработчики кнопок и готовит БД к работе.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Загружаем интерфейс из mainwindow.ui.
    ui->setupUi(this);

    // Конфигурация БД хранится рядом с исполняемым файлом.
    m_configPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));
    m_dbManager = std::make_unique<DbManager>(m_configPath);

    // До первого успешного поиска кнопку показа результатов держим заблокированной.
    ui->showResultsButton->setEnabled(false);

    // Кнопка "Искать" запускает обработчик поиска.
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    // Нажатие Enter в поле запроса запускает тот же поиск.
    connect(ui->queryEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchClicked);
    // Кнопка показывает детальный список найденных документов.
    connect(ui->showResultsButton, &QPushButton::clicked, this, &MainWindow::onShowResultsClicked);
    // Кнопка обновляет вкладку словаря из текущих данных БД.
    connect(ui->refreshWordsButton, &QPushButton::clicked, this, &MainWindow::onRefreshWordsClicked);

    // Если подключение/инициализация БД не удались, отключаем рабочие кнопки.
    if (!initializeDatabase()) {
        ui->searchButton->setEnabled(false);
        ui->refreshWordsButton->setEnabled(false);
        return;
    }

    // При старте сразу показываем актуальную статистику слов.
    onRefreshWordsClicked();
}

// Освобождает объект интерфейса.
MainWindow::~MainWindow()
{
    delete ui;
}

// Обрабатывает выполнение поиска по введенному запросу.
void MainWindow::onSearchClicked()
{
    // Нормализуем и валидируем слова запроса.
    const QStringList queryWords = parseQueryWords(ui->queryEdit->text());
    if (queryWords.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("Некорректный запрос"),
                             QStringLiteral("Введите от 1 до 4 слов (длина каждого 4..32 символа)."));
        return;
    }

    QString errorMessage;
    QList<QPair<QString, int>> results;
    // Получаем из БД документы, содержащие все слова запроса.
    if (!searchDocuments(queryWords, &results, &errorMessage)) {
        QMessageBox::critical(this, QStringLiteral("Ошибка поиска"), errorMessage);
        return;
    }

    // Сохраняем результаты, чтобы их можно было открыть отдельной кнопкой.
    m_lastResults = results;
    ui->showResultsButton->setEnabled(true);

    // Выводим короткую сводку по выполненному запросу.
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

// Показывает подробный список найденных документов и их релевантность.
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

// Обновляет вкладку словаря на основе текущих данных в БД.
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

// Инициализирует доступ к БД: подключение и создание таблиц при необходимости.
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

// Приводит путь к единому формату со слешами '/' для аккуратного отображения в UI.
QString MainWindow::normalizePathForLog(const QString &path) const
{
    return QDir::fromNativeSeparators(path);
}

// Преобразует строку запроса в список уникальных поисковых слов.
QStringList MainWindow::parseQueryWords(const QString &queryText) const
{
    // Приводим запрос к нижнему регистру и делим по не буквенно-цифровым символам.
    const QString normalized = queryText.toLower();
    const QStringList rawTokens = normalized.split(QRegularExpression(QStringLiteral("[^\\p{L}\\p{N}]+")),
                                                   Qt::SkipEmptyParts);

    QStringList result;
    for (const QString &token : rawTokens) {
        // Учитываем только слова длиной 4..32 символа.
        if (token.length() <= 3 || token.length() > 32) {
            continue;
        }
        // Убираем дубликаты слов в рамках одного запроса.
        if (!result.contains(token)) {
            result.append(token);
        }
        // По требованиям ограничиваем запрос максимум четырьмя словами.
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
    // Проверяем, что контейнер результатов передан вызывающим кодом.
    if (results == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан контейнер результатов.");
        }
        return false;
    }

    results->clear();

    // Динамически формируем список именованных параметров под количество слов в запросе.
    QStringList placeholders;
    for (int i = 0; i < queryWords.size(); ++i) {
        placeholders << QStringLiteral(":w%1").arg(i);
    }

    // Ищем документы, где встречаются все слова запроса, и считаем релевантность
    // как сумму частот этих слов в документе.
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

    // Подготавливаем и параметризуем запрос.
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

    // Читаем результат выборки в список (путь, релевантность).
    while (query.next()) {
        const QString path = query.value(0).toString();
        const int relevance = query.value(1).toInt();
        results->append(qMakePair(path, relevance));
    }

    return true;
}

bool MainWindow::loadWordsStatistic(QList<QPair<QString, int>> *wordsStat, QString *errorMessage)
{
    // Проверяем, что контейнер статистики передан вызывающим кодом.
    if (wordsStat == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан контейнер статистики.");
        }
        return false;
    }

    wordsStat->clear();

    // Загружаем слова и их суммарную частоту по всем документам.
    // Слова с нулевой частотой исключаем из вывода.
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

    // Перекладываем строки SQL-результата в контейнер для UI.
    while (query.next()) {
        wordsStat->append(qMakePair(query.value(0).toString(), query.value(1).toInt()));
    }

    return true;
}

