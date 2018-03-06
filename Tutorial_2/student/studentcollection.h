#pragma once

#include <stdio.h>
#include "student.h"

typedef struct StudentCollection
{
	StudentNode *head;
	int total;
} StudentCollection;

StudentCollection *InitStudentCollection();

void Insert(StudentNode *currentStudent, StudentCollection *coll);
bool InsertAtIndex(StudentNode *currentStudent, int index, StudentCollection *coll);

bool ModifyAtIndex(int index, int age, char* name, float grade, Level level, StudentCollection *coll);

bool DeleteAtIndex(int index, StudentCollection *coll);
void DeleteAll(StudentCollection *coll);

void PrettyPrint(StudentCollection *coll);

int DumpToFile(StudentCollection *coll);
int PopulateFromFile(StudentCollection *coll);
