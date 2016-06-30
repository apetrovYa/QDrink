#ifndef BASE_H
#define BASE_H
#include "ingridiente.h"


class Base: public Ingridiente
{
public:

    Base(std::string ="default",
         int = 0,
         int = 0);
    Ingridiente* copia() const;
    std::string getTipo() const;
    virtual ~Base() {}
};
#endif // BASE_H
