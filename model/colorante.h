#ifndef COLORANTE_H
#define COLORANTE_H
#include "ingridiente.h"

class Colorante: public Ingridiente
{
public:
Colorante(std::string ="default", int = 0, int = 0);
Ingridiente* copia() const;
std::string getTipo() const;
virtual ~Colorante() {}
};

#endif // COLORANTE_H
