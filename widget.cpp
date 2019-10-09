
#include "widget.h"
#include "getpixmap.h"
#include "downloadfile.h"
#include  "file_info.h"
#include "getlrc.h"
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
//处理404的位置
#include <QEventLoop>
#include <QFile>
//QT中的数学库
#include <QtMath>
#include <QApplication>

//判断系统
#if defined(Q_OS_WIN64)
#define    SAVE_PATH   "C:\百度FM_API/"
#endif
#if defined(Q_OS_WIN32)
#define    SAVE_PATH   "E:\百度音乐/"
#endif
#if defined(Q_OS_ANDROID)
#define    MP3_PATH       "/sdcard/Music/Mp3/"
#endif
#if defined(Q_OS_ANDROID)
#define    LRC_PATH   "/sdcard/Music/Lrc/"
#endif
#if defined(Q_OS_ANDROID)
#define    PIC_PATH       "/sdcard/Music/image/"
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    update_info(29)
{     
//数字10=随便听听
//23=火爆新歌
	//指定窗口大小
	this ->setFixedSize(640,480);
	this->init();
	   isplay = false;
  	moved =0;
	//更新进度条位置
	timer =new QTimer(this );	
  	this->setStyleSheet("QWidget{ border: 1px solid rgb(51, 161, 201);background: rgb(51,161,201);}");
}

Widget::~Widget()
{
    
}
void Widget::init()
{
	
		   mediaPlayer = new QMediaPlayer(this );
		       info_Btn =new QPushButton("点我开始播放网络音乐");
   info_Btn->setStyleSheet("QPushButton{border-radius: 5px;color:rgb(255, 255, 255);font: 75 16pt;}"
                                    "QPushButton:hover{background-color:rgb(51,161,201); color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}"); connect(info_Btn,&QPushButton::clicked,this,&Widget::info_clicked);
		    	        	   
    prev_Button=new QPushButton("上一曲");
               prev_Button->setIcon(QIcon(":/image/file_down/shang_2.png"));
    prev_Button->setIconSize(QSize(164,164));
    prev_Button->setFlat(true ); connect(prev_Button,&QPushButton::clicked,this,&Widget::prevSong);
    pause_btn=new QPushButton("暂停");
       pause_btn->setIcon(QIcon(":/image/file_down/pause.png"));
 pause_btn->setIconSize(QSize(164,164));
     connect(pause_btn,&QPushButton::clicked,this,&Widget::on_btn_start_clicked);                             
                                    
    next_Button=new QPushButton("下一曲");
    next_Button->setIcon(QIcon(":/image/file_down/next_2.png"));
    next_Button->setIconSize(QSize(164,164));
     connect(next_Button,&QPushButton::clicked,this,&Widget::on_nextButton_clicked);
                                    
    downLoadButton=new QPushButton("下载");
    downLoadButton->setIcon(QIcon(":/image/file_down/down_2.png"));
    downLoadButton->setIconSize(QSize(164,164));
     connect(downLoadButton,&QPushButton::clicked,this,&Widget::on_downLoadButton_clicked);
     //详细歌曲信息
          info_song_btn=new QPushButton("信息");                         	info_song_btn->setStyleSheet("QPushButton{border-radius: 5px;color:rgb(255, 255, 255);font: 25 26pt;}"
                                    "QPushButton:hover{background-color:rgb(51,161,205); color: black;}"
                                    "QPushButton:pressed{background-color:rgb(85, 170, 255);}");
           connect(info_song_btn,&QPushButton::clicked,this,&Widget::info_song_clicked);

	hBoxLayout =new QHBoxLayout;
	hBoxLayout->addWidget(prev_Button);
	hBoxLayout->addWidget(pause_btn);
	hBoxLayout->addWidget(next_Button);
	hBoxLayout->addWidget(downLoadButton);
	
    lyricLabel=new QTextEdit;
    
         //禁止输入
    lyricLabel->setReadOnly(true );
   
    //公用控件
    label=new QLabel;
    //实现显示歌手图片
    show_songPicRadio=new QLabel;
    //设置图片大小
    show_songPicRadio->setFixedSize(400,400);
    show_songPicRadio->setScaledContents(true );
   show_songPicRadio->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观
    hboxLayout_1=new QHBoxLayout;
    //添加弹簧
    hboxLayout_1->addSpacerItem(new QSpacerItem(200, 200));
    hboxLayout_1->addWidget(show_songPicRadio);
    hboxLayout_1->addSpacerItem(new QSpacerItem(200, 200));
//进度条部分
  	show_time=new QLabel;
	show_time->setFont(QFont("timer",20,QFont::Bold));
	QTime mo(0,0,0);

	show_time->setText(mo.toString("mm:ss"));
	show_shijian =new QLabel;
	show_shijian->setFont(QFont("timer",20,QFont::Bold));
	QTime mov(0,0,0);

	show_shijian->setText(mov.toString("mm:ss"));
    //进度条
    horizontalSlider=new QSlider(Qt::Horizontal,this ); connect(horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slot_setPosition(int) ) );
    
    hboxLayout_2=new QHBoxLayout;
    hboxLayout_2->addWidget(show_shijian);
    hboxLayout_2->addWidget(horizontalSlider);
    hboxLayout_2->addWidget(show_time);

	vBoxLayout =new QVBoxLayout;
	vBoxLayout->addWidget(info_Btn);
	    //显示歌曲图片
    vBoxLayout->addLayout(hboxLayout_1);
	vBoxLayout->addWidget(lyricLabel);
    vBoxLayout->addWidget(label);
    vBoxLayout->addWidget(info_song_btn);
    //布置进度条
    vBoxLayout->addLayout(hboxLayout_2);
    vBoxLayout->addLayout(hBoxLayout);
	setLayout(vBoxLayout);
	
	main_info();

	
	}

void Widget::main_info()
{
      
    

	}
void Widget::info_clicked()
{
        update_info=qrand()%update_info;	
     if (update_info==30)
     update_info=1;
       channelList = this->getChannelList();
  
    //随机产生
    currentChannelInfo = channelList.at(update_info);
    //初始化当前频道为channelList的第一个
    songIdList = this->getSongIdList(currentChannelInfo.channelId);

    currentSongIndex = 0;//歌曲编号索引
    currentLyricIndex = 0;//歌曲歌词行号索引
    
    //实时显示每一行歌词
//positionChanged(qint64)
// 这个是播放到什么位置的信号， 参数是以毫秒来计算的
 connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(slotShowLyric(qint64)));
    //在这里可以添加进度条连接信号
	//在这里添加进度条               
	
//positionChanged(qint64)// 这个是播放到什么位置的信号， 参数是以毫秒来计算的
	connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(slot_positionChanged(qint64)));
   //durationChanged(qint64)//这个是播放文件数据总大小的信号， 它可以获得文件时间长度。
 connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(slot_durationChanged(qint64)));
    connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slot_player_stateChanged(QMediaPlayer::State) ) );
     	    //播放歌曲
    playMusicButton_clicked(0);
}


//1、获取频道列表
QList<CHANNEL_INFO> Widget::getChannelList()
{
    const QString channelUrl = "http://fm.taihe.com/dev/api/?tn=channellist";
    QList<CHANNEL_INFO> channelInfoList;

    QNetworkRequest networkRequest;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager;

    networkRequest.setUrl(QUrl(channelUrl));

    networkManager->setCookieJar(0);
    QNetworkReply *reply = networkManager->get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();
    
    
     //int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    

    QByteArray bytes = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(bytes, &json_error));
          

    if(json_error.error != QJsonParseError::NoError)
    {
    //	return QString("error,错误提示").split(",");
    }
 
    	 
        if(jsonDoc.isObject())
        {
            QVariantMap result = jsonDoc.toVariant().toMap();//提取花括号里的键值对

            foreach(QVariant channel, result["channel_list"].toList())
            //提取[]里的频道
            
            {   //由于没个频道也是一个{}
                QVariantMap channelMap = channel.toMap();//提取花括号的键值对

                CHANNEL_INFO channelInfo;
                channelInfo.channelId = channelMap["channel_id"].toString();
                channelInfo.channelName = channelMap["channel_name"].toString();

                channelInfoList.append(channelInfo);

            }
        }
   
    

    
    return channelInfoList;
}

//2、根据频道id,获取某个频道下的歌曲列表(比如推荐频道public_tuijian_spring)
QList<QString> Widget::getSongIdList(QString channelId)
{
    const QString playListUrl = "http://fm.taihe.com/dev/api/?tn=playlist&format=json&id=";
    QNetworkRequest networkRequest;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager;

    networkRequest.setUrl(QUrl(playListUrl + channelId));

    networkManager->setCookieJar(0);

    QNetworkReply *reply = networkManager->get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();

    QList<QString> songId;
    QByteArray buf = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument jsonRes = QJsonDocument::fromJson(buf, &jsonError);;

    if(jsonError.error == QJsonParseError::NoError)
    {
        if(jsonRes.isObject())
        {
            QVariantMap result = jsonRes.toVariant().toMap();

            foreach(QVariant song, result["list"].toList())
            {
                QVariantMap songMap = song.toMap();
                QString id = songMap["id"].toString();//获取歌曲id

                //如果歌曲ID有效
                if(!id.isEmpty())
                {
                    songId.append(id);
                }
            }
        }
    }
    //返回歌曲ID
    return songId;

}

//3、根据songID(比如1615837),获取一首歌的歌曲名称和下载链接
SONG_INFO Widget::getSongRealLinkById(QString songId)
{
    const QString downLoadLinkUrl = "http://music.taihe.com/data/music/fmlink?type=mp3&rate=320&songIds=";
    QNetworkRequest networkRequest;
    QNetworkAccessManager networkManager;

    networkRequest.setUrl(QUrl(downLoadLinkUrl + songId));
    networkManager.setCookieJar(0);

    QNetworkReply *reply = networkManager.get(networkRequest);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    reply->deleteLater();

    //歌曲信息
    SONG_INFO songInfo;
    QByteArray buf = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument jsonRes = QJsonDocument::fromJson(buf, &jsonError);;


    if(jsonError.error == QJsonParseError::NoError)
    {
        if(jsonRes.isObject())
        {
            QVariantMap result = jsonRes.toVariant().toMap();
            QVariantMap dataList = result["data"].toMap();

            foreach(QVariant data, dataList["songList"].toList())
            {
                QVariantMap linkMap = data.toMap();

                songInfo.songRealLink = linkMap["songLink"].toString();
                songInfo.songName = linkMap["songName"].toString();
                songInfo.artistName = linkMap["artistName"].toString();
                songInfo.songPicSmall = linkMap["songPicSmall"].toString();
                //歌手图片
                songInfo.songPicRadio = linkMap["songPicRadio"].toString();
                songInfo.albumName = linkMap["albumName"].toString();
                songInfo.lyricLink = linkMap["lrcLink"].toString();
                songInfo.size =
                linkMap["size"].toString();
            }
        }
    }

    return songInfo;


}



//解析从网上获取的歌词
 QList<QLyric> Widget::parse(QString lyric)
{
	if (lyric==" ")
	{
		label->setText("未找到歌词");
		
		}
    QTextStream stream(&lyric);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    stream.setCodec(codec);
    currentLyricIndex = 0;
    lyricList.clear();

    //QRegExp解析歌词
    QRegExp timeExp;
    timeExp.setPatternSyntax(QRegExp::RegExp);
    timeExp.setCaseSensitivity(Qt::CaseSensitive);
    timeExp.setPattern("\\[([0-9]{2}):([0-9]{2})\\.([0-9]{2})\\]");
    //匹配[00:02.42]
    QList<QLyric> result;
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        int ret = timeExp.indexIn(line);
        QList<QTime> ticks;
        int lastindex = 0;
        while (ret >= 0)
        {
            QStringList tstr = timeExp.capturedTexts();
            QTime time(0, tstr[1].toInt(), tstr[2].toInt(), tstr[3].toInt());
            ticks.append(time);
            lastindex = ret + timeExp.matchedLength();
            ret = timeExp.indexIn(line, lastindex);
        }//经过测试，ticks只会含有一个项
        QString lyricstr = line.right(line.size() - lastindex);//提取歌词
        for (const QTime& t : ticks)//c++11
        {
            QLyric lyric;
            lyric.time = t.minute() * 60 * 1000 + t.second() * 1000 + t.msec();//单位ms
            lyric.lyric = lyricstr;
            result.append(lyric);
        }
    }
    std::sort(result.begin(), result.end(), [] (const QLyric& a, const QLyric& b) -> bool {
        return a.time < b.time;
    });

    return result;//保存了一行行的歌词
}

//显示歌词到界面上
void Widget::slotShowLyric(qint64 position)
{
    if(lyricList.size() <= 0 || currentLyricIndex >= lyricList.size())
        return;

    for(int i = 0; i < lyricList.size(); i++)
    {

        if(position > lyricList.at(i).time)
        {
            currentLyricIndex = i;
        }
    }

    //显示position之后的歌词，position之前的已经播放过了
    if(position > lyricList.at(currentLyricIndex).time)
    {
     
        lrc.clear();
        //歌词标题设置成绿色
        lrc += QString("<p align='center'><span style=' font-style:italic;color:#FFF0F5'>");
        lrc += currentSongInfo.artistName + " - " + currentSongInfo.songName;
        lrc += QString("</span></p>");

        //j从m_iCurrentIndex - 1开始，是为了显示出正在唱的前一句
        for(int j = currentLyricIndex - 1; j < lyricList.size(); j++)
        {
            if(j < 0)
                continue;

            if(currentLyricIndex == j)//正在唱的歌词，字体加粗颜色为粉红色
            {
                lrc += QString("<p align='center'><span style=' font-weight:600;color:#FFF0F5'>");
                lrc += lyricList.at(currentLyricIndex).lyric;
                lrc += QString("</span></p>");
            }
            else
            {
                lrc += "<p align='center'>";
                lrc += lyricList.at(j).lyric;
                lrc += "</p>";
            }
        }
        //加载歌词
        lyricLabel->setText(lrc);
        currentLyricIndex++;
    }
}
void Widget::playMusicButton_clicked(int index)
//播放歌曲
{
	
    if(currentSongIndex > songIdList.size()|| index < 0)
        return ;

    currentSongInfo = this->getSongRealLinkById(songIdList.at(currentSongIndex));
     
 mediaPlayer->setMedia(QUrl(currentSongInfo.songRealLink));
     
    mediaPlayer->play();
              //当前频道
  song_info =QString::number(currentChannelInfo.channelId.size())+"频道"+"\n频道名"+ currentChannelInfo.channelName + " \n该频道共有歌曲: " + QString::number(songIdList.size())+"首歌曲";
         info_song_btn->setText(QString("%1").arg(currentSongInfo.songName));
       //更新频道
	info_Btn->setText(QString("%1").arg(currentChannelInfo.channelName));
	GetLrc get_lrc;
QString lyric=get_lrc.getLrc(currentSongInfo.lyricLink);
    //从网上获取歌词
    lyricList = this->parse(lyric);//将lyric一行行地解析到lyricList
   
       //先清除图片
           show_songPicRadio->clear();
    //显示歌手图片
    Get_Pixmap getPic2; 
    QPixmap bj=getPic2.setPixmap(currentSongInfo.songPicRadio);
    //保持长宽比进行缩放
        bj = bj.scaled(show_songPicRadio->width(), show_songPicRadio->height(), Qt::KeepAspectRatio);
   //直接在QLabel上直接显示网络歌手图片
    show_songPicRadio->setPixmap(bj);
      

}
void Widget::prevSong()
{
    qDebug() << "上一曲"<< currentSongIndex << songIdList.size();
    
    if(currentSongIndex <= 0)
    {
        getChannelList();
        return;
    }

    currentSongIndex--;
   

    playMusicButton_clicked(currentSongIndex);


}
void Widget::on_nextButton_clicked()
{
    qDebug()<<"当前歌曲名:"<<currentSongInfo.songName;
        
    qDebug() << "下一首" << currentSongIndex << songIdList.size();

    
    if(currentSongIndex >= songIdList.size())
    {
        getChannelList();
        return;
    }

    currentSongIndex++;
//播放下一曲
    playMusicButton_clicked(currentSongIndex);
}


void Widget::on_downLoadButton_clicked()//点击下载歌曲按钮
{
     QDir dir;
    if(!dir.exists(PIC_PATH))
    {
        dir.mkdir(PIC_PATH);
        
    }
   
    QString fileName_Pic=PIC_PATH + currentSongInfo.songName + ".png";
    Get_Pixmap getpic;
    getpic.getPixmap_File(fileName_Pic,currentSongInfo.songPicRadio);
    label->setText("歌手图片已下载");
     QDir dir2;
    if(!dir2.exists(LRC_PATH))
    {
       
        dir2.mkdir(LRC_PATH);
    }
   
        QString file_Name =LRC_PATH + currentSongInfo.songName + ".lrc";
    GetLrc get_lrc;
    get_lrc.down_Lrc_file(file_Name,currentSongInfo.lyricLink);
    label->setText("歌词已下载");
     QDir dir3;
    if(!dir3.exists(MP3_PATH))
    {
        dir3.mkdir(MP3_PATH);

    }
    QString fileName =MP3_PATH + currentSongInfo.songName + ".mp3";
    DownLoadFile  down_mp3;
    down_mp3.getMp3File(fileName, currentSongInfo.songRealLink);
    
    label->setText("下载完成");
    
    
}


//处理进度条部分
//滑块时间事件
void Widget::timerEvent(QTimerEvent *event)
{
	//设置滑块长度为音乐长度
    if( timerID == event->timerId() )
    {
        int value = horizontalSlider->value() + 1;
        horizontalSlider->setValue( value );
        if( value == horizontalSlider->maximum() )
        {
            killTimer( timerID );
        }
    }
}

//调节快进
void Widget::slot_positionChanged(qint64 position)
{
    horizontalSlider->setValue(position);
    moved=position;
}
//durationChanged(qint64)//这个是播放文件数据总大小的信号， 它可以获得文件时间长度。
void Widget::slot_durationChanged(qint64 duration)
{
    horizontalSlider->setRange(0,duration);
    
    	//获取音乐时间总长度(进度条右边)
    	//play->duration()返回值就是音频文件的大小

}
//调节快进后,音乐播放也快进
void Widget::slot_setPosition(int value)
{
	//如果滑块改变位置，则改变音乐进度
    mediaPlayer->setPosition(value);
    moved=value;
}
	//显示当前播放进度时间和总时间长
void Widget::posChange()
{
	
    	//获取音乐时间总长度(进度条右边)
    	
			QTime displayTime(0,(mediaPlayer->duration()/60000)%60,(mediaPlayer->duration()/1000)%60);
			
			show_time->setText(displayTime.toString("mm:ss"));
	
	//显示当前播放进度时间(进度条左边那个时间)
    	moved=moved +1000;
	QTime moveTime(0,(moved/60000)%60,(moved/1000)%60);
	show_shijian->setText(moveTime.toString("mm:ss"));

}
//播放或者暂停
void Widget::on_btn_start_clicked()
{
  
    switch (mediaPlayer->state())
    {
    case QMediaPlayer::PlayingState:
    //暂停
        mediaPlayer->pause();
        
        break;
    default:
    
    //继续
        mediaPlayer->play();
        break;
    }
   

}
//播放状态的改变
void Widget::slot_player_stateChanged(QMediaPlayer::State state)
{
	
	   isplay = !isplay;
    //时间开始工作
   if (isplay)
    {
        connect(timer,SIGNAL(timeout()),this,SLOT(posChange()));
        

        timer->start(1000);

        }
        else
        {
            timer->stop();
            }
    switch (state)
    {
    case QMediaPlayer::PlayingState:
    pause_btn->setIcon(QIcon(":/image/file_down/pause.png"));
 pause_btn->setIconSize(QSize(64,64));
       
       label->setText(tr("正在播放"));
      
        break;
    default:
    pause_btn->setIcon(QIcon(":/image/file_down/play.png"));
 pause_btn->setIconSize(QSize(64,64));
    label->setText("播放以暂停");
   
    
        break;
    }
    }
    //歌曲详细信息（当点击歌曲名时显示）
    void Widget::info_song_clicked()
    {
    	
    	//转换成M
     File_Info file_info;
    
    //将QString转换成int
     // int mp3_size=currentSongInfo.size.toInt();
    	       QString  song_msg=QString("当前%1\n正在播放第%2首\n当前歌曲名:%3\n当前mp3大小:\n%4\n").arg(song_info).arg(currentSongIndex).arg(currentSongInfo.songName).arg(file_info.size(currentSongInfo.size.toInt()));
       	QMessageBox msgBox;
       	
	msgBox.setText(song_msg);
	msgBox.exec();
	
    	}
		