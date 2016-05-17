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
 * rozbicie programu na kilka plikow (main.c functions.h functions.c)
 * DONE nowa funkcje zajmujace sie komunikatami
 * DONE getopt
 * DONE funkcja help - napisac co uzytkownik ma robic z programem
 * jak na razie brak nowych pomyslow :) */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
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


/* sprawdzenie, czy pamiec zostala poprawnie zaalokowana */
void sprawdz_bledy (int *p)
   {
   if (p == NULL)
      {
      perror ("malloc");
      exit (EXIT_FAILURE);
      }
   }


/* okreslenie rozmiaru szachownicy (wierszy i przekatnych) */
void okresl_rozmiar ()
   {
   wiersze = malloc (ile_wierszy * sizeof wiersze);
      sprawdz_bledy (wiersze);
   lprzek  = malloc (ile_przekatnych * sizeof wiersze);
      sprawdz_bledy (lprzek);
   rprzek  = malloc (ile_przekatnych * sizeof wiersze);
      sprawdz_bledy (rprzek);
   }


/* czyszczenie informacji o zajetych polach (potrzebne do liczenia rozwiazan) */
void czysc_pola ()
   {
   int i;
   for (i=0; i<ile_wierszy; i++)
      wiersze[i] = -1;
   for (i=0; i<ile_przekatnych; i++)
      {
      lprzek[i]  = -1;
      rprzek[i]  = -1;
      }
   }


/* tworzenie pliku wyjsciowego lub czyszczenie go, jesli juz istnieje */
void czysc_plik ()
   {
   FILE *wymazywanie = fopen (plik, "w");
   fclose (wymazywanie);
   }


/* rysowanie szachownicy o wymiarach nxn */
void rysuj_szachownice ()
   {
   int i, j;
   FILE *wyjsc = fopen (plik, "a");

   printf("\nRozwiazanie nr %d:\n", nr);
   fprintf(wyjsc, "\nRozwiazanie nr %d:\n", nr);
   nr++;
   for (i=0; i<ile_wierszy; i++)    /* pisanie n wierszy */
      {
      for (j=0; j<ile_wierszy; j++) /* pisanie n kolumn  */
         if (wiersze[i]==j)         /* jesli w danym wierszu i kolumnie stoi hetman */
            {
            printf("X ");           /* to pisanie X */
            fprintf(wyjsc, "X ");
            }
         else                       /* jesli w danym wierszu i kolumnie nie ma hetmana */
            {
            printf(". ");
            fprintf(wyjsc, ". ");   /* to pisanie . */
            }
      printf("\n");
      fprintf(wyjsc, "\n");
      }
   fclose (wyjsc);
   }


/* licz_rozwiazania (int w, int k) - umieszczenie hetmana w wierszu w i kolumnie k
 * jesli hetmana tam jeszcze nie ma, to w odpowiednich miejscach
 * wszystkich 3 tablic bedzie wpisana wartosc -1.
 * odwolywanie sie do tych trzech tablic:
 * do tablicy 'wiersze' - przez numer wiersza
 * do tablicy 'lprzek'  - przez sumê numeru wiersza i kolumny (indeksowanie od lewego górnego rogu)
 * do tablicy 'rprzek'  - przez sumê numeru wiersza i kolumny (indeksowanie od prawego górnego rogu) */
void licz_rozwiazania (int w, int k)
   {
   int i;
   if ((wiersze[w]<0) && (lprzek[w+k]<0) && (rprzek[w+(ile_wierszy-1)-k]<0))
      {
      wiersze[w]  = k;              /* zapamietanie w wierszu informacji w ktorej kolumnie stoi hetman */
      lprzek[w+k] = 1;              /* a takze zajecie przekatnych */
      rprzek[w+(ile_wierszy-1)-k] = 1;
      if (k==(ile_wierszy-1))       /* jesli jest to ostatnia kolumna to pokazanie wynikow obliczen */
         rysuj_szachownice ();
      for (i=0; i<ile_wierszy; i++) /* umieszczenie hetmana w kolumnie k+1 w n mozliwych wierszach */
         {
         licz_rozwiazania(i, k+1);
         if (nr==max_rozwiazan+1)
            break;
         }
      wiersze[w]  = -1;             /* zwolnienie wiersza w */
      lprzek[w+k] = -1;             /* oraz przekatnych      */
      rprzek[w+(ile_wierszy-1)-k] = -1;
      }
   }


/* wypisanie pomocy */
void wypisz_help ()
   {
   printf ("\nUruchamianie programu z nastepujacymi argumentami:"
           "\n  -n  ilosc wierszy i kolumn szachownicy (np. -n 7)"
           "\n  -r  maksylana ilosc wypisanych rozwiazan (np. -r 35)"
           "\n  -o  nazwa pliku, do ktorego zostana zapisane rozwiazania (np. -o plik2.txt)"
           "\n  -h  wyswietlenie pomocy\n"
           "\nBrak argumentow powoduje uruchomienie programu z parametrami domyslnymi:"
           "\n  rozmiar szachownicy: 8x8"
           "\n  maksymalna ilosc wypisanych rozwiazan: 92"
           "\n  nazwa pliku: hetmani.txt\n\n");
   }


/* wypisanie informacji o parametrach wejsciowych*/
void wypisz_info ()
   {
   FILE *info = fopen (plik, "a");
   printf ("\nProblem rozstawienia hetmanow na szachownicy\nw taki sposob, aby sie nawzajem nie atakowaly.\n\n"
           "Rozmiar szachownicy:\t\t%dx%d\nMax wypisanych rozwiazan:\t%d\nRozwiazania zapisane w:\t\t%s\n\n",
                   ile_wierszy, ile_wierszy, max_rozwiazan, plik);
   fprintf(info, "\nProblem rozstawienia hetmanow na szachownicy\nw taki sposob, aby sie nawzajem nie atakowaly.\n\n"
           "Rozmiar szachownicy:\t\t%dx%d\nMax wypisanych rozwiazan:\t%d\nRozwiazania zapisane w:\t\t%s\n\n",
                   ile_wierszy, ile_wierszy, max_rozwiazan, plik);
   fclose (info);
   }


/* wypisanie komunikatu o braku rozwiazan */
void wypisz_komunikat ()
   {
   if (ile_wierszy==2 || ile_wierszy==3)
      printf ("\nBrak rozwiazan dla n = %d\n", ile_wierszy);
   }


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
