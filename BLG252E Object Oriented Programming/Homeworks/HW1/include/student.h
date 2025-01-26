/* @Author
 * Student Name:  Mustafa Can Caliskan
 * Student ID : 150200097
 */

#include <string>
#include <iostream>

class Student {
    public:
        Student(std::string, double, int, int); //constructor
        Student(const Student&); //copy constructor
        ~Student(); //destructor
         double get_gpa() const; //The object called by const member function cannot be modified.
         std::string get_name() const;
         int get_gre() const;
         int get_toefl() const;
         int get_n_applications() const;
        void set_name(std::string) const;
        void set_n_applications(int) const;
    private:
        mutable std::string name = ""; // set mutable to allow particular class members to be modifiable even for a const object
        const double gpa = 0.0;
        const int gre = 0;
        const int toefl = 0;
        mutable int n_applications = 0; 
};