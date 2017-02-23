#pragma once
#include <stdio.h>

enum Level
{
	GRADE_1 = 0,
	GRADE_2,
	GRADE_3,
	GRADE_4,
	GRADE_5
};

typedef struct StudentNode StudentNode;

struct StudentNode
{
	int Age;
	char* Name;
	float Grade;
	enum Level StudentLevel;
	StudentNode* Next;
	StudentNode* Prev;
};

StudentNode* CreateStudent(int age, char* name, float grade, enum Level level);
void UpdateStudent(StudentNode* currentStudent,int age, char* name, float grade, enum Level level);


