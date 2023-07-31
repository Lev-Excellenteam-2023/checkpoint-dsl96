#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_LENGTH 50

 
struct Student {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char phone_number[11];
    int scores[12];  
};

struct NodeStudent {
    struct Student* student;
    struct NodeStudent* next;
};

struct NodeStudent* createNodeStudent() {
    struct NodeStudent* newNode = (struct NodeStudent*)malloc(sizeof(struct NodeStudent));
    newNode->next = NULL;
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }

    newNode->student = (struct Student*)malloc(sizeof(struct Student));
    if (newNode->student == NULL) {
        free(newNode); 
        printf("Memory allocation error\n");
        return NULL;
    }

    return newNode;
}

void processFile(const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[256]; // Adjust buffer size accordingly
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        struct  NodeStudent* nodeStudent = createNodeStudent();

       
        int parsed_items = sscanf(line, "%s %s %llu %d %d %d %d %d %d %d %d %d %d %d %d",
            &nodeStudent->student->first_name, &nodeStudent->student->last_name, &nodeStudent->student->phone_number,
            &nodeStudent->student->scores[0], &nodeStudent->student->scores[1], &nodeStudent->student->scores[2],
            &nodeStudent->student->scores[3], &nodeStudent->student->scores[4], &nodeStudent->student->scores[5],
            &nodeStudent->student->scores[6], &nodeStudent->student->scores[7], &nodeStudent->student->scores[8],
            &nodeStudent->student->scores[9], &nodeStudent->student->scores[10], &nodeStudent->student->scores[11]);

        if (parsed_items != 15) {
            printf("Error: Invalid line format on line %d\n", line_count + 1);
            fclose(file);
            return;
        }

        // Do something with the struct instance, e.g., store it in an array or process the data

        printf("Line %d: %s %s %llu", line_count + 1, nodeStudent->student->first_name, nodeStudent->student->last_name, nodeStudent->student->phone_number);
        for (int i = 0; i < 12; i++) {
            printf(" %d", nodeStudent->student->scores[i]);
        }
        printf("\n");

        line_count++;
    }

    fclose(file);

}

