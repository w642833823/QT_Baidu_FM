#ifndef GETPIXMAP_H
#define GETPIXMAP_H

#include <QObject>
#include <QString>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QPixmap>
#include <QFile>


class Get_Pixmap : public QObject
{
    Q_OBJECT
public:
    explicit Get_Pixmap(QObject *parent = 0);

signals:

public slots:


public:
    void getPixmap_File(QString fileName,QString url);
    QPixmap setPixmap(QString url);
  
};

#endif // GETARISTPIC_H