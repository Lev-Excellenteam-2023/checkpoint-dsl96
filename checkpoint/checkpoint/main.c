#include <stdio.h>
#include"fileReader.h"
#include"school.h"

int main() {
	const char* filename = "students_with_class.txt";
	 
	struct School school = createEmptySchool();

	processFile(filename, &school);
	printSchool(&school);

	deleteAllStudents(&school);

	return 0;
}

