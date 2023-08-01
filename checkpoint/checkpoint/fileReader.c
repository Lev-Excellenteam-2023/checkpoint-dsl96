#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "school.h"
 
void processFile(const char* filename, struct School* school) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256];  
  
    while (fgets(line, sizeof(line), file)) {
        struct  NodeStudent* nodeStudent = createNodeStudent("", "", 0, 0, 0);

       
        int parsed_items = sscanf(line, "%s %s %d %d %d %d %d %d %d %d %d %d %d %d %d",
            &nodeStudent->student->first_name, &nodeStudent->student->last_name, &nodeStudent->student->phone_number,
            &nodeStudent->student->level, &nodeStudent->student->_class, &nodeStudent->student->scores[0],
            &nodeStudent->student->scores[1], &nodeStudent->student->scores[2], &nodeStudent->student->scores[3],
            &nodeStudent->student->scores[4], &nodeStudent->student->scores[5], &nodeStudent->student->scores[6],
            &nodeStudent->student->scores[7], &nodeStudent->student->scores[8], &nodeStudent->student->scores[9]);
 
        
        insertStudentToSchool(school, nodeStudent);    

    }

    fclose(file);
}

