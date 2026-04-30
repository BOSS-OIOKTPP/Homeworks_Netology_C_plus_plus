#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../DatabaseManager/DbManager.h"

#include <QMainWindow>
#include <QPair>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchClicked();
    void onShowResultsClicked();
    void onRefreshWordsClicked();

private:
    bool initializeDatabase();
    QString normalizePathForLog(const QString &path) const;
    QStringList parseQueryWords(const QString &queryText) const;
    bool searchDocuments(const QStringList &queryWords,
                         QList<QPair<QString, int>> *results,
                         QString *errorMessage);
    bool loadWordsStatistic(QList<QPair<QString, int>> *wordsStat, QString *errorMessage);

    std::unique_ptr<DbManager> m_dbManager;
    QString m_configPath;
    QList<QPair<QString, int>> m_lastResults;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
