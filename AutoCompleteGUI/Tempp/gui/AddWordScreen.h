#ifndef ADDWORDSCREEN_H
#define ADDWORDSCREEN_H

#include <QMainWindow>
#include <QSize>
#include "Backend/trie.h"

class AddWordScreen : public QMainWindow
{
    Q_OBJECT

public:
    AddWordScreen(trie& tRef, QSize parentSize, QWidget *parent = nullptr);

private slots:
    //void onAddClicked();
   // void onBackClicked();

private:
    trie& t;
};

#endif // ADDWORDSCREEN_H
