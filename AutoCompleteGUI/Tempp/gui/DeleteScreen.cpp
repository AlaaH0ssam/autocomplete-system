#include "DeleteScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QScreen>
#include <QApplication>

DeleteScreen::DeleteScreen(trie& trieRef, QSize parentSize,QWidget *parent)
    : QMainWindow(parent), t(trieRef)
{
    this->resize(parentSize);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Delete Word");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    titleLabel->setFont(font);
    titleLabel->setStyleSheet("color: #17263E;");

    wordInput = new QLineEdit(this);
    wordInput->setPlaceholderText("Enter word or prefix");
    wordInput->setStyleSheet("padding: 8px; border: 2px solid #17263E; border-radius: 6px; font-size: 14px; font-weight: bold; color: #17263E;");

    deleteModeCombo = new QComboBox(this);
    deleteModeCombo->addItem("Delete exact word");
    deleteModeCombo->addItem("Delete by prefix");
    deleteModeCombo->setStyleSheet("padding: 8px; border: 2px solid #17263E; border-radius: 6px; font-size: 14px; font-weight: bold; color: #17263E;");

    deleteButton = new QPushButton("Delete", this);
    deleteButton->setStyleSheet("background-color: #17263E; color: #B9CFDE; border-radius: 6px; padding: 10px; font-weight: bold; font-size: 14px;");

    wordList = new QListWidget(this);
    wordList->setStyleSheet("border: 2px solid #17263E; border-radius: 6px; font-size: 14px; font-weight: bold; color: #17263E;");

    QPushButton *backBtn = new QPushButton("Back");
    QFont btnFont;
    btnFont.setPointSize(12);
    btnFont.setBold(true);
    backBtn->setFont(btnFont);

    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(wordInput);
    layout->addWidget(deleteModeCombo);
    layout->addWidget(deleteButton);
    layout->addWidget(wordList);
    layout->addWidget(backBtn);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 30, 40, 30);
    centralWidget->setLayout(layout);

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

    connect(deleteButton, &QPushButton::clicked, this, &DeleteScreen::onDeleteClicked);
    connect(wordList, &QListWidget::itemClicked, this, &DeleteScreen::onWordSelected);
    connect(backBtn, &QPushButton::clicked, this, &DeleteScreen::close);

}

DeleteScreen::~DeleteScreen() {}

void DeleteScreen::onDeleteClicked() {
    QString input = wordInput->text().trimmed();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a word or prefix.");
        return;
    }

    std::string str = input.toStdString();
    int mode = deleteModeCombo->currentIndex(); // 0 = exact, 1 = prefix

    if (mode == 0) {
        if (t.deleteWordGUI(str)) {
            QMessageBox::information(this, "Deleted", "Word deleted successfully.");
        } else {
            QMessageBox::warning(this, "Not Found", "Word not found in dictionary.");
        }
        wordList->clear();
    } else {
        loadMatchingWords(input);
    }
}



void DeleteScreen::loadMatchingWords(const QString& prefix) {
    wordList->clear();
    std::vector<std::string> matches = t.dfs(prefix.toStdString());

    if (matches.empty()) {
        QMessageBox::warning(this, "No Matches", "No words found with this prefix.");
        return;
    }

    for (const std::string& word : matches) {
        wordList->addItem(QString::fromStdString(word));
    }
}

void DeleteScreen::onWordSelected(QListWidgetItem* item) {
    if (!item) return;

    QString selected = item->text();
    std::string word = selected.toStdString();

    if (t.deleteWordGUI(word)) {
        QMessageBox::information(this, "Deleted", "Word deleted: " + selected);
        wordList->clear();
    } else {
        QMessageBox::warning(this, "Error", "Could not delete the word.");
    }
}
