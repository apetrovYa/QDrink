#include <QString>
#include <string>
#include <QtTest>
#include "../../model/cocktail.h"
#include "../../model/base.h"
#include "../../model/aromatizzante.h"
#include "../../model/colorante.h"
#include "../../model/drink.h"


class CocktailTest : public QObject
{
    Q_OBJECT

    Cocktail* c;
public:
    CocktailTest();

private Q_SLOTS:
    void defaultConstructor();
    void getNomeCocktail();
    void getMomentoConsumo();
    void getDrink();
    void setNomeCocktail();
    void setMomentoConsumo();
    void setDrink();
    void addIngrediente();
    void removeIngrediente();
};

void CocktailTest::defaultConstructor ()
{
    Cocktail* test = new Cocktail();
    QVERIFY(test->getNomeCocktail () == "NomeCocktail");
    QVERIFY (test->getMomentoConsumo ()=="MomentoConsumo");
    QVERIFY (
 test->getDrink ()->howManyElements () == 0);
}

CocktailTest::CocktailTest()
{
    Drink* d = new Drink();

    Base* b = new Base("Base",4,40);
    Aromatizzante* a = new Aromatizzante("Aromatizzante",4,20);
        d->add (b);
        d->add (a);
      c = new Cocktail("PrimaliaCocktai", "Aperitivo", d);
}

void CocktailTest::getNomeCocktail()
{
    std::string s  = c->getNomeCocktail ();
    QVERIFY (s == "PrimaliaCocktai");
}

void CocktailTest::getMomentoConsumo()
{
    std::string s  = c->getMomentoConsumo ();
    QVERIFY (s == "Aperitivo");
}


void CocktailTest::getDrink()
{
Drink * k = c ->getDrink ();
int n = k->howManyElements ();
QVERIFY (n == 2);
}

void CocktailTest::setNomeCocktail()
{
    c->setNomeCocktail ("Amore");
    QVERIFY (c->getNomeCocktail () == "Amore");
}

void CocktailTest::setMomentoConsumo()
{
    c->setMomentoConsumo ("DopoCena");
    QVERIFY (c->getMomentoConsumo ()=="DopoCena");
}

void CocktailTest::setDrink()
{
    Drink* d = new Drink();

    Base* b = new Base("BB",5,30);
    Aromatizzante* a = new Aromatizzante("AA",5,24);
    Aromatizzante* aa = new Aromatizzante("AAA",6,25);
    d->add (b);
    d->add (a);
    d->add (aa);


     c->setDrink (*d);

     Drink* t = c->getDrink ();
     int xx = t->howManyElements ();
     QVERIFY (xx == 3);
}

void CocktailTest::addIngrediente()
{
    Colorante* cc = new Colorante("C", 2, 0);
    c->addIngrediente (*cc);

    int n = c->getDrink ()->howManyElements ();
    QVERIFY (n == 4);

}

void CocktailTest::removeIngrediente()
{
    c->removeIngrediente ("C");
    int n = c->getDrink ()->howManyElements ();

    QVERIFY (n == 3);
}









QTEST_APPLESS_MAIN(CocktailTest)

#include "tst_cocktailtest.moc"
