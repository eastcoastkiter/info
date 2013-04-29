#include "application.h"
using namespace std;

ApplicationWindow::ApplicationWindow()
	: QMainWindow( 0 )
{

clipboard = QApplication::clipboard();



setWindowTitle("Info");
installPath=QDir(QDir::currentPath() + "\\scripts");
    if (!installPath.exists())
    {
        QMessageBox::critical(this, "Info", "Could not open install path " + installPath.absolutePath() + ".");
        exit (1);
    }

//Tray Icon
iconTray = new QSystemTrayIcon;
    QIcon mwIcon(":/info.png");
        iconTray->setIcon(mwIcon);
    iconTray->setVisible(true);
    iconTray->show();
    connect(iconTray, SIGNAL(activated ( QSystemTrayIcon::ActivationReason )), this, SLOT(systemTrayActivated(QSystemTrayIcon::ActivationReason)));

//main widget
window = new QWidget(this);

        setCentralWidget(window);
        resize(540,480);
        statusBar()->showMessage( "Welcome" );

        QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

        QAction* updateAction   = new QAction(tr("&Update"), window);
        updateAction->setShortcut(Qt::CTRL + Qt::Key_U);
       //     connect(updateAction, SIGNAL(triggered(bool)), this, SLOT(writeServiceSlot()));
        fileMenu->addAction(updateAction);
        updateAction->setEnabled(false);

        QAction* findAction   = new QAction(tr("&Find"), window);
        findAction->setShortcut(Qt::CTRL + Qt::Key_F);
       //     connect(findAction, SIGNAL(triggered(bool)), this, SLOT(findItem()));
        fileMenu->addAction(findAction);
        findAction->setEnabled(false);

        QAction* refreshAction   = new QAction(tr("&Refresh"), window);
        refreshAction->setShortcut(Qt::CTRL + Qt::Key_R);
            connect(refreshAction, SIGNAL(triggered(bool)), this, SLOT(refreshGUI()));
        fileMenu->addAction(refreshAction);

        fileMenu->addSeparator ();

        QAction* exitAction   = new QAction(tr("&Exit"), window);
            exitAction->setShortcut(Qt::CTRL + Qt::Key_X);
            connect(exitAction, SIGNAL(triggered()), this, SLOT(realExit()));
            fileMenu->addAction(exitAction);


       QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));

       QAction* clipAction   = new QAction(tr("&Copy to Clipboard"), window);
           clipAction->setShortcut(Qt::CTRL + Qt::Key_C);
           connect(clipAction, SIGNAL(triggered()), this, SLOT(copyToClipboard()));
           editMenu->addAction(clipAction);

       QAction* logfileAction   = new QAction(tr("&Open Logfile"), window);
           logfileAction->setShortcut(Qt::CTRL + Qt::Key_O);
           connect(logfileAction, SIGNAL(triggered()), this, SLOT(openLogfile()));
           editMenu->addAction(logfileAction);


       QMenu* helpMenu = menuBar()->addMenu(tr("&?"));

       QAction* aboutAction   = new QAction(tr("&about"), window);
           connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
           helpMenu->addAction(aboutAction);

// End of Menu
/*
|----------------|
| Maingrid       |
| |----------|   |
| |Topgrid   |   |
| |          |   |
| |----------|   |
|                |
| |-------------||
| |Body |-----| ||
| |     |Info | ||
| |     |     | ||
| |     |-----| ||
| |-------------||
|----------------|

*/



        QGridLayout *mainGrid = new QGridLayout (window);
        QGridLayout *topGrid = new QGridLayout (window);
            mainGrid->addLayout(topGrid,0,0);

        QGridLayout *bodyGrid = new QGridLayout (window);
                mainGrid->addLayout(bodyGrid,1,0,1,2);

        QGridLayout *infoGrid = new QGridLayout (window);
                bodyGrid->addLayout(infoGrid,0,1);

        //Hostname
        topGrid->addWidget(new QLabel("Computername:", window),0,0);
        QLineEdit *hostLine = new QLineEdit(window);
            hostLine->setText(qgetenv("COMPUTERNAME"));
            hostLine->setReadOnly(true);
            topGrid->addWidget(hostLine,0,1);
        //End Hostname

        //Domain
        topGrid->addWidget(new QLabel("Domain:", window),1,0);
        QLineEdit *userdomainLine = new QLineEdit(window);
            userdomainLine->setText(qgetenv("USERDOMAIN"));
            userdomainLine->setReadOnly(true);
            topGrid->addWidget(userdomainLine,1,1);
        //End Domain


        //Username
        topGrid->addWidget(new QLabel("Username:", window),2,0);
        QLineEdit *userLine = new QLineEdit(window);
            userLine->setText(qgetenv("USERNAME"));
            userLine->setReadOnly(true);
            topGrid->addWidget(userLine,2,1);
        //End Username

        //Interface
        topGrid->addWidget(new QLabel("Interface:", window),5,0);

        interfaceBox = new QComboBox(window);
            connect(interfaceBox, SIGNAL(currentIndexChanged ( int )), this, SLOT(interfaceBoxIndexChanged ( int )));
        topGrid->addWidget(interfaceBox,5,1);
        //End Interface


        //MAC
        topGrid->addWidget(new QLabel("MAC:", window),6,0);
        macLine = new QLineEdit(window);
        macLine->setReadOnly(true);
            topGrid->addWidget(macLine,6,1);
        //End MAC

        //IP
        topGrid->addWidget(new QLabel("IP:", window),7,0);
        ipLine = new QLineEdit(window);
        ipLine->setReadOnly(true);
            topGrid->addWidget(ipLine,7,1);
        //End IP

        //Mask
        topGrid->addWidget(new QLabel("Netmask:", window),8,0);
        maskLine = new QLineEdit(window);
        maskLine->setReadOnly(true);
            topGrid->addWidget(maskLine,8,1);
        //End Mask

        topGrid->addItem(new QSpacerItem ( 10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum ),0,1);
        //Index
            /*
        topGrid->addWidget(new QLabel("Index:", window),9,0);
        indexLine = new QLineEdit(window);
        indexLine->setReadOnly(true);
            topGrid->addWidget(indexLine,9,1);
            */
        //End Mask

        //The Tree
        treeWidget = new QTreeWidget(window);
            treeWidget->setColumnCount(6);
            treeWidget->setSortingEnabled(false);
            treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
            treeWidget->setFont(QFont(font().family(), 12));

            QStringList treeHeaderLabels;
            treeHeaderLabels << "Tool" << "Author" << "Version" << "Path" << "Tree" << "who";
                treeWidget->setHeaderLabels(treeHeaderLabels);
                treeWidget->setColumnHidden(1, true);
                treeWidget->setColumnHidden(2, true);
                treeWidget->setColumnHidden(3, true);
                treeWidget->setColumnHidden(4, true);
                treeWidget->setColumnHidden(5, true);
          connect(treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(treeItemPressed(QTreeWidgetItem*,int)));
        bodyGrid->addWidget(treeWidget,0,0);


        //Infos on the right
        infoScript = new QLabel(window);
            infoGrid->addWidget(infoScript,0,0);

        infoPath = new QLabel(window);
            infoGrid->addWidget(infoPath,1,0);

        infoAuthor = new QLabel(window);
            infoGrid->addWidget(infoAuthor,2,0);

        infoVersion = new QLabel(window);
            infoGrid->addWidget(infoVersion,3,0);

        QHBoxLayout *buttonLayout = new QHBoxLayout(window);
        runButton = new QPushButton("  Start  ",window);
            runButton->setEnabled(false);
            connect(runButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));

        //Push Button to the right
        buttonLayout->addWidget(runButton);
        buttonLayout->addItem(new QSpacerItem ( 10, 10, QSizePolicy::Expanding, QSizePolicy::Maximum ));
        infoGrid->addLayout(buttonLayout,4,0);


        //QSpacerItem ( int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Minimum, QSizePolicy::Policy vPolicy = QSizePolicy::Minimum )
        //top Grid nach links
        mainGrid->addItem(new QSpacerItem ( 300, 10, QSizePolicy::Expanding, QSizePolicy::Maximum ),0,1);

        //make tree big
        bodyGrid->addItem(new QSpacerItem ( 0, 10, QSizePolicy::Maximum, QSizePolicy::Expanding ),0,2);

        //button up
        infoGrid->addItem(new QSpacerItem ( 10, 10, QSizePolicy::Maximum, QSizePolicy::Expanding ),5,0);



        //Initial IP filling
        refreshGUI();

}

ApplicationWindow::~ApplicationWindow()
{
}

QString ApplicationWindow::createHeaderText()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString text;
    text=dt.toString(Qt::ISODate)+"\n\n";
    text=text + "Computername: " + qgetenv("COMPUTERNAME")+"\n";
    text=text + "Userdomain: " + qgetenv("USERDOMAIN")+"\n";
    text=text + "Usernamename: " + qgetenv("USERNAME")+"\n\n";
    text=text + "Interface: " + interfaceBox->currentText()+"\n";
    text=text + "IP: " + ipLine->text()+"\n";
    text=text + "Netmask: " + maskLine->text()+"\n";
    text=text + "MAC: " + macLine->text()+"\n\n";
    return text;
}

void ApplicationWindow::writeLogHeader()
{
    writeLog(createHeaderText());
}

void ApplicationWindow::copyToClipboard()
{
    clipboard->setText(createHeaderText());
}

void ApplicationWindow::realExit()
{
    qApp->quit();
}

void ApplicationWindow::openLogfile()
{
        QDateTime dt = QDateTime::currentDateTime();
        QString Logfile="log_" + qgetenv("USERNAME") + "_" + dt.toString("ddMMyy") + ".txt";
            QProcess *p = new QProcess(this);
        p->startDetached("notepad.exe",QStringList() << Logfile);
}

void ApplicationWindow::systemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        showNormal();
        raise();
    }
}

void ApplicationWindow::refreshGUI()
{
            interfaceBoxIndexChanged(0);
            getInterfaces();
            getScripts();
            writeLogHeader();
            QString text=interfaceBox->currentText() + ": " + ipLine->text() +  "\nComputer: " + qgetenv("COMPUTERNAME") + "\nUser: " +qgetenv("USERNAME") + "\n";
            iconTray->setToolTip(text);
}

void ApplicationWindow::interfaceBoxIndexChanged(int boxIndex)
{
    //get the right index data
    int interfaceIndex=interfaceBox->itemData(boxIndex).toInt();
    QNetworkInterface tmpInterface = QNetworkInterface::interfaceFromIndex (interfaceIndex);

    macLine->setText(tmpInterface.hardwareAddress());
   // indexLine->setText(QString("%1").arg(interfaceIndex));

    QList<QNetworkAddressEntry> interfaceAdresses;
    interfaceAdresses=tmpInterface.addressEntries();

    if (interfaceAdresses.size()>0)
    {
        ipLine->setText(interfaceAdresses[0].ip().toString());
        maskLine->setText(interfaceAdresses[0].netmask().toString());
    }
    else
    {
        ipLine->setText("");
        maskLine->setText("");
    }

}

//Get all the Scripts
void ApplicationWindow::getScripts()
{
    treeWidget->clear();

    QList<QTreeWidgetItem *> items;

    installPath.setFilter(QDir::Files);

    QFileInfoList list = installPath.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        //send FilePath to function below and get back a nice stringlist
        QStringList scriptInfos;
        scriptInfos=getScriptComments(fileInfo.filePath());

        //this is the path tree like "network ping"
        QString scriptTree=QString(scriptInfos[4]).trimmed();
        if (!(scriptTree.isEmpty()))
        {
            QStringList treeList=scriptTree.split(" ");
            for (int i=0;i < treeList.size();i++)
            {
                QList<QTreeWidgetItem *> foundList1 = treeWidget->findItems(treeList.at(i),Qt::MatchRecursive, 0);
                //There has been no such item so far, lets create it as topLevelItem
                // but only for the first item, that not have been found

                //TopLevel
                if ((foundList1.size() < 1) && (i<1))
                {
                    treeWidget->addTopLevelItem(new QTreeWidgetItem(treeWidget,QStringList( treeList.at(i) ) ));
                    //QMessageBox::information(this,"topLevel","TopLevel: foundlist: " + QString("%1").arg(foundList1.size()) + " " +scriptTree +" | " + treeList.at(i));
                }

                //Next Level
                if ((foundList1.size() < 1) && (i>0))
                {
                        //find "parent", TopLevel was created
                        QList<QTreeWidgetItem *> foundList2 = treeWidget->findItems(treeList.at(i-1),Qt::MatchRecursive, 0);
                        QTreeWidgetItem *parentItem=foundList2[0];

                        QTreeWidgetItem *subfolder = new QTreeWidgetItem((QTreeWidgetItem *)0,QStringList(treeList.at(i)));
                        subfolder->setText(5,"Subfolder");
                        parentItem->addChild(subfolder);
                        //QMessageBox::information(this,"addChildasParent","SubFolder: Parent->" + parentItem->text(0) + " foundlist2: " + QString("%1").arg(foundList2.size()) + " " +scriptTree +" | " + treeList.at(i));
                }

                //Create Child, if Last Level
                if (i==treeList.size()-1)
                {
                    QList<QTreeWidgetItem *> foundList2 = treeWidget->findItems(treeList.at(i),Qt::MatchRecursive, 0);
                    QTreeWidgetItem *parentItem=foundList2[0];
                    QTreeWidgetItem *child = new QTreeWidgetItem((QTreeWidgetItem *)0,scriptInfos);
                    child->setText(5,"Child");
                    parentItem->addChild(child);
                    //QMessageBox::information(this,"Child","Child: Parent->" + parentItem->text(0) + " " + scriptTree + " | " + treeList.at(i));
                }
            //else -> you already exists, go home, you're drunk

            }
        }

        //items.append(new QTreeWidgetItem(treeWidget, scriptInfos));
        //QMessageBox::information(this,"info",fileInfo.fileName());
    }
     //treeWidget->insertTopLevelItems(0, items);
}

//gets comments for all scripts
QStringList ApplicationWindow::getScriptComments(QString filePath)
{
    QString author;
    QString displayname;
    QString version;
    QString tree;
    int infoCount=0;

    QStringList returnStrings;
    QFile file(filePath);
    if (file.open(QFile::ReadOnly))
    {
        for (int i=0;i<6;i++)
        {
            QByteArray line = file.readLine();
            if (QString(line.data()).contains(QRegExp("^rem displayname")))
            {
                displayname=QString(line.data()).split(":")[1].trimmed();
                infoCount++;
            }
            else if (QString(line.data()).contains(QRegExp("^rem author")))
            {
                author=QString(line.data()).split(":")[1].trimmed();
                infoCount++;
            }
            else if (QString(line.data()).contains(QRegExp("^rem version")))
            {
                version=QString(line.data()).split(":")[1].trimmed();
                infoCount++;
            }
            else if (QString(line.data()).contains(QRegExp("^rem tree")))
            {
                tree=QString(line.data()).split(":")[1].trimmed();
                infoCount++;
            }

        }

    }
    if (infoCount>3)
    {
        returnStrings << displayname << author << version << filePath << tree;
    }
return returnStrings;
}


void ApplicationWindow::treeItemPressed(QTreeWidgetItem* item,int coloum)
{
    //"Tool" << "Author" << "Version" << "Path" << "Tree" << "who";
    if (!(item->text(3).isEmpty()))
    {
        infoScript->setText(item->text(0).trimmed());
        infoAuthor->setText("Author: " + item->text(1).trimmed());
        infoVersion->setText("Version: "+item->text(2).trimmed());
        infoPath->setText(item->text(3));
        runButton->setEnabled(true);

        QString text="Click Start to execute \"" + infoScript->text() + "\"";
        statusBar()->showMessage(text);


    }
    else
    {
        infoScript->setText("");
        infoAuthor->setText("");
        infoVersion->setText("");
        infoPath->setText("");
        runButton->setEnabled(false);
        statusBar()->showMessage("Welcome");
    }
}


void ApplicationWindow::runButtonClicked()
{
    if (!(infoPath->text().isEmpty()))
    {
       cmdProcess *myProcess = new cmdProcess(this,infoScript->text());
            connect(myProcess, SIGNAL(writeLog(QString)), this, SLOT(writeLog(QString)));
                QDateTime dt = QDateTime::currentDateTime();
                QString text;
                text="\n########################################################################\n";
                    text=text + dt.toString(Qt::ISODate)+"\n";
                    text=text + "Starting " + infoPath->text() + "\n\n";
                writeLog(text);

            myProcess->start("cmd.exe", QStringList() << "/c" << infoPath->text());
    }
}

void ApplicationWindow::getInterfaces()
{
    interfaceBox->clear();
    networkInterfaceList = QNetworkInterface::allInterfaces();
    for (int i = 0; i < networkInterfaceList.size(); ++i)
    {
        if (networkInterfaceList.at(i).isValid())
        {
         //   if (networkInterfaceList.at(i).humanReadableName().contains(QRegExp(".*(LAN|Mobil|Ethernet).*",Qt::CaseInsensitive)))
           // {
            if (networkInterfaceList.at(i).flags().testFlag(QNetworkInterface::IsRunning))
            {
                if (networkInterfaceList.at(i).addressEntries().size()>0)
                {
                    interfaceBox->addItem(networkInterfaceList.at(i).humanReadableName(),networkInterfaceList.at(i).index());
                }
            }
            //}
        }
    }

}

void ApplicationWindow::writeLog(QString text)
{
    QDateTime dt = QDateTime::currentDateTime();

    QFile file("log_" + qgetenv("USERNAME") + "_" + dt.toString("ddMMyy") + ".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        QMessageBox::critical(this,"Write to log" ,"Could not write log file " + file.fileName());

    QTextStream out(&file);
    out << text;
}

void ApplicationWindow::about()
{
    QMessageBox::information(this, "Info", "Info written by Rene Storm (2013)\nLicense GPL v3\n");
}

/////////////////////////////////////////

