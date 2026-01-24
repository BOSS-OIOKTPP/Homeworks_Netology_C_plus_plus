# Дипломный проект «Поисковая система»

Проект разбит на модули для удобства тестирования и поддержки.

## Структура проекта

```text
FinalDiplom/
├── Source/                     # Исходный код
│   ├── DatabaseManager/        # Работа с PostgreSQL
│   ├── Indexer/                # Обработка HTML → частота слов
│   ├── IniFile/                # Чтение config.ini
│   ├── LinkExtractor/          # Извлечение ссылок из HTML
│   ├── SpiderClient/           # HTTP/HTTPS-запросы
│   ├── SpiderEngine/           # Рекурсивный обход
│   └── spider/                 # Основной проект Visual Studio (с Main.cpp и config.ini)
└── Distributiv/                # Готовый к запуску дистрибутив
```

## Установка зависимостей

### 1. Установка vcpkg

Установите `vcpkg` в папку `C:\Tools\`:

```powershell
cd C:\
git clone https://github.com/microsoft/vcpkg.git Tools\vcpkg
cd Tools\vcpkg
.\bootstrap-vcpkg.bat
```

### 2. Интеграция с Visual Studio

```powershell
.\vcpkg integrate install
```
Это позволит Visual Studio автоматически находить заголовки и библиотеки без ручной настройки путей.

### 3. Установка необходимых библиотек

Выполните в папке C:\Tools\vcpkg:
```powershell
.\vcpkg install boost-asio:x64-windows boost-beast:x64-windows boost-locale:x64-windows libpqxx:x64-windows openssl:x64-windows
```
Эти команды установят:

- **Boost.Asio** и **Boost.Beast** — для сетевых операций и HTTPS,  
- **Boost.Locale** — для корректной обработки текста (включая UTF-8 и кириллицу),  
- **libpqxx** — для взаимодействия с PostgreSQL,  
- **OpenSSL** — обеспечивает поддержку шифрования SSL/TLS, необходимую для безопасного HTTPS-соединения и работы с защищёнными базами данных.

## Настройка базы данных

### 1. Установка PostgreSQL

Скачайте и установите PostgreSQL с официального сайта:  
https://www.postgresql.org/download/windows/

Убедитесь, что служба PostgreSQL запущена.

### 2. Создание пользователя и базы данных

Откройте **SQL Shell (psql)** или **pgAdmin** и выполните следующие команды:

```sql
-- Создаём пользователя
CREATE USER spider_user WITH PASSWORD 'ваш_пароль';

-- Создаём базу данных
CREATE DATABASE spider_db OWNER spider_user;

-- Даём права на схему public
GRANT ALL ON SCHEMA public TO spider_user;
```

Таблицы будут созданы после первого запуска **spider.exe**.

### 3. Проверка подключения

Убедитесь, что в файле `Source/spider/config.ini` указаны корректные параметры:

```ini
[Spider]
StartUrl=https://example.com
MaxDepth=2

[Database]
Host=localhost
Port=5432
Name=spider_db
User=spider_user
Password=ваш_пароль
```

Теперь проект готов к сборке и запуску.
