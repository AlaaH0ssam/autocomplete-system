#ifndef DELETESCREEN_H
#define DELETESCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include "Backend/trie.h"
#include <QMainWindow>

class DeleteScreen : public QMainWindow {
    Q_OBJECT

public:
    explicit DeleteScreen(trie& trieRef, QSize parentSize, QWidget *parent = nullptr);
    ~DeleteScreen();
private slots:
    void onDeleteClicked();
    void onWordSelected(QListWidgetItem* item);

private:
    trie& t;
    QLineEdit* wordInput;
    QComboBox* deleteModeCombo;
    QPushButton* deleteButton;
    QListWidget* wordList;

    void loadMatchingWords(const QString& prefix);
};

#endif // DELETESCREEN_H
