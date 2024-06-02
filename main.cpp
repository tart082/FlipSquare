#include "FlipSquare.hpp"
#include "iostream"

int main()
{
    auto base_state = FlipSquareState(); 
    std::cout << base_state.toString() << std::endl;
    
    return 0;
}