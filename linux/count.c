#include <stdio.h>
#include <stdlib.h>
#include "count.h"

int *wiersze;
int *lprzek;
int *rprzek;
int nr;
int ile_wierszy;
int max_rozwiazan;
char *plik;


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
