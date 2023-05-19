#include <stdio.h>
#include <stdlib.h>
#include <csv.h>
#include <unistd.h>
#include <stdbool.h>

char* get_curr_dir() {
  static char cwd[200];
  getcwd(cwd, sizeof(cwd));
  int size = 0;
  while (cwd[size] != '\0') {
    printf("%c", cwd[size]);
    size++;
  }
  printf("%d\n", size);
  cwd[size] = cwd[0];
  cwd[size+1] = '\0'; 
  return cwd;
}


void setup_file(char* filename, char headers[10][20]) {
  FILE *file = fopen(filename, "a");

  // Check if file exists
  bool exist = 0;
  if (access(filename, F_OK) != -1)
    return;
  
  // Open CSV file for writing
  if (file == NULL) {
      printf("Error creating file\n");
      return;
  }
  csv_fwrite(file, headers, sizeof(headers) / sizeof(char*));
}

int main() {
    char filenames[3][20] = {"patient_info.csv", "rooms_info.csv", "blood_amount.csv"};
    char headers[3][10][20] = {
      {"ID", "Name", "ServiceType", "Age", "Address","Sex","DiseaseDescription", "SpecialistRoomNumber", "FamilyContacts"},
      {"ID", "AvailableBeds", "Type"},
      {"BloodType", "Amount(L)"}
    };
    for (int i = 0; i < sizeof(filenames) / sizeof(char*); ++i) {
      setup_file(filenames[i], headers[i]);
    }
    printf("%s", get_curr_dir());
    /*
    csv_init_file(&file, ',');

    if (!exists) {
        // Write CSV header
        const char * header[] = {};
    }

    //Write sample data
    const char * row1[] = {"1", "2", "3"};
    csv_fwrite(file, row1, 3);
    const char * row2[] = {"4", "5", "6"};
    csv_fwrite(file, row2, 3);

    // Close CSV file
    csv_fini(&file, 0, 0, 0);
    fclose(file);

    printf("File created successfully\n");
    */
    return 0;
}




















/*int main(){

    FILE *fpt;

    fpt = fopen("Patient_info.csv", "w+");
    if(fpt == NULL){
        printf("This was an error found in this file.\n");
        printf("Downloading file...");
        
        return 1;
    }
    fprintf(fpt,"Name , Patient type, Service name , Address, Age, Sex, Blood Type, Disease Description, Specialist Room Number ");
    fprintf(fpt,"%s, %d, %s, %s, %d, %d, %s, %s, %d", name , patient_type, service_name , address, age, sex, blood_type, disease_description, spec_room_number);
    //patient type and sex are %d because we will give the user a choice of numbers 
    fclose(fpt);
//////
    fpt = fopen("Free_beds", "w+");
    fprintf(fpt,"")
    fclose(fpt);
//////
    fpt = fopen("Blood_types", "w+");
    fprintf(fpt,"")
    fclose(fpt);
//////

}
*/
