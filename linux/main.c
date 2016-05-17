/* Problem n hetmanow: nalezy na szachownicy nxn rozstawic n hetmanów tak, aby sie nawzajem nie atakowaly */

/* Poprawki, pomysly:
 * DONE wypisywanie wynikow do pliku zewnetrznego (oprocz w konsoli)
 * DONE czyszczenie pliku hetmani.txt jesli juz istnieje
 * rozmiar tablicy i ilosc wypisanych rozwiazan w nazwie pliku
 * DONE nie zapomniec o naglowku (malym info) takze w pliku tekstowym
 * DONE wprowadzanie przez konsole ilosci wierszy oraz kolumn
 * DONE w takim razie alokacja tablic mallokiem
 * DONE okreslenie maksymalnej liczby wypisywanych rozwiazan i stosowny komunikat w konsoli
 * DONE stosowny komunikat rowniez w pliku zewnetrznym
 * DONE komunikat, ze dla n = 2 lub n = 3 nie ma rozwiazan
 * DONE rozbicie programu na kilka plikow (main.c functions.h functions.c)
 * DONE nowa funkcje zajmujace sie komunikatami
 * DONE getopt
 * funkcje sprawdzajace bledne dane wprowadzone przez uzytkownika
 * DONE funkcja help - napisac co uzytkownik ma robic z programem
 * jak na razie brak nowych pomyslow :) */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "count.h"
#include "functions.h"
#define ile_przekatnych ((2*ile_wierszy)-1)

/* wiersze - tablica n wierszy szachownicy
 * lprzek  - tablica lewoskosnych przekatnych szachownicy
 * rprzek  - tablica prawoskosnych przekatnych szachownicy
 * lewoskosne przekatne beda indeksowane od lewego gornego rogu szachownicy
 * prawoskosne przekatne beda indeksowane od prawego gornego rogu szachownicy */
int *wiersze;
int *lprzek;
int *rprzek;
int nr = 1;
int ile_wierszy;
int max_rozwiazan;
char *plik = "hetmani.txt";


int main (int argc, char **argv)
   {
   char *wymiar = "8";
   char *rozwiazania = "92";
   int d, l, help=0;

   /* funkcja getopt */
   while ((d = getopt (argc, argv, "n:r:o:h")) != -1)
      switch (d)
         {
         case 'n':
            wymiar = optarg;
            break;
         case 'r':
            rozwiazania = optarg;
            break;
         case 'o':
            plik = optarg;
            break;
         case 'h':
            help = 1;
            break;
         }

   if (help==1)
      wypisz_help();
   else
      {
      ile_wierszy = atoi(wymiar);
      max_rozwiazan = atoi(rozwiazania);
      okresl_rozmiar();
      czysc_pola();
      czysc_plik();
      wypisz_info();
      for (l=0; l<ile_wierszy; l++)    /* umieszczenie hetmana w kolumnie 0 w n mozliwych wierszach */
         licz_rozwiazania(l, 0);       /* wypisanie mozliwych ukladow w konsoli oraz do pliku */
      wypisz_komunikat();
      }

   return EXIT_SUCCESS;
   }
