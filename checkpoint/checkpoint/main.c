#include <stdio.h>
#include"fileReader.h"
#include"school.h"


int main() {
	const char* filename = "students_with_class.txt";
	 
	struct School school = createEmptySchool();

	processFile(filename, &school);
 
	pirntTopNInSchoole(&school, 10, 0);

	deleteAllStudents(&school);

	return 0;
}


