#include "downloadfile.h"
#include <QDebug>

DownLoadFile::DownLoadFile(QObject *parent) : QObject(parent)
{

}

void DownLoadFile::getMp3File(QString fileName, QString url)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl(QUrl(url));
    qDebug()<<"mp3地址:"<<url;

    QNetworkReply *reply = networkManager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();

    QFile file;
    file.setFileName(fileName);
    bool bOk = file.open(QIODevice::WriteOnly);
    if(bOk)
    {
        file.write(reply->readAll());
    }
}