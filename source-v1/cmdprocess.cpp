#include "cmdprocess.h"
using namespace std;

cmdProcess::cmdProcess(QObject * parent,QString title, Qt::WindowFlags f)
{
  //  start(program, arguments);
        setWindowTitle(title);

    show();
    resize(540,480);

    QGridLayout *mainGrid = new QGridLayout (this);

    textEdit = new QTextEdit(this);
       // textEdit->setPlainText("Text von mir...");
        textEdit->setTextBackgroundColor(QColor("black"));
        textEdit->setTextColor(QColor("white"));
        QPalette palette;
        palette.setColor(QPalette::Base, QColor("black"));
        textEdit->setFont(QFont("Courier", 10));
        textEdit->setPalette(palette);

        mainGrid->addWidget(textEdit,0,0);
}

cmdProcess::~cmdProcess()
{
}


void cmdProcess::start(QString command, QStringList arguments)
{
    p = new QProcess(this);
        connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(gotStdOut()));
        connect(p, SIGNAL(readyReadStandardError()), this, SLOT(gotStdErr()));
    p->start(command,arguments);
}

void cmdProcess::gotStdOut()
{
    QByteArray new_data;
    new_data = p->readAllStandardOutput();
    QString text = textEdit->toPlainText();



        textEdit->setPlainText(text + QString(new_data));
    emit writeLog(textEdit->toPlainText());
}

void cmdProcess::gotStdErr()
{
    QByteArray new_data;
    new_data = p->readAllStandardError();
    QString text = "Err:" + textEdit->toPlainText();
        textEdit->setPlainText(text + QString(new_data));
    emit writeLog(textEdit->toPlainText());
}

