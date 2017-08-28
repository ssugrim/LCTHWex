#include <iostream>
#include <cstdlib>
#include <ctime>


#include "SimplePRNG.h"



int main( int argc, char * argv [] ) {

    SimplePRNG pld_generator;
    std::srand(std::time(0));
    pld_generator.seed(std::rand(),std::rand());
    std::cout << "SimplePNG random number " << pld_generator.next_uniform_uint32() << std::endl;
    std::cout << "SimplePNG random number " << pld_generator.next_uniform_uint32() << std::endl;
    std::cout << "SimplePNG random number " << pld_generator.next_uniform_uint32() << std::endl;
    std::cout << "SimplePNG random number " << pld_generator.next_uniform_uint32() << std::endl;



}
