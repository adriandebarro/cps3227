#pragma once

#include <stdbool.h>
#include <stdio.h>

enum Level
{
	GRADE_1,
	GRADE_2,
	GRADE_3,
	GRADE_4,
	GRADE_5
};

typedef enum Level Level;

typedef struct StudentNode StudentNode;

struct StudentNode
{
	int age;
	char *name;
	float grade;
	Level level;
	StudentNode *next;
	StudentNode *prev;
};

StudentNode *CreateStudent(int age, char *name, float grade, Level level);
void DeleteStudent(StudentNode *student);

bool UpdateStudent(StudentNode *student, int age, char *name, float grade, Level level);
