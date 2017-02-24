#pragma once

#include <stdio.h>
#include "./student.h"

typedef struct StudentCollection
{
	StudentNode* Head;
	int Total;	
}
StudentCollection;

StudentCollection* InitStudentCollection();
int Insert(StudentNode* currentStudent,StudentCollection* coll);
int InsertAtIndex(StudentNode* currentStudent, int index,StudentCollection* coll);
int ModifyAtIndex(int index, int age, char* name, float grade, enum Level level,StudentCollection* coll);
int DeleteAtIndex(int index,StudentCollection* coll);
void DeleteAll(StudentCollection* coll);
void PrettyPrint(StudentCollection* coll);
int DumpToFile(StudentCollection* coll);
int PopulateFromFile(StudentCollection* coll);

