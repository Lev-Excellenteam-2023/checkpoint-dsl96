 
#ifndef SCHOOL_H
#define SCHOOL_H

#define MAX_SCHOOL_NAME 30
#define MAX_NAME_LENGTH 30
#define NUM_LEVELS  12
#define NUM_CLASSES 10
#define NUM_SCORES 10
#define MAX_GRADE 100

struct Student {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    int level;
    int _class;
    int phone_number;
    int scores[NUM_SCORES];
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
    char name[MAX_SCHOOL_NAME];
    int numOfStudents;

};


void printSchool(struct School* school);
void insertStudentToSchool(struct School* school, struct NodeStudent* nodeStudent);
struct NodeStudent* createNodeStudent(const char* first_name, const char* last_name, int level, int _class, int phone_number);
struct School createEmptySchool();
void deleteAllStudents(struct School* school);
void deleteStudentByPhoneNumber(struct School* school, int phone_number);
void editStudentGradeInSchool(struct School* school, int phone_number, int exam_number, int new_grade);
void printStudentByPhone(struct School* school, int phoneNumber);
struct Student* searchStudentInScool(struct School* school, int phoneNumber);
void pirntTopNInSchoole(struct School* school, int N, int course);
#endif  
