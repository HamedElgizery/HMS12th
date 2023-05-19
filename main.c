#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
    char name[100];
    int patient_ID;
    int age;
    char address[100];
    char gender;
    char blood_type[4];
    char disease[100];
    int specialist_roomno;
    int fam_contact[20];

};

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
  puts(generate_id());
  return 0;
}
