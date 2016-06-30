#ifndef COCKTAIL_H
#define COCKTAIL_H
#include "drink.h"


using std::string;

class Cocktail
{
  string nomeCocktail, momentoConsumo;
  Drink* drink;

public:
   Cocktail(string n = "NomeCocktail",
            string mc = "MomentoConsumo",
            Drink* d = new Drink()):
        nomeCocktail(n),
        momentoConsumo(mc),
        drink(new Drink(*d)) {}

   Cocktail(const Cocktail& c):
       nomeCocktail(c.nomeCocktail),
       momentoConsumo(c.momentoConsumo),
       drink(new Drink(*(c.drink))) {}

   // getters
   string getNomeCocktail() const;
   string getMomentoConsumo() const;
   Drink* getDrink() const;

   // setters

   void setNomeCocktail(const string& n);
   void setMomentoConsumo(const string& mc);
   void setDrink(const Drink& d);
   void addIngrediente(const Ingridiente& i);
   bool removeIngrediente(const string& nomeIngrediente);

};

#endif // COCKTAIL_H
