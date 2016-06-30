#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cocktaildialog.h"
#include "ricettariodialog.h"
#include "model/cocktail.h"

#include <QMessageBox>
#include <QtGui>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    r = new Ricettario();
    bool esito = r->load ();
    if (!esito)
    {
        QMessageBox* errore = new QMessageBox();
        errore->setText ("Non posso caricare i dati");
        errore->exec();
    }

    ui->setupUi(this);


    connect(ui->cercaButton,
            SIGNAL(clicked()),
            this,
            SLOT(cercaButton_clicked()));
    connect (ui->chiudiButton,
             SIGNAL(clicked()),
             this,
             SLOT(chiudiButton_clicked()));

    connect (ui->listaRicetteButton,
             SIGNAL(clicked()),
             this,
             SLOT(listaRicetteButton_clicked()));
    connect (ui->aggiungiRicettaButon,
             SIGNAL(clicked()),
             this,
             SLOT(aggiungiRicettaButon_clicked()));
    connect (ui->svuotaRicettarioButton,
             SIGNAL(clicked()),
             this,
             SLOT(svuotaRicettarioButton_clicked()));
    connect( ui->buckupButton,
             SIGNAL(clicked()),
             this,
             SLOT(backup()));

    connect(ui->caricaBackup,
            SIGNAL(clicked()),
            this,
            SLOT(caricaBackup()));

}


MainWindow::~MainWindow()
{
    delete r;
    delete ui;
}



void MainWindow::comunicazioneErroreCerca (const QString& mess)
{
    QMessageBox* m = new QMessageBox;
    m->setText (mess);
    m->exec();
}

bool MainWindow::salvaFile (const QString& fileName)
{
     return r->save (fileName.toStdString ());
}


bool MainWindow::salvaCome ()
{
    QFileDialog dialog(this);
    dialog.setWindowModality (Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    return (dialog.exec () == QDialog::Accepted)?
            salvaFile (dialog.selectedFiles ().first ()):false;
}


void MainWindow::backup ()
{
    bool ok = salvaCome ();
    (ok)? comunicazioneErroreCerca ("Backup completato!"):
          comunicazioneErroreCerca ("Backup non riuscito!");
}


bool MainWindow::caricaFile(const QString& fileName)
{
    Ricettario* nuovo = new Ricettario();
    bool caricamento = nuovo->load(fileName.toStdString());
    if (caricamento)
    {
        delete r;
        r = nuovo;
    }
    else
        delete nuovo;

    return caricamento;
}
bool MainWindow::caricaCome()
{
   if (r->size()>0)
        r->save();

    QString fileName = QFileDialog::getOpenFileName(this);
    return (!fileName.isEmpty())? caricaFile(fileName): false;
}

void MainWindow::caricaBackup()
{
    bool ok = caricaCome();
    (ok)? comunicazioneErroreCerca ("Backup caricato!"):
          comunicazioneErroreCerca ("Non posso caricare il backup :(");
}


void MainWindow::cercaButton_clicked()
{
    if (r->size ()==0) // prima verifica sul db
    {
        comunicazioneErroreCerca ("Carica una ricetta... nulla da visualizzare");
        return;

    }


    // carico il testo dalla lineEdit per recupero testo di ricerca
    QString lookForText = ui->lineEditCerca->text ();
    Cocktail* c = 0;


    if(lookForText.length ()==0)
     {
        comunicazioneErroreCerca ("Riprova... inserisci del testo");
        return;
     }

     c = r->find (lookForText.toStdString());

     if (!c)
     {
         comunicazioneErroreCerca ("Mi spiace :( Riprova andra' meglio la prossima :) ");
         return;
     }

     // visualizzazione risultato --> deve essere un CocktailWidget
     CocktailDialog* cdiag = new CocktailDialog(c, this);

     connect (this,
              SIGNAL(setPB_salva(const QString&)),
              cdiag,
              SLOT(setPB_salva(const QString&)));

     emit setPB_salva ("Salva Modifiche");

     cdiag->setWindowTitle ("Visualizza | Modifica Cocktail");

     cdiag->setModal (true);

     connect(cdiag,
             SIGNAL(request_insertCocktail(Cocktail*)),
             this,
             SLOT(request_insertCocktail(Cocktail*)));
     cdiag->show ();
}


void MainWindow::chiudiButton_clicked()
{
    if (r->size () > 0)
    {
        comunicazioneErroreCerca ("Sto salvando i dati... ");
        r->save ();
    }
    qApp->quit ();
}


void MainWindow::listaRicetteButton_clicked()
{
    if (r->size () == 0)
    {
        comunicazioneErroreCerca ("Il ricetttario e' vuoto");
        return;
    }


    RicettarioDialog* rc = new RicettarioDialog(r, this);
    connect (rc,
             SIGNAL(request_insertCocktail(Cocktail*)),
             this,
             SLOT(request_insertCocktail(Cocktail*)));
    rc->setWindowTitle ("Elenco ricette");
    rc->show();

}

void MainWindow::aggiungiRicettaButon_clicked()
{
    CocktailDialog* newCocktail = new CocktailDialog(0,this);

    newCocktail->setWindowTitle ("Aggiungi Ricetta");

    connect (this,
             SIGNAL(setPB_salva(const QString&)),
             newCocktail,
             SLOT(setPB_salva(const QString&)));

    emit setPB_salva ("Aggiungi cocktail");

    newCocktail->setModal (true);

    connect(newCocktail,
            SIGNAL(request_insertCocktail(Cocktail*)),
            this,
            SLOT(request_insertCocktail(Cocktail*)));

    newCocktail->show ();
}


void MainWindow::svuotaRicettarioButton_clicked()
{
    if (r->size () > 0) 
    {
    delete r;
    comunicazioneErroreCerca ("Ora il ricettario e' vuoto");
    Ricettario* x = new Ricettario();
    r = x;
    } 
    else 
    {
      comunicazioneErroreCerca ("Ricettario vuoto! Inserisci qualche ricetta");
    }
}


void MainWindow::request_insertCocktail (Cocktail* c)
{
    std::string s = c->getNomeCocktail ();

    bool trovato = r->find (s);

    if (trovato)
    {
        r->remove (s);
    }
    r->insert (*c);
    comunicazioneErroreCerca ("Operazione conclusa con successo");
}
