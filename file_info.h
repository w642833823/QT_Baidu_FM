#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <QObject>
#include <QString>


class File_Info : public QObject
{
    Q_OBJECT
public:
    explicit File_Info(QObject *parent = nullptr);
public :

    // 字节转KB、MB、GB
    QString size(qint64 bytes);
    // 速度转KB/S、MB/S、GB/S
     QString speed(qint64 speed  );
     // 秒转*d *h *m *s
    QString timeFormat(int seconds);
    //信号
signals:

public slots:
};

#endif // FILE_INFO_H