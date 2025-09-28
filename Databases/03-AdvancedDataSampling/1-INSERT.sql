-- Жанры
INSERT INTO Genre (Name) VALUES
('Rock'),
('Pop'),
('Jazz'),
('Electronic'),
('Hip-Hop'),
('Classical');

-- Исполнители
INSERT INTO Performer (Name) VALUES
('Queen'),
('Adele'),
('Miles Davis'),
('Daft Punk'),
('Kendrick Lamar'),
('Ludovico Einaudi'),
('Dua Lipa'),
('Billie Eilish');

-- Связи: Жанры и Исполнители
INSERT INTO GenrePerformer (Genre_ID, Performer_ID) VALUES
(1, 1), -- Queen → Rock
(2, 2), -- Adele → Pop
(3, 3), -- Miles Davis → Jazz
(4, 4), -- Daft Punk → Electronic
(5, 5), -- Kendrick Lamar → Hip-Hop
(6, 6), -- Ludovico Einaudi → Classical
(1, 4), -- Daft Punk → Rock (доп. связь)
(2, 1), -- Queen → Pop (доп. связь)
(2, 7),  -- Dua Lipa → Pop
(2, 8),  -- Billie Eilish → Pop
(4, 8);  -- Billie Eilish → Electronic

-- Альбомы
INSERT INTO Album (Name, YearOfRelease) VALUES
('A Night at the Opera', '1975-11-21'),
('25', '2015-11-20'),
('Kind of Blue', '1959-08-17'),
('Random Access Memories', '2013-05-17'),
('To Pimp a Butterfly', '2015-03-15'),
('Elements', '2013-09-13'),
('Future Nostalgia', '2020-03-27'),
('When We All Fall Asleep, Where Do We Go?', '2019-03-29');

-- Связи: Альбомы ↔ Исполнители
INSERT INTO AlbumPerformer (Album_ID, Performer_ID) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5),
(6, 6),
(7, 7),  
(8, 8);  

-- Треки (Duration в секундах)
INSERT INTO Track (Name, Duration, Album_ID) VALUES
('Bohemian Rhapsody', 354, 1),
('Another One Bites the Dust', 214, 1),
('Hello', 295, 2),
('Rolling in the Deep', 228, 2),
('So What', 564, 3),
('Get Lucky', 369, 4),
('Alright', 219, 5),
('Experience', 330, 6),
('My Universe', 210, 2),
('Don''t Start Now', 183, 7), 
('bad guy', 194, 8);  


-- Сборники
INSERT INTO Collection (Name, YearOfRelease) VALUES
('Greatest Hits Vol.1', '2020-01-15'),
('Chill Vibes', '2021-06-10'),
('Workout Mix 2022', '2022-03-01'),
('Classical Focus', '2023-09-22'),
('Top Tracks of the Decade', '2024-01-01');

-- Связи: Сборники ↔ Треки
INSERT INTO CollectionTrack (Track_ID, Collection_ID) VALUES
(1, 1), -- Bohemian Rhapsody
(3, 1), -- Hello
(5, 1), -- So What

(4, 2), -- Rolling in the Deep
(8, 2), -- Experience

(2, 3), -- Another One Bites the Dust
(7, 3), -- Alright

(8, 4), -- Experience
(6, 4), -- Get Lucky

(1, 5), -- Bohemian Rhapsody
(7, 5), -- Alright
(3, 5); -- Hello