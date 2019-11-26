#include "owl.hh"

Owl::Owl(): Bird()
{

}

void Owl::hoot(std::ostream &output) const
{
 output << "Hoo hoo!" << std::endl;
}


