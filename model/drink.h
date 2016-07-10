#ifndef DRINK_H
#define DRINK_H
#include "ingridiente.h"
#include <vector>
#include <iostream>

using std::vector;




class Drink
{

    vector<Ingridiente*> ingridienti;
    static vector<Ingridiente*>
    copia(const vector<Ingridiente*>& x);



public:
 Drink();
 Drink(const Drink& x):
     ingridienti(copia(x.ingridienti)) {}


 int volume() const;
 double gradazioneAlcolica() const;

 void add(Ingridiente*);
 bool remove(const std::string&);
 void setDrink(const Drink& d);

 Ingridiente* getChild(int) const;

 unsigned int howManyElements() const;

 ~Drink();

};
#endif // DRINK_H
