#include <QString>
#include <string>
#include <QtTest>
#include "../../model/base.h"

class BaseIngrTest : public QObject
{
    Q_OBJECT
private:
    Base* b;

public:
    BaseIngrTest();

private Q_SLOTS:
    void volume();
    void gradazioneAlcolica() ;
    void getPercentualeAlcolica() ;
    void getNome() ;

    // setters
    void setQuantita();
    void setPercentualeAlcolica();
    void setNome();
    void copia();
};

BaseIngrTest::BaseIngrTest()
{
    b = new Base();
}

void BaseIngrTest::volume()
{
    int v = b->volume ();
    QVERIFY (v == 0);
}


void BaseIngrTest::gradazioneAlcolica()
{
    int g = b->gradazioneAlcolica ();
    QVERIFY (g == 0);
}

void BaseIngrTest::getPercentualeAlcolica()
{
    int v = b->getPercentualeAlcolica ();
    QVERIFY (v == 0);
}

void BaseIngrTest::getNome()
{
    std::string n = b->getNome ();
    QVERIFY(n == "default");
}

void BaseIngrTest::setQuantita()
{
    b->setQuantita (4);
    int v = b->volume ();
    QVERIFY (v == 4);
}

void BaseIngrTest::setPercentualeAlcolica()
{
    b->setPercentualeAlcolica (40);
    int v = b->getPercentualeAlcolica ();
    QVERIFY (v == 40);
}
void BaseIngrTest::setNome()
{
    b->setNome ("Andreina");
    std::string n = b->getNome ();
    QVERIFY(n == "Andreina");
}

void BaseIngrTest::copia()
{
    Ingridiente* ingr = b->copia ();
    std::string n = ingr->getNome ();
    int q = ingr->volume ();
    int p = ingr->getPercentualeAlcolica ();

    bool value = (n == "Andreina") && (q == 4) && (p == 40);
    QVERIFY (value == true);

}



QTEST_APPLESS_MAIN(BaseIngrTest)

#include "tst_baseingrtest.moc"
