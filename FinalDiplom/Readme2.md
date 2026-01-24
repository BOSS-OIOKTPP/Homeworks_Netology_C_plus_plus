FinalDiplom/
├── Source/                     # Исходный код
│   └── spider/                 # Основной проект Visual Studio
│       ├── DatabaseManager/    # Работа с PostgreSQL
│       ├── Indexer/            # Обработка HTML → частота слов
│       ├── IniFile/            # Чтение config.ini
│       ├── LinkExtractor/      # Извлечение ссылок из HTML
│       ├── SpiderClient/       # HTTP/HTTPS-запросы
│       ├── UrlUtils/           # Нормализация URL
│       ├── SpiderEngine/       # Рекурсивный обход
│       ├── Main.cpp            # Точка входа
│       ├── config.ini          # Конфигурация
│       └── deploy.bat          # Сборка дистрибутива
├── Distributiv/                # Готовый к запуску дистрибутив
└── README.md                   # Этот файл