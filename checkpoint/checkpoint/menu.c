
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "school.h"

enum menu_inputs {
    Insert = '0',
    Delete = '1',
    Edit = '2',
    Search = '3',
    Showall = '4',
    Top10 = '5',
    UnderperformedStudents = '6',
    Average = '7',
    Export = '8',
    Exit = '9'
};


void insertNewStudent(struct School* school)
{
    int level;
    int _class;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int phoneNumber;

     
        printf("Enter level (1 to %d) to add a student : ", NUM_LEVELS );
        scanf("%d", &level);
        level = level - 1;
 
        printf("Enter class (1 to %d) to add a student : ", NUM_CLASSES );
        scanf("%d", &_class);

        _class = _class - 1;
        if (_class < 0 || _class >= NUM_CLASSES) {
            printf("Invalid class");
            return;
        }

        printf("Enter student first name: ");
        scanf(" %s", firstName);  

        printf("Enter student last name: ");
        scanf(" %s", lastName); // Read last name with spaces

        printf("Enter student phone number: ");
        scanf("%d", &phoneNumber);  

        struct NodeStudent* student =  createNodeStudent(firstName, lastName, level, _class, phoneNumber);

          
        insertStudentToSchool(school, student);

}

void deleteStudent(struct School* school)
{
    int phoneNumber;
    printf("Enter student phone number: ");
    scanf("%d", &phoneNumber);

    

    deleteStudentByPhoneNumber(school, phoneNumber);
}


void editStudentGrade(struct School* school) {
    int phoneNumber;
    int examNum;
    int newGrade;

    printf("Enter student phone number :");
    scanf("%d", &phoneNumber);

    printf("Enter student exam number 0<=<%d:  ", NUM_SCORES);
    scanf("%d", &examNum);

    printf("Enter student new grade 0<=<%d:  ", MAX_GRADE);
    scanf("%d", &newGrade);

    editStudentGradeInSchool(school, phoneNumber, examNum, newGrade);
}
printTopNStudentsPerCourse(struct School* school)
{
    int course;
    printf("Enter courseclass (1 to %d)   : ", NUM_SCORES);
    scanf("%d", &course);
      course = course - 1;


      if (course < 0 || course >= NUM_SCORES)
      {
          printf(" incalide course " );
          return;
      }
   

    
      printTopNInSchoole(school, 10, course);
}
void searchStudent(struct School* school)
{
    int phoneNumber;
    printf("Enter student phone number :");
    scanf("%d", &phoneNumber);

    printStudentByPhone(&school, phoneNumber);
}

void menu() {
    char input;

    

    struct School school = createEmptySchool();

    const char* filename = "students_with_class.txt";
    processFile(filename, &school);
    strcpy(school.name, "lev");

    do {
        printf("\n|School Manager<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);
        printf("\t[0] |--> Insert\n");
        printf("\t[1] |--> Delete\n");
        printf("\t[2] |--> Edit\n");
        printf("\t[3] |--> Search\n");
        printf("\t[4] |--> Show All\n");
        printf("\t[5] |--> Top 10 students per course\n");
        printf("\t[6] |--> Underperformed students\n");
        printf("\t[7] |--> Average per course\n");
        printf("\t[8] |--> Export\n");
        printf("\t[9] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (0-9): ");
        input = getc(stdin);
        fflush(stdin);
        getc(stdin);
        switch (input) {
        case Insert:
            insertNewStudent(&school);
            break;
        case Delete:
            deleteStudent(&school);
            break;
        case Edit:
            editStudentGrade(&school);
            break;
        case Search:
            searchStudent(&school);
            break;
        case Showall:
            printSchool(&school);
            break;
        case Top10:
            printTopNStudentsPerCourse(&school);
            break;
        case UnderperformedStudents:
            //printUnderperformedStudents();
            break;
        case Average:
            //printAverage();
            break;
        case Export:
            //exportDatabase();
            break;
        case Exit:
            deleteAllStudents(&school);
            return;
        default:
            printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...",
                input);
            getc(stdin);
            getc(stdin);
            break;
        }

    } while (input != Exit);


}

void test()
{
    struct School school = createEmptySchool();

    struct NodeStudent* student1 = createNodeStudent("d1", "gh", 1, 5, 123);
    struct NodeStudent* student2 = createNodeStudent("d1", "gh", 1, 5, 8002);
    struct NodeStudent* student3 = createNodeStudent("d1", "gh", 1, 5, 4);
    struct NodeStudent* student4 = createNodeStudent("d1", "gh", 1, 5, 8);
    struct NodeStudent* student5 = createNodeStudent("d1", "gh", 1, 5, 9);
    struct NodeStudent* student6 = createNodeStudent("d1", "gh", 1, 5, 85);


    insertStudentToSchool(&school, student1);
    insertStudentToSchool(&school, student2);
    insertStudentToSchool(&school, student3);
    insertStudentToSchool(&school, student4);
    insertStudentToSchool(&school, student5);
    insertStudentToSchool(&school, student6);

    student1->student->scores[2] = 101;
    student2->student->scores[2] = 7;
    student3->student->scores[2] = 78;
    student4->student->scores[2] = 46;
    student5->student->scores[2] = 125;
    student6->student->scores[2] = 100;

    

    printTopNInSchoole(&school, 3, 2);
}


int main() {
    menu();

   // test();
    return 0;
}


