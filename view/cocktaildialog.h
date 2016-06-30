#ifndef COCKTAILDIALOG_H
#define COCKTAILDIALOG_H
#include "model/cocktail.h"
#include "ui_cocktaildialog.h"
#include <QDialog>

namespace Ui {
class CocktailDialog;
}

class CocktailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CocktailDialog(Cocktail* inp = 0, QWidget *parent = 0);
    ~CocktailDialog();


signals:
    void request_insertCocktail(Cocktail*);


private slots:
    void pb_aggiungi_clicked();
    void pb_elimina_clicked();
    void pb_svuota_cocktail_clicked();
    void salvaInfo();
    void setPB_salva(const QString&);

private:
    void aggRigaTabWidget();
    void eliminaRigaTabWidget();
    void svuotaCocktailLineEdits();

    void setInfoCocktail(Cocktail*);
    bool setDrink(int, Cocktail*);

    void initQTablaWidget();

    bool emptyLineEdits();


    static Ingridiente* cocktailFactoryMethod(const std::string&);
    static void throwErrorMessage(const QString&);
    static bool emptableRow(QTableWidgetItem*,
                         QTableWidgetItem*,
                         QTableWidgetItem*,
                         QTableWidgetItem*);
    Ui::CocktailDialog *ui;
    Cocktail* c;


};

#endif // COCKTAILDIALOG_H
