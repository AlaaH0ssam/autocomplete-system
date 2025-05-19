#include "menu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include "gui/SearchScreen.h"
#include "gui/DeleteScreen.h"
#include "gui/ViewDictionaryScreen.h"
#include "gui/AddWordScreen.h"

MainMenu::MainMenu(trie& trieRef, QWidget *parent)
    : QMainWindow(parent), t(trieRef)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->availableSize();
    resize(screenSize * 0.6);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Auto-Complete System");
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #17263E;");
    layout->addWidget(titleLabel);

    QPushButton *searchBtn = new QPushButton("Search", this);
    QPushButton *addWordBtn = new QPushButton("Add Word");
    QPushButton *deleteWordBtn = new QPushButton("Delete Word");
    QPushButton *viewDictBtn = new QPushButton("View Dictionary");
    QPushButton *exitBtn = new QPushButton("Exit");

    layout->addSpacing(20);
    layout->addWidget(searchBtn);
    layout->addWidget(addWordBtn);
    layout->addWidget(deleteWordBtn);
    layout->addWidget(viewDictBtn);
    layout->addWidget(exitBtn);

    layout->setSpacing(15);
    layout->setContentsMargins(40, 30, 40, 30);

    this->setStyleSheet(R"(
        QWidget {
            background-color: #B9CFDE;
        }
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

    connect(searchBtn, &QPushButton::clicked, this, &MainMenu::onSearchClicked);
    connect(addWordBtn, &QPushButton::clicked, this, &MainMenu::onAddWordClicked);
    connect(deleteWordBtn, &QPushButton::clicked, this, &MainMenu::ondeleteWordClicked);
    connect(viewDictBtn, &QPushButton::clicked, this, &MainMenu::onviewDictionaryClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MainMenu::onexitClicked);

    currentScreen = new QWidget(this);
    layout->addWidget(currentScreen);
}

void MainMenu::onSearchClicked()
{
    currentScreen->hide();
    SearchScreen *searchScreen = new SearchScreen(t, this->size());
    currentScreen = searchScreen;
    layout()->addWidget(searchScreen);
    searchScreen->show();
}

void MainMenu::ondeleteWordClicked()
{
    currentScreen->hide();
    DeleteScreen* deleteScreen = new DeleteScreen(t, this->size());
    currentScreen = deleteScreen;
    layout()->addWidget(deleteScreen);
    deleteScreen->show();
}

void MainMenu::onviewDictionaryClicked()
{
    currentScreen->hide();
    ViewDictionaryScreen* viewDictScreen = new ViewDictionaryScreen(t, this->size());
    currentScreen = viewDictScreen;
    layout()->addWidget(viewDictScreen);
    viewDictScreen->show();
}

void MainMenu::onAddWordClicked()
{
    currentScreen->hide();
    AddWordScreen* addScreen = new AddWordScreen(t, this->size());
    currentScreen = addScreen;
    layout()->addWidget(addScreen);
    addScreen->show();
}

void MainMenu::onexitClicked()
{
    int ret = QMessageBox::question(this, "Confirm Exit", "Do you want to save your changes?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        QString filePath = "..\\..\\Backend\\Dictionary.txt";
        QDir dir("..\\..\\Backend");
        if (!dir.exists()) {
            if (!dir.mkpath(".")) {
                QMessageBox::critical(this, "Error",
                                      "Failed to create directory:\n" + dir.absolutePath());
                return;
            }
        }

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error",
                                  QString("Cannot open file for writing:\n%1\nError: %2")
                                      .arg(filePath)
                                      .arg(file.errorString()));
            return;
        }

        try {
            t.save_to_file(filePath.toStdString());
            QMessageBox::information(this, "Success", "Dictionary saved successfully.");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Failed to save dictionary:\n%1").arg(e.what()));
        }
    }

    QApplication::quit();
}
