#include "SearchScreen.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScreen>

SearchScreen::SearchScreen(trie& trieRef, QSize parentSize,QWidget *parent)
    : QMainWindow(parent), t(trieRef)
{
    this->resize(parentSize);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Search Dictionary");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #17263E;");

    prefixInput = new QLineEdit(this);
    prefixInput->setPlaceholderText("Enter prefix to search");
    prefixInput->setStyleSheet(R"(
        QLineEdit {
            padding: 8px;
            border: 2px solid #17263E;
            border-radius: 6px;
            font-size: 14px;
            color: #17263E;
        }
    )");


    sortComboBox = new QComboBox(this);
    sortComboBox->addItem("DFS (Alphabetical order)");
    sortComboBox->addItem("BFS (Shortest words first)");
    sortComboBox->setCurrentIndex(0);
    sortComboBox->setStyleSheet(R"(
        QComboBox {
            padding: 8px;
            border: 2px solid #17263E;
            border-radius: 6px;
            font-size: 14px;
            color: #17263E;
        }
    )");

    searchButton = new QPushButton("Search", this);
    searchButton->setStyleSheet(R"(
        QPushButton {
            background-color: #17263E;
            color: #B9CFDE;
            border-radius: 6px;
            padding: 10px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #101A2B;
        }
        QPushButton:pressed {
            background-color: #0A121F;
        }
    )");

    suggestionsList = new QListWidget(this);
    suggestionsList->setStyleSheet(R"(
        QListWidget {
            border: 2px solid #17263E;
            border-radius: 6px;
            font-size: 14px;
            background-color: white;
            color: #17263E;
        }
    )");

    QPushButton *backBtn = new QPushButton("Back");
    QFont btnFont;
    btnFont.setPointSize(12);
    btnFont.setBold(true);
    backBtn->setFont(btnFont);


    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(prefixInput);
    layout->addWidget(sortComboBox);
    layout->addWidget(searchButton);
    layout->addWidget(suggestionsList);
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
    connect(backBtn, &QPushButton::clicked, this, &SearchScreen::close);
    connect(searchButton, &QPushButton::clicked, this, &SearchScreen::onSearchClicked);
}

SearchScreen::~SearchScreen() {}

void SearchScreen::onSearchClicked()
{
    try {
        QString input = prefixInput->text();
        if (input.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Prefix cannot be empty!");
            return;
        }

        string prefix = input.toStdString();
        t.track_and_insert(prefix);
        int sortType = (sortComboBox->currentIndex() == 0) ? 1 : 2;

        std::cout << "Prefix: " << prefix << std::endl;
        std::cout << "Sort Type: " << sortType << std::endl;

        vector<pair<string, bool>> suggestions = getSuggestions(t, prefix, sortType);

        if (suggestions.empty()) {
            QMessageBox::information(this, "No Results", "No suggestions found.");
            return;
        }

        displaySuggestions(suggestions);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error",
                              QString("An error occurred: %1").arg(e.what()));
    }
    catch (...) {
        QMessageBox::critical(this, "Error", "Unknown error occurred");
    }
}
void SearchScreen::displaySuggestions(const vector<pair<string, bool>>& suggestions)
{
    suggestionsList->clear();

    for (const auto &pair : suggestions) {
        if (pair.first.empty()) {
            continue;
        }

        QString word = QString::fromStdString(pair.first);
        if (word.isEmpty()) {
            continue;
        }

        QListWidgetItem* item = new QListWidgetItem(word);
        if (pair.second) {
            item->setText(word + " (exact match)");
            item->setForeground(Qt::blue);
        }
        suggestionsList->addItem(item);
    }
}
