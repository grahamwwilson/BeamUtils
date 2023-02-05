#include <iostream>

int main(){

    float x;
    float y;
    float dx;
    
    x = 1.0;
    
    dx = 1.0;
    
    std::cout.precision(16);
    
    for (int i=0; i<30; ++i){
        dx= dx/2.0;
        
        y = x + dx;
        
        std::cout << i << " x = " << x << " dx " << dx << " dx / x = " << dx/x << " y " << y << std::endl;
        
    }
}
