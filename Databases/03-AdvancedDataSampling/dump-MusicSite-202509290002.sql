--
-- PostgreSQL database cluster dump
--

-- Started on 2025-09-29 00:02:21

\restrict q2g54Hw1bUdohHTm9XCTfygeizAZKxx83YKVRQRERQ64uFy4ft4qgspj0uspdff

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS;

--
-- User Configurations
--








\unrestrict q2g54Hw1bUdohHTm9XCTfygeizAZKxx83YKVRQRERQ64uFy4ft4qgspj0uspdff

--
-- Databases
--

--
-- Database "template1" dump
--

\connect template1

--
-- PostgreSQL database dump
--

\restrict eSK33GvHwmesCwHbgkGCOjb8IQOg42ZPFBR8LG2Zx8lIgbDhhZWM7pNa319SkEm

-- Dumped from database version 17.6
-- Dumped by pg_dump version 17.6

-- Started on 2025-09-29 00:02:21

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

-- Completed on 2025-09-29 00:02:21

--
-- PostgreSQL database dump complete
--

\unrestrict eSK33GvHwmesCwHbgkGCOjb8IQOg42ZPFBR8LG2Zx8lIgbDhhZWM7pNa319SkEm

--
-- Database "MusicSite" dump
--

--
-- PostgreSQL database dump
--

\restrict rlJHb5XGeRBzaf6w2omwdU7BwYAIEP0G5s9zF4OYP92c9Xpvx3srhAGCRYdxCXb

-- Dumped from database version 17.6
-- Dumped by pg_dump version 17.6

-- Started on 2025-09-29 00:02:21

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4873 (class 1262 OID 16389)
-- Name: MusicSite; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE "MusicSite" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Russian_Russia.1251';


ALTER DATABASE "MusicSite" OWNER TO postgres;

\unrestrict rlJHb5XGeRBzaf6w2omwdU7BwYAIEP0G5s9zF4OYP92c9Xpvx3srhAGCRYdxCXb
\connect "MusicSite"
\restrict rlJHb5XGeRBzaf6w2omwdU7BwYAIEP0G5s9zF4OYP92c9Xpvx3srhAGCRYdxCXb

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 224 (class 1259 OID 16717)
-- Name: album; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.album (
    album_id integer NOT NULL,
    name character varying(255) NOT NULL,
    yearofrelease date NOT NULL
);


ALTER TABLE public.album OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 16716)
-- Name: album_album_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.album_album_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.album_album_id_seq OWNER TO postgres;

--
-- TOC entry 4874 (class 0 OID 0)
-- Dependencies: 223
-- Name: album_album_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.album_album_id_seq OWNED BY public.album.album_id;


--
-- TOC entry 226 (class 1259 OID 16724)
-- Name: albumperformer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.albumperformer (
    id integer NOT NULL,
    album_id integer NOT NULL,
    performer_id integer NOT NULL
);


ALTER TABLE public.albumperformer OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 16723)
-- Name: albumperformer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.albumperformer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.albumperformer_id_seq OWNER TO postgres;

--
-- TOC entry 4875 (class 0 OID 0)
-- Dependencies: 225
-- Name: albumperformer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.albumperformer_id_seq OWNED BY public.albumperformer.id;


--
-- TOC entry 230 (class 1259 OID 16753)
-- Name: collection; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.collection (
    collection_id integer NOT NULL,
    name character varying(255) NOT NULL,
    yearofrelease date NOT NULL
);


ALTER TABLE public.collection OWNER TO postgres;

--
-- TOC entry 229 (class 1259 OID 16752)
-- Name: collection_collection_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.collection_collection_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.collection_collection_id_seq OWNER TO postgres;

--
-- TOC entry 4876 (class 0 OID 0)
-- Dependencies: 229
-- Name: collection_collection_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.collection_collection_id_seq OWNED BY public.collection.collection_id;


--
-- TOC entry 232 (class 1259 OID 16760)
-- Name: collectiontrack; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.collectiontrack (
    id integer NOT NULL,
    track_id integer NOT NULL,
    collection_id integer NOT NULL
);


ALTER TABLE public.collectiontrack OWNER TO postgres;

--
-- TOC entry 231 (class 1259 OID 16759)
-- Name: collectiontrack_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.collectiontrack_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.collectiontrack_id_seq OWNER TO postgres;

--
-- TOC entry 4877 (class 0 OID 0)
-- Dependencies: 231
-- Name: collectiontrack_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.collectiontrack_id_seq OWNED BY public.collectiontrack.id;


--
-- TOC entry 218 (class 1259 OID 16686)
-- Name: genre; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genre (
    genre_id integer NOT NULL,
    name character varying(255) NOT NULL
);


ALTER TABLE public.genre OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16685)
-- Name: genre_genre_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.genre_genre_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.genre_genre_id_seq OWNER TO postgres;

--
-- TOC entry 4878 (class 0 OID 0)
-- Dependencies: 217
-- Name: genre_genre_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.genre_genre_id_seq OWNED BY public.genre.genre_id;


--
-- TOC entry 222 (class 1259 OID 16700)
-- Name: genreperformer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genreperformer (
    id integer NOT NULL,
    genre_id integer NOT NULL,
    performer_id integer NOT NULL
);


ALTER TABLE public.genreperformer OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16699)
-- Name: genreperformer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.genreperformer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.genreperformer_id_seq OWNER TO postgres;

--
-- TOC entry 4879 (class 0 OID 0)
-- Dependencies: 221
-- Name: genreperformer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.genreperformer_id_seq OWNED BY public.genreperformer.id;


--
-- TOC entry 220 (class 1259 OID 16693)
-- Name: performer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.performer (
    performer_id integer NOT NULL,
    name character varying(255) NOT NULL
);


ALTER TABLE public.performer OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16692)
-- Name: performer_performer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.performer_performer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.performer_performer_id_seq OWNER TO postgres;

--
-- TOC entry 4880 (class 0 OID 0)
-- Dependencies: 219
-- Name: performer_performer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.performer_performer_id_seq OWNED BY public.performer.performer_id;


--
-- TOC entry 228 (class 1259 OID 16741)
-- Name: track; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.track (
    track_id integer NOT NULL,
    name character varying(255) NOT NULL,
    duration integer NOT NULL,
    album_id integer NOT NULL
);


ALTER TABLE public.track OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 16740)
-- Name: track_track_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.track_track_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.track_track_id_seq OWNER TO postgres;

--
-- TOC entry 4881 (class 0 OID 0)
-- Dependencies: 227
-- Name: track_track_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.track_track_id_seq OWNED BY public.track.track_id;


--
-- TOC entry 4679 (class 2604 OID 16720)
-- Name: album album_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album ALTER COLUMN album_id SET DEFAULT nextval('public.album_album_id_seq'::regclass);


--
-- TOC entry 4680 (class 2604 OID 16727)
-- Name: albumperformer id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer ALTER COLUMN id SET DEFAULT nextval('public.albumperformer_id_seq'::regclass);


--
-- TOC entry 4682 (class 2604 OID 16756)
-- Name: collection collection_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collection ALTER COLUMN collection_id SET DEFAULT nextval('public.collection_collection_id_seq'::regclass);


--
-- TOC entry 4683 (class 2604 OID 16763)
-- Name: collectiontrack id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack ALTER COLUMN id SET DEFAULT nextval('public.collectiontrack_id_seq'::regclass);


--
-- TOC entry 4676 (class 2604 OID 16689)
-- Name: genre genre_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genre ALTER COLUMN genre_id SET DEFAULT nextval('public.genre_genre_id_seq'::regclass);


--
-- TOC entry 4678 (class 2604 OID 16703)
-- Name: genreperformer id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer ALTER COLUMN id SET DEFAULT nextval('public.genreperformer_id_seq'::regclass);


--
-- TOC entry 4677 (class 2604 OID 16696)
-- Name: performer performer_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.performer ALTER COLUMN performer_id SET DEFAULT nextval('public.performer_performer_id_seq'::regclass);


--
-- TOC entry 4681 (class 2604 OID 16744)
-- Name: track track_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track ALTER COLUMN track_id SET DEFAULT nextval('public.track_track_id_seq'::regclass);


--
-- TOC entry 4859 (class 0 OID 16717)
-- Dependencies: 224
-- Data for Name: album; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.album (album_id, name, yearofrelease) FROM stdin;
1	A Night at the Opera	1975-11-21
2	25	2015-11-20
3	Kind of Blue	1959-08-17
4	Random Access Memories	2013-05-17
5	To Pimp a Butterfly	2015-03-15
6	Elements	2013-09-13
7	Future Nostalgia	2020-03-27
8	When We All Fall Asleep, Where Do We Go?	2019-03-29
\.


--
-- TOC entry 4861 (class 0 OID 16724)
-- Dependencies: 226
-- Data for Name: albumperformer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.albumperformer (id, album_id, performer_id) FROM stdin;
1	1	1
2	2	2
3	3	3
4	4	4
5	5	5
6	6	6
7	7	7
8	8	8
\.


--
-- TOC entry 4865 (class 0 OID 16753)
-- Dependencies: 230
-- Data for Name: collection; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.collection (collection_id, name, yearofrelease) FROM stdin;
1	Greatest Hits Vol.1	2020-01-15
2	Chill Vibes	2021-06-10
3	Workout Mix 2022	2022-03-01
4	Classical Focus	2023-09-22
5	Top Tracks of the Decade	2024-01-01
\.


--
-- TOC entry 4867 (class 0 OID 16760)
-- Dependencies: 232
-- Data for Name: collectiontrack; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.collectiontrack (id, track_id, collection_id) FROM stdin;
1	1	1
2	3	1
3	5	1
4	4	2
5	8	2
6	2	3
7	7	3
8	8	4
9	6	4
10	1	5
11	7	5
12	3	5
\.


--
-- TOC entry 4853 (class 0 OID 16686)
-- Dependencies: 218
-- Data for Name: genre; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genre (genre_id, name) FROM stdin;
1	Rock
2	Pop
3	Jazz
4	Electronic
5	Hip-Hop
6	Classical
\.


--
-- TOC entry 4857 (class 0 OID 16700)
-- Dependencies: 222
-- Data for Name: genreperformer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genreperformer (id, genre_id, performer_id) FROM stdin;
1	1	1
2	2	2
3	3	3
4	4	4
5	5	5
6	6	6
7	1	4
8	2	1
\.


--
-- TOC entry 4855 (class 0 OID 16693)
-- Dependencies: 220
-- Data for Name: performer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.performer (performer_id, name) FROM stdin;
1	Queen
2	Adele
3	Miles Davis
4	Daft Punk
5	Kendrick Lamar
6	Ludovico Einaudi
7	Dua Lipa
8	Billie Eilish
\.


--
-- TOC entry 4863 (class 0 OID 16741)
-- Dependencies: 228
-- Data for Name: track; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.track (track_id, name, duration, album_id) FROM stdin;
1	Bohemian Rhapsody	354	1
2	Another One Bites the Dust	214	1
3	Hello	295	2
4	Rolling in the Deep	228	2
5	So What	564	3
6	Get Lucky	369	4
7	Alright	219	5
8	Experience	330	6
9	My Universe	210	2
10	Don't Start Now	183	7
11	bad guy	194	8
\.


--
-- TOC entry 4882 (class 0 OID 0)
-- Dependencies: 223
-- Name: album_album_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.album_album_id_seq', 8, true);


--
-- TOC entry 4883 (class 0 OID 0)
-- Dependencies: 225
-- Name: albumperformer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.albumperformer_id_seq', 8, true);


--
-- TOC entry 4884 (class 0 OID 0)
-- Dependencies: 229
-- Name: collection_collection_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.collection_collection_id_seq', 5, true);


--
-- TOC entry 4885 (class 0 OID 0)
-- Dependencies: 231
-- Name: collectiontrack_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.collectiontrack_id_seq', 12, true);


--
-- TOC entry 4886 (class 0 OID 0)
-- Dependencies: 217
-- Name: genre_genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.genre_genre_id_seq', 6, true);


--
-- TOC entry 4887 (class 0 OID 0)
-- Dependencies: 221
-- Name: genreperformer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.genreperformer_id_seq', 8, true);


--
-- TOC entry 4888 (class 0 OID 0)
-- Dependencies: 219
-- Name: performer_performer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.performer_performer_id_seq', 8, true);


--
-- TOC entry 4889 (class 0 OID 0)
-- Dependencies: 227
-- Name: track_track_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.track_track_id_seq', 11, true);


--
-- TOC entry 4691 (class 2606 OID 16722)
-- Name: album album_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album
    ADD CONSTRAINT album_pkey PRIMARY KEY (album_id);


--
-- TOC entry 4693 (class 2606 OID 16729)
-- Name: albumperformer albumperformer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_pkey PRIMARY KEY (id);


--
-- TOC entry 4697 (class 2606 OID 16758)
-- Name: collection collection_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collection
    ADD CONSTRAINT collection_pkey PRIMARY KEY (collection_id);


--
-- TOC entry 4699 (class 2606 OID 16765)
-- Name: collectiontrack collectiontrack_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_pkey PRIMARY KEY (id);


--
-- TOC entry 4685 (class 2606 OID 16691)
-- Name: genre genre_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genre
    ADD CONSTRAINT genre_pkey PRIMARY KEY (genre_id);


--
-- TOC entry 4689 (class 2606 OID 16705)
-- Name: genreperformer genreperformer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_pkey PRIMARY KEY (id);


--
-- TOC entry 4687 (class 2606 OID 16698)
-- Name: performer performer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.performer
    ADD CONSTRAINT performer_pkey PRIMARY KEY (performer_id);


--
-- TOC entry 4695 (class 2606 OID 16746)
-- Name: track track_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track
    ADD CONSTRAINT track_pkey PRIMARY KEY (track_id);


--
-- TOC entry 4702 (class 2606 OID 16730)
-- Name: albumperformer albumperformer_album_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_album_id_fkey FOREIGN KEY (album_id) REFERENCES public.album(album_id) ON DELETE CASCADE;


--
-- TOC entry 4703 (class 2606 OID 16735)
-- Name: albumperformer albumperformer_performer_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_performer_id_fkey FOREIGN KEY (performer_id) REFERENCES public.performer(performer_id) ON DELETE CASCADE;


--
-- TOC entry 4705 (class 2606 OID 16771)
-- Name: collectiontrack collectiontrack_collection_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_collection_id_fkey FOREIGN KEY (collection_id) REFERENCES public.collection(collection_id) ON DELETE CASCADE;


--
-- TOC entry 4706 (class 2606 OID 16766)
-- Name: collectiontrack collectiontrack_track_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_track_id_fkey FOREIGN KEY (track_id) REFERENCES public.track(track_id) ON DELETE CASCADE;


--
-- TOC entry 4700 (class 2606 OID 16706)
-- Name: genreperformer genreperformer_genre_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_genre_id_fkey FOREIGN KEY (genre_id) REFERENCES public.genre(genre_id) ON DELETE CASCADE;


--
-- TOC entry 4701 (class 2606 OID 16711)
-- Name: genreperformer genreperformer_performer_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_performer_id_fkey FOREIGN KEY (performer_id) REFERENCES public.performer(performer_id) ON DELETE CASCADE;


--
-- TOC entry 4704 (class 2606 OID 16747)
-- Name: track track_album_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track
    ADD CONSTRAINT track_album_id_fkey FOREIGN KEY (album_id) REFERENCES public.album(album_id) ON DELETE CASCADE;


-- Completed on 2025-09-29 00:02:22

--
-- PostgreSQL database dump complete
--

\unrestrict rlJHb5XGeRBzaf6w2omwdU7BwYAIEP0G5s9zF4OYP92c9Xpvx3srhAGCRYdxCXb

--
-- Database "postgres" dump
--

\connect postgres

--
-- PostgreSQL database dump
--

\restrict kyna9fnsOX1wlAlLQTbZCNMjzlrCllihFS0RYg8gLEvoE1KcV1CHC4Nc2wm9kHU

-- Dumped from database version 17.6
-- Dumped by pg_dump version 17.6

-- Started on 2025-09-29 00:02:22

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 224 (class 1259 OID 16534)
-- Name: album; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.album (
    album_id integer NOT NULL,
    name character varying(255) NOT NULL,
    yearofrelease date NOT NULL
);


ALTER TABLE public.album OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 16533)
-- Name: album_album_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.album_album_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.album_album_id_seq OWNER TO postgres;

--
-- TOC entry 4873 (class 0 OID 0)
-- Dependencies: 223
-- Name: album_album_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.album_album_id_seq OWNED BY public.album.album_id;


--
-- TOC entry 226 (class 1259 OID 16541)
-- Name: albumperformer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.albumperformer (
    id integer NOT NULL,
    album_id integer NOT NULL,
    performer_id integer NOT NULL
);


ALTER TABLE public.albumperformer OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 16540)
-- Name: albumperformer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.albumperformer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.albumperformer_id_seq OWNER TO postgres;

--
-- TOC entry 4874 (class 0 OID 0)
-- Dependencies: 225
-- Name: albumperformer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.albumperformer_id_seq OWNED BY public.albumperformer.id;


--
-- TOC entry 230 (class 1259 OID 16570)
-- Name: collection; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.collection (
    collection_id integer NOT NULL,
    name character varying(255) NOT NULL,
    yearofrelease date NOT NULL
);


ALTER TABLE public.collection OWNER TO postgres;

--
-- TOC entry 229 (class 1259 OID 16569)
-- Name: collection_collection_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.collection_collection_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.collection_collection_id_seq OWNER TO postgres;

--
-- TOC entry 4875 (class 0 OID 0)
-- Dependencies: 229
-- Name: collection_collection_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.collection_collection_id_seq OWNED BY public.collection.collection_id;


--
-- TOC entry 232 (class 1259 OID 16577)
-- Name: collectiontrack; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.collectiontrack (
    id integer NOT NULL,
    track_id integer NOT NULL,
    collection_id integer NOT NULL
);


ALTER TABLE public.collectiontrack OWNER TO postgres;

--
-- TOC entry 231 (class 1259 OID 16576)
-- Name: collectiontrack_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.collectiontrack_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.collectiontrack_id_seq OWNER TO postgres;

--
-- TOC entry 4876 (class 0 OID 0)
-- Dependencies: 231
-- Name: collectiontrack_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.collectiontrack_id_seq OWNED BY public.collectiontrack.id;


--
-- TOC entry 218 (class 1259 OID 16503)
-- Name: genre; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genre (
    genre_id integer NOT NULL,
    name character varying(255) NOT NULL
);


ALTER TABLE public.genre OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 16502)
-- Name: genre_genre_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.genre_genre_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.genre_genre_id_seq OWNER TO postgres;

--
-- TOC entry 4877 (class 0 OID 0)
-- Dependencies: 217
-- Name: genre_genre_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.genre_genre_id_seq OWNED BY public.genre.genre_id;


--
-- TOC entry 222 (class 1259 OID 16517)
-- Name: genreperformer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.genreperformer (
    id integer NOT NULL,
    genre_id integer NOT NULL,
    performer_id integer NOT NULL
);


ALTER TABLE public.genreperformer OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16516)
-- Name: genreperformer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.genreperformer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.genreperformer_id_seq OWNER TO postgres;

--
-- TOC entry 4878 (class 0 OID 0)
-- Dependencies: 221
-- Name: genreperformer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.genreperformer_id_seq OWNED BY public.genreperformer.id;


--
-- TOC entry 220 (class 1259 OID 16510)
-- Name: performer; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.performer (
    performer_id integer NOT NULL,
    name character varying(255) NOT NULL
);


ALTER TABLE public.performer OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 16509)
-- Name: performer_performer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.performer_performer_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.performer_performer_id_seq OWNER TO postgres;

--
-- TOC entry 4879 (class 0 OID 0)
-- Dependencies: 219
-- Name: performer_performer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.performer_performer_id_seq OWNED BY public.performer.performer_id;


--
-- TOC entry 228 (class 1259 OID 16558)
-- Name: track; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.track (
    track_id integer NOT NULL,
    name character varying(255) NOT NULL,
    duration integer NOT NULL,
    album_id integer NOT NULL
);


ALTER TABLE public.track OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 16557)
-- Name: track_track_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.track_track_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.track_track_id_seq OWNER TO postgres;

--
-- TOC entry 4880 (class 0 OID 0)
-- Dependencies: 227
-- Name: track_track_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.track_track_id_seq OWNED BY public.track.track_id;


--
-- TOC entry 4679 (class 2604 OID 16537)
-- Name: album album_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album ALTER COLUMN album_id SET DEFAULT nextval('public.album_album_id_seq'::regclass);


--
-- TOC entry 4680 (class 2604 OID 16544)
-- Name: albumperformer id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer ALTER COLUMN id SET DEFAULT nextval('public.albumperformer_id_seq'::regclass);


--
-- TOC entry 4682 (class 2604 OID 16573)
-- Name: collection collection_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collection ALTER COLUMN collection_id SET DEFAULT nextval('public.collection_collection_id_seq'::regclass);


--
-- TOC entry 4683 (class 2604 OID 16580)
-- Name: collectiontrack id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack ALTER COLUMN id SET DEFAULT nextval('public.collectiontrack_id_seq'::regclass);


--
-- TOC entry 4676 (class 2604 OID 16506)
-- Name: genre genre_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genre ALTER COLUMN genre_id SET DEFAULT nextval('public.genre_genre_id_seq'::regclass);


--
-- TOC entry 4678 (class 2604 OID 16520)
-- Name: genreperformer id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer ALTER COLUMN id SET DEFAULT nextval('public.genreperformer_id_seq'::regclass);


--
-- TOC entry 4677 (class 2604 OID 16513)
-- Name: performer performer_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.performer ALTER COLUMN performer_id SET DEFAULT nextval('public.performer_performer_id_seq'::regclass);


--
-- TOC entry 4681 (class 2604 OID 16561)
-- Name: track track_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track ALTER COLUMN track_id SET DEFAULT nextval('public.track_track_id_seq'::regclass);


--
-- TOC entry 4859 (class 0 OID 16534)
-- Dependencies: 224
-- Data for Name: album; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.album (album_id, name, yearofrelease) FROM stdin;
\.


--
-- TOC entry 4861 (class 0 OID 16541)
-- Dependencies: 226
-- Data for Name: albumperformer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.albumperformer (id, album_id, performer_id) FROM stdin;
\.


--
-- TOC entry 4865 (class 0 OID 16570)
-- Dependencies: 230
-- Data for Name: collection; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.collection (collection_id, name, yearofrelease) FROM stdin;
\.


--
-- TOC entry 4867 (class 0 OID 16577)
-- Dependencies: 232
-- Data for Name: collectiontrack; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.collectiontrack (id, track_id, collection_id) FROM stdin;
\.


--
-- TOC entry 4853 (class 0 OID 16503)
-- Dependencies: 218
-- Data for Name: genre; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genre (genre_id, name) FROM stdin;
\.


--
-- TOC entry 4857 (class 0 OID 16517)
-- Dependencies: 222
-- Data for Name: genreperformer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.genreperformer (id, genre_id, performer_id) FROM stdin;
\.


--
-- TOC entry 4855 (class 0 OID 16510)
-- Dependencies: 220
-- Data for Name: performer; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.performer (performer_id, name) FROM stdin;
\.


--
-- TOC entry 4863 (class 0 OID 16558)
-- Dependencies: 228
-- Data for Name: track; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.track (track_id, name, duration, album_id) FROM stdin;
\.


--
-- TOC entry 4881 (class 0 OID 0)
-- Dependencies: 223
-- Name: album_album_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.album_album_id_seq', 1, false);


--
-- TOC entry 4882 (class 0 OID 0)
-- Dependencies: 225
-- Name: albumperformer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.albumperformer_id_seq', 1, false);


--
-- TOC entry 4883 (class 0 OID 0)
-- Dependencies: 229
-- Name: collection_collection_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.collection_collection_id_seq', 1, false);


--
-- TOC entry 4884 (class 0 OID 0)
-- Dependencies: 231
-- Name: collectiontrack_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.collectiontrack_id_seq', 1, false);


--
-- TOC entry 4885 (class 0 OID 0)
-- Dependencies: 217
-- Name: genre_genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.genre_genre_id_seq', 1, false);


--
-- TOC entry 4886 (class 0 OID 0)
-- Dependencies: 221
-- Name: genreperformer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.genreperformer_id_seq', 1, false);


--
-- TOC entry 4887 (class 0 OID 0)
-- Dependencies: 219
-- Name: performer_performer_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.performer_performer_id_seq', 1, false);


--
-- TOC entry 4888 (class 0 OID 0)
-- Dependencies: 227
-- Name: track_track_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.track_track_id_seq', 1, false);


--
-- TOC entry 4691 (class 2606 OID 16539)
-- Name: album album_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.album
    ADD CONSTRAINT album_pkey PRIMARY KEY (album_id);


--
-- TOC entry 4693 (class 2606 OID 16546)
-- Name: albumperformer albumperformer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_pkey PRIMARY KEY (id);


--
-- TOC entry 4697 (class 2606 OID 16575)
-- Name: collection collection_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collection
    ADD CONSTRAINT collection_pkey PRIMARY KEY (collection_id);


--
-- TOC entry 4699 (class 2606 OID 16582)
-- Name: collectiontrack collectiontrack_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_pkey PRIMARY KEY (id);


--
-- TOC entry 4685 (class 2606 OID 16508)
-- Name: genre genre_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genre
    ADD CONSTRAINT genre_pkey PRIMARY KEY (genre_id);


--
-- TOC entry 4689 (class 2606 OID 16522)
-- Name: genreperformer genreperformer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_pkey PRIMARY KEY (id);


--
-- TOC entry 4687 (class 2606 OID 16515)
-- Name: performer performer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.performer
    ADD CONSTRAINT performer_pkey PRIMARY KEY (performer_id);


--
-- TOC entry 4695 (class 2606 OID 16563)
-- Name: track track_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track
    ADD CONSTRAINT track_pkey PRIMARY KEY (track_id);


--
-- TOC entry 4702 (class 2606 OID 16547)
-- Name: albumperformer albumperformer_album_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_album_id_fkey FOREIGN KEY (album_id) REFERENCES public.album(album_id);


--
-- TOC entry 4703 (class 2606 OID 16552)
-- Name: albumperformer albumperformer_performer_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.albumperformer
    ADD CONSTRAINT albumperformer_performer_id_fkey FOREIGN KEY (performer_id) REFERENCES public.performer(performer_id);


--
-- TOC entry 4705 (class 2606 OID 16588)
-- Name: collectiontrack collectiontrack_collection_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_collection_id_fkey FOREIGN KEY (collection_id) REFERENCES public.collection(collection_id);


--
-- TOC entry 4706 (class 2606 OID 16583)
-- Name: collectiontrack collectiontrack_track_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.collectiontrack
    ADD CONSTRAINT collectiontrack_track_id_fkey FOREIGN KEY (track_id) REFERENCES public.track(track_id);


--
-- TOC entry 4700 (class 2606 OID 16523)
-- Name: genreperformer genreperformer_genre_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_genre_id_fkey FOREIGN KEY (genre_id) REFERENCES public.genre(genre_id);


--
-- TOC entry 4701 (class 2606 OID 16528)
-- Name: genreperformer genreperformer_performer_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.genreperformer
    ADD CONSTRAINT genreperformer_performer_id_fkey FOREIGN KEY (performer_id) REFERENCES public.performer(performer_id);


--
-- TOC entry 4704 (class 2606 OID 16564)
-- Name: track track_album_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.track
    ADD CONSTRAINT track_album_id_fkey FOREIGN KEY (album_id) REFERENCES public.album(album_id);


-- Completed on 2025-09-29 00:02:22

--
-- PostgreSQL database dump complete
--

\unrestrict kyna9fnsOX1wlAlLQTbZCNMjzlrCllihFS0RYg8gLEvoE1KcV1CHC4Nc2wm9kHU

-- Completed on 2025-09-29 00:02:22

--
-- PostgreSQL database cluster dump complete
--

