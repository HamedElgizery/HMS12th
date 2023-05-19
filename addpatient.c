#include<stdio.h>

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
