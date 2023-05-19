#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int patient_ID[5];
    char name[100];
    int age;
    char address[100];
    char gender;
    char blood_type[4];
    char disease[100];
    int specialist_room_no;
    int fam_contact[20];

} patient;

const char* generate_id() {
  static char id[4];
  for (int i = 0; i < 4; ++i) {
    int num = rand() % 10;
    if (i + num) id[i] = num + '0';
    else --i;
  }
  for (int i = 0; i < 4; ++i) {
    printf("%c", id[i]);
  }
  return id;
}

void Track_intensive_care(){
    
}

void Track_baby_incubators(){

}

void Track_blood_types(){
    char* Query (char file_name[6], char bloodType[6])
{
    char bloodQuantity[6];
    for (int i = 0; i < 9; i++)
    {
        if (  == bloodType) {
           char bloodQuantity[6] = bloodType;
           break;
         }
    } 
    return bloodQuantity;
    }
}

void Hospital_capacity() {

}

void Add_patient(){
    patient new_patient;
    headmessage("Add a new patient\n");
    //printf("Enter patient ID: \n");
    printf("Enter the patient's name: \n");
    gets(new_patient.name);
    printf("Enter the patient's age: \n");
    scanf("%d", &new_patient.age);
    printf("Enter the patient's address: \n");
    scanf("%s", &new_patient.address);
    printf("Choose (M) or (F) for gender: \n");
    scanf("%s", &new_patient.gender);
    printf("Enter the patient's blood type: \n");
    scanf("%s", &new_patient.blood_type);
    printf("Enter patient's illness: \n");
    scanf("%s",&new_patient.disease);
    printf("Enter specialist room number: \n");
    scanf("%d", &new_patient.specialist_room_no);
    printf("Enter emergency family contact: \n");
    scanf("%d", &new_patient.fam_contact);
}

void Edit_patient() {

}

void List_patients() {

}

void Delete_patient() {

}


int main() {
    //main appearance menu 
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
                Add_patient();
                break;
            case 6:
                Edit_patients();
                break;
            case 7:
                List_patients();
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
  return 0;
}
