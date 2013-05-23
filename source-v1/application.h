#ifndef APPLICATION_H
#define APPLICATION_H

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QFontDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QObject>
#include <QPushButton>
#include <QRegExp>
#include <QStatusBar>
#include <QString>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QProcess>
#include <QClipboard>
#include <QPixmap>
#include <QColor>
#include <QBitmap>

//#include "icons.h"
#include "cmdprocess.h"

class ApplicationWindow: public QMainWindow
{
    Q_OBJECT

public:
    ApplicationWindow();
    ~ApplicationWindow();


protected:

private slots:
    void interfaceBoxIndexChanged(int);
    void getScripts();
    QStringList getScriptComments(QString);
    void treeItemPressed(QTreeWidgetItem*,int);
    void runButtonClicked();
    void getInterfaces();
    void refreshGUI();
    void realExit();
    void systemTrayActivated(QSystemTrayIcon::ActivationReason);
    void writeLogHeader();
    void copyToClipboard();
    QString createHeaderText();
    void openLogfile();
    void about();

public slots:
    void writeLog(QString);
private:
       QString appPath;
       QString logfilePath;
       QWidget *window;
       QList<QNetworkInterface> networkInterfaceList;
       QComboBox *interfaceBox;
       QLineEdit *macLine;
       QLineEdit *maskLine;
       QLineEdit *ipLine;
      // QLineEdit *indexLine;
       QTreeWidget *treeWidget;
       QDir installPath;

       QLabel *infoScript;
       QLabel *infoPath;
       QLabel *infoAuthor;
       QLabel *infoVersion;
       QLabel *infoArgumentsTitle;
       QLineEdit *infoArgumentsValue;
       QPushButton *runButton;
       QSystemTrayIcon *iconTray;
       QClipboard *clipboard;
       bool writeLogBool;
};
#endif
/* TODO
  if installPath not exists, then create
*/


