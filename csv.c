#include <stdio.h>
#include <stdlib.h>
#include <csv.h>
#include <unistd.h>

int main() {
    FILE *file;
    char filename[] = "patient_info.csv";
    int exists = 0;

    // Check if file exists
    if (access(filename, F_OK) != -1) {
        printf("File already exists\n");
        exists = 1;
    }

    // Open CSV file for writing
    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error creating file\n");
        return 1;
    }
    csv_init_file(&file, ',');

    if (!exists) {
        // Write CSV header
        const char * header[] = {"Name", "Service type", "Age", "Address","Sex","Disease description", "Specialist room number", "Family contacts"};
        csv_fwrite(file, header, 8);
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