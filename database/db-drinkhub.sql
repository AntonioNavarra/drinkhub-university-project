PGDMP  5                     |            DrinkHub    16.1    16.1     �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false                        0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false                       0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false                       1262    16439    DrinkHub    DATABASE     }   CREATE DATABASE "DrinkHub" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Italian_Italy.1252';
    DROP DATABASE "DrinkHub";
                postgres    false            �            1259    16440    sequence_carrello    SEQUENCE     z   CREATE SEQUENCE public.sequence_carrello
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 (   DROP SEQUENCE public.sequence_carrello;
       public          postgres    false            �            1259    16441    carrello    TABLE     �   CREATE TABLE public.carrello (
    idcarrello character varying(100) DEFAULT nextval('public.sequence_carrello'::regclass) NOT NULL,
    nomeprodotto2 character varying(100) NOT NULL,
    username2 character varying(100) NOT NULL
);
    DROP TABLE public.carrello;
       public         heap    postgres    false    215            �            1259    16445    sequence_prodotto    SEQUENCE     z   CREATE SEQUENCE public.sequence_prodotto
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 (   DROP SEQUENCE public.sequence_prodotto;
       public          postgres    false            �            1259    16446    prodotto    TABLE     ?  CREATE TABLE public.prodotto (
    idprodotto character varying(100) DEFAULT nextval('public.sequence_prodotto'::regclass) NOT NULL,
    nomeprodotto character varying(100) NOT NULL,
    prezzo double precision NOT NULL,
    descrizione character varying(255) NOT NULL,
    categoria character varying(100) NOT NULL
);
    DROP TABLE public.prodotto;
       public         heap    postgres    false    217            �            1259    16452    sequence_utenti    SEQUENCE     x   CREATE SEQUENCE public.sequence_utenti
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 &   DROP SEQUENCE public.sequence_utenti;
       public          postgres    false            �            1259    16453    utente    TABLE     7  CREATE TABLE public.utente (
    idutente character varying(100) DEFAULT nextval('public.sequence_utenti'::regclass) NOT NULL,
    password character varying(255) NOT NULL,
    username character varying(255) NOT NULL,
    logged boolean DEFAULT false NOT NULL,
    categoriapreferita character varying(255)
);
    DROP TABLE public.utente;
       public         heap    postgres    false    219            �          0    16441    carrello 
   TABLE DATA           H   COPY public.carrello (idcarrello, nomeprodotto2, username2) FROM stdin;
    public          postgres    false    216   	       �          0    16446    prodotto 
   TABLE DATA           \   COPY public.prodotto (idprodotto, nomeprodotto, prezzo, descrizione, categoria) FROM stdin;
    public          postgres    false    218   &       �          0    16453    utente 
   TABLE DATA           Z   COPY public.utente (idutente, password, username, logged, categoriapreferita) FROM stdin;
    public          postgres    false    220                     0    0    sequence_carrello    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.sequence_carrello', 1, true);
          public          postgres    false    215                       0    0    sequence_prodotto    SEQUENCE SET     @   SELECT pg_catalog.setval('public.sequence_prodotto', 58, true);
          public          postgres    false    217                       0    0    sequence_utenti    SEQUENCE SET     =   SELECT pg_catalog.setval('public.sequence_utenti', 1, true);
          public          postgres    false    219            _           2606    16461    carrello carrello_pkey 
   CONSTRAINT     \   ALTER TABLE ONLY public.carrello
    ADD CONSTRAINT carrello_pkey PRIMARY KEY (idcarrello);
 @   ALTER TABLE ONLY public.carrello DROP CONSTRAINT carrello_pkey;
       public            postgres    false    216            a           2606    16463    prodotto prodotti_pkey 
   CONSTRAINT     \   ALTER TABLE ONLY public.prodotto
    ADD CONSTRAINT prodotti_pkey PRIMARY KEY (idprodotto);
 @   ALTER TABLE ONLY public.prodotto DROP CONSTRAINT prodotti_pkey;
       public            postgres    false    218            c           2606    16465    utente unique_nome_utente 
   CONSTRAINT     X   ALTER TABLE ONLY public.utente
    ADD CONSTRAINT unique_nome_utente UNIQUE (username);
 C   ALTER TABLE ONLY public.utente DROP CONSTRAINT unique_nome_utente;
       public            postgres    false    220            e           2606    16467    utente utenti_pkey 
   CONSTRAINT     V   ALTER TABLE ONLY public.utente
    ADD CONSTRAINT utenti_pkey PRIMARY KEY (idutente);
 <   ALTER TABLE ONLY public.utente DROP CONSTRAINT utenti_pkey;
       public            postgres    false    220            f           2606    16468    carrello FK_menuprodotto    FK CONSTRAINT     �   ALTER TABLE ONLY public.carrello
    ADD CONSTRAINT "FK_menuprodotto" FOREIGN KEY (nomeprodotto2) REFERENCES public.prodotto(idprodotto) NOT VALID;
 D   ALTER TABLE ONLY public.carrello DROP CONSTRAINT "FK_menuprodotto";
       public          postgres    false    218    216    4705            g           2606    16473    carrello FK_utente    FK CONSTRAINT     �   ALTER TABLE ONLY public.carrello
    ADD CONSTRAINT "FK_utente" FOREIGN KEY (username2) REFERENCES public.utente(idutente) NOT VALID;
 >   ALTER TABLE ONLY public.carrello DROP CONSTRAINT "FK_utente";
       public          postgres    false    220    4709    216            �      x������ � �      �   �  x��W�n#7<S_��e�G[_b%F�� A.=3��1��%9�H_�k�9����HKp��rYx!������=g_�lQ���f7Www�g|/�E�2�s���<�`-溽0�V����K,Ř�<�	���Vp�z-�f�F��,�J
�h�%u�r��xV�9���$��

���)�%�-/���w�tBy�~�e��M��l]Ԗ�gb�g*����6��	���gTq�Q�ڇFL
,1�(�Ʉ� �F+d�����zInc����L���v;n���l�ٓ�!8��p1��#��ӎ�o2�J*�]_P��D�bwΣ���w�>ɪ.���Җ��w)��t�~�!�铞�+cH�	��?HJ��6�����Q+�W�·��[*����TP}z�za?ȋl����O�̖����\u�<C���%D�g�����QVA���,�j]��g|��JK(��z�OB������i"E�� ��jAq ��J���
�]�M'�}�_kmBR ��gu�+o_��7�6���bХ�?���~ɴJ_��w��^���(�v矞"j�AnuԖZ'�-�Z�\��^�e��A�b���"(���+y�}h2A���B�[�hj)���B�w&�~ʍ(}a?d�$�
�yUKR\���h�L�l��T�y�"��_�Ij����Ɲ��K��^��A1�`���G��l�DUD1�N)��E�B�J��Q�+{�7^���$���><��
u>���y�A�������
-�8h���T׻�K#�����J��=$��t샂N�	�W�T���z�]�DEGwbp��z�~WO���8�����M8Tp8�=�X��CO��TcN/ט��7���h���sv�Ɯ]�1g�k��Esv�Ƥ���"L�?�f+���e�4@q��3�0�������0���P|�ä��m�~�ׅl���4k<���P������Ž��|��
�I)i����Gj�p>�qڥ�kAƧh��B�Y9�u��7ANEǟk���,̎����1���Ƨ��8KK�F(L�7����6�2h�Fc�K�a�j�X2U8G��8�v��́|���q�кx����2�Rkڨ���=	_�B�G<��T�-�NG�7kA3���:�[��i>��&�&�Z/R�~?T��%Ҭ.����f�P��A֢A]�r���q�SP؍4���PJ��(b�߮F��?s�PM      �      x������ � �     