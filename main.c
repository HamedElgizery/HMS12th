#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    char* id;
    char name[30];
    char age[30];
    char address[50];
    char gender[30];
    char blood_type[30];
    char disease[30];
    char specialist_room_no[30];
    char fam_contact[30];
    bool exist;
} patient;

const char* PATIENT_HEADERS[] = {
  "ID",
  "Name",
  "Age",
  "Address",
  "Gender",
  "Blood Type",
  "Illness",
  "Specialist Room No.",
  "Family Contact No."
};


char* generate_id() {
  char* id = malloc(sizeof(char) * 5);
  for (int i = 0; i < 4; ++i) {
    int num = rand() % 10;
    if (i + num) id[i] = num + '0';
    else --i;
  }
  id[4] = '\0';
  return id;
}

void track_intensive_care(){
    
}

void track_baby_incubators(){

}

void track_blood_types(){
}

void hospital_capacity() {

}


void printMessageCenter(const char* message) {
    int len = 0, pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++) {
        printf(" ");
    }
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

void remove_trialing_endl(char* str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    //printf("%d", i);
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

void add_patient() {
  patient* new_patient;
  headMessage("Add a new patient\n");
  new_patient->id = generate_id();
  fflush(stdin);
  printf("Enter the patient's name: \n");
  fgets(new_patient->name, 30, stdin);
  remove_trialing_endl(new_patient->name);
  fflush(stdin);
  printf("Enter the patient's age: \n");
  fgets(new_patient->age, 3, stdin);
  remove_trialing_endl(new_patient->age);
  fflush(stdin);
  printf("Enter the patient's address: \n");
  fgets(new_patient->address, 50, stdin);
  remove_trialing_endl(new_patient->address);
  fflush(stdin);
  printf("Choose (M) or (F) for gender: \n");
  fgets(new_patient->gender, 30, stdin);
  remove_trialing_endl(new_patient->gender);
  fflush(stdin);
  printf("Enter the patient's blood type: \n");
  fgets(new_patient->blood_type, 3, stdin);
  remove_trialing_endl(new_patient->blood_type);
  fflush(stdin);
  printf("Enter patient's illness: \n");
  fgets(new_patient->disease, 30, stdin);
  remove_trialing_endl(new_patient->disease);
  fflush(stdin);
  printf("Enter specialist room number: \n");
  fgets(new_patient->specialist_room_no, 30, stdin);
  remove_trialing_endl(new_patient->specialist_room_no);
  fflush(stdin);
  printf("Enter emergency family contact: \n");
  fgets(new_patient->fam_contact, 30, stdin);
  remove_trialing_endl(new_patient->fam_contact);
  fflush(stdin);
}

void add_patient_file(patient* to_add) {
  FILE* patients_file =  fopen("patients_info.txt", "a");
  fprintf(patients_file, "%s\n", to_add->id);
  fprintf(patients_file, "%s\n", to_add->name);
  fprintf(patients_file, "%s\n", to_add->age);
  fprintf(patients_file, "%s\n", to_add->address);
  fprintf(patients_file, "%s\n", to_add->gender);
  fprintf(patients_file, "%s\n", to_add->blood_type);
  fprintf(patients_file, "%s\n", to_add->disease);
  fprintf(patients_file, "%s\n", to_add->specialist_room_no);
  fprintf(patients_file, "%s\n", to_add->fam_contact);
  fclose(patients_file);
}


patient* extract_from_file(char* id) {
  char buffer[50];
  patient* extracted_patient;
  FILE* file = fopen("patients_info.txt", "r");
  int line_number = 0;
  while (!extracted_patient->exist && fgets(buffer, 50, file)) {
    if (line_number % 9 == 0) {
      printf("g%d\n", line_number);
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        extracted_patient->exist = true;
        strcpy(extracted_patient->id, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->name, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->age, buffer);
        fgets(buffer, 50, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->address, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->gender, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->blood_type, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->disease, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->specialist_room_no, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient->fam_contact, buffer);
        break;
      }
    }
    line_number++;
  }
  fclose(file);
  return extracted_patient;
}

void list_patient_id(char* id) {
  patient* extracted_patient;
  extracted_patient->exist = false;
  if (!extracted_patient->exist) {
    printf("No such patient exists...\n");
    return;
  }
  printf("ID: %s\n", extracted_patient->id);
  printf("Name: %s", extracted_patient->name);
  printf("Age: %s", extracted_patient->age);
  printf("Address: %s", extracted_patient->address);
  printf("Gender: %s", extracted_patient->gender);
  printf("Blood Type: %s", extracted_patient->blood_type);
  printf("Illness: %s", extracted_patient->disease);
  printf("Specialist Room No.: %s", extracted_patient->specialist_room_no);
  printf("Family Contact Number: %s", extracted_patient->fam_contact);
}

void delete_patient_id(char* id) {
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

char* get_id(char* title) {
  //headMessage(title);
  printf("Enter the id of patient: \n");
  char* id = malloc(sizeof(char) * 6);// = malloc(sizeof(char) );

  fflush(stdin);
  fgets(id, 5, stdin); 
  remove_trialing_endl(id);
  return id;
}

void edit_patient_id(char* id) {
  printf("Hello");
  patient* extracted_patient = extract_from_file(id);
  if (!extracted_patient->exist) {
    printf("No such patient exists...\n");
    return;
  }
  char buffer[50];
  FILE* file = fopen("patients_info.txt", "r");
  delete_patient_id(id);
  list_patient_id(id);
  for (int i = 1; i < 9; ++i)
    printf("\t\t\t%d) %s\n", i, PATIENT_HEADERS[i]);
  printf("---- Press zero to discard ----");
  int choice;
  scanf("%d", &choice);
  if (choice == 0) return;
  printf("Enter the new '%s':\n", PATIENT_HEADERS[choice]);
  fgets(buffer, 50, stdin);
  remove_trialing_endl(buffer);
  switch (choice) {
    case 1:
      strcpy(extracted_patient->name, buffer);
      break;
    case 2:
      strcpy(extracted_patient->age, buffer);
      break;
    case 3:
      strcpy(extracted_patient->address, buffer);
      break;
    case 4:
      strcpy(extracted_patient->gender, buffer);
      break;
    case 5:
      strcpy(extracted_patient->blood_type, buffer);
      break;
    case 6:
      strcpy(extracted_patient->disease, buffer);
      break;
    case 7:
      strcpy(extracted_patient->specialist_room_no, buffer);
      break;
    case 8:
      strcpy(extracted_patient->fam_contact, buffer);
      break;
    default:
      printf("Invalid choice!");
  }
  add_patient_file(extracted_patient);
  fclose(file);
}

void edit_patient() {
  char* id = get_id("Edit patient data");
  edit_patient_id(id);
}



void list_patient() {
  char* id = get_id("View patient details\n");
  list_patient_id(id);
}


void delete_patient() {
  char* id = get_id("Delete a patient\n");
  delete_patient_id(id);
}


int main() {
  char* id = get_id("test");
  printf("%s, %d", id, (int)strlen(id));
  list_patient_id(id);
  free(id);
  /*
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

        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                track_intensive_care();
                break;
            case 2:
                track_baby_incubators();
                break;
            case 3:
                hospital_capacity();
                break;
            case 4:
                track_blood_types();
                break;
            case 5:
                add_patient();
                break;
            case 6:
                edit_patient();
                break;
            case 7:
                list_patient();
                break;
            case 8:
                delete_patient();
                break;
            case 0:
                printf("You are now exiting the menu...");
                sleep(3);
                exit(1);
        }
    }
    while(choice!=0);
    */
  return 0;

}
