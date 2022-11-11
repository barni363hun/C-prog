#include <stdio.h>
#include <stdlib.h>

int main() {
  // open the file
  FILE *fp = fopen("test.txt", "r");

  // Return if could not open file
  if (fp == NULL)
    return 0;

  do {
    // Taking input single character at a time
    char c = fgetc(fp);

    // Checking for end of file
    if (feof(fp))
      break;

    printf("%c", c);
  } while (1);

  fclose(fp);
  return (0);
  int i = 0;

  
  FILE *fp = fopen("output.txt", "w");

  // Return if could not open file
  if (fp == NULL)
    return 0;

  char string[] = "good bye", received_string[20];

  for (i = 0; string[i] != '\0'; i++)

    // Input string into the file
    // single character at a time
    fputc(string[i], fp);

  fclose(fp);
  fp = fopen("output.txt", "r");

  // Reading the string from file
  fgets(received_string, 20, fp);

  printf("%s", received_string);

  fclose(fp);
  return 0;
}