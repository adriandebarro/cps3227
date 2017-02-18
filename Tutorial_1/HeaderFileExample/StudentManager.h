#pragma once

typedef struct
{
    int age;
    int id;
    int length;
    char* name;
}
student;

student CreateStudent(int p_age, int p_index, char* p_name, int p_nameLength);
void UpdateStudent(student *p_student, int p_age, int p_index, char* p_name, int p_nameLength);
void ToString(student *p_student);