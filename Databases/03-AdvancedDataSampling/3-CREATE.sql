-- Таблица жанров
CREATE TABLE IF NOT EXISTS Genre (
    Genre_ID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL
);

-- Таблица исполнителей
CREATE TABLE IF NOT EXISTS Performer (
    Performer_ID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL
);

-- Таблица связей многие ко многим: жанры — исполнители
CREATE TABLE IF NOT EXISTS GenrePerformer (
    ID SERIAL PRIMARY KEY,
    Genre_ID INTEGER NOT NULL REFERENCES Genre(Genre_ID) ON DELETE CASCADE,
    Performer_ID INTEGER NOT NULL REFERENCES Performer(Performer_ID) ON DELETE CASCADE
);

-- Таблица альбомов
CREATE TABLE IF NOT EXISTS Album (
    Album_ID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    YearOfRelease DATE NOT NULL
);

-- Таблица связей многие ко многим: альбомы — исполнители
CREATE TABLE IF NOT EXISTS AlbumPerformer (
    ID SERIAL PRIMARY KEY,
    Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID) ON DELETE CASCADE,
    Performer_ID INTEGER NOT NULL REFERENCES Performer(Performer_ID) ON DELETE CASCADE
);

-- Таблица треков
CREATE TABLE IF NOT EXISTS Track (
    Track_ID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Duration INTEGER NOT NULL, -- в секундах
    Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID) ON DELETE CASCADE
);

-- Таблица сборников
CREATE TABLE IF NOT EXISTS Collection (
    Collection_ID SERIAL PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    YearOfRelease DATE NOT NULL
);

-- Таблица связей многие ко многим: сборники — треки
CREATE TABLE IF NOT EXISTS CollectionTrack (
    ID SERIAL PRIMARY KEY,
    Track_ID INTEGER NOT NULL REFERENCES Track(Track_ID) ON DELETE CASCADE,
    Collection_ID INTEGER NOT NULL REFERENCES Collection(Collection_ID) ON DELETE CASCADE
);