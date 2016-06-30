#include "colorante.h"

Ingridiente* Colorante::copia () const
{
    return new Colorante(getNome (),
                         volume (),
                         getPercentualeAlcolica ());
}

std::string Colorante::getTipo() const
{
return "Colorante";
}

Colorante::Colorante(std::string n, int q, int p) {
    Ingridiente::setNome (n);
    Ingridiente::setQuantita (q);
    Ingridiente::setPercentualeAlcolica (p);
}

