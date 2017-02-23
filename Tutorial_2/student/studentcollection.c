#include <stdio.h>
#include <stdlib.h>
#include "./studentcollection.h"

StudentCollection* InitStudentCollection()
{
    StudentCollection* pCollection = malloc(sizeof(StudentCollection));
    pCollection->Head=NULL;
    return  pCollection;
}

int Insert(StudentNode* currentStudent,StudentCollection* coll)
{
    if (coll->Head==NULL)
    {
        coll->Head=currentStudent;
        coll->Total++;
        return 1;
    }
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

int InsertAtIndex(StudentNode* currentStudent, int index,StudentCollection* coll)
{
    if ((index>=0) && (index <= coll->Total))
    {
        StudentNode* tempStudent = coll->Head;

        for (int x = 0; x<index; x++)
        {
            if(tempStudent != NULL)
                tempStudent = tempStudent->Next;
            else
                break;

        }
        StudentNode* prevStudent = tempStudent->Prev;
        tempStudent->Prev = currentStudent;
        currentStudent->Next = tempStudent;
        if(prevStudent != NULL)
        {
            prevStudent->Next = currentStudent;
            currentStudent->Prev = prevStudent;
        }
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
    if ((index>=0) && (index <= coll->Total))
    {
        StudentNode* tempStudent = coll->Head;

        for (int x = 0; x<index; x++)
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
    if ((index>=0) && (index < coll->Total))
    {
        StudentNode* tempStudent = coll->Head;
        StudentNode* Blank = NULL;

        for (int x = 0; x<index-1; x++)
        {
            if(tempStudent->Next == NULL)
            {
                return 0;
            }
            tempStudent = tempStudent->Next;
        }
        Blank = tempStudent->Next;
        tempStudent->Next = Blank->Next;
        free(Blank);
        return 1;
    }
    else
        return 0;
}
void PrettyPrint(StudentCollection* coll)
{
    if(coll->Total == 0)
    {
        printf("Linked list is empty\n");
        return;
    }
    else
    {
        StudentNode *tempStudent = coll->Head;
        for (int x = 0; x < coll->Total; x++) {

            printf(" Student %s is %d years old and his current grade is %lf at level %d\n", tempStudent->Name, tempStudent->Age, tempStudent->Grade, tempStudent->StudentLevel);
            tempStudent = tempStudent->Next;
//            if (tempStudent->Next == NULL) {
//                return;
//            }
        }
    }

    return;

}

//int DumpToFile(char* path,StudentCollection* coll);
//int PopulateFromFile(char* path,StudentCollection* coll);

