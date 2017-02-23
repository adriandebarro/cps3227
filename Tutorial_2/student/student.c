#include <stdio.h>
#include <stdlib.h>
#include "student.h"

StudentNode* CreateStudent(int age, char* name, float grade, enum Level level)
{
    StudentNode* tempStudent = malloc(sizeof(StudentNode));
    tempStudent->Age = age;
    tempStudent->Name = name;
    tempStudent->Grade = grade;
    tempStudent->StudentLevel = level;
    tempStudent->Next = NULL;
    tempStudent->Prev = NULL;
    return tempStudent;
}

void UpdateStudent(StudentNode* currentStudent,int age, char* name, float grade, enum Level level)
{
    currentStudent->Age = age;
    currentStudent->Name = name;
    currentStudent->Grade = grade;
    currentStudent->StudentLevel = level;
}