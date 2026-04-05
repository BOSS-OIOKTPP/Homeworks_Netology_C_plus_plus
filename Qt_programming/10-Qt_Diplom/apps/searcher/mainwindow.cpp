/**
 * Поисковик: интерфейс Qt + вызовы SearchDatabase.
 */

#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

namespace {

constexpr int kMaxQueryWords = 4;
constexpr int kMaxResults = 10;

QString configPath()
{
    return QApplication::applicationDirPath() + QStringLiteral("/searcher.ini");
}

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_searchDb(QStringLiteral("searcher_conn"))
{
    setWindowTitle(QStringLiteral("Поисковик (диплом Qt)"));
    resize(720, 520);

    if (!connectDatabase()) {
        showError(QStringLiteral("Не удалось подключиться к базе данных. Проверьте searcher.ini и сервер PostgreSQL."));
    }

    m_tabs = new QTabWidget(this);
    setCentralWidget(m_tabs);

    auto *searchPage = new QWidget;
    auto *searchLay = new QVBoxLayout(searchPage);

    auto *row1 = new QHBoxLayout;
    row1->addWidget(new QLabel(QStringLiteral("Запрос (слова через пробел, не более %1):").arg(kMaxQueryWords)));
    m_queryEdit = new QLineEdit;
    m_queryEdit->setPlaceholderText(QStringLiteral("например: привет мир"));
    row1->addWidget(m_queryEdit, 1);

    m_searchBtn = new QPushButton(QStringLiteral("Искать"));
    row1->addWidget(m_searchBtn);
    searchLay->addLayout(row1);

    m_resultsEdit = new QPlainTextEdit;
    m_resultsEdit->setReadOnly(true);
    m_resultsEdit->setPlaceholderText(QStringLiteral("Здесь появятся пути к файлам — от большей релевантности к меньшей."));
    searchLay->addWidget(m_resultsEdit);

    connect(m_searchBtn, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(m_queryEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearch);

    m_tabs->addTab(searchPage, QStringLiteral("Поиск"));

    auto *statsPage = new QWidget;
    auto *statsLay = new QVBoxLayout(statsPage);

    auto *row2 = new QHBoxLayout;
    m_refreshWordsBtn = new QPushButton(QStringLiteral("Обновить список слов"));
    m_relevanceDetailsBtn = new QPushButton(QStringLiteral("Показать документы и релевантность последнего запроса"));
    m_relevanceDetailsBtn->setEnabled(false);
    row2->addWidget(m_refreshWordsBtn);
    row2->addWidget(m_relevanceDetailsBtn);
    row2->addStretch();
    statsLay->addLayout(row2);

    m_wordsTable = new QTableWidget(0, 2);
    m_wordsTable->setHorizontalHeaderLabels({QStringLiteral("Слово"), QStringLiteral("Суммарная частота в БД")});
    m_wordsTable->horizontalHeader()->setStretchLastSection(true);
    statsLay->addWidget(m_wordsTable);

    connect(m_refreshWordsBtn, &QPushButton::clicked, this, &MainWindow::reloadWordStatistics);
    connect(m_relevanceDetailsBtn, &QPushButton::clicked, this, &MainWindow::onShowRelevanceDetails);

    m_tabs->addTab(statsPage, QStringLiteral("Слова и детали"));

    reloadWordStatistics();
}

MainWindow::~MainWindow() = default;

bool MainWindow::connectDatabase()
{
    const QString ini = configPath();
    if (!QFile::exists(ini))
        return false;
    return m_searchDb.openFromIni(ini);
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::warning(this, QStringLiteral("Ошибка"), message);
}

QStringList MainWindow::parseQueryWords(const QString &text) const
{
    QString lower = text.toLower();
    static const QRegularExpression nonWord(QStringLiteral("[^\\p{L}\\p{N}]+"));
    lower.replace(nonWord, QStringLiteral(" "));
    QStringList parts = lower.split(QLatin1Char(' '), Qt::SkipEmptyParts);

    QStringList out;
    for (QString w : parts) {
        w = w.trimmed();
        if (w.length() < 3 || w.length() > 32)
            continue;
        if (!out.contains(w))
            out.append(w);
        if (out.size() >= kMaxQueryWords)
            break;
    }
    return out;
}

void MainWindow::onSearch()
{
    m_lastHits.clear();
    m_relevanceDetailsBtn->setEnabled(false);

    if (!m_searchDb.isOpen()) {
        showError(QStringLiteral("Нет подключения к базе данных."));
        return;
    }

    const QStringList words = parseQueryWords(m_queryEdit->text());
    if (words.isEmpty()) {
        m_resultsEdit->setPlainText(QStringLiteral("Введите от одного до четырёх слов (буквы/цифры, длина слова 3–32)."));
        return;
    }

    QString sqlErr;
    if (!m_searchDb.search(words, kMaxResults, &m_lastHits, &sqlErr)) {
        showError(QStringLiteral("Ошибка SQL: %1").arg(sqlErr));
        m_resultsEdit->setPlainText(QStringLiteral("Внутренняя ошибка при выполнении запроса."));
        return;
    }

    QStringList lines;
    for (const auto &p : m_lastHits)
        lines << QStringLiteral("%1  (релевантность: %2)").arg(p.first).arg(p.second);

    if (lines.isEmpty()) {
        m_resultsEdit->setPlainText(QStringLiteral("Ничего не найдено: нет документов, где встречались бы все указанные слова."));
    } else {
        m_resultsEdit->setPlainText(lines.join(QLatin1Char('\n')));
        m_relevanceDetailsBtn->setEnabled(true);
    }

    reloadWordStatistics();
}

void MainWindow::onShowRelevanceDetails()
{
    if (m_lastHits.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("Нет данных"), QStringLiteral("Сначала выполните поиск."));
        return;
    }

    QString text;
    for (const auto &p : m_lastHits)
        text += QStringLiteral("%1 — релевантность %2\n").arg(p.first).arg(p.second);

    QMessageBox::information(this, QStringLiteral("Документы и релевантность"), text.trimmed());
}

void MainWindow::reloadWordStatistics()
{
    if (!m_searchDb.isOpen() || !m_wordsTable)
        return;

    QVector<QPair<QString, qint64>> rows;
    QString err;
    if (!m_searchDb.loadWordStatistics(&rows, &err)) {
        showError(QStringLiteral("Не удалось загрузить статистику слов: %1").arg(err));
        return;
    }

    m_wordsTable->setRowCount(0);
    int row = 0;
    for (const auto &pr : rows) {
        m_wordsTable->insertRow(row);
        m_wordsTable->setItem(row, 0, new QTableWidgetItem(pr.first));
        m_wordsTable->setItem(row, 1, new QTableWidgetItem(QString::number(pr.second)));
        ++row;
    }
}
