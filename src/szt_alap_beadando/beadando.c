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
#include <math.h>
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
  int res_arr_size = ((arr1_size > arr2_size) ? arr1_size : arr2_size) + 1;
  res_arr = calloc(res_arr_size, sizeof(int));
  int arr1_i = arr1_size - 1;
  int arr2_i = arr2_size - 1;
  int res_arr_i = res_arr_size - 1;
  int leftover = 0;
  int current_sum = 0;
  int *tmp_arr1 = calloc(res_arr_size, sizeof(int));
  int *tmp_arr2 = calloc(res_arr_size, sizeof(int));
  int i;
  struct MyResult res;
  // left padding the shorter input array with 0's

  if (arr1_size < res_arr_size) {
    for (i = 0; i <= arr1_i; i++) {
      tmp_arr1[res_arr_i - i] = arr1[arr1_i - i];
    }

    arr1_size = res_arr_size;
    arr1 = realloc(tmp_arr1, arr1_size * sizeof(int));
    if (arr1 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  }

  if (arr2_size < res_arr_size) {
    for (i = 0; i <= arr2_i; i++) {
      tmp_arr2[res_arr_i - i] = arr2[arr2_i - i];
    }

    arr2_size = res_arr_size;
    arr2 = realloc(tmp_arr2, arr2_size * sizeof(int));
    if (arr2 == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
  }
  // printf("r:%d, 1:%d, 2:%d\n", res_arr_size, arr1_size, arr2_size);
  // for (i = 0; i < arr1_size; i++) {
  //   printf("%d", arr1[i]);
  // }
  // printf("\n");
  // for (i = 0; i < arr2_size; i++) {
  //   printf("%d", arr2[i]);
  // }
  // printf("\n");

  // left padding the longer input array with 0's

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
  // printf("%d", leftover);
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
  struct MyResult curr_res;
  int leftover = 0;
  int current_mult;
  int sorok = arr2_size;
  int oszlopok = arr1_size + arr2_size;
  int **matrix;
  matrix = bekerMatrix(sorok, oszlopok);
  // printf("sorok: %d, oszlopok: %d\n", sorok, oszlopok);
  // creating matrix like you would on paper
  for (int i = 0; i < arr2_size; i++) {
    for (int j = 0; j < arr1_size + 1; j++) {

      current_mult = (arr2[arr2_i - i] * arr1[arr1_i - j]) + leftover;

      // because i cant use '%' operator i need to do it by hand
      leftover = (int)(current_mult / 10);
      matrix[sorok - 1 - i][oszlopok - 1 - j - i] =
          current_mult - (leftover * 10);
      /*
            printf("[%d][%d] = %d (%d*%d) leftover: %d\n", sorok - 1 - i,
                   oszlopok - 1 - j, current_mult - (leftover * 10), arr2[arr2_i
         - i], arr1[arr1_i - j], leftover);
                   */
    }
    leftover = 0;
  }

  curr_res.res_arr = calloc(oszlopok + 1, sizeof(int));
  curr_res.res_arr = matrix[0];
  curr_res.res_arr_size = oszlopok;

  for (int i = 0; i < sorok - 1; i++) {
    // printf("\n");
    // for (int j = 0; j < curr_res.res_arr_size; j++) {
    //   printf("%d", curr_res.res_arr[j]);
    // }
    curr_res.res_arr =
        realloc(curr_res.res_arr, (curr_res.res_arr_size + 1) * sizeof(int));
    if (curr_res.res_arr == NULL) {
      fprintf(stderr, "Array not reallocated");
    }

    curr_res =
        sum(curr_res.res_arr, matrix[i + 1], curr_res.res_arr_size, oszlopok);
  }

  // printf("\n");

  // printf("Matrix:\n");
  // for (int i = 0; i < sorok; i++) {
  //   for (int j = 0; j < oszlopok; j++)
  //     printf("%d", matrix[i][j]);
  //   printf("\n");
  // }

  felszabaditMatrix(sorok, oszlopok, matrix);
  res = curr_res;
  return res;
}

struct MyResult divide(int *arr1, int *arr2, int arr1_size, int arr2_size) {
  // return result array and its lenght as a struct
  struct MyResult res;
  int res_arr_size = 0;
  int *res_arr = calloc(res_arr_size, sizeof(int));
  unsigned int ans = 0, divisor = 0;
  int i, j;

  // make the divisor from the array
  for (i = 0; i < arr2_size; i++)
    divisor = 10 * divisor + arr2[i];
  printf("%d", divisor);
  int arr1_i = 0;
  int tmp = arr1[arr1_i];

  // find a big enough number to start the division with
  while (tmp < divisor) {
    arr1_i++;
    tmp = tmp * 10 + arr1[arr1_i];
  }
  // divide like you would on paper
  while (arr1_i < arr1_size) {
    ans = ans * 10 + (int)(tmp / divisor);
    res_arr_size++;
    res_arr = realloc(res_arr, res_arr_size * sizeof(int));
    if (res_arr == NULL) {
      fprintf(stderr, "Array not reallocated");
    }
    arr1_i++;
    tmp = (tmp - (divisor * (tmp / divisor))) * 10 + arr1[arr1_i];
  }

  // printf("%d", ans);

  // convert ans to array
  for (i = 0; i < res_arr_size; i++) {
    res_arr[res_arr_size - 1 - i] = (ans - (10 * (ans / 10)));
    ans /= 10;
  }

  res.res_arr = res_arr;
  res.res_arr_size = res_arr_size;
  res.is_negative = 0;
  return res;
}

struct MyResult remove_leading_zeros(struct MyResult input) {
  struct MyResult res;
  int *arr1 = input.res_arr;
  int arr1_size = input.res_arr_size;
  res.res_arr = calloc(arr1_size, sizeof(int));
  int i = 0;
  int is_leading_0s_ended = 0;
  while (is_leading_0s_ended == 0) {
    if (arr1[i] == 0) {
      // printf("true");
      i++;
    } else {
      // printf("false");
      is_leading_0s_ended = 1;
    }
  }
  // printf("i:%d\n", i);
  // printf("arr_size:%d\n", arr1_size);
  res.res_arr_size = arr1_size - i;
  res.res_arr = realloc(arr1, res.res_arr_size * sizeof(int));
  res.is_negative = input.is_negative;
  for (i = 0; i < res.res_arr_size; i++) {
    // printf("set %d. item to %d. item of arr (%d)\n", res.res_arr_size - i,
    //        (arr1_size - i) - 1, arr1[(arr1_size - i) - 1]);
    res.res_arr[(res.res_arr_size - i) - 1] = arr1[(arr1_size - i) - 1];
  }
  return res;
}

struct MyResult divide_by_subtraction(int *arr1, int *arr2, int arr1_size,
                                      int arr2_size) {

  struct MyResult res;
  res.is_negative = 0;
  res.res_arr = arr1;
  res.res_arr_size = arr1_size;
  int count = 0;
  int i = 0;

  // for (i = 0; i < arr1_size; i++) {
  //   printf("%d", arr1[i]);
  // }
  // printf("\n");
  // res = remove_leading_zeros(arr1, arr1_size);

  // for (i = 0; i < res.res_arr_size; i++) {
  //   printf("%d", res.res_arr[i]);
  // }
  // printf("\n");

  while (res.is_negative != 1) {
    res = subtract(res.res_arr, arr2, res.res_arr_size, arr2_size);
    count++;
    res = remove_leading_zeros(res);
    printf("%d - ", count);
    for (i = 0; i < res.res_arr_size; i++) {
      printf("%d", res.res_arr[i]);
    }
    printf("\n");
  }
  /*
  int res_arr_size = count;
  int lenght_of_count = 0;
  while (count / 10 > 1) {
    count /= 10;
    lenght_of_count++;
  }
  int *res_arr = calloc(lenght_of_count, sizeof(int));
  for (i = 0; i < lenght_of_count; i++) {
    res_arr[i] = count / (10 * lenght_of_count);
  }
  res.res_arr res.
  */
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
    result = divide_by_subtraction(arr1, arr2, arr1_size, arr2_size);
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

  // close files, free memory
  fclose(ifp);
  fclose(ofp);
  free(arr1);
  free(arr2);

  return 0;
}