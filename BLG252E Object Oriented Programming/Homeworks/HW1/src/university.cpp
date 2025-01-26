/* @Author
 * Student Name:  Mustafa Can Caliskan
 * Student ID : 150200097
 */

#include "university.h"

University::University(std::string name, double w1, double w2, double w3, double bias, std::string country) 
                        :name{name}, w1{w1}, w2{w2}, w3{w3}, bias{bias}, country{country} //member initializer list to initialize const variables
{}

University::University(std::string name, double w1, double w2, double w3, double bias) //member initializer list to initialize const variables
                        :name{name}, w1{w1}, w2{w2}, w3{w3}, bias{bias}
{}

void University::evaluate_student(const Student& student) {
    if (this->w1 * student.get_gpa() + this->w2 * student.get_gre() + this->w3 * student.get_toefl() + this->bias >= 0)
        std::cout << student.get_name() <<" is admitted to " << this->name << ".\n";
    else
        std::cout << student.get_name() <<" is rejected from " << this->name << ".\n";
    student.set_n_applications(student.get_n_applications() + 1);
}

