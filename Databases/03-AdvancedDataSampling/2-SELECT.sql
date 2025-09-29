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


--    Задание 4
--
--Названия альбомов, в которых присутствуют исполнители более чем одного жанра.
select a.name 
from album a
where exists(select gp.performer_id, count(*) 
			   from albumperformer ap  
			   		inner join genreperformer gp on ap.performer_id =gp.performer_id 
			   		inner join genre g on gp.genre_id = g.genre_id 
			   where ap.album_id = a.album_id 
			   group by gp.performer_id
			   having count(*)>1
			   )
			   
--Наименования треков, которые не входят в сборники.
-- версия 1			   
select t.name
from track t
where not exists(select 1 from collectiontrack ct where ct.track_id = t.track_id limit 1)

-- версия 2
select t.name
from track t
	 left join collectiontrack ct on t.track_id = ct.track_id 
where ct.track_id is null	 

--Исполнитель или исполнители, написавшие самый короткий по продолжительности трек, — теоретически таких треков может быть несколько.
select p.name
from track t 
	 inner join albumperformer ap on t.album_id = ap.album_id 
	 inner join performer p on ap.performer_id = p.performer_id 
where t.duration = (select MIN(duration) from track)


--Названия альбомов, содержащих наименьшее количество треков.
select a.name
from album a
     inner join track t on a.album_id =t.album_id 
group by a.album_id
having count(*) = (
		select MIN(res.album_track_count)
		from (select a1.album_id, count(*) album_track_count
				from album a1
				     inner join track t1 on a1.album_id =t1.album_id 
				group by a1.album_id) res
				)		
    
