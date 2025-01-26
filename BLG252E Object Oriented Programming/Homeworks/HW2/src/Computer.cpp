/*
    Mustafa Can Caliskan
    150200097
*/

#include "Computer.h"

Computer::Computer(){
    this->attachedCPU = NULL; //Pointer initialization.
    this->attachedGPU = NULL;
    std::cout << "Computer is ready" << std::endl;
}

void Computer::operator+(const GPU& gpu) {
    if (this->attachedGPU != NULL) //Sanity check
        std::cout << "There is already a GPU" << std::endl;
    else {
        this->attachedGPU = &gpu;
        std::cout << "GPU is attached" << std::endl;
    }
}

void Computer::operator+(const CPU& cpu) {
    if (this->attachedCPU != NULL) //Sanity check
        std::cout << "There is already a CPU" << std::endl;
    else {
        this->attachedCPU = &cpu;
        std::cout << "CPU is attached" << std::endl;
    }
}

void Computer::execute(const std::string& str) const { 
    if (str == "add" || str == "subtract" || str == "multiply") //neccessary function call
        std::cout << this->get_cpu()->execute(str) << std::endl;
    else
        std::cout << this->get_gpu()->execute(str) << std::endl;
}

const CPU* Computer::get_cpu() const{ //getter
    return this->attachedCPU;
}

const GPU* Computer::get_gpu() const{ //getter
    return this->attachedGPU;
}

const ALU CPU::get_alu() const{ //getter
    return this->alu_object;
}

CPU::CPU(const int& n_core) //CPU constructor
    :alu_object{ALU(n_core)}
{
    std::cout << "CPU is ready" << std::endl;
}

const int CPU::execute(const std::string& str) const {
    int o1, o2;
    std::cout << "Enter two integers" << std::endl;
    std::cin >> o1;
    std::cin >> o2;
    if (str == "add")
        return this->get_alu().add(o1, o2); //neccessary function call
    if (str == "subtract")
        return this->get_alu().subtract(o1, o2);
    if (str == "multiply")
        return this->get_alu().multiply(o1, o2);
    return -1;
}

const CUDA GPU::get_cuda() const { //getter
    return this->cuda_object;
}

GPU::GPU(const int& n_core)  //GPU constructor
    :cuda_object{CUDA(n_core)}
{
    std::cout << "GPU is ready" << std::endl;
}

const std::string GPU::execute(const std::string& str) const {
    if (str == "render")
        return this->get_cuda().render();
    if (str == "trainModel")
        return this->get_cuda().trainModel();
    return "An error occurred";
}

ALU::ALU(const int& n_core) //ALU constructor
    :numPerCores{n_core}
{
    std::cout << "ALU is ready" << std::endl;
}

const int ALU::add(const int& o1, const int& o2) const {
    return o1 + o2;
}

const int ALU::subtract(const int& o1, const int& o2) const {
    return o1 - o2;
}

const int ALU::multiply(const int& o1, const int& o2) const {
    return o1 * o2;
}

CUDA::CUDA(const int& n_core) //CUDA constructor
    :numCores{n_core}
{
    std::cout << "CUDA is ready" << std::endl;
}

const std::string CUDA::render() const {
    return "Video is rendered";
}
const std::string CUDA::trainModel() const {
    return "AI Model is trained";
}
