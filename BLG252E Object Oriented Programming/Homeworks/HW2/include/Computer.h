/*
    Mustafa Can Caliskan
    150200097
*/

#include <string>
#include <iostream>

class ALU {
    public:
        ALU(const int&); //Constructor
        const int add(const int&, const int&) const; //const member function
        const int subtract(const int&, const int&) const;
        const int multiply(const int&, const int&) const;
    private:
        const int numPerCores;
};

class CUDA {
    public:
        CUDA(const int&); //Constructor
        const std::string render() const;
        const std::string trainModel() const;
    private:
        const int numCores;
};

class CPU {
    public:
        CPU(const int&); //Constructor
        const int execute(const std::string&) const;
        const ALU get_alu() const; //getter of ALU object
    private:
        const ALU alu_object;
};

class GPU {
    public:
        GPU(const int&); //Constructor
        const std::string execute(const std::string&) const;
        const CUDA get_cuda() const; //getter of CUDA object
    private:
        const CUDA cuda_object;
};

class Computer {
    public:
        Computer();
        void operator+(const GPU&); //Given address will not be changed.
        void operator+(const CPU&); //overload of overloaded operator.
        void execute(const std::string&) const; //Execution does not change the member variables.
        const CPU* get_cpu() const; //getter
        const GPU* get_gpu() const; //getter
    private:
        const CPU* attachedCPU; //the data is constant, but the pointer may be changed.
        const GPU* attachedGPU;
};