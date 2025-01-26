/* @Author
 * Student Name:  Mustafa Can Caliskan
 * Student ID : 150200097
 */

#include "student.h"

Student::Student(std::string name, double gpa, int gre, int toefl)
                :name{name}, gpa{gpa}, gre{gre}, toefl{toefl} //member initializer list to initialize const variables
{
    std::cout << this->name << " logged in to the system.\n";
}

Student::Student(const Student& student)
                :name{student.name}, gpa{student.gpa}, gre{student.gre}, toefl{student.toefl} //member initializer list to initialize const variables
{
    std::cout << this->name << " logged in to the system.\n";
}

Student::~Student() {
    std::cout << this->name << " logged out of the system with " << this->n_applications << " application(s).\n";
}

std::string Student::get_name() const{
    return this->name;
}

double Student::get_gpa() const{
    return this->gpa;
}

int Student::get_gre() const{
    return this->gre;
}

int Student::get_toefl() const{
    return this->toefl;
}

int Student::get_n_applications() const{
    return this->n_applications;
}

void Student::set_name(const std::string name) const{
    this->name = name;
}

void Student::set_n_applications(int n_applications) const{
    this->n_applications = n_applications;
}