#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

StudentNode* CreateStudent(int age, char* name, int size, float grade, enum Level level)
{
    printf("Creating student %s \n", name);
    StudentNode* tempStudent = malloc(sizeof(StudentNode));
    printf("second step \n");
    tempStudent->Age = age;
    tempStudent->Name = malloc(sizeof(char)*size);
    printf("%s \n", name);
    strcpy(tempStudent->Name, name);
    tempStudent->Grade = grade;
    tempStudent->StudentLevel = level;
    tempStudent->Next = NULL;
    tempStudent->Prev = NULL;
    return tempStudent;
}

void UpdateStudent(StudentNode* currentStudent,int age, char* name, float grade, enum Level level)
{
    currentStudent->Age = age;
    strcpy(currentStudent->Name, name);
    currentStudent->Grade = grade;
    currentStudent->StudentLevel = level;
}