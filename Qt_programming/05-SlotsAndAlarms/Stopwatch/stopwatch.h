#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QList>


class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);


    // Основные методы управления
    void start();   // Нажали кнопку Старт/Стоп
    void stop();    // Нажали кнопку Старт/Стоп
    void reset();   // Нажали кнопку Очистить
    void lap();     // Нажали кнопку Круг


    // Вычисляем интервал
    qint64 getElapsedMs() const;
    // Количество кругов
    int getLapCount() const;
    // Список времени кругов
    QList<qint64> getLapTimes() const;
    // Определяем, что таймер запущен
    bool isRunning() const;

signals:
    // Сигналы, которые отправляет Stopwatch главному окну

    // 1. Сигнал генерируется таймером каждые 100мс, пока запущен секундомер
    //    Главное окно подключается к этому сигналу, чтобы обновлять label стекущим временем
    void timeUpdated(qint64 elapsedMs);

    // 2. Сигнал генерируется при нажатии кнопки Круг.
    //    Главное окно подключается к этому сигналу и добавляет запись о Круге в textBrowser
    //    lapNumber - номер круга, lapTimeMs - интервал времени круга в мс
    void lapRecorded(int lapNumber, qint64 lapTimeMs);

    // 3. Сигнал генерируется при нажатии кнопки Очистить в методе reset().
    //    Главное окно подключается к этому сигналу и устанавливает время в 0.0 сек, очищает текстовый браузер,
    //    устанавливает кнопку в состояние Старт и запрещает кнопку Круг
    void resetOccurred();

private slots:

    // Слот вызывается по таймеру для обновления времени на главной форме. Он подключён к сигналу timeout() объекта QTimer
    // и вызывается каждые 100 миллисекунд, когда секундомер запущен.
    // Проверяет, запущен ли секундомер
    // Вычисляет общее прошедшее время работы секундомера
    // Запускает сигнал timeUpdated() с новым значением времени
    void updateTime();


private:
    QTimer *_timer;              // Таймер для обновления, интервал 100 мс
    QElapsedTimer _elapsedTimer; // Для точного замера интервала
    qint64 _totalElapsed;        // Общее время в миллисекундах
    qint64 _lastLapTime;         // Время, когда закончилось измерение последнего круга. Необходимо для измерения интервала времени круга, т.к. мы можем останавливать счетчик и продолжать далее не очищая его.
    int _lapCount;               // Счётчик кругов
    QList<qint64> _lapTimes;     // Список времени кругов
    bool _isRunning;             // Запущен счетчик или нет


};

#endif // STOPWATCH_H
