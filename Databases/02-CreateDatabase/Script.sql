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
-- Таблица связей многие ко многим исполнителей и жанров
CREATE TABLE IF NOT EXISTS GenrePerformer (
	ID SERIAL PRIMARY KEY,
	Genre_ID INTEGER NOT NULL REFERENCES Genre(Genre_ID), 
	Performer_ID INTEGER NOT NULL REFERENCES Performer(Performer_ID)	
);
-- Таблица альбомов
CREATE TABLE IF NOT EXISTS Album (
	Album_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	YearOfRelease DATE NOT NULL
);
-- Таблица связей многие ко многим альбомов и исполнителей
CREATE TABLE IF NOT EXISTS AlbumPerformer (
	ID SERIAL PRIMARY KEY,
	Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID), 
	Performer_ID INTEGER NOT NULL REFERENCES Performer(Performer_ID)	
);
-- Таблица трэков
CREATE TABLE IF NOT EXISTS Track (
	Track_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	Duration INTEGER NOT NULL,
	Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID)
);
-- Таблица сборников
CREATE TABLE IF NOT EXISTS Collection (
	Collection_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	YearOfRelease DATE NOT NULL
);
-- Таблица связей многие ко многим сборников и треков
CREATE TABLE IF NOT EXISTS CollectionTrack (
	ID SERIAL PRIMARY KEY,
	Track_ID INTEGER NOT NULL REFERENCES Track(Track_ID), 
	Collection_ID INTEGER NOT NULL REFERENCES Collection(Collection_ID)	
);



