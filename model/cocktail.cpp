#include "cocktail.h"
#include "base.h"
#include "aromatizzante.h"
#include "colorante.h"

string Cocktail::getNomeCocktail() const
{
  return nomeCocktail;
}

string Cocktail::getMomentoConsumo() const
{
    return momentoConsumo;
}

Drink* Cocktail::getDrink() const {
    return new Drink(*drink);
}




// setters

void Cocktail::setNomeCocktail(const string& n)
{
    if (nomeCocktail != n)
        nomeCocktail = n;
}
void Cocktail::setMomentoConsumo(const string& mc)
{
    if (momentoConsumo != mc)
    momentoConsumo = mc;
}



void Cocktail::setDrink(const Drink& d)
{
    if (drink)
        drink->setDrink (d);
}

void Cocktail::addIngrediente(const Ingridiente& i)
{
    drink->add (i.copia ());
}
bool Cocktail::removeIngrediente(const string& nomeIngrediente)
{
 return (drink->howManyElements ()>0)? drink->remove (nomeIngrediente): false;
}
