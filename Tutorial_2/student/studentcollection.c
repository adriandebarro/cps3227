#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studentcollection.h"

#define FILE_NAME "students.lst"

// function for creating a student collection
StudentCollection *InitStudentCollection()
{
    // allocates a space in the heap for the student collection
    StudentCollection *pCollection = malloc(sizeof(StudentCollection));
    if (!pCollection)
        return NULL;

    pCollection->head = NULL;
    pCollection->total = 0;

    return pCollection;
}

// function that takes the student details and student collection as argument
int Insert(StudentNode *currentStudent, StudentCollection *coll)
{
    // check if we already have an element in the list
    if (!coll->head)
    {
        coll->head = currentStudent;
        coll->total++;
        return 1;
    }
    else
    {
        // if an element already exists, find the last element and append the new element to the tail of the list

        StudentNode *tempStudent = coll->head;

        while(tempStudent->next != NULL)
            tempStudent = tempStudent->next;
        tempStudent->next = currentStudent;
        currentStudent->prev = tempStudent;
        coll->total++;
        return 0;
    }
}

// Doubly Linked List
// ----------------

//          head
//           |
//           |
//  +------+-----+--+    +--+-----+--+       +-----+------+
//  |      |     |o------>  |     |o------>  |     |      |
//  | NULL |  1  |          |  2  |          |  3  | NULL |
//  |      |     |  <------o|     |  <------o|     |      |
//  +------+-----+--+    +--+-----+--+       +-----+------+
//
// https://github.com/freeCodeCamp/freeCodeCamp/wiki/Data-Structure-Linked-Lists

int InsertAtIndex(StudentNode *currentStudent, int index, StudentCollection *coll)
{
    StudentNode *prevStudent = NULL;

    //check if the index argument is in range
    if (index >= 0 && index < coll->total)
    {
        StudentNode *tempStudent = coll->head;
        // find the index entry point
        for (int i = 0; i < index; i++)
        {
            if (tempStudent)
                tempStudent = tempStudent->next;
            else
                break;
        }

        // set the current element as Previous node
        prevStudent = tempStudent->prev;
        tempStudent->prev = currentStudent;
        currentStudent->next = tempStudent;

        // check if we are in the first node
        if (prevStudent)
        {
            prevStudent->next = currentStudent;
            currentStudent->prev = prevStudent;
        }
        else
        {
            // if yes set the element as the head of the list
            coll->head = currentStudent;
        }
        coll->total++;
        return 1;
    }
    else
    {
  	    return 0;
    }
}

int ModifyAtIndex(int index, int age, char *name, float grade, Level level, StudentCollection *coll)
{
    StudentNode *tempStudent = NULL;

    if (index >= 0 && index <= coll->total)
    {
        tempStudent = coll->head;

        for (int i = 0; i <= index - 1; i++)
        {
            if (tempStudent)
                tempStudent = tempStudent->next;
            else
                break;
        }

        UpdateStudent(tempStudent, age, name, grade, level);
        return 1;
    }
    else
    {
        return 0;
    }
}

int DeleteAtIndex(int index, StudentCollection *coll)
{
    StudentNode* tempStudent = coll->head;
    StudentNode* nextStudent = NULL;
    StudentNode* prevStudent = NULL;

    if (index >= 0 && index < coll->total)
    {
        for (int i = 0; i <= index - 1; i++)
        {
            if (!tempStudent->next)
                return 0;
            tempStudent = tempStudent->next;
        }

        nextStudent = tempStudent->next;
        prevStudent = tempStudent->prev;

        if (prevStudent)
        {
            // if a center node, link to previous to the next node
            prevStudent->next = nextStudent;
        }
        else
        {
            // then node is the head node
            coll->head = tempStudent->next;
        }

        if (nextStudent)
            nextStudent->prev = prevStudent;

        DeleteStudent(tempStudent);
        coll->total -= 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

void DeleteAll(StudentCollection *coll)
{
	StudentNode *currentStudent = coll->head;
	StudentNode *nextStudent = NULL;
	
	while(currentStudent)
	{
        nextStudent = currentStudent->next;
		DeleteStudent(currentStudent);
		currentStudent = nextStudent;
	}

	coll->total = 0;
	coll->head = NULL;

}

void PrettyPrint(StudentCollection *coll)
{
    printf("Doubly linked list collection with a total of %d\n", coll->total);

    if (coll->total == 0)
    {
        printf("Linked list is empty\n");
        return;
    }
    else
    {
        StudentNode *tempStudent = coll->head;
        while(tempStudent)
        {
            printf(" Student %s is %d years old and his current grade is %.2f at level %d\n", tempStudent->name,
                tempStudent->age, tempStudent->grade, tempStudent->level);
            tempStudent = tempStudent->next;
        }
    }
}

int DumpToFile(StudentCollection *coll)
{
    StudentNode *currentStudent = coll->head;
    FILE *fp = fopen(FILE_NAME, "w");

    //check that file was opened successfully
    if (fp)
    {
        while(currentStudent)
        {
            fprintf(fp, "%d,%s,%lf,%d \n", currentStudent->age,  currentStudent->name, currentStudent->grade,
                currentStudent->level);
            currentStudent = currentStudent->next;
        }
    }

    return 0;
}

int GetLine(FILE *fp, char *buffer)
{
    char currentChar;
    int bufferIndex = 0;

    while((currentChar = (char)fgetc(fp)) != '\n')
    {
        if(currentChar == EOF)
            return 1;
        buffer[bufferIndex] = currentChar;
        bufferIndex++;
    }

    return 0;
}

void GetStudentDetails(int *age, char *name, int *grade, Level *level, char *line)
{
    char *token;

    token = strtok(line, ",");
    *age = atoi(token);
    token = strtok(NULL, ",");
    strcpy(name, token);
    token = strtok(NULL, ",");
    *grade = atoi(token);
    token = strtok(NULL, ",");
    *level = atoi(token);
}

int PopulateFromFile(StudentCollection *coll)
{
    char buffer[1024];
    char tempName[200];
    int age = 0;
    Level level;
    int grade = 0;
    StudentNode *newStudent = NULL;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp)
    {
        while (GetLine(fp, &buffer[0]) != 1)
        {
            GetStudentDetails(&age, &tempName[0], &grade, &level, &buffer[0]);
            newStudent = CreateStudent(age, tempName, grade, level);
            Insert(newStudent, coll);
        }
    }

    return 0;
}
