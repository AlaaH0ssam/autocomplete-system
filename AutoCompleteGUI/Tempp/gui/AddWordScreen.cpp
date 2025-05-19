#include "gui/AddWordScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QFont>
#include <QSpacerItem>
#include "Backend/Validator.h"
AddWordScreen::AddWordScreen(trie& tRef, QSize parentSize, QWidget *parent)
    : QMainWindow(parent), t(tRef)
{
    this->resize(parentSize);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel("Enter a New Word");
    label->setAlignment(Qt::AlignCenter);
    QFont labelFont;
    labelFont.setPointSize(18);
    labelFont.setBold(true);
    label->setFont(labelFont);
    label->setStyleSheet("color: #17263E;");

    QLineEdit *lineEdit = new QLineEdit;
    QFont lineFont;
    lineFont.setPointSize(14);
    lineFont.setBold(true);
    lineEdit->setFont(lineFont);
    lineEdit->setPlaceholderText("Type word here...");
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setStyleSheet("color: #17263E;");

    QPushButton *addBtn = new QPushButton("Add");
    QPushButton *backBtn = new QPushButton("Back");

    QFont btnFont;
    btnFont.setPointSize(12);
    btnFont.setBold(true);
    addBtn->setFont(btnFont);
    backBtn->setFont(btnFont);

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(label);
    layout->addSpacing(10);
    layout->addWidget(lineEdit);
    layout->addSpacing(20);
    layout->addWidget(addBtn);
    layout->addWidget(backBtn);
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->setContentsMargins(60, 30, 60, 30);
    layout->setSpacing(15);
    Validator validator;
    connect(addBtn, &QPushButton::clicked, this, [=]() {
        QString word = lineEdit->text().trimmed();
        if (word.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "<b>Please enter a word.</b>");
            return;
        }

        std::string stdWord = word.toStdString();
        if (t.search(stdWord)) {
            QMessageBox::information(this, "Info", "<b>Word already exists.</b>");
        } else {
            t.insert(stdWord,1);
            QMessageBox::information(this, "Success", "<b>Word added successfully.</b>");
            lineEdit->clear();
        }
    });

    connect(backBtn, &QPushButton::clicked, this, &AddWordScreen::close);

    this->setStyleSheet(R"(
        QWidget {
            background-color: #B9CFDE;
        }
        QLineEdit, QPushButton {
            padding: 12px;
            font-size: 14px;
        }
        QLineEdit {
            background-color: #ffffff;
            border: 2px solid #17263E;
            border-radius: 6px;
        }
        QPushButton {
            background-color: #17263E;
            color: #B9CFDE;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #101A2B;
        }
        QPushButton:pressed {
            background-color: #0A121F;
        }
    )");
}
