#include <stdio.h>
#include "student/studentcollection.h"

int main(void) 
{
    printf("Program Started \n");
    printf("---------------------- \n");

    // Create four students
    StudentNode* currentStudent = CreateStudent(12, "John", 4, GRADE_1);
    StudentNode* currentStudent_1 = CreateStudent(15, "Tom", 4, GRADE_2);
    StudentNode* currentStudent_2 = CreateStudent(11, "Jane", 4, GRADE_3);
    StudentNode* currentStudent_3 = CreateStudent(10, "Jade", 4, GRADE_1);

    // Create a student collection
    StudentCollection* studentCollection = InitStudentCollection();
    printf("Initialised collection \n");
    printf("---------------------- \n");

    // Insert students in list
    Insert(currentStudent, studentCollection);
    Insert(currentStudent_1, studentCollection);
    Insert(currentStudent_2, studentCollection);
    printf("Inserted into collection \n");
    printf("---------------------- \n");

    // Output the list to console
    PrettyPrint(studentCollection);
    printf("---------------------- \n");

    // Insert student at a specified list index
    InsertAtIndex(currentStudent_3, 0, studentCollection);
    PrettyPrint(studentCollection);
    printf("---------------------- \n");

    // Modify student at a specified list index
    ModifyAtIndex(2, 33, "Ian", 2, GRADE_2, studentCollection);
    PrettyPrint(studentCollection);
    printf("---------------------- \n");

    // Delete student at a specified list index
    DeleteAtIndex(1, studentCollection);
    PrettyPrint(studentCollection);
    printf("---------------------- \n");

    DumpToFile(studentCollection);
    printf("List was dumped to file \n");
    printf("---------------------- \n");

    PopulateFromFile(studentCollection);
    printf("List populated from file \n");
    printf("---------------------- \n");

    PrettyPrint(studentCollection);
    printf("---------------------- \n");

    // Delete all list
    DeleteAll(studentCollection);  
    PrettyPrint(studentCollection);

    return 0;
}
