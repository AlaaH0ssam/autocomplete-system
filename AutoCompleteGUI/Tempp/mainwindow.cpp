#include "MainWindow.h"
#include "gui/menu.h"
#include "Backend/trie.h"
trie myTrie;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainMenu *menu = new MainMenu(myTrie, this);
    setCentralWidget(menu);

    connect(menu, &MainMenu::exitClicked, this, &MainWindow::close);
}
    MainWindow::~MainWindow() {
    }

