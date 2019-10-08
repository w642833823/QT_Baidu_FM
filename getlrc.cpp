#include "getlrc.h"

GetLrc::GetLrc(QObject *parent) : QObject(parent)
{

}

QString GetLrc::getLrc(QString url)
{
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    qDebug() <<"歌词地址:"<< url;

    networkRequest.setUrl(QUrl(url));

    QNetworkReply *reply = networkManager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();

    QString lrc;
    lrc = reply->readAll();

    return lrc;

}

void GetLrc::down_Lrc_file(QString fileName,QString url)

{
	  QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    qDebug() <<"歌词地址:"<< url;

    networkRequest.setUrl(QUrl(url));

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