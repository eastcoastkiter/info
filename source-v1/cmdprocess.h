#ifndef CMDPROCESS_H
#define CMDPROCESS_H

#include <QEvent>
#include <QProcess>
#include <QObject>
#include <QByteArray>
#include <QTextEdit>
#include <QGridLayout>
#include <QWidget>
#include <QPalette>
#include <QMessageBox>



class cmdProcess: public QWidget
{
    Q_OBJECT

  public:
    cmdProcess( QObject * parent = 0, QString title = "Info", Qt::WindowFlags f = Qt::Window );
    ~cmdProcess();

public slots:
    void start(QString, QStringList);

private slots:
        void gotStdOut();
        void gotStdErr();

private:
    QTextEdit *textEdit;
    QProcess *p;
signals:
    void writeLog(QString);



};


#endif // CMDPROCESS_H
