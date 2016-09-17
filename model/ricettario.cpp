#include "ricettario.h"
#include "base.h"
#include "aromatizzante.h"
#include "colorante.h"

#include <iostream>
#include <string>

#include <QDomDocument>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

using std::string;
using std::cout;
using std::endl;

Ricettario::~Ricettario ()
{
   while(ricettario.size ()>0)
       ricettario.pop_front ();
}

unsigned int Ricettario::size () const
{
    return ricettario.size ();
}

void Ricettario::insert(const Cocktail& c) {
   this->ricettario.push_front (c);
}

Cocktail* Ricettario::find(const std::string& n)
{
    if (ricettario.is_empty ()) return 0;

    bool ok =true;
    Cocktail* t =0;

    for (CList<Cocktail>::iteratore it = ricettario.begin ();
         ok && it != ricettario.end ();
         ++it)
        {
        if(ricettario[it].getNomeCocktail () == n )
        {

           t = new Cocktail(
                     ricettario[it].getNomeCocktail(),
                     ricettario[it].getMomentoConsumo()
                     ,new Drink(*(ricettario[it].getDrink ()
                     )));
         ok = false;
        }
    }
    return (!ok)? t: 0;
}



bool Ricettario::remove(const string& n)
{
    bool ok = true;

    for(CList<Cocktail>::iteratore it = this->ricettario.begin ();
        ok && it != this->ricettario.end ();
        ++it)
     if(this->ricettario[it].getNomeCocktail () == n)
     {
        this->ricettario.rimuoviElemento (it);
        ok = false;
     }
    return ok;
}





vector<Cocktail> Ricettario::getRicettario() const
{

vector<Cocktail> x;

for(CList<Cocktail>::iteratore it = ricettario.begin ();
    it != ricettario.end();
    ++it
    )
x.push_back (*(new Cocktail(
                   ricettario[it].getNomeCocktail (),
                   ricettario[it].getMomentoConsumo (),
                   ricettario[it].getDrink ()
                   )
               )
             );
    return x;
}



bool Ricettario::load(const std::string& path)
{

QFile file(QString::fromStdString(path));

if (!file.fileName().contains(".xml"))
{
    std::cerr << "Il formatto file non e' xml\n";
    return false;
}

if (!file.open(QFile::ReadOnly | QFile::Text))
{
    std::cerr << "Errore di lettura File \n"
              << file.fileName ().toStdString ()
              << endl;
    return false;
}

QDomDocument doc;
if (!doc.setContent (&file))
{
    std::cerr << "Errore lettura documento DOM\n";
    return false;
}

QDomElement radice = doc.documentElement ();
if(radice.tagName () != "ricettario")
{
    std::cerr << "Errore elemento radice\n";
    return false;
}


QDomNodeList listaCocktail = radice.elementsByTagName ("cocktail");

int lunghezzaListaCo = listaCocktail.count ();

if ( !lunghezzaListaCo )
{
    std::cerr << "Documento vuoto!!!\n";
    return false;
}

for (int i = 0; i < lunghezzaListaCo; ++i)
{
   Cocktail* c = 0;
   QString nomeCo, momCons;

   QDomElement curCockail = listaCocktail.at (i).toElement ();
   QDomNode n = curCockail.firstChild ();

   while (!n.isNull())
   {

      QDomElement nq = n.toElement ();
      QString tagName = nq.tagName();

      if (tagName == "nomeCocktail")
            nomeCo = nq.text ();
      if (tagName == "momentoConsumo")
            momCons = nq.text ();

      if(tagName == "drink")
      {
      Drink d;
      QDomNode ingrList = nq.firstChild ();

      while (!ingrList.isNull ())
      {
        Ingridiente* ingri = 0;

        QDomNode elem = ingrList.firstChild ();
        QString n;
        int q = 0, p = 0;

        while (!elem.isNull ())
        {
          if (elem.toElement ().tagName () == "nome")
             n = elem.toElement ().text ();
          if(elem.toElement ().tagName () == "quantita")
             q = elem.toElement ().text ().toInt ();
          if(elem.toElement ().tagName () == "percentualeAlcolica")
             p = elem.toElement ().text ().toInt ();

             elem = elem.nextSibling ();
        }

          if (ingrList.toElement ().tagName () == "base")
             ingri = new Base(n.toStdString (), q, p);
          if (ingrList.toElement ().tagName () == "aromatizzante")
             ingri = new Aromatizzante(n.toStdString (), q, p);
          if (ingrList.toElement ().tagName () == "colorante")
             ingri = new Colorante(n.toStdString (), q, p);

        d.add (ingri);
        ingrList = ingrList.nextSibling ();
      }
      c = new Cocktail(nomeCo.toStdString (),
                       momCons.toStdString (),
                       &d);
      ricettario.push_back (*c);
      }

       n = n.nextSibling ();
      }
    }
    file.close ();

    return true;
} // fine load() function




bool Ricettario::save(const std::string& path) const
{
    QFile* file = new QFile(QString::fromStdString (path));

    if(!file->open(QIODevice::WriteOnly | QIODevice::Text) )
    {

      return false;
    }
    else{
        QXmlStreamWriter* inp = new QXmlStreamWriter;
            inp->setAutoFormatting(true);
            inp->setDevice(file);
            inp->writeStartDocument();
            inp->writeStartElement("ricettario");

     for(CList<Cocktail>::iteratore it = ricettario.begin ();
         it != ricettario.end(); ++it)
     {

         inp->writeStartElement ("cocktail");
         inp->writeTextElement("nomeCocktail",
         QString::fromStdString(ricettario[it].getNomeCocktail ()));
         inp->writeTextElement("momentoConsumo", QString::fromStdString(ricettario[it].getMomentoConsumo ()));

         Drink* d = ricettario[it].getDrink ();
         unsigned int s = d->howManyElements ();
         inp->writeStartElement ("drink");

         for (unsigned int i = 0; i < s; ++i) {
                 Ingridiente* ing = d->getChild ( (int) i);
                 std::string name = ing -> getTipo ();
                 inp->writeStartElement (QString::fromStdString (name));
                 inp->writeTextElement("nome", QString::fromStdString(ing->getNome ()));
                 inp->writeTextElement("quantita", QString::number( ing->volume ()));
                 inp->writeTextElement("percentualeAlcolica", QString::number(ing->getPercentualeAlcolica ()));
                 inp->writeEndElement ();

         } // fine for
         inp->writeEndElement ();
        inp->writeEndElement ();
     }
     inp->writeEndDocument ();
    }
    file->close ();

    return true;
}
