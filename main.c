#include <stdio.h>
#include <stdlib.h>

char* generate_id() {
  char id[4] = {'0', '0', '0', '0'};
  
  return id;
}

void add_patient() {
  
}

void hospital_capacity() {

}

void edit_patient() {

}

void list_patients() {

}

void delete_patient() {

}

int main() {
       //main appearance menu 
#include<stdio.h>
void menu(){
    int choice = 0; 
    do{
        headMessage("HOSPITAL MANAGEMENT SYSTEM\n");
        
        printf("\t\t\t1) Track intensive care\n");
        printf("\t\t\t2) Track newborn babies\n");
        printf("\t\t\t3) Check which patients occupy what department\n");
        printf("\t\t\t4) Check quantity of a blood type\n");
        printf("\t\t\t5) Add a new patient record\n");
        printf("\t\t\t6) Edit existing patient record\n");
        printf("\t\t\t7) Show patient list and info\n");
        printf("\033[0;31m");
        printf("\t\t\t8) Delete a patient record\n");
        printf("\033[0m");
        printf("---- Press zero to exit ----");
        ///////////
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                Track_intensive_care();
                break;
            case 2:
                Track_baby_incubators();
                break;
            case 3:
                Hospital_capacity();
                break;
            case 4:
                Track_blood_types();
                break;
            case 5:
                Add_patients();
                break;
            case 6:
                Edit_patients();
                break;
            case 7:
                list_patients();
                break;
            case 8:
                Delete_patients();
                break;
            case 0:
                printf("You are now exiting the menu...");
                sleep(3);
                exit(1);
        }
    }
    while(choice!=0);
}
  return 0;
}
