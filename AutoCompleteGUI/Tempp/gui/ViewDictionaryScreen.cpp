
#include "ViewDictionaryScreen.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QMessageBox>
#include <QFont>
#include <QSpacerItem>

ViewDictionaryScreen::ViewDictionaryScreen(trie& trieRef, QSize parentSize, QWidget *parent)
    : QMainWindow(parent), t(trieRef)
{
    this->resize(parentSize);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("View Dictionary");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #17263E;");


    sortComboBox = new QComboBox(this);
    sortComboBox->addItem("Frequently searched terms first");
    sortComboBox->addItem("By word length (shortest first)");
    sortComboBox->addItem("Lexicographical order");

    QFont comboFont;
    comboFont.setPointSize(12);
    comboFont.setBold(true);
    sortComboBox->setFont(comboFont);
    sortComboBox->setStyleSheet("color: #17263E;");

    QPushButton *backBtn = new QPushButton("Back");

    QFont btnFont;
    btnFont.setPointSize(12);
    btnFont.setBold(true);
    backBtn->setFont(btnFont);


    listWidget = new QListWidget(this);
    QFont listFont;
    listFont.setPointSize(12);
    listFont.setBold(true);
    listWidget->setFont(listFont);
    listWidget->setStyleSheet("QListWidget::item { color: #17263E; padding: 5px; }");

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(sortComboBox);
    layout->addSpacing(10);
    layout->addWidget(listWidget);
    layout->addSpacing(20);
    layout->addWidget(backBtn);
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->setContentsMargins(60, 30, 60, 30);
    layout->setSpacing(15);

    connect(sortComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSortOrderChanged(int)));
    connect(backBtn, &QPushButton::clicked, this, &ViewDictionaryScreen::close);

    displayWords(0);

    this->setStyleSheet(R"(
        QWidget {
            background-color: #B9CFDE;
        }
        QComboBox, QListWidget, QPushButton {
            padding: 12px;
            font-size: 14px;
        }
        QComboBox {
            background-color: #ffffff;
            border: 2px solid #17263E;
            border-radius: 6px;
        }
        QListWidget {
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




void ViewDictionaryScreen::onSortOrderChanged(int index)
{
    displayWords(index);
}

void ViewDictionaryScreen::displayWords(int sortOption)
{
    listWidget->clear();

    std::vector<std::string> words;

    switch(sortOption) {
    case 0:
        words = t.getAllWords();
        std::sort(words.begin(), words.end(), [](const std::string &a, const std::string &b) {
            return a < b;
        });
        break;
    case 1:
        words = t.bfs("");
        break;
    case 2:
        words = t.dfs("");
        break;
    }

    for (const auto &word : words) {
        listWidget->addItem(QString::fromStdString(word));
    }
}
