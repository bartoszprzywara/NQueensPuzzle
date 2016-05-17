#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define ile_przekatnych ((2*ile_wierszy)-1)

int *wiersze;
int *lprzek;
int *rprzek;
int ile_wierszy;
int max_rozwiazan;
char *plik;


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
