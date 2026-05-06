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
    // Создает главное окно поисковика и настраивает начальное состояние UI/БД.
    MainWindow(QWidget *parent = nullptr);
    // Освобождает ресурсы интерфейса.
    ~MainWindow();

private slots:
    // Обрабатывает запуск поиска по тексту из поля ввода.
    void onSearchClicked();
    // Показывает документы из последнего выполненного запроса.
    void onShowResultsClicked();
    // Обновляет вкладку словаря (слово -> суммарная частота).
    void onRefreshWordsClicked();

private:
    // Подключается к БД и гарантирует наличие рабочих таблиц.
    bool initializeDatabase();
    // Приводит путь к единому виду для вывода в интерфейс.
    QString normalizePathForLog(const QString &path) const;
    // Нормализует запрос пользователя: разбиение на слова, фильтрация и ограничение до 4 слов.
    QStringList parseQueryWords(const QString &queryText) const;
    // Выполняет SQL-поиск документов, где встречаются все слова запроса.
    bool searchDocuments(const QStringList &queryWords,
                         QList<QPair<QString, int>> *results,
                         QString *errorMessage);
    // Загружает статистику словаря из БД (слово и суммарная частота).
    bool loadWordsStatistic(QList<QPair<QString, int>> *wordsStat, QString *errorMessage);

    // Объект работы с БД.
    std::unique_ptr<DbManager> m_dbManager;
    // Путь к config.ini рядом с исполняемым файлом.
    QString m_configPath;
    // Результаты последнего поиска для кнопки "Показать найденные документы".
    QList<QPair<QString, int>> m_lastResults;

    // Автогенерируемый объект UI из mainwindow.ui.
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
