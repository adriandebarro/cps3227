#include <stdio.h>

#include "StudentManager.h"

void UpdateStudent(student *p_student, int p_age, int p_index, char* p_name, int p_nameLength)
{
    p_student->age = p_age;
    p_student->id = p_index;
    p_student->name = p_name;
    p_student->length = p_nameLength;
}

student CreateStudent(int p_age, int p_index, char* p_name, int p_nameLength)
{
    student tempStudent;
    tempStudent.age = p_age;
    tempStudent.name = p_name;
    tempStudent.id = p_index;
    tempStudent.length = p_nameLength;

    return tempStudent;
}

void ToString(student *p_student)
{
    printf(" The student: %s is %d years old and his id is %d \n", p_student->name, p_student->age, p_student->id);
}