#ifndef RICETTARIO_H
#define RICETTARIO_H
#include "clist.h"
#include "cocktail.h"

class Ricettario
{
private:
    CList<Cocktail> ricettario;

public:
    Ricettario(): ricettario(CList<Cocktail>()) { }

    Ricettario(const Ricettario& c)
    : ricettario(c.ricettario) { }

    unsigned int size() const;
    void insert(const Cocktail& c);
    bool remove(const string& n);
    Cocktail* find(const string& n);
    vector<Cocktail> getRicettario() const;

    bool load(const std::string& = "../app/resurces/file-ricettario.xml");
    bool save(const std::string& = "../app/resurces/file-ricettario.xml") const;

    ~Ricettario();

};

#endif // RICETTARIO_H
