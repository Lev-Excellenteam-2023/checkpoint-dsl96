#define _CRT_SECURE_NO_WARNINGS
#include "school.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>

float calculateAverage(struct Student* student) {
	int sum = 0;
	for (int i = 0; i < NUM_SCORES; i++) {
		sum += student->scores[i];
	}

	return (float)sum / NUM_SCORES;
}

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
	newStudent->avg = 0;


	for (int i = 0; i < NUM_SCORES; i++) {
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

	for (int i = 0; i < NUM_LEVELS; ++i) {
		for (int j = 0; j < NUM_CLASSES; ++j) {
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

	if (level < 0 || level >= NUM_LEVELS || _class < 0 || _class >= NUM_CLASSES) {
		printf("Invalid input: level or class is out of range\n");
		return;
	}

	newStudentNode->student->avg = calculateAverage(newStudentNode->student);
	struct NodeStudent** currentStudentPtr = &school->levels[level].classes[_class].students;

	if (*currentStudentPtr == NULL) {
		newStudentNode->next = NULL;
		*currentStudentPtr = newStudentNode;
		
	}
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
	for (int i = 0; i < NUM_SCORES; i++) {
		printf("%d ", student->scores[i]);
	}
	printf("AVG: %f\n", student->avg);
	printf("\n\n");
}

void printSchool(struct School* school) {
	for (int level = 0; level < NUM_LEVELS; ++level) {
		printf("Level %d:\n", level + 1);

		for (int class = 0; class < NUM_CLASSES; ++class) {
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

	if (MAX_GRADE < new_grade || exam_number < 0) {
		printf("Invalid exam grade \n");
		return;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;

			while (currentStudentNode != NULL) {
				if (currentStudentNode->student->phone_number == phone_number) {

					currentStudentNode->student->scores[exam_number - 1] = new_grade;
					currentStudentNode->student->avg = calculateAverage(currentStudentNode->student);
					printStudent(currentStudentNode->student);
					return;
				}

				currentStudentNode = currentStudentNode->next;
			}
		}
	}

	printf("Student with phone number %d not found in the school.\n", phone_number);
}


struct Student* searchStudentInScool(struct School* school, int phoneNumber) {
	if (school == NULL) {
		printf("Invalid input: school is NULL\n");
		return NULL;
	}

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;

			while (currentStudentNode != NULL) {
				if (currentStudentNode->student->phone_number == phoneNumber) {

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

	if (student == NULL)
		return;

	printStudent(student);
}

int findMinStudentIndex(struct  Student** arr, int size, int course) {
	int minIndex = 0;
	for (int i = 1; i < size; i++) {
		if (arr[i]->scores[course] < arr[minIndex]->scores[course]) {
			minIndex = i;
		}
	}
	return minIndex;
}


void replaceMinStudent(struct Student** arr, int size, struct Student* newStudent, int course) {
	//the func dont delete the deleted student !!!!
	int minIndex = findMinStudentIndex(arr, size, course);

	if (arr[minIndex]->scores[course] < newStudent->scores[course])
		arr[minIndex] = newStudent;
}




void getTopNInLevel(struct Level* level, int N, int course)
{

	if (N < 1 || N>300) {
		printf("Invalid N \n");
		return;
	}
	struct  Student** top_students_array = (struct NodeStudent**)malloc(N * sizeof(struct  Student*));

	struct NodeStudent* head = level->classes[0].students;


	int countClass = 0;
	for (int i = 0; i < N; i++) {
		top_students_array[i] = NULL;
	}

	for (size_t i = 0; i < N; i++)
	{
	

		if (head == NULL)
		{
			countClass = countClass + 1;

			if (countClass >= NUM_CLASSES)
				break;
			i = i - 1;
			head = level->classes[countClass].students;

		}
		else
		{
			top_students_array[i] = head->student;

			head = head->next;
		}
	}



	while (1)
	{
		if (head == NULL)
		{
			countClass = countClass + 1;
			if (countClass >= NUM_CLASSES)
				break;
			head = head = level->classes[countClass].students;
		}
		else
		{
			replaceMinStudent(top_students_array, N, head->student, course);
			head = head->next;
		}
	}

	for (size_t i = 0; i < N; i++)
	{
		if (top_students_array[i] == NULL)
			break;

		printStudent(top_students_array[i]);
	}

	free(top_students_array);
}

void printTopNInSchoole(struct School* school, int N, int course)
{
	if (NUM_SCORES <= course || course < 0) {
		printf("Invalid course number \n");
		return;
	}
	for (size_t i = 0; i < NUM_LEVELS; i++)
	{
		printf("TOP %d in level %i course %d \n", N, i, course);
		getTopNInLevel(&school->levels[i], N, course);
	}
}


void printStudentByAvg(struct School* school, int minAvg)
{

	for (int level = 0; level < NUM_LEVELS; level++) {
		for (int _class = 0; _class < NUM_CLASSES; _class++) {
			struct NodeStudent* currentStudentNode = school->levels[level].classes[_class].students;

			while (currentStudentNode != NULL) {
				if (currentStudentNode->student->avg <= minAvg) {
					printStudent(currentStudentNode->student);
				}

				currentStudentNode = currentStudentNode->next;
			}
		}
	}
}







