#include "base.h"


Ingridiente* Base::copia() const
{
    return new Base(getNome (),
                    volume (),
                    getPercentualeAlcolica ());
}

std::string Base::getTipo() const
{
    return "Base";
}

Base::Base(std::string n, int q, int p)
{
    Ingridiente::setNome (n);
    Ingridiente::setQuantita (q);
    Ingridiente::setPercentualeAlcolica (p);
}



