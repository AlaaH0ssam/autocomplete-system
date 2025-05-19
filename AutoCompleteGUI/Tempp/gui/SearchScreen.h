#ifndef SEARCHSCREEN_H
#define SEARCHSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include "Backend/trie.h"
#include "Backend/Search.h"
#include <QMainWindow>

class trie;
class SearchScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchScreen(trie& trieRef, QSize parentSize, QWidget *parent = nullptr);
    ~SearchScreen();

private slots:
    void onSearchClicked();
    //void onBackClicked();
private:
    QLineEdit *prefixInput;
    QListWidget *suggestionsList;
    QComboBox *sortComboBox;
    // QPushButton *backButton;
    QPushButton *searchButton;

    trie &t;
    //void showCustomMessage(const QString &title, const QString &message);
    void displaySuggestions(const vector<pair<string, bool>>& suggestions);
};
#endif // SEARCHSCREEN_H
