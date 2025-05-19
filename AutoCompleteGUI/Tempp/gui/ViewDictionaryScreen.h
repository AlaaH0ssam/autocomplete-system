#ifndef VIEWDICTIONARYSCREEN_H
#define VIEWDICTIONARYSCREEN_H

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include "Backend/trie.h"
#include <QMainWindow>

class ViewDictionaryScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewDictionaryScreen(trie& trieRef, QSize parentSize, QWidget *parent = nullptr);


private slots:
    void onSortOrderChanged(int index);

private:
    trie& t;
    QListWidget *listWidget;
    QComboBox *sortComboBox;

    void displayWords(int sortOption);
};

#endif // VIEWDICTIONARYSCREEN_H
