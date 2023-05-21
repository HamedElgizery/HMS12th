#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define MAX_CAPACITY_NORMAL 560
#define MAX_CAPACITY_INCUBATORS 70
#define MAX_CAPACITY_INTENSIVE 30

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

char buffer[50];
typedef struct {
    char id[10];
    char name[30];
    char age[30];
    char patient_type[30];
    char address[50];
    char gender[30];
    char blood_type[30];
    char disease[30];
    char specialist_room_no[30];
    char fam_contact[30];
    bool exist;
} patient;

typedef struct {
  char type[5];
  int amount_L;
} blood_type;

const char* PATIENT_HEADERS[] = {
  "ID",
  "Name",
  "Age",
  "Patient Type",
  "Address",
  "Gender",
  "Blood Type",
  "Illness",
  "Specialist Room No.",
  "Family Contact No."
};

void remove_trialing_endl(char* str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

bool id_exists(char* id) {
  FILE* file = fopen("patients_info.txt", "r");
  char buffer[50];
  int line_number = 0;
  while (fgets(buffer, 50, file)) {
    if (line_number % 9 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        return 1;
      }
    }
    line_number++;
  }
  fclose(file);
  return 0;
}


const char* generate_id() {
  bool found = 0;
  while (true) {
    srand(time(NULL));
    char* id = malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; ++i) {
      int num = rand() % 10;
      if (i + num) id[i] = num + '0';
      else --i;
    }
    id[4] = '\0';
    if (!id_exists(id)) return id;
  }
}

patient extract_from_file(FILE* file) {
  char buffer[50];
  patient extracted_patient;
  extracted_patient.exist = true;
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.id, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.name, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.age, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.patient_type, buffer);
  fgets(buffer, 50, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.address, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.gender, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.blood_type, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.disease, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.specialist_room_no, buffer);
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.fam_contact, buffer);
  return extracted_patient;
}


void print_patient_data(patient extracted_patient) {
  printf("ID: %s\n", extracted_patient.id);
  printf("Name: %s\n", extracted_patient.name);
  printf("Age: %s\n", extracted_patient.age);
  printf("Patient Type: %s\n", extracted_patient.patient_type);
  printf("Address: %s\n", extracted_patient.address);
  printf("Gender: %s\n", extracted_patient.gender);
  printf("Blood Type: %s\n", extracted_patient.blood_type);
  printf("Illness: %s\n", extracted_patient.disease);
  printf("Specialist Room No.: %s\n", extracted_patient.specialist_room_no);
  printf("Family Contact Number: %s\n", extracted_patient.fam_contact);
}


void track_intensive_care(){
  headMessage("TRACK INTENSIVE CARE");
  int count = 0;
  char buffer[30];
  FILE* file = fopen("patients_info.txt", "r");
  if (file == 0){
      printf("Unable to open file\n");
  } else {
    patient holder;
    while(!feof(file)) {
      holder = extract_from_file(file); 
      if (strcmp(holder.patient_type, "emergency") == 0) {
        count++;
        print_patient_data(holder);    
      }
    }
    fclose(file);
  }
  printf("Available Intensive Care Beds: %d\n", MAX_CAPACITY_INTENSIVE - count);
}


void track_blood_types(){
  headMessage("TRACK BLOOD QUANTITIY");
  char buffer[50];
  blood_type blood_type_holder;
  FILE* file = fopen("bloodtype.txt", "r");
  printf("Type\tAmount(L)\n");
  if (file == NULL) {
    printf("Unable to open 'bloodtype.txt' file!\n");
  } else {
    while (fgets(buffer, 20, file)) {
      remove_trialing_endl(buffer);
      strcpy(blood_type_holder.type, buffer);
      fgets(buffer, 20, file);
      remove_trialing_endl(buffer);
      blood_type_holder.amount_L = atoi(buffer);
      printf("%s\t%d\n", blood_type_holder.type, blood_type_holder.amount_L);
    }
  }
}

void change_blood() {
  headMessage("MODIFIY BLOOD AMOUNT");
  char type[30];
  int delta;
  puts("Enter blood type:");
  scanf("%s", type);
  puts("Enter delta:");
  scanf("%d", &delta);
  FILE* file1 = fopen("bloodtype.txt", "r");
  FILE* file2 = fopen("bloodtype2.txt", "w");
  if (file1 == NULL || file2 == NULL) {
    printf("Couldn't open the files!");
  } else {
    while (fgets(buffer, 30, file1)) {
      remove_trialing_endl(buffer);
      fprintf(file2, "%s\n", buffer);
      if (strcmp(type, buffer) == 0) {
        fgets(buffer, 30, file1);
        int amount = atoi(buffer);
        amount += delta;
        fprintf(file2, "%d\n", amount);
      }
    }
  }
  fclose(file1);
  fclose(file2);
  rename("bloodtype2.txt", "bloodtype.txt"); 
}

void track_baby_incubators() {
  headMessage("TRACK BABY INCUBATORS");
  int count = 0;
  char buffer[30];
  FILE* file = fopen("patients_info.txt", "r");
  if (file == 0){
      printf("Unable to open file\n");
  } else {
    patient holder;
    while(!feof(file)) {
      holder = extract_from_file(file); 
      if (strcmp(holder.patient_type, "newborn") == 0) {
        count++;
        print_patient_data(holder);    
      }
    }
    fclose(file);
  }
  printf("Available Incubators: %d\n", MAX_CAPACITY_INCUBATORS - count);
}

void hospital_capacity() {
  headMessage("HOSPITAL CAPACITY");
  //return MAX_CAPACITY - count_newborn_patients();
}

void add_patient_file(patient* to_add) {
  FILE* patients_file =  fopen("patients_info.txt", "a");
  fprintf(patients_file, "%s\n", to_add->id);
  fprintf(patients_file, "%s\n", to_add->name);
  fprintf(patients_file, "%s\n", to_add->age);
  fprintf(patients_file, "%s\n", to_add->patient_type);
  fprintf(patients_file, "%s\n", to_add->address);
  fprintf(patients_file, "%s\n", to_add->gender);
  fprintf(patients_file, "%s\n", to_add->blood_type);
  fprintf(patients_file, "%s\n", to_add->disease);
  fprintf(patients_file, "%s\n", to_add->specialist_room_no);
  fprintf(patients_file, "%s\n", to_add->fam_contact);
  fclose(patients_file);
}

void add_patient() {
  patient new_patient;
  headMessage("ADD NEW PATIENT");
  strcpy(new_patient.id, generate_id());
  fflush(stdin);
  printf("Enter the patient's name: \n");
  fgets(new_patient.name, 30, stdin);
  remove_trialing_endl(new_patient.name);
  fflush(stdin);
  printf("Enter the patient's age: \n");
  fgets(new_patient.age, 3, stdin);
  remove_trialing_endl(new_patient.age);
  fflush(stdin);
  printf("Enter the patient's type: \n");
  fgets(new_patient.patient_type, 30, stdin);
  remove_trialing_endl(new_patient.patient_type);
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
  add_patient_file(&new_patient);
}

patient extract(char* id) {
  char buffer[50];
  patient extracted_patient;
  FILE* file = fopen("patients_info.txt", "r");
  int line_number = 0;
  while (!extracted_patient.exist && fgets(buffer, 50, file)) {
    if (line_number % 10 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        extracted_patient.exist = true;
        strcpy(extracted_patient.id, id);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.name, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.age, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.patient_type, buffer);
        fgets(buffer, 50, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.address, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.gender, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.blood_type, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.disease, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.specialist_room_no, buffer);
        fgets(buffer, 30, file);
        remove_trialing_endl(buffer);
        strcpy(extracted_patient.fam_contact, buffer);
        break;
      }
    }
    line_number++;
  }
  fclose(file);
  return extracted_patient;
}

void list_patient_id(char* id) {
  patient extracted_patient;
  extracted_patient = extract(id);
  if (!extracted_patient.exist) {
    printf("No such patient exists...\n");
    return;
  }
  print_patient_data(extracted_patient);
}

void delete_patient_id(char* id) {
  FILE* f1 = fopen("patients_info.txt", "r");
  FILE* f2 = fopen("patients_info2.txt", "w");
  char buffer[50];
  int line_number = 0;
  bool found = 0;
  while (fgets(buffer, 50, f1)) {
    if (line_number % 10 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        found = 1;
        for (int i = 0; i < 9; ++i) fgets(buffer, 50, f1);
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
  headMessage(title);
  printf("Enter the id of patient: \n");
  char* id = malloc(sizeof(char) * 6);

  fflush(stdin);
  fgets(id, 5, stdin); 
  fflush(stdin);
  remove_trialing_endl(id);
  return id;
}

void edit_patient_id(char* id) {
  patient extracted_patient = extract(id);
  if (!extracted_patient.exist) {
    printf("No such patient exists...\n");
    return;
  }
  char buffer[50];
  FILE* file = fopen("patients_info.txt", "r");
  list_patient_id(id);
  delete_patient_id(id);
  for (int i = 1; i <= 9; ++i)
    printf("\t\t\t%d) %s\n", i, PATIENT_HEADERS[i]);
  printf("---- Press zero to discard ----");
  int choice;
  scanf("%d", &choice);
  if (choice) {
    printf("Enter the new '%s':\n", PATIENT_HEADERS[choice]);
    fflush(stdin);
    fgets(buffer, 50, stdin);
    remove_trialing_endl(buffer);
  }
  switch (choice) {
    case 1:
      strcpy(extracted_patient.name, buffer);
      break;
    case 2:
      strcpy(extracted_patient.age, buffer);
      break;
    case 3:
      strcpy(extracted_patient.patient_type, buffer);
      break;
    case 4:
      strcpy(extracted_patient.address, buffer);
      break;
    case 5:
      strcpy(extracted_patient.gender, buffer);
      break;
    case 6:
      strcpy(extracted_patient.blood_type, buffer);
      break;
    case 7:
      strcpy(extracted_patient.disease, buffer);
      break;
    case 8:
      strcpy(extracted_patient.specialist_room_no, buffer);
      break;
    case 9:
      strcpy(extracted_patient.fam_contact, buffer);
      break;
    case 0:
      break;
    default:
      printf("Invalid choice!");
  }
  add_patient_file(&extracted_patient);
  fclose(file);
}

void edit_patient() {
  char* id = get_id("EDIT PATIENT DATA");
  edit_patient_id(id);
}

void list_patient() {
  char* id = get_id("VIEW PATIENT DETAILS");
  list_patient_id(id);
}

void delete_patient() {
  char* id = get_id("DELETE PATIENT DATA");
  delete_patient_id(id);
}

int main() {
  //main appearance menu
  int choice; 
  do{
      headMessage("HOSPITAL MANAGEMENT SYSTEM");
      printf("\t\t\t1) Track intensive care\n");
      printf("\t\t\t2) Track newborn babies\n");
      printf("\t\t\t3) Check which patients occupy what department\n");
      printf("\t\t\t4) Check quantity of a blood type\n");
      printf("\t\t\t5) Add a new patient record\n");
      printf("\t\t\t6) Change blood amount\n");
      printf("\t\t\t7) Edit existing patient record\n");
      printf("\t\t\t8) Show patient list and info\n");
      printf("\033[0;31m");
      printf("\t\t\t9) Delete a patient record\n");
      printf("\033[0m");
      printf("---- Press zero to exit ----");
      fflush(stdin);
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
          change_blood();
          break;
        case 7:
          edit_patient();
          break;
        case 8:
          list_patient();
          break;
        case 9:
          delete_patient();
          break;
        case 0:
          printf("You are now exiting the menu...");
          sleep(3);
          exit(1);
    }
    puts("\nPress Enter to continue...");
    fflush(stdin);
    fgetc(stdin);
    //getch();
  } while(choice!=0);
  return 0;
}
