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
// result array and its lenght as a struct
struct MyResult {
  int *res_arr;
  int res_arr_size;
  int is_negative; // boolean
};

struct MyResult sum(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  // init
  int *res_arr;
  int res_arr_size = (arr1_size > arr2_size) ? arr1_size : arr2_size;
  res_arr = calloc(res_arr_size, sizeof(int));
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int res_arr_i = res_arr_size - 1;
  int leftover = 0;
  int current_sum = 0;
  int *tmp_arr = calloc(res_arr_size, sizeof(int));
  int i;
  struct MyResult res;

  // left padding the shorter input array with 0's
  if (arr1_size < res_arr_size) {
    for (i = 0; i <= arr1_i; i++) {
      tmp_arr[res_arr_i - i] = arr1[arr1_i - i];
    }

    arr1_size = res_arr_size;
    arr1 = realloc(tmp_arr, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  } else if (arr2_size < res_arr_size) {
    for (i = 0; i <= arr2_i; i++) {
      tmp_arr[res_arr_i - i] = arr2[arr2_i - i];
    }

    arr2_size = res_arr_size;
    arr2 = realloc(tmp_arr, arr2_size * sizeof(int));
    if (arr2 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  }

  // add the two arrays like you would on paper
  while (res_arr_i >= 0) {
    current_sum = arr1[res_arr_i] + arr2[res_arr_i] + leftover;
    if (current_sum >= 10) {
      leftover = 1;
      current_sum = current_sum - 10;
    } else {
      leftover = 0;
    }
    res_arr[res_arr_i] = current_sum;
    // printf("%d+%d=%d\n", arr1[res_arr_i], arr2[res_arr_i],
    // res_arr[res_arr_i]);
    res_arr_i = res_arr_i - 1;
  }
  // return result array and its lenght as a struct
  res.res_arr = res_arr;
  res.res_arr_size = res_arr_size;
  res.is_negative = 0;
  return res;
}
struct MyResult subtract(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  // init
  int *res_arr;
  int res_arr_size = (arr1_size > arr2_size) ? arr1_size : arr2_size;
  res_arr = calloc(res_arr_size, sizeof(int));
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int res_arr_i = res_arr_size - 1;
  int leftover = 0;
  int current_subt = 0;
  int *tmp_arr = calloc(res_arr_size, sizeof(int));
  int tmp;
  int i;
  struct MyResult res;
  int a, b;
  int which_bigger = 0; // 0=equal, 1=first, 2=second
  res.is_negative = 0;

  // left padding the shorter input array with 0's
  if (arr1_size < res_arr_size) {
    for (i = 0; i <= arr1_i; i++) {
      tmp_arr[res_arr_i - i] = arr1[arr1_i - i];
    }
    arr1 = realloc(tmp_arr, res_arr_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  } else if (arr2_size < res_arr_size) {
    for (i = 0; i <= arr2_i; i++) {
      tmp_arr[res_arr_i - i] = arr2[arr2_i - i];
    }
    arr2 = realloc(tmp_arr, res_arr_size * sizeof(int));
    if (arr2 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  }
  // if they are initially the same lenght find out if the second is bigger
  if (arr1_size == arr2_size) {
    for (i = 0; i < res_arr_size; i++) {
      if (which_bigger == 0) {
        if (arr1[i] > arr2[i])
          which_bigger = 1;
        else if (arr1[i] < arr2[i])
          which_bigger = 2;
      }
    }
  }
  // if the second number is bigger switch them and switch res.is_negative
  if (arr2_size > arr1_size || which_bigger == 2) {
    tmp_arr = arr1;
    arr1 = arr2;
    arr2 = tmp_arr;
    res.is_negative = 1;
  }

  // subtract the two arrays like you would on paper
  while (res_arr_i >= 0) {
    a = arr1[res_arr_i];
    b = arr2[res_arr_i] + leftover;
    if (a < b) {
      a = a + 10;
      leftover = 1;
    } else {
      leftover = 0;
    }
    current_subt = a - b;
    res_arr[res_arr_i] = current_subt;
    // printf("%d-%d=%d\n", arr1[res_arr_i], arr2[res_arr_i],
    // res_arr[res_arr_i]);
    res_arr_i = res_arr_i - 1;
  }
  // return result array and its lenght as a struct
  res.res_arr = res_arr;
  res.res_arr_size = res_arr_size;
  return res;
}

int **bekerMatrix(int sorok, int oszlopok) {
  int **matrix = (int **)malloc(sizeof(int *) * sorok);
  for (int i = 0; i < sorok; i++)
    matrix[i] = (int *)malloc(sizeof(int) * oszlopok);

  for (int i = 0; i < sorok; i++) {
    // printf("Kerem az %d. indexu sor elemeit", i);
    for (int j = 0; j < oszlopok; j++)
      matrix[i][j] = 0;
  }
  return matrix;
}
void felszabaditMatrix(int sorok, int oszlopok, int **matrix) {
  for (int i = 0; i < sorok; i++)
    free(matrix[i]);
  free(matrix);
}

struct MyResult multiply(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  // init
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int i, j;
  struct MyResult res;
  int leftover = 0;
  int current_mult;
  int sorok = arr2_size;
  int oszlopok = arr1_size + arr2_size;
  int **matrix;
  matrix = bekerMatrix(sorok, oszlopok);
  // creating matrix like you would on paper
  for (int i = 0; i < arr2_size; i++) {
    for (int j = 0; j < arr1_size + 1; j++) {
      current_mult = (arr2[arr2_i - i] * arr1[arr1_i - j]) + leftover;
      // because i cant use '%' operator i need to do it by hand
      leftover = (int)(current_mult / 10);
      matrix[sorok - 1 - i][oszlopok - 1 - j - i] =
          current_mult - (leftover * 10);
      /*
  printf("[%d][%d] = %d (%d*%d) left: %d\n", sorok - 1 - i,
         oszlopok - 1 - j, current_mult - (leftover * 10), arr2[arr2_i - i],
         arr1[arr1_i - j], leftover);
         */
    }
    leftover = 0;
  }
  int *matrix_summed = calloc(oszlopok, sizeof(int));
  for (int i = 0; i < sorok; i++) {
    matrix_summed = sum(matrix_summed, matrix[i], oszlopok, oszlopok).res_arr;
  }
  /*
    printf("Matrix:\n");
    for (int i = 0; i < sorok; i++) {
      for (int j = 0; j < oszlopok; j++)
        printf("%d", matrix[i][j]);
      printf("\n");
    }
  */
  felszabaditMatrix(sorok, oszlopok, matrix);
  res.res_arr = matrix_summed;
  res.res_arr_size = oszlopok;
  res.is_negative = 0;
  return res;
}
struct MyResult divide(int *arr1, int *arr2, int arr1_size, int arr2_size) {

  // return result array and its lenght as a struct
  struct MyResult res;
  int res_arr_size = 0;
  int *res_arr = calloc(res_arr_size, sizeof(int));
  int num1 = 0;
  int i;
  for (i = 0; i < arr1_size; i++)
    num1 = 10 * num1 + arr1[i];

  int arr_2_i = 0;
  int num2 = arr2[0];
  int is_done = 0;
  while (is_done == 0) {
    if (num2 / num1 >= 1) {
      res_arr_size++;
      res_arr = realloc(res_arr, res_arr_size * sizeof(int));
      if (res_arr == NULL) {
        fprintf(stderr, "Array not reallocated");
      }
      res_arr[i] = (int)(c)-48;
    } else {
      num2 = (num2 * 10) +
    }
  }

  res.res_arr = arr1;
  res.res_arr_size = arr1_size;
  res.is_negative = 0;
  return res;
}

int main() {
  // init
  int *arr1; // first input number
  int *arr2; // second input number
  char c;
  int i;
  char operator;
  unsigned int arr1_size = 0;
  unsigned int arr2_size = 0;
  arr1 = calloc(arr1_size, sizeof(int));
  arr2 = calloc(arr2_size, sizeof(int));
  struct MyResult result;
  int is_leading_0s_ended = 0;

  // open files
  FILE *ofp = fopen("output.txt", "w");
  FILE *ifp = fopen("input.txt", "r");
  int file_end = 0;
  // Return if could not open file
  if (ofp == NULL)
    return 0;
  // Return if could not open file
  if (ifp == NULL) {
    fprintf(stderr, "input.txt not found!");
    return 0;
  }

  if (arr1 == NULL) {
    fprintf(stderr, "Array 1 not allocated");
  }
  if (arr2 == NULL) {
    fprintf(stderr, "Array 2 not allocated");
  }
  c = fgetc(ifp); // read in first character of first number
  // read numbers until we foud '\n' character
  while ((int)(c)-48 >= 0) {
    arr1_size++;
    arr1 = realloc(arr1, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
    arr1[arr1_size - 1] = (int)(c)-48;
    c = fgetc(ifp);
  }
  // write out first number
  for (i = 0; i < arr1_size; i++) {
    fputc((arr1[i]) + '0', ofp);
  }
  // read and write out operator
  operator= fgetc(ifp);
  fputc('\n', ofp);
  fputc(operator, ofp);
  fputc('\n', ofp);
  // printf("\n%c\n", operator);
  c = fgetc(ifp); // read in first character of first number
  // read numbers until we reach the end of the file
  while (file_end != 1) {
    c = fgetc(ifp);
    if (!feof(ifp)) {
      arr2_size++;
      arr2 = realloc(arr2, arr2_size * sizeof(int));
      if (arr2 == NULL) {
        fprintf(stderr, "Array not reallocated");
      }
      arr2[arr2_size - 1] = (int)(c)-48;
    } else {
      file_end = 1;
    }
  }

  // write out second number
  for (i = 0; i < arr2_size; i++) {
    fputc((arr2[i]) + '0', ofp);
  }
  // write out '=' sign
  fputc('\n', ofp);
  fputc('=', ofp);
  fputc('\n', ofp);

  // get the result based on the operator
  if (operator== '+') {
    result = sum(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '-') {
    result = subtract(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '*') {
    result = multiply(arr1, arr2, arr1_size, arr2_size);
  } else if (operator== '/') {
    result = divide(arr1, arr2, arr1_size, arr2_size);
  }

  // write a '-' sign if its neccessary
  if (result.is_negative == 1) {
    fputc('-', ofp);
  }

  // write out result without leading 0's
  for (i = 0; i < result.res_arr_size; i++) {
    if (((result.res_arr[i]) + '0') != '0') {
      is_leading_0s_ended = 1;
    }
    if (is_leading_0s_ended) {
      fputc((result.res_arr[i]) + '0', ofp);
    }
  }

  // clode files, free memory
  fclose(ifp);
  fclose(ofp);
  free(arr1);
  free(arr2);

  return 0;
}