#ifndef RICETTARIODIALOG_H
#define RICETTARIODIALOG_H
#include "ui_ricettariodialog.h"
#include "model/ricettario.h"
#include "cocktaildialog.h"
#include <QDialog>

namespace Ui {
class RicettarioDialog;
}

class RicettarioDialog : public QDialog
{
    Q_OBJECT

public:
explicit RicettarioDialog(Ricettario* r =0,
                          QWidget *parent = 0);
    ~RicettarioDialog();
signals:
void request_insertCocktail(Cocktail*);



private slots:
    void visualizzaDettagli_clicked();
    void elimina_clicked();


private:
    void visualizzaDettagli();
    void setupQTableWidget();
    void eliminaRigaTabella();
    static void shareMessage(const QString&);

    Ui::RicettarioDialog *ui;
    Ricettario* ric;
};

#endif // RICETTARIODIALOG_H
