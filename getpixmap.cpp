#include "getpixmap.h"

#include <QDebug>
Get_Pixmap::Get_Pixmap(QObject *parent) : QObject(parent)
{

}

void Get_Pixmap::getPixmap_File(QString fileName,QString url)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl(QUrl(url));
qDebug()<<"图片地址:"<<url;
    QNetworkReply *reply = networkManager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();
        
      QFile file;
    file.setFileName(fileName);
    bool ok = file.open(QIODevice::WriteOnly);
    if(ok)
    {
        file.write(reply->readAll());
    }
}

QPixmap Get_Pixmap::setPixmap(QString url)
{
	    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl(QUrl(url));
qDebug()<<"图片地址:"<<url;
    QNetworkReply *reply = networkManager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();
        QPixmap pic;
    pic.loadFromData(reply->readAll());

    return pic;
	}