/******************************************************************************

Készítsen programot amely alkalmas BCD kód formájában tárolt egész
számokkal való alapm¶veletek elvégzésére
M¶veletek:
Összeadás
Kivonás
Szorzás
Osztás
Feltételek
A feladat során maximum 32 bites aritmetikát alkalmazhat
A m¶veletek megvalósításához csak összeadás, kivonás, negálás, eltolás
és logikai muveleteket használhat.
A file-ból karakterenként kell beolvasni az adatokat és string m¶veletek
nem használhatók
Nem lehet semmilyen hiba a m¶velet elvégzése közben.
A megoldásnak tartalmaznia kell a program megfelel® dokumentációját.
Az els® 15 helyes megoldást tudjuk csak értékelni.

A bemeneti adatsor egy szöveges file-ban található (input.txt)
1002
-
502
A program irja ki egy TXT file-ba (output.txt) a m¶velet eredményét.
1002 (0x3EA)
-
502 (0x1F6)
=
500 (0x1F4)
Mellékeljen műveletenként 1-2 darab bemeneti minta file-t.
Dr. Fodor Attila, Dr. Görbe Péter (Pannon Egyetem)A számítástechnika alapjai
2022. 3 / 3

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
struct MyResult {
  int *res_arr;
  int res_arr_size;
};

struct MyResult sum(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  int *res_arr;
  int res_arr_size = (arr1_size > arr2_size) ? arr1_size : arr2_size;
  res_arr = calloc(res_arr_size, sizeof(int));
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int res_arr_i = res_arr_size - 1;
  int leftover = 0;
  int current_sum = 0;
  // printf("res arr lenght: %d\n",res_arr_size);
  /*
    while (res_arr_i >= 0) {
      if (arr1_i > arr2_i) {
        res_arr[res_arr_i] = arr1[res_arr_i];
        arr1_i--;
        printf("%d+_=%d\n", arr1[res_arr_i], res_arr[res_arr_i]);
      } else if (arr2_i > arr1_i) {
        res_arr[res_arr_i] = arr2[res_arr_i];
        arr2_i--;
        printf("_+%d=%d\n", arr2[res_arr_i], res_arr[res_arr_i]);
      } else {
        current_sum = arr1[res_arr_i] + arr2[res_arr_i];
        if (current_sum >= 10) {
          leftover = 1;
          current_sum = current_sum - 10;
        }
        res_arr[res_arr_i] = current_sum;
        printf("%d+%d=%d\n", arr1[res_arr_i], arr2[res_arr_i],
               res_arr[res_arr_i]);
      }
      res_arr_i = res_arr_i - 1;
    }
    */
  struct MyResult res;
  res.res_arr = res_arr;
  res.res_arr_size = res_arr_size;
  return res;
}

int main() {
  int *arr1;
  int *arr2;
  char c;
  int i;
  char operator;
  unsigned int arr1_size = 0;
  unsigned int arr2_size = 0;
  arr1 = calloc(arr1_size, sizeof(int));
  arr2 = calloc(arr2_size, sizeof(int));
  FILE *ifp = fopen("input.txt", "r");
  if (arr1 == NULL) {
    fprintf(stderr, "Array 1 not allocated");
  }
  if (arr2 == NULL) {
    fprintf(stderr, "Array 2 not allocated");
  }
  scanf("%c", &c);
  while ((int)(c)-48 >= 0) {
    arr1_size++;
    arr1 = realloc(arr1, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
    arr1[arr1_size - 1] = (int)(c)-48;
    scanf("%c", &c);
  }
  for (i = 0; i < arr1_size; i++) {
    printf("%d", arr1[i]);
  }
  scanf("%c", &operator);
  printf("\n%c\n", operator);

  scanf("%c", &c);
  scanf("%c", &c);

  while ((int)(c)-48 >= 0) {
    arr2_size++;
    arr2 = realloc(arr2, arr2_size * sizeof(int));
    if (arr2 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
    arr2[arr2_size - 1] = (int)(c)-48;
    scanf("%c", &c);
  }
  for (i = 0; i < arr2_size; i++) {
    printf("%d", arr2[i]);
  }
  printf("\n=\n");
  struct MyResult res = sum(arr1, arr2, arr1_size, arr2_size);
  printf("my res_lenght:%d", res.res_arr_size);
  /*
  for(i=0;i<res_arr_size;i++){
      printf("%d",res_arr[i]);
  }
  */

  free(arr1);
  free(arr2);

  return 0;
}