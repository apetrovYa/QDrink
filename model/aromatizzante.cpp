#include "aromatizzante.h"

Ingridiente* Aromatizzante::copia() const
{
    return new Aromatizzante(getNome (),
                             volume (),
                             getPercentualeAlcolica ());
}


std::string Aromatizzante::getTipo() const
{
    return "Aromatizzante";
}
Aromatizzante::Aromatizzante(std::string n , int q, int p) {
    this->Ingridiente::setNome (n);
    this->Ingridiente::setQuantita (q);
    this->Ingridiente::setPercentualeAlcolica (p);
}



