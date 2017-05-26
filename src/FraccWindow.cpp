#include "config.h"
#include "FraccWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>


FraccWindow::FraccWindow(): QMainWindow()
{
    generateMenuBar();
}


FraccWindow::~FraccWindow()
{

}


void FraccWindow::generateMenuBar()
{
    QMenuBar *bar = menuBar();

    QMenu *help = new QMenu("Help");
    QAction *about = help->addAction("About", this, &FraccWindow::about);

    bar->addMenu(help);
}


void FraccWindow::about()
{
    QMessageBox::information(
        this,
        "About Fracc",
        QString("Fracc version %1.%2").arg(FRACC_VERSION_MAJOR).arg(FRACC_VERSION_MINOR));
}