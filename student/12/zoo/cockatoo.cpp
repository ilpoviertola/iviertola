#include "cockatoo.hh"

Cockatoo::Cockatoo(): Bird()
{

}

void Cockatoo::sing(std::ostream &output){
    output << "Kee-ow kee-ow!\n";
}
