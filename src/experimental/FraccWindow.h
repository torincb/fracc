#ifndef FRACCWINDOW_H
#define FRACCWINDOW_H

#include <QMainWindow>

class FraccWindow: public QMainWindow {
    Q_OBJECT
public:
	FraccWindow();
	~FraccWindow();

private slots:
    void about();

private:
    void generateMenuBar();
};

#endif