#include <QApplication> 
#include <QTranslator>
#include <QLibraryInfo>
#include <QResource>
#include <QLocale>

#include "application.h"
#include "closeEvent.h"


int main( int argc, char ** argv ) {

   Q_INIT_RESOURCE(application);

    QApplication window( argc, argv );
        window.setQuitOnLastWindowClosed(false);
        window.installEventFilter(new myEventFilter());


        QTranslator translator;
        translator.load(QString(":/application_" + QLocale::system().name()));
            window.installTranslator(&translator);

    ApplicationWindow *mw = new ApplicationWindow();
    QIcon mwIcon(":/info.png");
        mw->setWindowIcon(mwIcon);
       // mw->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
       // mw->show();

    window.connect( &window, SIGNAL(lastWindowClosed()), &window, SLOT(quit()) );
    return window.exec();
}


