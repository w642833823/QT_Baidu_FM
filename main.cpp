#include "widget.h"
#include <QApplication>
#include <QRegExp>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#pragma execution_character_set("utf-8")
   
    Widget w;
    
    w.show();

    return a.exec();
}