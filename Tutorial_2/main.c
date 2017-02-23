#include <stdio.h>
#include "./student/studentcollection.h"

int main(void) {
    //printf("Program Started!\n");
    StudentNode* currentStudent = CreateStudent(10,"john",4,GRADE_1);
    StudentNode* currentStudent1 = CreateStudent(10,"john1",4,GRADE_1);
    StudentNode* currentStudent2 = CreateStudent(10,"john2",4,GRADE_1);
    StudentNode* currentStudent3 = CreateStudent(10,"john3",4,GRADE_1);
    StudentCollection* New = InitStudentCollection();
    Insert(currentStudent,New);
    Insert(currentStudent1,New);
    Insert(currentStudent2,New);
    InsertAtIndex(currentStudent3,0,New); //Bug on MAX
    PrettyPrint(New);
    ModifyAtIndex(0,33,"Tom",2,GRADE_2,New);
    PrettyPrint(New);
    DeleteAtIndex(1,New);
    PrettyPrint(New);
    return 0;
}
