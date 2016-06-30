#include <QString>
#include <QtTest>
#include "../../model/drink.h"
#include "../../model/base.h"
#include "../../model/aromatizzante.h"
#include "../../model/colorante.h"
#include <iostream>
using std::cout;

class DrinkTest : public QObject
{
    Q_OBJECT

   Drink * d;

public:
    DrinkTest();

private Q_SLOTS:
    void volume();
    void gradazioneAlcolica();
    void add();
    void remove();
    void setDrink();
    void getChild();
    void howManyElements();
    void destructor();
};

DrinkTest::DrinkTest()
{
Base* b = new Base("Base",4,40);
Aromatizzante* a = new Aromatizzante("Aromatizzante",4,20);
Colorante* c = new Colorante("Colorante", 2, 0);
    d = new Drink();
    d->add (b);
    d->add (a);
    d->add (c);
}

void DrinkTest::volume()
{
    int v = d->volume ();
    QVERIFY (v == 10);
}
void DrinkTest::gradazioneAlcolica()
{
    double gr = d->gradazioneAlcolica ();
    double m = 0.1896;
    m-=gr;
    //cout << "[VALORE]-- " << gr << std::endl;
    //cout << "[Diff]-- " << gr - m << std::endl;
    QVERIFY (m == 0.0 );

}

void DrinkTest::add()
{
    int n = d->howManyElements ();
    Base* b = new Base("Vodka", 4, 60);
    d->add (b);
    int m = d->howManyElements ();

    m-=n;

    QVERIFY (m == 1);


}

void DrinkTest::remove()
{
    int n = d->howManyElements ();
    bool x = d->remove ("Vodka");
    int m = d->howManyElements ();

    n-=m;

    bool test = x && (n == 1);
    QVERIFY (test==true);
}


void DrinkTest::setDrink()
{
    Drink* dd = new Drink();
    Base* b = new Base("V",4,40);
    Aromatizzante* a = new Aromatizzante("A",4,20);
    Colorante* c = new Colorante("C", 2, 0);

    dd->add (b);dd->add (a);dd->add (c);
    d->setDrink (*dd);

    int n = dd->howManyElements ();
    int m = d -> howManyElements ();

    QVERIFY (n == m);

}


void DrinkTest::getChild()
{
    Ingridiente* i = d->getChild (0);
    std::string s  = i->getNome ();
    QVERIFY (s == "V");
}


void DrinkTest::howManyElements()
{

    int i = d->howManyElements ();

    QVERIFY (i == 3);

}


void DrinkTest::destructor()
{
    delete d;
    bool test = (d != 0)        ;

    QVERIFY (test == true);

}



QTEST_APPLESS_MAIN(DrinkTest)

#include "tst_drinktest.moc"
