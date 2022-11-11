#include <stdio.h>
#include <stdlib.h>

int main() {
  // open the files

  FILE *ofp = fopen("output.txt", "w");

  // Return if could not open file
  if (ofp == NULL)
    return 0;

  FILE *ifp = fopen("input.txt", "r");
  int file_end = 0;
  // Return if could not open file
  if (ifp == NULL) {
    printf("input.txt not found!");
    return 0;
  }

  do {
    // Checking for end of file
    if (!feof(ifp)) {
      // Taking input single character at a time
      char c = fgetc(ifp);
      fputc(c, ofp);
    } else {
      file_end = 1;
    }
    // printf("%c", c);
  } while (file_end != 1);

  fclose(ifp);
  fclose(ofp);

  return 0;
}