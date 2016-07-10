#include "drink.h"

Drink::Drink() {}

vector<Ingridiente*>
Drink::copia(const vector<Ingridiente*>& x)
{

    vector<Ingridiente*> y;

    for (unsigned int i = 0; i < x.size(); ++i)
       y.push_back (x[i]->copia ());
    return y;
}

int
Drink::volume() const
{
    int vol = 0;
    for (unsigned int i =0; i < ingridienti.size(); ++i) {
        vol+=ingridienti[i]->volume();
    }
    return vol;
}


double Drink::gradazioneAlcolica() const
{
    double ga = 0;
    for (unsigned int i =0; i < ingridienti.size(); ++i)
        ga+=ingridienti[i]->gradazioneAlcolica();

    return ga;
}

void Drink::add(Ingridiente* i)
{
    ingridienti.push_back (i->copia ());
}



bool Drink::remove(const std::string& n)
{

bool ok = false;

for (vector<Ingridiente*>::iterator it = ingridienti.begin(); !ok && it != ingridienti.end (); ++it)
        if ((*it)->getNome() == n)
        {
            ok = true;
            ingridienti.erase (it);
        }
    return ok;
}


Ingridiente* Drink::getChild(int i) const
{
    
    return (static_cast<int>(ingridienti.size()) > i)? ingridienti[static_cast<unsigned long>(i)]: 0;
}



unsigned int Drink::howManyElements() const {
    return static_cast<unsigned int>(ingridienti.size());
}


void Drink::setDrink (const Drink& d)
{
    bool input = d.ingridienti.size () > 0;
    if (input)
     ingridienti = d.ingridienti;
}


Drink::~Drink ()
{   if (ingridienti.size () >= 1)
    for (vector<Ingridiente*>::iterator it = ingridienti.begin (); it != ingridienti.end(); ++it )
        delete *it;

}
