#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "SearchDatabase.h"

class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class QTableWidget;
class QTabWidget;

/**
 * Главное окно: поиск по БД через класс SearchDatabase.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearch();
    void onShowRelevanceDetails();
    void reloadWordStatistics();

private:
    bool connectDatabase();
    void showError(const QString &message);

    QStringList parseQueryWords(const QString &text) const;

    SearchDatabase m_searchDb;

    QTabWidget *m_tabs = nullptr;

    QLineEdit *m_queryEdit = nullptr;
    QPlainTextEdit *m_resultsEdit = nullptr;
    QPushButton *m_searchBtn = nullptr;

    QTableWidget *m_wordsTable = nullptr;
    QPushButton *m_refreshWordsBtn = nullptr;
    QPushButton *m_relevanceDetailsBtn = nullptr;

    QVector<QPair<QString, qint64>> m_lastHits;
};

#endif // MAINWINDOW_H
