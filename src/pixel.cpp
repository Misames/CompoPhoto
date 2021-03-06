
#include "pixel.hpp"

Pixel::Pixel(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(int nr,int ng, int nb){
    this->r = nr;
    this->g = ng;
    this->b = nb;
}

Pixel::Pixel(const Pixel &p){
    this->r = p.r;
    this->g = p.g;
    this->b = p.b;
}

void Pixel::setPixel(int nr,int ng, int nb){
    this->r = nr;
    this->g = ng;
    this->b = nb;
}

// Opérateur de comparaison
bool Pixel::operator==(const Pixel& p){					 					 	   	  
    return (r==p.r && g==p.g && b==p.b);					 					 	   	  
}	

// retourne le niveau de gris d'un pixel
int Pixel::grey() const{
    return (r+g+b)/3;
}
