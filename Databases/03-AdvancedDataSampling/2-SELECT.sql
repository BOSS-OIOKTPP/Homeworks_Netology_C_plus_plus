--    Задание 2
--
-- Название и продолжительность самого длительного трека.
select name, max(duration) as duration from track group by name order by duration DESC limit 1;

-- Название треков, продолжительность которых не менее 3,5 минут.
select name, max(duration) as duration from track group by name having max(duration)/60>=3.5 order by duration desc;

-- Названия сборников, вышедших в период с 2018 по 2020 годы включительно.
select name from collection where EXTRACT(YEAR FROM yearofrelease) between 2018 and 2020;

-- Исполнители, чьё имя состоит из одного слова.
select name from performer where name not like '% %';

-- Название треков, которые содержат слова «мой» или «my».
select name from track where UPPER(name) like '%МОЙ%' or UPPER(name) like '%MY%';


--    Задание 3
--
--Количество исполнителей в каждом жанре.
select a.name, count(*) performer_count
from genre a 
     inner join genreperformer g on a.genre_id = g.genre_id 
	 inner join performer p on g.performer_id = p.performer_id 
group by a.name 

--Количество треков, вошедших в альбомы 2019–2020 годов.
select a.name, EXTRACT(YEAR FROM a.yearofrelease) "year", count(*) album_track_count_2019_2020
from album a 
     inner join track t on a.album_id = t.album_id
where EXTRACT(YEAR FROM a.yearofrelease) between 2019 and 2020
group by a.name, EXTRACT(YEAR FROM a.yearofrelease);

-- Средняя продолжительность треков по каждому альбому.
select a.name, AVG(t.Duration) AS avg_duration_seconds
from album a 
     inner join track t on a.album_id = t.album_id
group by a.name     

-- Все исполнители, которые не выпустили альбомы в 2020 году.
select p.name
from album a 
     inner join albumperformer ap on a.album_id = ap.album_id
     inner join performer p on ap.performer_id = p.performer_id
where EXTRACT(YEAR FROM a.yearofrelease) <> 2020

--Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами).
select c.name
from collection c 
	 inner join collectiontrack ct on c.collection_id = ct.collection_id
	 inner join track t on ct.track_id = t.track_id 
	 inner join albumperformer ap on ap.album_id = t.album_id 
	 inner join performer p on ap.performer_id = p.performer_id
where p.name = 'Queen'