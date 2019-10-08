#ifndef WIDGET_H
#define WIDGET_H

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QJsonParseError>
#include <QJsonDocument>
//解析歌词
#include <QTextStream>
#include <QTextCodec>
#include <QTime>
#include <QTimer>
//写文件
#include <QDir>
#include <QFile>
//处理进度条
#include <QTimerEvent>
#include <QSlider>
#include <QMessageBox>

struct CHANNEL_INFO
{
    QString channelId;   //频道ID
    QString channelName;    //频道名称
};
struct SONG_INFO
{
    QString songRealLink;//歌曲下载链接
    QString songName;    //歌名
    QString artistName;  //作者名
    QString songPicSmall; //歌手小图片
    QString songPicRadio;//歌手大图片
    QString time;
    QString albumName;//专辑名
    QString lyricLink;//歌词下载地址
    QString  size;
};

struct QLyric
{
    qint64 time;//时间
    QString lyric;//歌词
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
            
    //public slots：    //在这个区内声明的槽意味着任何对象都可将信号与之相连接
   //始终显示作者名和歌曲名
        QString lrc;
        QString song_info;
        //更新频道
        int update_info;
            QLabel *label;
        QString  fileNames;
private slots:
   void init();
   void main_info();
   void info_clicked();
    //下一曲
    void on_nextButton_clicked();
        //自定义暂停函数
    void on_btn_start_clicked();
//上一曲
    void prevSong();
    //下载按钮
    void on_downLoadButton_clicked();
    //播放
    void playMusicButton_clicked(int index);
    void slotShowLyric(qint64 position);


private:
//存放频道
    QList<CHANNEL_INFO> getChannelList();
    //存放歌曲信息
    QList<QString> getSongIdList(QString channelId);
    SONG_INFO getSongRealLinkById(QString songId);
//解析歌词
    QList<QLyric> parse(QString lyric);
    //歌曲详细信息
   void info_song_clicked();

//显示当前歌曲下载地址
    QLabel *show_songPicRadio;
    QPushButton *next_Button,*prev_Button;
    QPushButton  *pause_btn;
    QPushButton *downLoadButton;
    QPushButton  *info_Btn,*info_song_btn;
    QTextEdit *lyricLabel;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    //处理歌手图片区域
    QHBoxLayout  *hboxLayout_1;
    QMediaPlayer *mediaPlayer;
    QList <CHANNEL_INFO> channelList;
    //频道列表
    
    CHANNEL_INFO currentChannelInfo;
    //当前频道信息
    QList <QString> songIdList;
    //某个频道下的歌曲列表,保存songId
    int currentSongIndex;//从songIdList获取songId
    //换频道之后，当前歌曲索引要重新设为0，并更新当前频道信息，当前歌曲信息，
    SONG_INFO currentSongInfo;
    //由songId得到的当前歌曲信息

    //解析歌词
    int  currentLyricIndex;//歌词行号索引
    QList <QLyric> lyricList;//歌词列表

//显示进度条部分
private :
QHBoxLayout *hboxLayout_2;
    bool        isplay;
   int timerID;
    int moved;
    QTimer *timer;
    QTimer *timer2;
    QTime *mov;
    QTime *mo;
    //时间标签
    QLabel *show_shijian;
    QLabel *show_time;
    //进度条
    QSlider *horizontalSlider;
    //必须加slots
    private slots: //在这个区内声明的槽意味着只有类自己可以将信号与之相连接。这适用于联系非常紧密的类。
   void posChange();
    void slot_setPosition(int value);
    void slot_durationChanged(qint64 duration );
    void slot_positionChanged(qint64 position );
       void slot_player_stateChanged(QMediaPlayer::State state);
        //受保护槽
protected slots:
//在这个区内声明的槽意味着当前类及其子类可以将信号与之相连接
        virtual void timerEvent(QTimerEvent *event);
       
     
};

#endif // WIDGET_H