-- Таблица жанров
CREATE TABLE IF NOT EXISTS Genres (
	Genres_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL
);
-- Таблица исполнителей
CREATE TABLE IF NOT EXISTS Performers (
	Performers_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL
);
-- Таблица связей многие ко многим исполнителей и жанров
CREATE TABLE IF NOT EXISTS GenresAndPerformers (
	ID SERIAL PRIMARY KEY,
	Genres_ID INTEGER NOT NULL REFERENCES Genres(Genres_ID), 
	Performers_ID INTEGER NOT NULL REFERENCES Performers(Performers_ID)	
);
-- Таблица альбомов
CREATE TABLE IF NOT EXISTS Album (
	Album_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	YearOfRelease DATE NOT NULL
);
-- Таблица связей многие ко многим альбомов и исполнителей
CREATE TABLE IF NOT EXISTS AlbumAndPerformers (
	ID SERIAL PRIMARY KEY,
	Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID), 
	Performers_ID INTEGER NOT NULL REFERENCES Performers(Performers_ID)	
);
-- Таблица трэков
CREATE TABLE IF NOT EXISTS Track (
	Track_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	Duration TIME,
	Album_ID INTEGER NOT NULL REFERENCES Album(Album_ID)
);
-- Таблица сборников
CREATE TABLE IF NOT EXISTS Collection (
	Collection_ID SERIAL PRIMARY KEY,
	Name VARCHAR(255) NOT NULL,
	YearOfRelease DATE NOT NULL
);
-- Таблица связей многие ко многим сборников и треков
CREATE TABLE IF NOT EXISTS CollectionAndTrack (
	ID SERIAL PRIMARY KEY,
	Track_ID INTEGER NOT NULL REFERENCES Track(Track_ID), 
	Collection_ID INTEGER NOT NULL REFERENCES Collection(Collection_ID)	
);



