#include "ricettariodialog.h"
#include "ui_ricettariodialog.h"
#include <QMessageBox>

RicettarioDialog::RicettarioDialog(Ricettario* r,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RicettarioDialog),
    ric(r)
    {
        ui->setupUi(this);
        if (ric)
        setupQTableWidget ();

        connect (ui->pushButtonVisualizza,
                 SIGNAL(clicked()),
                 this,
                 SLOT(visualizzaDettagli_clicked()));

        connect (ui->pushButtonElimina,
                 SIGNAL(clicked()),
                 this,
                 SLOT(elimina_clicked()));


    }

RicettarioDialog::~RicettarioDialog()
{
    delete ui;
}


void RicettarioDialog::setupQTableWidget ()
{

    vector<Cocktail> v = ric ->getRicettario ();

    int s = v.size ();
    ui->tableWidgetRicettario->setRowCount (s);

    for (int i = 0; i < s; ++i)
    {
     QTableWidgetItem* iCockTail = new QTableWidgetItem;
     QTableWidgetItem* iGalc = new QTableWidgetItem;

     QString nome =
     QString::fromStdString(v[i].getNomeCocktail ());
     QString g    =
     QString::number(v[i].getDrink ()->gradazioneAlcolica ());


     iCockTail->setData (0, QVariant(nome));
     iGalc->setData (0, QVariant(g));

     ui->tableWidgetRicettario->setItem (i,0, iCockTail);
     ui->tableWidgetRicettario->setItem (i,1,iGalc);
    }
     ui->tableWidgetRicettario->setEditTriggers(QAbstractItemView::NoEditTriggers);

}



void RicettarioDialog::shareMessage (const QString& m)
{
    QMessageBox* mess = new QMessageBox;
    mess->setText(m);
    mess->exec ();
}

void RicettarioDialog::eliminaRigaTabella ()
{
    int row = ui->tableWidgetRicettario->currentRow ();
    ui->tableWidgetRicettario->removeRow (row);
}


void RicettarioDialog::elimina_clicked()
{
    int row = ui->tableWidgetRicettario->currentRow();
    QTableWidgetItem* item = ui->tableWidgetRicettario->item(row,0);

    if (item != 0)
    {
        QString nome = item->data (0).toString ();

        Cocktail* daRimuovere = ric->find(nome.toStdString ());

        if(daRimuovere)
        {
        ric->remove (daRimuovere->getNomeCocktail());
        eliminaRigaTabella ();
        ui->tableWidgetRicettario->clear ();
        setupQTableWidget ();
        }
        else
        {shareMessage ("Non posso eliminare");}
    }
     else
     {shareMessage ("Nessuna voce selezionata");}
}

void RicettarioDialog::visualizzaDettagli_clicked ()
{
    int row = ui->tableWidgetRicettario->currentRow();
    QTableWidgetItem* cItem = ui->tableWidgetRicettario->item(row,0);

    if (cItem)
    {
        QString name = cItem->data (0).toString ();

        Cocktail* c = ric->find (name.toStdString ());
        if (c)
        {
        CocktailDialog* cd = new CocktailDialog(c, this);
        cd->setWindowTitle ("Visualizzazione dettagli ricetta");
        connect (cd,
                 SIGNAL(request_insertCocktail(Cocktail*)),
                 this,
                 SIGNAL(request_insertCocktail(Cocktail*)));

        cd->show ();
        }
     }
    else
        shareMessage ("Nessuna voce selezionata");
}





