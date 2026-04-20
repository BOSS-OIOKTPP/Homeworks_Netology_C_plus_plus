# Модуль 1: DatabaseManager (Qt Console)

Консольный модуль на Qt 6.4.2 для первого шага диплома:
- читает настройки БД из `config.ini`;
- при первом запуске проверяет существование БД и создаёт её (если нет прав - вернёт понятную ошибку);
- подключается к БД и создаёт таблицы `documents`, `words`, `doc_word` через `CREATE TABLE IF NOT EXISTS`.

## Открытие в Qt Creator (`C:\Qt\Tools\QtCreator\`)

1. Запустите `C:\Qt\Tools\QtCreator\bin\qtcreator.exe`.
2. Откройте файл `CMakeLists.txt` из папки `Source/1.DatabaseManager`.
3. В Qt Creator выберите Kit с Qt 6.4.2 (например `Desktop Qt 6.4.2 MinGW 64-bit`).
4. Нажмите **Configure Project**, затем **Run** или **Build**.

## Сборка из консоли (опционально)

Пример для Qt 6.4.2 MinGW:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.4.2/mingw_64"
cmake --build build
```

Если используете другой комплект Qt, замените путь в `CMAKE_PREFIX_PATH`.

## Запуск

1. Убедитесь, что установлен PostgreSQL и доступен драйвер Qt `QPSQL`.
2. Проверьте параметры в `config.ini`.
3. Запустите:

```powershell
.\build\DatabaseManagerQtConsole.exe
```

Успешный вывод:

`Готово: БД доступна, таблицы созданы или уже существовали.`
