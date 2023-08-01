#define _CRT_SECURE_NO_WARNINGS
#include "school.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>

struct Student* createStudent(const char* first_name, const char* last_name, int level, int _class, int phone_number) {
	struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));

	if (newStudent == NULL) {
		printf("Memory allocation error\n");
		return NULL;
	}

	//TODO add len validation
	strncpy(newStudent->first_name, first_name, MAX_NAME_LENGTH - 1);
	newStudent->first_name[MAX_NAME_LENGTH - 1] = '\0';

	strncpy(newStudent->last_name, last_name, MAX_NAME_LENGTH - 1);
	newStudent->last_name[MAX_NAME_LENGTH - 1] = '\0';

	newStudent->level = level;
	newStudent->_class = _class;
	newStudent->phone_number = phone_number;


	for (int i = 0; i < 12; i++) {
		newStudent->scores[i] = 0;
	}

	return newStudent;
}
struct NodeStudent* createNodeStudent(const char* first_name, const char* last_name, int level, int _class, int phone_number) {
	struct NodeStudent* newNode = (struct NodeStudent*)malloc(sizeof(struct NodeStudent));

	if (newNode == NULL) {
		printf("Memory allocation error\n");
		return NULL;
	}


	newNode->student = createStudent(first_name, last_name, level, _class, phone_number);
	newNode->next = NULL;
	if (newNode->student == NULL) {
		free(newNode);
		printf("Memory allocation error\n");
		return NULL;
	}
	return newNode;
}



struct School createEmptySchool() {
	struct School newSchool;

	for (int i = 0; i < NUM_LEVELS; i++) {
		for (int j = 0; j < NUM_CLASSES; j++) {
			newSchool.levels[i].classes[j].students = NULL;
		}
	}

	newSchool.numOfStudents = 0;

	strcpy(newSchool.name, "");

	return newSchool;
};


void insertStudentToSchool(struct School* school, struct NodeStudent* newStudentNode) {
	if (school == NULL || newStudentNode == NULL) {
		printf("Invalid input: school or newStudentNode is NULL\n");
		return;
	}

	int level = newStudentNode->student->level;
	int _class = newStudentNode->student->_class;

	if (level <= 0 || level > NUM_LEVELS || _class <= 0 || _class > NUM_CLASSES) {
		printf("Invalid input: level or class is out of range\n");
		return;
	}

	struct NodeStudent** currentStudentPtr = &school->levels[level - 1].classes[_class - 1].students;

	if (currentStudentPtr == NULL)
		*currentStudentPtr = newStudentNode;

	else
	{
		newStudentNode->next = *currentStudentPtr;
		*currentStudentPtr = newStudentNode;
	}

	school->numOfStudents = school->numOfStudents + 1;
	return;
}

void printStudent(struct Student* student) {
	printf("Name: %s %s\n", student->first_name, student->last_name);
	printf("Level: %d\n", student->level);
	printf("Class: %d\n", student->_class);
	printf("Phone Number: %d\n", student->phone_number);
	printf("Scores: ");
	for (int i = 0; i < 12; i++) {
		printf("%d ", student->scores[i]);
	}
	printf("\n\n");
}

void printSchool(struct School* school) {
	for (int level = 0; level < NUM_LEVELS; level++) {
		printf("Level %d:\n", level + 1);

		for (int class = 0; class < NUM_CLASSES; class++) {
			printf("\tClass %d:\n", class + 1);

			struct NodeStudent* currentStudent = school->levels[level].classes[class].students;
			while (currentStudent != NULL) {
				printStudent(currentStudent->student);
				currentStudent = currentStudent->next;
			}
		}
	}
}

void freeNodeStudent(struct NodeStudent* node) {
	if (node != NULL) {
		free(node->student);
		free(node);
	}
}

void deleteAllStudents(struct School* school) {
	if (school == NULL) {
		printf("Invalid input: school is NULL\n");
		return;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;
			while (currentStudentNode != NULL) {
				struct NodeStudent* nextStudentNode = currentStudentNode->next;
				freeNodeStudent(currentStudentNode);
				currentStudentNode = nextStudentNode;
			}
			school->levels[level].classes[_class].students = NULL;
		}
	}
}

void deleteStudentByPhoneNumber(struct School* school, int phone_number) {
	if (school == NULL) {
		printf("Invalid input: school is NULL\n");
		return;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;
			struct NodeStudent* prevStudentNode = NULL;

			while (currentStudentNode != NULL) {
				if (currentStudentNode->student->phone_number == phone_number) {
					school->numOfStudents = school->numOfStudents - 1;

					if (prevStudentNode == NULL) {
						// If the student is the first node in the list
						school->levels[level].classes[_class].students = currentStudentNode->next;
					}
					else {
						prevStudentNode->next = currentStudentNode->next;
					};

					printf("Student with phone number %d deleted from the school.\n", phone_number);
					printStudent(currentStudentNode->student);
					freeNodeStudent(currentStudentNode);

					return;
				}

				prevStudentNode = currentStudentNode;
				currentStudentNode = currentStudentNode->next;
			}
		}
	}

	printf("Student with phone number %d not found in the school.\n", phone_number);
}


void editStudentGradeInSchool(struct School* school, int phone_number, int exam_number, int new_grade) {
	if (school == NULL) {
		printf("Invalid input: school is NULL\n");
		return;
	}

	if (NUM_SCORES <= exam_number || exam_number < 0) {
		printf("Invalid exam_number \n");
		return;
	}

	if (MAX_GRADE < new_grade|| exam_number < 0) {
		printf("Invalid exam grade \n");
		return;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;

			while (currentStudentNode != NULL) {
				if (currentStudentNode->student->phone_number == phone_number) {

					currentStudentNode->student->scores[exam_number - 1] = new_grade;
					printStudent(currentStudentNode->student);
					return;
				}

				currentStudentNode = currentStudentNode->next;
			}
		}
	}

	printf("Student with phone number %d not found in the school.\n", phone_number);
}


struct Student* searchStudentInScool(struct School* school , int phoneNumber) {
	if (school == NULL) {
		printf("Invalid input: school is NULL\n");
		return NULL;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;

			while (currentStudentNode != NULL) {
				if ( currentStudentNode->student->phone_number == phoneNumber) {
					 
					return currentStudentNode->student;
				}

				currentStudentNode = currentStudentNode->next;
			}
		}
	}

	return NULL;
}

void printStudentByPhone(struct School* school, int phoneNumber)
{
	struct Student* student = searchStudentInScool(school, phoneNumber);
	printStudent(student);
}







