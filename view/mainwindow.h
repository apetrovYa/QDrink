#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "ui_mainwindow.h"
#include "../model/ricettario.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    Ricettario* getRicettario() const;

signals:
    void setPB_salva (const QString&);

private slots:
    void cercaButton_clicked();
    void chiudiButton_clicked();
    void listaRicetteButton_clicked();
    void svuotaRicettarioButton_clicked();
    void aggiungiRicettaButon_clicked();
    void caricaBackup();
    void backup();
    void request_insertCocktail(Cocktail*);

private:
    bool caricaCome();
    bool caricaFile(const QString& fileName);

    bool salvaCome();
    bool salvaFile(const QString& fileName);
    static void comunicazioneErroreCerca(const QString&);


    Ui::MainWindow *ui;

    Ricettario* r;

 };

#endif // MAINWINDOW_H
