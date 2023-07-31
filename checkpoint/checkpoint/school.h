#ifndef SCHOOL_H
#define SCHOOL_H

#define MAX_NAME_LENGTH 50
#define NUM_LEVELS  12
#define NUM_CLASSES 10

struct Student {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    int level;
    int _class;
    int phone_number;
    int scores[12];
};

struct NodeStudent {
    struct Student* student;
    struct NodeStudent* next;
};

struct Class {
    struct NodeStudent* students;
};

struct Level
{
    struct Class classes[NUM_CLASSES];
};

struct School
{
    struct Level levels[NUM_LEVELS];
};


void printSchool(struct School* school);
void insertStudentToSchool(struct School* school, struct NodeStudent* nodeStudent);
struct NodeStudent* createNodeStudent(const char* first_name, const char* last_name, int level, int _class, int phone_number);
struct School createEmptySchool();
void deleteAllStudents(struct School* school);

#endif  
