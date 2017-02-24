#include <stdio.h>
#include "./student/studentcollection.h"

int main(void) 
{
    printf("Program Started!\n");
    //StudentNode* currentStudent = CreateStudent(10,"john",4,4,GRADE_1);
    //StudentNode* currentStudent1 = CreateStudent(10,"john1",5,4,GRADE_1);
    //StudentNode* currentStudent2 = CreateStudent(10,"john2",5,4,GRADE_1);
    // StudentNode* currentStudent3 = CreateStudent(10,"john3",4,GRADE_1);
    StudentCollection* studentCollection = InitStudentCollection();
    printf("Initialised collection \n");
    //Insert(currentStudent,studentCollection);
    //Insert(currentStudent1,studentCollection);
    //Insert(currentStudent2,studentCollection);
    printf("Inserted into collection \n");
    // PrettyPrint(studentCollection);
    // printf("------- \n");
    // InsertAtIndex(currentStudent3,0,studentCollection);
    // PrettyPrint(studentCollection);
    // ModifyAtIndex(2,33,"Tom",2,GRADE_2,studentCollection);
    // PrettyPrint(studentCollection);
    // printf("------- \n");
    // DeleteAtIndex(1,studentCollection);
    // PrettyPrint(studentCollection);
    //DumpToFile(studentCollection);
    PopulateFromFile(studentCollection);
    PrettyPrint(studentCollection);
    return 0;
}
