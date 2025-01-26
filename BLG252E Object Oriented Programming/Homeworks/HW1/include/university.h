
/* @Author
 * Student Name:  Mustafa Can Caliskan
 * Student ID : 150200097
 */
#include "student.h"

class University {
    public:
        University(std::string, double, double, double, double, std::string); //constructor
        University(std::string, double, double, double, double); //constructor
        void evaluate_student(const Student&);
    private:
        const std::string name = "";
        const double w1, w2, w3;
        const double bias;
        const std::string country = "";
};