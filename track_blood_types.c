#include<stdio.h>
#include<stdlib.h>
int main()
{
    int quantity[8];
    char blood[5];
    FILE* fbptr = fopen("D:\\bloodtype.txt", "w");
    if ((fbptr == NULL)){
        printf("Unable to open file\n");
    }
    else
    {
        printf("Enter bloodtype and quantity:\n");
        for (int i = 0; i < 9; i++)
        {
            scanf("%s%d", blood, quantity);
        }
        fprintf(fbptr, "%s %d\n", blood, quantity);
        fclose(fbptr);
    }
}