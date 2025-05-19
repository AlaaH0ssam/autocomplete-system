#include "mainwindow.h"
#include <QPixmap>
#include <QSplashScreen>
#include <QMainWindow>
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QFile>
#include <QTemporaryFile>
#include "gui/menu.h"
#include "Backend/trie.h"
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    trie t;

    QFile resourceFile(":/files/Backend/Dictionary.txt");
    if (!resourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Failed to open resource file.");
    } else {
        QTemporaryFile tempFile;
        if (tempFile.open()) {
            tempFile.write(resourceFile.readAll());
            tempFile.flush();
            tempFile.seek(0);
            t.load_from_file(tempFile.fileName().toStdString());
/*            qDebug() << "Suggestions for 'pro':";
            for (const auto& s : myTrie.bfs("pro")) {
                qDebug() << QString::fromStdString(s);
            }*/
        } else {
            qWarning("Failed to create temporary file.");
        }
    }



    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->size();
    QSize windowSize(screenSize.width() / 2, screenSize.height() / 2);

    QPixmap originalPixmap(":/images/splash.jpeg");
    QPixmap scaledPixmap = originalPixmap.scaled(windowSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QSplashScreen splash(scaledPixmap);
    splash.resize(windowSize);
    splash.show();
    a.processEvents();

    MainMenu w(t);
    w.resize(windowSize);
    w.move(splash.pos());

    QTimer::singleShot(3000, [&]() {
        splash.close();
        w.show();
    });
   /*    QString dictPath = QCoreApplication::applicationDirPath() + "/Backend/Dictionary.txt";
    QDir().mkpath(QFileInfo(dictPath).absolutePath());
    t.save_to_file(dictPath.toStdString());*/
    return a.exec();
}
