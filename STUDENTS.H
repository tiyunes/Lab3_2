#ifndef STUDENTS_H
#define STUDENTS_H
#include <string>

using namespace std;

class StudentID
{
public:
    StudentID()
    {
        this->number = 0;
        this->series = 0;
    }

    StudentID(int number, int series)
    {
        this->number = number;
        this->series = series;
    }

    int GetNumber()
    {
        return this->number;
    }

    bool operator==(StudentID& id1)
    {
        return (this->number == id1.number && this->series == id1.series);
    }

    bool operator>(StudentID& id1)
    {
        if(this->number > id1.number)
        {
            return true;
        }
        else return false;
    }

    bool operator<(StudentID& id1)
    {
        if(this->number < id1.number)
        {
            return true;
        }
        else return false;
    }
private:
    int number;
    int series;
};

class Student
{
public:
    friend class StudentID;
    Student()
    {
        this->id = new StudentID();
        string* s1 = new string;
        s1->clear();
        this->firstName = s1;
        this->lastName = s1;
    }

    Student(StudentID* id, string* firstName, string* lastName)
    {
        this->id = id;
        this->firstName = firstName;
        this->lastName = lastName;
    }

    Student(StudentID* id, int age, string* firstName, string* lastName)
    {
        this->id = id;
        this->age = age;
        this->firstName = firstName;
        this->lastName = lastName;
    }

    Student(StudentID* id, int age, int grade, string* firstName, string* lastName)
    {
        this->id = id;
        this->age = age;
        this->grade = grade;
        this->firstName = firstName;
        this->lastName = lastName;
    }

    StudentID* GetID()
    {
        return this->id;
    }

    int GetNumber()
    {
        return this->GetID()->GetNumber();
    }

    int GetAge()
    {
        return this->age;
    }

    int GetGrade()
    {
        return this->grade;
    }

    string* GetFirstName()
    {
        return this->firstName;
    }

    string* GetLastName()
    {
        return this->lastName;
    }

    void SetAge(int age)
    {
        this->age = age;
    }

    void SetGrade(int grade)
    {
        this->grade = grade;
    }

    bool operator==(Student s)
    {
        return s.id == this->id && s.firstName == this->firstName && s.lastName == this->lastName && this->age == s.age &&
        s.grade == this->grade;
    }

    bool operator>(Student& s)
    {
        if(this->id > s.id)
        {
            return true;
        }
        else return false;
    }

    bool operator<(Student& s)
    {
        if(this->id < s.id)
        {
            return true;
        }
        else return false;
    }

protected:

private:
    StudentID* id;
    int age;
    int grade;
    string* firstName;
    string* lastName;
};

#endif // STUDENTS_H
