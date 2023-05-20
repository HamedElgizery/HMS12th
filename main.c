#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
    char* id;
    char name[30];
    char age[3];
    char address[50];
    char gender[30];
    char blood_type[3];
    char disease[30];
    char specialist_room_no[30];
    char fam_contact[30];
} patient;

char* generate_id() {
  char* id = malloc(sizeof(char) * 5);
  for (int i = 0; i < 4; ++i) {
    int num = rand() % 10;
    if (i + num) id[i] = num + '0';
    else --i;
  }
  return id;
}

void Track_intensive_care(){
    
}

void Track_baby_incubators(){

}
/*
char* Query (char file_name[6], char bloodType[6]) {
  char bloodQuantity[6];
  for (int i = 0; i < 9; i++) {
    if (  == bloodType) {
      char bloodQuantity[6] = bloodType;
      break;
    }
  } 
  return bloodQuantity;
}
    */
void Track_blood_types(){
}

void Hospital_capacity() {

}

/*
 * ID
 *
 *
 * */

void printMessageCenter(const char* message) {
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}

void headMessage(const char *message) {
  printf("\033[2J\033[1;1H");
  printf("\t\t\t###########################################################################");
  printf("\n\t\t\t############                                                   ############");
  printf("\n\t\t\t############      Hospital management System Project in C      ############");
  printf("\n\t\t\t############                                                   ############");
  printf("\n\t\t\t###########################################################################");
  printf("\n\t\t\t---------------------------------------------------------------------------\n");
  printMessageCenter(message);
  printf("\n\t\t\t----------------------------------------------------------------------------\n");
}

void remove_trialing_endl(char *str) {
  for (int i = 0; str[i] != '\0'; ++i)
    if (str[i] == '\n') str[i] = '\0';
}

void Add_patient(){
    patient new_patient;
    headMessage("Add a new patient\n");
    new_patient.id = generate_id();
    fflush(stdin);
    printf("Enter the patient's name: \n");
    fgets(new_patient.name, 30, stdin);
    remove_trialing_endl(new_patient.name);
    fflush(stdin);
    printf("Enter the patient's age: \n");
    fgets(new_patient.age, 3, stdin);
    remove_trialing_endl(new_patient.age);
    fflush(stdin);
    printf("Enter the patient's address: \n");
    fgets(new_patient.address, 50, stdin);
    remove_trialing_endl(new_patient.address);
    fflush(stdin);
    printf("Choose (M) or (F) for gender: \n");
    fgets(new_patient.gender, 30, stdin);
    remove_trialing_endl(new_patient.gender);
    fflush(stdin);
    printf("Enter the patient's blood type: \n");
    fgets(new_patient.blood_type, 3, stdin);
    remove_trialing_endl(new_patient.blood_type);
    fflush(stdin);
    printf("Enter patient's illness: \n");
    fgets(new_patient.disease, 30, stdin);
    remove_trialing_endl(new_patient.disease);
    fflush(stdin);
    printf("Enter specialist room number: \n");
    fgets(new_patient.specialist_room_no, 30, stdin);
    remove_trialing_endl(new_patient.specialist_room_no);
    fflush(stdin);
    printf("Enter emergency family contact: \n");
    fgets(new_patient.fam_contact, 30, stdin);
    remove_trialing_endl(new_patient.fam_contact);
    fflush(stdin);

    FILE* patients_file =  fopen("patients_info.txt", "a");
    fprintf(patients_file, "%s\n", new_patient.id);
    fprintf(patients_file, "%s\n", new_patient.name);
    fprintf(patients_file, "%s\n", new_patient.age);
    fprintf(patients_file, "%s\n", new_patient.address);
    fprintf(patients_file, "%s\n", new_patient.gender);
    fprintf(patients_file, "%s\n", new_patient.blood_type);
    fprintf(patients_file, "%s\n", new_patient.disease);
    fprintf(patients_file, "%s\n", new_patient.specialist_room_no);
    fprintf(patients_file, "%s\n", new_patient.fam_contact);
    fclose(patients_file);
}

void Edit_patient() {

}

void List_patients() {
  headMessage("View patient details\n");
  printf("Enter the id of patient: \n");
  char id[20], buffer[50];
  scanf("%s", id);
  FILE* file = fopen("patients_info.txt", "r");
  bool found = 0;
  int line_number = 0;
  while (!found && fgets(buffer, 50, file)) {
    if (line_number % 9 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        found = 1;
        printf("ID: %s\n", buffer);
        fgets(buffer, 30, file);
        printf("Name: %s", buffer);
        fgets(buffer, 5, file);
        printf("Age: %s", buffer);
        fgets(buffer, 50, file);
        printf("Address: %s", buffer);
        fgets(buffer, 30, file);
        printf("Gender: %s", buffer);
        fgets(buffer, 5, file);
        printf("Blood Type: %s", buffer);
        fgets(buffer, 30, file);
        printf("Illness: %s", buffer);
        fgets(buffer, 30, file);
        printf("Specialist Room No.: %s", buffer);
        fgets(buffer, 30, file);
        printf("Family Contact Number: %s", buffer);
        continue;
      }
    }
    line_number++;
  }
  if (!found) printf("No such patient exists...");
  fclose(file);
}

void Delete_patient() {
  headMessage("Delete a patient\n");
  printf("Enter the id of patient: \n");
  char id[20];
  scanf("%s", id);
  FILE* f1 = fopen("patients_info.txt", "r");
  FILE* f2 = fopen("patients_info2.txt", "w");
  char buffer[50];
  int line_number = 0;
  bool found = 0;
  while (fgets(buffer, 50, f1)) {
    if (line_number % 9 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        found = 1;
        for (int i = 0; i < 8; ++i) fgets(buffer, 50, f1);
        continue;
      }
      else fprintf(f2, "%s\n", buffer);
    }
    else fprintf(f2, "%s", buffer);
    line_number++;
  }
  if (!found) printf("Patient with the given ID wasn't found...\n");
  else printf("Patient with the ID '%s' was deleted successfully\n", id);
  fclose(f1);
  fclose(f2);
  rename("patients_info2.txt", "patients_info.txt"); 
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
                Edit_patient();
                break;
            case 7:
                List_patients();
                break;
            case 8:
                Delete_patient();
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
