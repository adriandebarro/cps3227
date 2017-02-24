#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./studentcollection.h"

// function for creating a student collection
StudentCollection* InitStudentCollection()
{
    // allocates a space in the heap for the student collection
    StudentCollection* pCollection = malloc(sizeof(StudentCollection));
    pCollection->Head=NULL;
    pCollection->Total = 0;
    return  pCollection;
}

// function that takes the student details and student collection as argument 
int Insert(StudentNode* currentStudent, StudentCollection* coll)
{
    // check if we already have an element in the list
    if (coll->Head==NULL)
    {
        coll->Head=currentStudent;
        coll->Total++;
        return 1;
    }
    // if an element already exists, find the last element and appened the new element to the tail of the list
    else
    {
        StudentNode* tempStudent = coll->Head;

        while(tempStudent->Next != NULL)
        {
            tempStudent=tempStudent->Next;
        }
        tempStudent->Next=currentStudent;
        currentStudent->Prev=tempStudent;
        coll->Total++;
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

int InsertAtIndex(StudentNode* currentStudent, int index, StudentCollection* coll)
{
    int x = 0;
    StudentNode* prevStudent = NULL;
    //check if the index argument is in range
    if ((index >= 0) && (index < coll->Total))
    {
        StudentNode* tempStudent = coll->Head;
	// find the index entry point
        for (x = 0; x<index; x++)
        {
            if(tempStudent != NULL)
                tempStudent = tempStudent->Next;
            else
                break;

        }
	// set the current element as Previous node
        prevStudent = tempStudent->Prev;
        tempStudent->Prev = currentStudent;
        currentStudent->Next = tempStudent;
	
	// check if we are in the first node
        if(prevStudent != NULL)
        {
            prevStudent->Next = currentStudent;
            currentStudent->Prev = prevStudent;
        }
	// if yes set the element as the head of the list
        else
        {
            coll->Head = currentStudent;
        }
        coll->Total++;
        return 1;
    }
    else
  	return 0;
}


int ModifyAtIndex(int index, int age, char* name, float grade, enum Level level,StudentCollection* coll)
{
    StudentNode* tempStudent = NULL;
    int x = 0;

    if ((index >= 0) && (index <= coll->Total))
    {
        tempStudent = coll->Head;

        for (x = 0; x <= index - 1; x++)
        {
            if(tempStudent != NULL)
                tempStudent = tempStudent->Next;
            else
                break;

        }

        UpdateStudent(tempStudent,age,name,grade,level);
        return 1;
    }
    else
        return 0;
}

int DeleteAtIndex(int index,StudentCollection* coll)
{
    StudentNode* tempStudent = coll->Head;
    StudentNode* toDelete = NULL;
    StudentNode* nextStudent = NULL;
    StudentNode* prevStudent = NULL;
    int x = 0;

    if ((index >= 0) && (index < coll->Total))
    {
        for (x = 0; x <= index - 1; x++)
        {
            if(tempStudent->Next == NULL)
            {
                return 0;
            }
            tempStudent = tempStudent->Next;
        }

        toDelete = tempStudent;
        nextStudent = tempStudent->Next;
        prevStudent = tempStudent->Prev;

        if(prevStudent != NULL)
        {
            //if a center node, link to previous to the next node
            prevStudent->Next = nextStudent;
        }
        else
        {
            //then node is the head node
            coll->Head = tempStudent->Next;
        }

        if(nextStudent != NULL)
        {
            nextStudent ->Prev = prevStudent;
        }

        free(tempStudent);
        coll->Total -= 1;
        return 1;
    }
    else
        return 0;
}

void DeleteAll(StudentCollection* coll)
{
	StudentNode* currentStudent = coll->Head;
	StudentNode* secondStudent = NULL;
	
	while(currentStudent != NULL)
	{
		secondStudent = currentStudent->Next;
		free(currentStudent);
		currentStudent = secondStudent;
	}

	coll->Total = 0;
	coll->Head = NULL;

}

void PrettyPrint(StudentCollection* coll)
{
    printf("Doubly linked list collection with a total of %d \n", coll->Total);

    if(coll->Total == 0)
    {
        printf("Linked list is empty\n");
        return;
    }
    else
    {
        StudentNode *tempStudent = coll->Head;
       while(tempStudent != NULL) 
       {
            printf(" Student %s is %d years old and his current grade is %lf at level %d\n", tempStudent->Name, tempStudent->Age, tempStudent->Grade, tempStudent->StudentLevel);
            tempStudent = tempStudent->Next;
        }
    }
}

int DumpToFile(StudentCollection* coll)
{
    StudentNode* currentStudent = coll->Head;
    FILE* fp = fopen("DUMPFILE.txt", "w");

    //check that file was opened successfully
    if(fp != NULL)
    {
        while(currentStudent != NULL)
        {
            fprintf(fp, "%d,%s,%lf,%d \n", currentStudent->Age,  currentStudent->Name, currentStudent->Grade, currentStudent->StudentLevel);
            currentStudent = currentStudent->Next;
        }
    }
}

int GetLine(FILE* fp, char* buffer)
{
    char currentChar = '-';
    int bufferIndex = 0;

    while((currentChar = (char)fgetc(fp)) != '\n')
    {
        if(currentChar == EOF)
        {
            return 1;
        }
        buffer[bufferIndex] = currentChar;
        bufferIndex++;
    }
    return 0;
}

void GetStudentDetails(int* age, char* name, int* grade, enum Level* level, char* line)
{
    char* token = "";
    token = strtok(line, ",");
    *age = atoi(token);
    token = strtok(NULL, ",");
    strcpy(name, token);
    token = strtok(NULL, ",");
    *grade = atoi(token);
    token = strtok(NULL, ",");
    *level = atoi(token);
}

int PopulateFromFile(StudentCollection* coll)
{
    FILE* fp = fopen("DUMPFILE.txt", "r");
    char buffer[1024];
    char tempName[200];
    int age = 0;
    enum Level level;
    int grade = 0;
    StudentNode* newStudent = NULL;

    while(GetLine(fp, &buffer[0]) != 1)
    {
        GetStudentDetails(&age, &tempName[0], &grade, &level, &buffer[0]);
        newStudent = CreateStudent(age, tempName, 200, grade, level); 
        Insert(newStudent, coll);
    }
}

