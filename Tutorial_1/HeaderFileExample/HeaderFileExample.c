#include <stdio.h>

#include "StudentManager.h"

int main(void)
{
    student currentStudent = CreateStudent(15, 10, "Test", 4);
    ToString(&currentStudent);
    return 0;
}