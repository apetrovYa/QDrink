#include <QString>
#include <QtTest>
//classe da testare
#include "../../model/ricettario.h"

// classi che interagiscono con Ricettario#class

#include "../../model/ingridiente.h"
#include "../../model/base.h"
#include "../../model/aromatizzante.h"
#include "../../model/colorante.h"
#include "../../model/drink.h"
#include "../../model/cocktail.h"


class RicettarioTest : public QObject
{
    Q_OBJECT

    Ricettario* r;

public:
    RicettarioTest();

private Q_SLOTS:
    void size();
    void load();
    void sizePostLoad();
    void insert();
    void remove();
    void remove2();
    void find();
    void find2();
    void save();
    void getRicettario();
};

RicettarioTest::RicettarioTest()
{
    r = new Ricettario();
}

void RicettarioTest::size()
{
    int s = static_cast<int>( r->size () );
    QCOMPARE (s, 0);
}

void RicettarioTest::load()
{
    bool test = r->load ();
    QCOMPARE(test, true);
}

void RicettarioTest::sizePostLoad ()
{
    int s = static_cast<int>( r->size () );
    QCOMPARE(s,3);
}


void RicettarioTest::insert ()
{
    Drink* d = new Drink();
    d->add(new Base("B1",4,40));
    d->add(new Aromatizzante("A1", 3, 30));
    d->add(new Colorante("C1", 2, 5));
    Cocktail* c = new Cocktail("ProvaCocktail", "Aperitivo", d);
    r->insert (*c);

    int s = static_cast<int>( r->size () );
    QCOMPARE(s,4);
}

void RicettarioTest::remove ()
{
    bool test = r->remove ("prova-x");
    QCOMPARE (test, false);
}


void RicettarioTest::remove2()
{
    bool test = r->remove ("prova-x");
    QCOMPARE (test, false);
}


void RicettarioTest::find()
{
    Cocktail* c = r->find("ProvaCocktail");
    bool test = (c!=0);
    QCOMPARE (test, true);
}

void RicettarioTest::find2()
{
    Cocktail* c = r->find("MioDio");
    bool test = (c!=0);
    QCOMPARE (test, false);
}

void RicettarioTest::save()
{
    r->save ();
}


void RicettarioTest::getRicettario ()
{
    vector<Cocktail> v = r->getRicettario ();
    int n = v.size ();
    int m = r->size ();

    QCOMPARE(n ,m );
}

QTEST_APPLESS_MAIN(RicettarioTest)

#include "tst_ricettariotest.moc"
