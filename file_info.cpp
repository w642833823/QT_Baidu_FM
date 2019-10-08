#include "file_info.h"

#define UNIT_KB         1024                                //KB
#define UNIT_MB        1024*1024                   //MB
#define UNIT_GB         1024*1024*1024        //GB


#define N_SEC          0                    //秒
#define N_MIN          60                  //分钟
#define N_HOUR      60*60              //小时
#define N_DAY          60*60*24          //天



File_Info::File_Info(QObject *parent) : QObject(parent)
{

}

QString File_Info::size(qint64 bytes)
{
    QString strUnit;
    double dSize = bytes * 1.0;
    if (dSize <= 0)
    {
        dSize = 0.0;
    }
    else if (dSize < UNIT_KB)
    {
        strUnit = "Bytes";
    }
    else if (dSize < UNIT_MB)
    {
        dSize /= UNIT_KB;
        strUnit = "KB";
    }
    else if (dSize < UNIT_GB)
    {
        dSize /= (UNIT_MB);
        strUnit = "MB";
    }
    else
    {
        dSize /= (UNIT_GB);
        strUnit = "GB";
    }

    return QString("%1 %2").arg(QString::number(dSize, 'f', 2)).arg(strUnit);
}

// 速度转KB/S、MB/S、GB/S
QString File_Info::speed(qint64 speed)
{
    QString strUnit;
    if (speed <= 0)
    {
        speed = 0;
        strUnit = "Bytes/S";
    }
    else if (speed < UNIT_KB)
    {
        strUnit = "Bytes/S";
    }
    else if (speed < UNIT_MB)
    {
        speed /= UNIT_KB;
        strUnit = "KB/S";
    }
    else if (speed < UNIT_GB)
    {
        speed /= (UNIT_MB);
        strUnit = "MB/S";
    }
    else
    {
        speed /= (UNIT_GB);
        strUnit = "GB/S";
    }

    QString strSpeed = QString::number(speed, 'f', 2);
    return QString("%1 %2").arg(strSpeed).arg(strUnit);
}

// 秒转*d *h *m *s
QString File_Info::timeFormat(int seconds)
{
    QString strValue;
    QString strSpacing(" ");
    if (seconds <= 0)
    {
        strValue = QString("%1s").arg(0);
    }
    //小于一分钟
    else if (seconds < 60)
    {
        strValue = QString("%1s").arg(seconds);
    }
    //小于一小时
    else if (seconds < 60 * 60)
    {
        int nMinute = seconds / 60;
        int nSecond = seconds - nMinute * 60;

        strValue = QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    //小于一天
    else if (seconds < 60 * 60 * 24)
    {
        int nHour = seconds / (60 * 60);
        int nMinute = (seconds - nHour * 60 * 60) / 60;
        int nSecond = seconds - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }
    else
    {
        //天
        int nDay = seconds / (60 * 60 * 24);
        //时
        int nHour = (seconds - nDay * 60 * 60 * 24) / (60 * 60);
        //分
        int nMinute = (seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60) / 60;
        //秒
        int nSecond = seconds - nDay * 60 * 60 * 24 - nHour * 60 * 60 - nMinute * 60;

        strValue = QString("%1d").arg(nDay);

        if (nHour > 0)
            strValue += strSpacing + QString("%1h").arg(nHour);

        if (nMinute > 0)
            strValue += strSpacing + QString("%1m").arg(nMinute);

        if (nSecond > 0)
            strValue += strSpacing + QString("%1s").arg(nSecond);
    }

    return strValue;
}

