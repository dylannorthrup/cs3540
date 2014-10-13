#include "student.h"

int main () {
	student* s = create_student ("Student Test", "123456789", 0.01);
	display_student(s);
	destroy_student(s);
	return 0;
}