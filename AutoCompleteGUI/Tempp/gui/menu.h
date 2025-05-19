#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "gui/SearchScreen.h"
#include "gui/AddWordScreen.h"

#include <QMainWindow>

class QPushButton;

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(trie& trieRef, QWidget *parent = nullptr);

signals:
    void searchClicked();
    void addWordClicked();
    void deleteWordClicked();
    void viewDictionaryClicked();
    void exitClicked();

private slots:
    void onSearchClicked();
   void onAddWordClicked();
    void ondeleteWordClicked();
   void onviewDictionaryClicked();
   void onexitClicked();

private:
    QPushButton *createButton(const QString &text, const char *slot);
    trie& t;
    QWidget* currentScreen;

};

#endif // MENU_H
