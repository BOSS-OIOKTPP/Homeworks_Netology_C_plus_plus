#include "stopwatch.h"

// Конструктор
Stopwatch::Stopwatch(QObject *parent): QObject{parent},
    _totalElapsed(0),
    _lastLapTime(0),
    _lapCount(0),
    _isRunning(false)
{
    // Создаем таймер
    _timer = new QTimer(this);
    // Устанавливаем интервал срабатывания 100 мс
    _timer->setInterval(100);
    // Связываем сигнал со слотом
    connect(_timer, &QTimer::timeout, this, &Stopwatch::updateTime);
}

// Запускаем секундомер
void Stopwatch::start()
{
    // Если не запущен
    if (!_isRunning) {
        _elapsedTimer.start();  // запускаем измерение времени
        _timer->start();        // запускаем таймер, у нас настроен интервал 100мс
        _isRunning = true;      // отмечаем, что секундомер запущен
    }
}

// Останавливаем секундомер
void Stopwatch::stop()
{
    // если запущен
    if (_isRunning) {

        _totalElapsed += _elapsedTimer.elapsed(); // обновляем общее время
        _timer->stop();                           // останавливаем таймер
        _isRunning = false;                       // отмечаем, что секундомер остановлен
    }
}

// Выполняем сброс измерений
void Stopwatch::reset()
{
    stop();               // останвливаем секундомер
    _totalElapsed = 0;    // очищаем общее время
    _lastLapTime = 0;     // очищаем время последнего круга
    _lapCount = 0;        // очищаем количество кругов
    _lapTimes.clear();    // очищаем список с временами кругов
}

// Сохраняем измерение при нажатии на кнопку Круга
void Stopwatch::lap()
{
    if (!_isRunning) return;

    qint64 currentTotal = _totalElapsed + _elapsedTimer.elapsed();  // Запомнили время завершения текущего круга
    qint64 lapTime = currentTotal - _lastLapTime;                   // Вычислили интервал времени, т.е. сколько круг длился
    _lastLapTime = currentTotal;                                    // Запомнили время завершения измерения круга

    _lapCount++;                            // увеличиваем счетчик кругов
    _lapTimes.append(lapTime);              // добавляем время измерения в список   
}


void Stopwatch::updateTime()
{
    if (_isRunning) {
        qint64 elapsed = _totalElapsed + _elapsedTimer.elapsed();

        emit timeUpdated(elapsed);
    }
}

qint64 Stopwatch::getElapsedMs() const
{
    if (_isRunning) {
        return _totalElapsed + _elapsedTimer.elapsed();
    }
    return _totalElapsed;
}


// Количество кругов
int Stopwatch::getLapCount() const
{
    return _lapCount;
}

// Список времени кругов
const QList<qint64>& Stopwatch::getLapTimes() const
{
    return _lapTimes;
}

// Состояние счетчика
bool Stopwatch::isRunning() const
{
    return _isRunning;
}
