#include <stdio.h>

#define N 6

int main() {
  // 4.2.1

  int tomb[N];

  int szam;
  int i;
  for (i = 0; i < N; i++) {
    scanf("%d", &szam);
    tomb[i] = szam;
  }
  int existing_number;
  int occurences = 0;
  printf("Megszamlalando szam: ");
  scanf("%d", &existing_number);
  for (i = 0; i < N; i++) {
    if (tomb[i] == existing_number) {
      occurences++;
    }
  }
  printf("%d darab szerepel\n", occurences);

  return 0;
}
