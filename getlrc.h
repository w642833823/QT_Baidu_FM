#ifndef GETLRC_H
#define GETLRC_H

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
class GetLrc : public QObject
{
    Q_OBJECT
public:
    explicit GetLrc(QObject *parent = 0);

public:
    QString getLrc(QString url);
    //下载歌词
    
    void down_Lrc_file(QString fileName,QString url);
};

#endif // GETARISTPIC_H