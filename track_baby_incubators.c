#include<stdio.h>
int count_newborn_patients(){
    int count =0;
    char line[30];
    FILE *fp= fopen("patients_info.txt", "r");
    if (fp == 0){
        printf("Unable to open file\n");
        return -1;
    }
    while(fgets(line, sizeof(line), fp) != 0){
        if(strcmp(line, "newborn")!=0)
        count++;
        }
    fclose(fp);
    return count;
}


int track_baby_incubators(int free_beds){
    int babies = count_newborn_patients();
    return 560 - babies;
}

