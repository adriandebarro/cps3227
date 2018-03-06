#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

StudentNode *CreateStudent(int age, char* name, float grade, Level level)
{
    assert(name);

    StudentNode *newStudent = malloc(sizeof(StudentNode));
    if (!newStudent)
        return NULL;

    newStudent->age = age;

    newStudent->name = malloc(sizeof(char) * (strlen(name) + 1));
    if (!newStudent->name)
    {
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->name, name);

    newStudent->grade = grade;
    newStudent->level = level;
    newStudent->next = NULL;
    newStudent->prev = NULL;

    return newStudent;
}

void DeleteStudent(StudentNode *student)
{
    assert(student);

    free(student->name);
    free(student);
}

bool UpdateStudent(StudentNode *student, int age, char *name, float grade, Level level)
{
    assert(student);
    assert(name);

    int nameLen = (int)strlen(name);
    if (strlen(student->name) != nameLen)
    {
        free(student->name);
        student->name = malloc(sizeof(char) * (nameLen + 1));
        if (!student->name)
            return false;
    }

    student->age = age;
    strcpy(student->name, name);
    student->grade = grade;
    student->level = level;

    return true;
}
