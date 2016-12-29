#include <QApplication>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QMessageBox>
#include <QSharedMemory>
#include "lunchdialog.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(flags);

    QApplication app(argc, argv);
    QSharedMemory shared("a0e2149d-3e7d-48b8-838f-e36dc07ec798");

    if( !shared.create( 512, QSharedMemory::ReadWrite) )
    {
        QMessageBox::critical(0, QObject::tr("Error"),
                              QObject::tr("Can't start more than one "
                                          "instance of the application."));
        return 2;
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    LunchDialog dialog;
    //dialog.setWindowFlags(Qt::Tool);
    dialog.show();
    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif
