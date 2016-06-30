#include <QString>
#include <QtTest>
#include "../../model/clist.h"

class CListTest : public QObject
{
    Q_OBJECT
CList<int> list;

public:
    CListTest();

private Q_SLOTS:
    void size();
    void begin();
    void end();
    void push_back();
    void push_front();
    void rimuoviElemento();

};

CListTest::CListTest()
{
   for (int i = 0; i < 50; ++i )
       list.push_back (i);
}

void CListTest::size()
{
    unsigned int s = list.size ();
    QVERIFY(s == 50);
}

void CListTest::begin()
{
    CList<int>::iteratore it = list.begin ();
    int b = list[it];

    QVERIFY(b == 0);
}

void CListTest::end()
{
    CList<int>::iteratore it = list.end();
    bool b = (!it.isNotNull ());
    QVERIFY(b == true);
}

void CListTest::push_back ()
{
    list.push_back (50);
    unsigned int s = list.size ();
    QVERIFY(s == 51);
}

void CListTest::push_front ()
{
    list.push_front (-1);
    unsigned int s = list.size ();
    QVERIFY(s == 52);
}

void CListTest::rimuoviElemento()
{
    CList<int>::iteratore x;
    bool ok = false;
    for (CList<int>::iteratore it = list.begin ();
         !ok
         &&
         it != list.end();
         ++it)
        if (list[it] == 2)
            x = it;

    if (x.isNotNull ())
    {
        list.rimuoviElemento (x);
    }

    unsigned int s = list.size ();
    QVERIFY(s == 51);


}

QTEST_APPLESS_MAIN(CListTest)

#include "tst_clisttest.moc"
