#include<stdio.h>
#include<stdlib.h>
int main() {
  char quantity[8];
  char blood[5];
  FILE* fbptr = fopen("bloodtype.txt", "w");
  if (fbptr == NULL) {
    printf("Unable to open file\n");
  }
  else {
    printf("Enter bloodtype and quantity:\n");
    for (int i = 0; i < 8; i++) {
      scanf("%s%s", blood, quantity);
      fprintf(fbptr, "%s %s\n", blood, quantity);
    }
    fclose(fbptr);
  }
}
