/*
 * 12th project PROBLEM SOLVING
 * Zeina Ahmed 221017888
 * Hamed Ashraf 221027642
 * Engy Elbatran 221007986
 * Shahd Adel 221007980
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define MAX_CAPACITY_NORMAL 560
#define MAX_CAPACITY_INCUBATORS 70
#define MAX_CAPACITY_INTENSIVE 30


typedef struct {
    char id[10];
    char name[50];
    char age[50];
    char patient_type[50];
    char address[50];
    char gender[50];
    char blood_type[50];
    char disease[50];
    char specialist_room_no[50];
    char fam_contact[50];
    char department[50];
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
  "Family Contact No.",
  "Department"
};

void printMessageCenter(const char*);
void headMessage(const char*);
void remove_trialing_endl(char*);

bool id_exists(char*); // check if a patient exists
const char* generate_id();
patient extract_from_file(FILE*); // extract the data of the first found patient in the file
void print_patient_data(patient); 
void track_intensive_care(); // list all patients that there type is "emergency"
void track_blood_types(); // list all the blood types that exist in the file and their amounts
void change_blood(); // add or remove an amount from a blood type
void track_baby_incubators(); // list all patients that there typs is "newborn"
void hospital_capacity(); // print the number of patients in each department
void add_patient_file(patient); // add a patient to a file (data already given in the parameter)
patient extract(char*); // extract the data of a patient from a file (given the id)
void list_patient_id(char*); // list the data of a patient (given the id)
void delete_patient_id(char*, bool); // delete a patient (given the id)
char* get_id(char*); // asks user for an id
void edit_patient_id(char*); // edit patient data (given the id)
void add_patient(); // runs the add patient request (accept data from the user)
void edit_patient(); // runs the edit patient request
void list_patient(); // runs the list patient request
void delete_patient(); // runs the delete patient request
void list_all(); // list all the patients in the file

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
  printf("\033[2J\033[1;1H"); // clear the screen
  printf("\t\t\t###########################################################################");
  printf("\n\t\t\t############                                                   ############");
  printf("\n\t\t\t############      Hospital management System Project in C      ############");
  printf("\n\t\t\t############                                                   ############");
  printf("\n\t\t\t###########################################################################");
  printf("\n\t\t\t---------------------------------------------------------------------------\n");
  printMessageCenter(message);
  printf("\n\t\t\t----------------------------------------------------------------------------\n");
}

// hamed
void remove_trialing_endl(char* str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == '\n') {
      str[i] = '\0';
      break;
    }
  }
}

// shahd
bool id_exists(char* id) {
  char buffer[50];
  FILE* file = fopen("patients_info.txt", "r");
  int line_number = 0;
  while (fgets(buffer, 50, file)) {
    if (line_number % 11 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        return true;
      }
    }
    line_number++;
  }
  fclose(file);
  return false;
}

// hamed
const char* generate_id() {
  while (true) {
    srand(time(NULL));
    char* id = malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; ++i) {
      int num = rand() % 10;
      if (i != 0 || num != 0) id[i] = num + '0';
      else --i;
    }
    id[4] = '\0';
    if (!id_exists(id)) return id;
  }
}

// zeina
patient extract_from_file(FILE* file) {
  // extract the next patient from file
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
  fgets(buffer, 30, file);
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
  fgets(buffer, 30, file);
  remove_trialing_endl(buffer);
  strcpy(extracted_patient.department, buffer);
  return extracted_patient;
}


// engy
void print_patient_data(patient extracted_patient) {
  // print data to the user on the console 
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
  printf("Department: %s\n", extracted_patient.department);
  printf("--------------------\n");
}

// shahd
void track_intensive_care() {
  headMessage("TRACK INTENSIVE CARE");
  int count = 0;
  FILE* file = fopen("patients_info.txt", "r");
  if (file == 0){
      printf("Unable to open file\n");
  } else {
    patient holder;
    while(!feof(file)) {
      holder = extract_from_file(file); // get next patient in file
      if (strcmp(holder.patient_type, "emergency") == 0) {
        count++;
        print_patient_data(holder); 
      }
    }
    printf("Available Intensive Care Beds: %d\n", MAX_CAPACITY_INTENSIVE - count); // number of intensive care beds available
  }
  fclose(file);
}

// shahd
void track_blood_types(){
  char buffer[50];
  headMessage("TRACK BLOOD QUANTITIY");
  blood_type blood_type_holder;
  FILE* file = fopen("bloodtype.txt", "r");
  printf("Type\tAmount(L)\n");
  if (file == NULL) {
    printf("Unable to open 'bloodtype.txt' file!\n");
  } else {
    while (fgets(buffer, 20, file)) { // get next blood type
      remove_trialing_endl(buffer);
      strcpy(blood_type_holder.type, buffer); 
      fgets(buffer, 20, file); // gets the amount of blood for the current type
      remove_trialing_endl(buffer);
      blood_type_holder.amount_L = atoi(buffer);
      printf("%s\t%d\n", blood_type_holder.type, blood_type_holder.amount_L);
    }
  }
  fclose(file);
}

// hamed
void change_blood() {
  char buffer[50];
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
    bool found = 0;
    while (fgets(buffer, 30, file1)) {
      remove_trialing_endl(buffer);
      fprintf(file2, "%s\n", buffer);
      if (strcmp(type, buffer) == 0) {
        found = 1;
        fgets(buffer, 30, file1);
        int amount = atoi(buffer);
        amount += delta;
        if (amount < 0) {
          printf("There isn't enought blood, can't perform that!");
          amount -= delta;
        }
        fprintf(file2, "%d\n", amount);
      }
    }
    if (!found) {
        if (delta < 0) {
          printf("There isn't enought blood, can't perform that!");
        }
        else {
          fprintf(file2, "%s\n%d\n", type, delta);
        }
    }
  }
  fclose(file1);
  fclose(file2);
  rename("bloodtype2.txt", "bloodtype.txt"); 
}

// zeina
void track_baby_incubators() {
  headMessage("TRACK BABY INCUBATORS");
  int count = 0;
  FILE* file = fopen("patients_info.txt", "r");
  if (file == 0) {
      printf("Unable to open file\n");
  } else {
    patient holder;
    while(!feof(file)) {
      holder = extract_from_file(file); // get next patient
      if (strcmp(holder.patient_type, "newborn") == 0) { // check if its type is newborn
        count++;
        print_patient_data(holder);    
      }
    }
    printf("Available Incubators: %d\n", MAX_CAPACITY_INCUBATORS - count);
  }
  fclose(file);
}

//hamed
void hospital_capacity() {
  char buffer[50];
  headMessage("HOSPITAL CAPACITY");
  char dep[30][30];
  int cnt[30], idx = 0;
  FILE* file = fopen("patients_info.txt", "r");
  if (file == NULL) {
    printf("No patients yet!\n");
    fclose(file);
    return;
  }
  int line_number = 0;
  while (fgets(buffer, 40, file)) {
    if (line_number % 11 == 10) { // check for the line holding the depeartment
      remove_trialing_endl(buffer); 
      bool found = 0;
      // check if that department already exists
      for (int i = 0; i < idx; ++i) {
        if (strcmp(buffer, dep[i]) == 0) {
          cnt[i]++;
          found = 1;
          break;
        }
      }
      // if deperatment not found -> add it
      if (!found) {
        strcpy(dep[idx], buffer);
        cnt[idx++] = 1;
      }
    }
    line_number++;
  }
  printf("Department\tNumber of Patients\n");
  for (int i = 0; i < idx; ++i) {
    printf("%s\t\t%d\n", dep[i], cnt[i]);
  }
  fclose(file);
}

// engy
void add_patient_file(patient to_add) {
  // save data to file
  FILE* patients_file =  fopen("patients_info.txt", "a");
  fprintf(patients_file, "%s\n", to_add.id);
  fprintf(patients_file, "%s\n", to_add.name);
  fprintf(patients_file, "%s\n", to_add.age);
  fprintf(patients_file, "%s\n", to_add.patient_type);
  fprintf(patients_file, "%s\n", to_add.address);
  fprintf(patients_file, "%s\n", to_add.gender);
  fprintf(patients_file, "%s\n", to_add.blood_type);
  fprintf(patients_file, "%s\n", to_add.disease);
  fprintf(patients_file, "%s\n", to_add.specialist_room_no);
  fprintf(patients_file, "%s\n", to_add.fam_contact);
  fprintf(patients_file, "%s\n", to_add.department);
  fclose(patients_file);
}

// engy
void add_patient() {
  // take data for new user
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
  printf("Enter patient's department: \n");
  fgets(new_patient.department, 30, stdin);
  remove_trialing_endl(new_patient.department);
  fflush(stdin);
  add_patient_file(new_patient);
}

// zeina
patient extract(char* id) {
  patient extracted_patient;
  FILE* file = fopen("patients_info.txt", "r");
  while (!feof(file)) {
    extracted_patient = extract_from_file(file);
    if (strcmp(extracted_patient.id, id) == 0) return extracted_patient;
  }
  fclose(file);
  extracted_patient.exist = false;
  return extracted_patient;
}

// engy
void list_patient_id(char* id) {
  patient extracted_patient;
  extracted_patient = extract(id); // get the data of the user with the given id
  if (!extracted_patient.exist) {
    printf("No such patient exists...\n");
    return;
  }
  print_patient_data(extracted_patient);
}

// hamed
void delete_patient_id(char* id, bool show_message) {
  char buffer[50];
  FILE* f1 = fopen("patients_info.txt", "r");
  FILE* f2 = fopen("patients_info2.txt", "w");
  if (f1 == NULL || f2 == NULL) {
    printf("Couldn't open file");
    fclose(f1);
    fclose(f2);
    return;
  }
  int line_number = 0;
  bool found = 0;
  while (fgets(buffer, 50, f1)) {
    if (line_number % 11 == 0) {
      remove_trialing_endl(buffer);
      if (strcmp(buffer, id) == 0) {
        found = 1;
        for (int i = 0; i < 10; ++i) fgets(buffer, 50, f1);
        continue;
      }
      else fprintf(f2, "%s\n", buffer);
    }
    else fprintf(f2, "%s", buffer);
    line_number++;
  }
  if (show_message) {
    if (!found) printf("Patient with the given ID wasn't found...\n");
    else printf("Patient with the ID '%s' was deleted successfully\n", id);
  }
  fclose(f1);
  fclose(f2);
  rename("patients_info2.txt", "patients_info.txt"); 
}

// zeina
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
  list_patient_id(id); // print the patient data before
  // print the choices to edit
  for (int i = 1; i <= 10; ++i)
    printf("\t\t\t%d) %s\n", i, PATIENT_HEADERS[i]);
  printf("---- Press zero to discard ----");
  int choice;
  scanf("%d", &choice);
  if (!choice) return;
  if (0 < choice && choice <= 10) {
    printf("Enter the new '%s':\n", PATIENT_HEADERS[choice]);
    fflush(stdin);
    fgets(buffer, 40, stdin);
    remove_trialing_endl(buffer);
  }
  delete_patient_id(id, false);
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
    case 10:
      strcpy(extracted_patient.department, buffer);
      break;
    case 0:
      break;
    default:
      printf("Invalid choice!");
  }
  add_patient_file(extracted_patient);
  fclose(file);
}

// hamed
void edit_patient() {
  char* id = get_id("EDIT PATIENT DATA");
  edit_patient_id(id);
  free(id);
}

// hamed
void list_patient() {
  char* id = get_id("VIEW PATIENT DETAILS");
  list_patient_id(id);
  free(id);
}

// hamed
void delete_patient() {
  char* id = get_id("DELETE PATIENT DATA");
  delete_patient_id(id, true);
  free(id);
}

// shahd
void list_all() {
  patient holder;
  FILE* file = fopen("patients_info.txt", "r");
  if (file == NULL) {
    printf("No data available!");
  } else {
    while (!feof(file)) {
      holder = extract_from_file(file); // get next patient
      print_patient_data(holder);
    } 
  }
  fclose(file);
}

int main() {
  //main appearance menu
  int choice; 
  do{
      headMessage("HOSPITAL MANAGEMENT SYSTEM");
      printf("\t\t\t1) List all patients\n");
      printf("\t\t\t2) Track intensive care\n");
      printf("\t\t\t3) Track newborn babies\n");
      printf("\t\t\t4) Check which patients occupy what department\n");
      printf("\t\t\t5) Check quantity of a blood type\n");
      printf("\t\t\t6) Add a new patient record\n");
      printf("\t\t\t7) Change blood amount\n");
      printf("\t\t\t8) Edit existing patient record\n");
      printf("\t\t\t9) Show patient list and info\n");
      printf("\033[0;31m");
      printf("\t\t\t10) Delete a patient record\n");
      printf("\033[0m");
      printf("---- Press zero to exit ----");
      fflush(stdin);
      scanf("%d", &choice);
      fflush(stdin);
      switch (choice) {
        case 1: 
          list_all();
          break;
        case 2: 
          track_intensive_care();
          break;
        case 3:
          track_baby_incubators();
          break;
        case 4:
          hospital_capacity();
          break;
        case 5:
          track_blood_types();
          break;
        case 6:
          add_patient();
          break;
        case 7:
          change_blood();
          break;
        case 8:
          edit_patient();
          break;
        case 9:
          list_patient();
          break;
        case 10:
          delete_patient();
          break;
        case 0:
          printf("You are now exiting the menu...\n");
          fflush(stdout);
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
