#ifndef AROMATIZZANTE_H
#define AROMATIZZANTE_H
#include "ingridiente.h"

class Aromatizzante: public Ingridiente
{
public:
    Aromatizzante(std::string ="default",
                  int =0,
                  int =0);
    Ingridiente* copia() const;
    std::string getTipo() const;
virtual ~Aromatizzante(){}

};

#endif // AROMATIZZANTE_H
