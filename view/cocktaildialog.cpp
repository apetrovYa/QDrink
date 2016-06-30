#include "cocktaildialog.h"
#include "model/base.h"
#include "model/aromatizzante.h"
#include "model/colorante.h"

#include <QMessageBox>



// constructor
CocktailDialog::CocktailDialog(Cocktail* inp,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CocktailDialog),
    c(inp)
{
    ui->setupUi(this);
    ui->tableIngridientiWidget->setSortingEnabled (false);
    if (c)
      initQTablaWidget ();

    connect(ui->pb_salva,
            SIGNAL(clicked()),
            this,
            SLOT(salvaInfo()));

    connect (ui->pb_aggiungi,
             SIGNAL(clicked()),
             this,
             SLOT(pb_aggiungi_clicked()));

    connect (ui->pb_elimina,
             SIGNAL(clicked()),
             this,
             SLOT(pb_elimina_clicked()));
    connect (ui->pb_svuota_cocktail,
             SIGNAL(clicked()),
             this,
             SLOT(pb_svuota_cocktail_clicked()));
    connect (ui->pb_salva,
             SIGNAL(clicked()),
             this,
             SLOT(salvaInfo()));


}


// destructor
CocktailDialog::~CocktailDialog()
{
    delete ui;
}




void CocktailDialog::initQTablaWidget()
{
    ui->lineEditNomeCocktail->setText (QString::fromStdString (c->getNomeCocktail ()));
    ui->lineEditMomCons->setText (QString::fromStdString (c->getMomentoConsumo ()));

    Drink* d  = c->getDrink ();


    QTableWidget* tw = ui->tableIngridientiWidget;

    int s = d->howManyElements ();

for (int i = 0; i < s; ++i)
{
    tw->insertRow (i);
    QTableWidgetItem* itemTipo  = new QTableWidgetItem;
    QTableWidgetItem* itemNome  = new QTableWidgetItem;
    QTableWidgetItem* itemQuantita  = new QTableWidgetItem;
    QTableWidgetItem* itemPalc  = new QTableWidgetItem;


    itemTipo->setData (0, QVariant(QString::fromStdString (d->getChild (i)->getTipo ())));
    itemNome->setData (0, QVariant(QString::fromStdString (d->getChild (i)->getNome ())));
    itemQuantita->setData(0, QVariant(QString::number (d->getChild (i)->volume ())));
    itemPalc->setData(0, QVariant(QString::number (d->getChild (i)->getPercentualeAlcolica ())));

    tw->setItem (i, 0, itemTipo);
    tw->setItem (i, 1, itemNome);
    tw->setItem (i, 2, itemQuantita);
    tw->setItem (i, 3, itemPalc);
 }
}




// private methods
void CocktailDialog::aggRigaTabWidget()
{
    int rows = ui->tableIngridientiWidget->rowCount ();
    ui->tableIngridientiWidget->insertRow (rows);
}

void CocktailDialog::eliminaRigaTabWidget()
{
  int curRow = ui->tableIngridientiWidget->currentRow ();
  ui->tableIngridientiWidget->removeRow (curRow);
}

void CocktailDialog::svuotaCocktailLineEdits()
{
    ui->lineEditNomeCocktail->setText ("");
    ui->lineEditMomCons->setText ("");
}


// private slots


void CocktailDialog::setPB_salva (const QString& str)
{
    if (!str.isEmpty ())
    {
        ui->pb_salva->setText (str);
    }
}

void CocktailDialog::pb_aggiungi_clicked()
{
    aggRigaTabWidget ();
}

void CocktailDialog::pb_elimina_clicked()
{
    eliminaRigaTabWidget ();
}

void CocktailDialog::pb_svuota_cocktail_clicked()
{
    svuotaCocktailLineEdits ();
}


bool CocktailDialog::emptyLineEdits()
{
    bool vuoto  =  ui->lineEditMomCons->text ().length () == 0 ||
                  ui->lineEditNomeCocktail->text ().length () == 0;
    if (vuoto)
        throwErrorMessage ("Campi vuoti non ammessi!");
    return vuoto;
}


bool CocktailDialog::emptableRow(QTableWidgetItem* a,
                         QTableWidgetItem* b,
                         QTableWidgetItem* c,
                         QTableWidgetItem* d)
{
    bool testPointers = a && b && c && d;

    return (testPointers)?
                (
                a->text ().isEmpty () ||
                b->text ().isEmpty () ||
                c->text ().isEmpty () ||
                d->text ().isEmpty ()
                )
                : false;

// pos_c: return TRUE <=> exists almeno un elemento vuoto, altrimenti false
}




bool CocktailDialog::setDrink(int rows, Cocktail* cDaSalvare)
{
    bool ok = true;
    for (int i  = 0; ok && i < rows; ++i)
    {
        QTableWidgetItem* curTip = ui->tableIngridientiWidget->item (i, 0);
        QTableWidgetItem* curNom = ui->tableIngridientiWidget->item (i, 1);
        QTableWidgetItem* curQuan = ui->tableIngridientiWidget->item (i, 2);
        QTableWidgetItem* curPalc = ui->tableIngridientiWidget->item (i, 3);

        ok = emptableRow (curTip, curNom, curQuan, curPalc );
        ok = 1 - ok; // ok deve essere true, emptableRow puo' ritornare false

        if (ok)
        {
            std::string tipo = curTip->data (0).toString ().toStdString ();
            std::string nome = curNom->data (0).toString ().toStdString ();
            int q = curQuan->data (0).toString ().toInt ();
            int palc = curPalc->data (0).toString ().toInt ();


            Ingridiente* ing = cocktailFactoryMethod (tipo);

            if (ing != 0)
            {
                ing -> setNome (nome);
                ing -> setQuantita (q);
                ing -> setPercentualeAlcolica (palc);
                cDaSalvare->addIngrediente (*ing);
            }
            else
                ok = false;
        } else
            throwErrorMessage ("Elementi vuoti internamente alla tabella ingredienti non ammessi");
  }
    return ok;
}

void CocktailDialog::setInfoCocktail (Cocktail* cDaSalvare)
{
    cDaSalvare->setNomeCocktail (ui->lineEditNomeCocktail->text ().toStdString ());
    cDaSalvare->setMomentoConsumo (ui->lineEditMomCons->text ().toStdString ());
}

void CocktailDialog::salvaInfo ()
{
    Cocktail* cDaSalvare = new Cocktail();

    if (emptyLineEdits ()) return;

    setInfoCocktail (cDaSalvare);

    int rows = ui->tableIngridientiWidget->rowCount ();

    bool ok = setDrink (rows, cDaSalvare);

    if (ok)
        emit request_insertCocktail(cDaSalvare);
    else
        throwErrorMessage("Problemi con i dati di input");
}


Ingridiente* CocktailDialog::cocktailFactoryMethod (const std::string& tipo)
{
   if (tipo == "Base")
       return  new Base();
   if (tipo == "Aromatizzante")
       return new Aromatizzante();
   if (tipo == "Colorante")
       return new Colorante();
   return 0;
}






void CocktailDialog::throwErrorMessage (const QString& m)
{
    QMessageBox* mess = new QMessageBox;
    mess->setText(m);
    mess->exec ();
}
