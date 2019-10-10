# QT_Baidu_FM
仅供自己学习使用

感谢网络上无私奉献开源的作者们
实验用的
﻿
![](https://github.com/zhengtianzuo/QtQuickExamples/blob/master/QtQuickExamples.jpg?raw=true)

# QtQuickExamples
QtQuick相关的技术分享

![](https://img.shields.io/badge/%E7%89%88%E6%9D%83%E8%AE%B8%E5%8F%AF-MIT-orange.svg)
![](https://img.shields.io/badge/Qt-5.10-blue.svg)
![](https://img.shields.io/badge/VS-2017-blue.svg)
![](https://img.shields.io/badge/QtQuick-2.2-blue.svg)
![](https://img.shields.io/badge/%E7%89%88%E6%9C%AC-1.0.0.0-blue.svg)
![](https://img.shields.io/badge/%E7%BC%96%E8%AF%91-%E6%88%90%E5%8A%9F-brightgreen.svg)

QmlBusyIndicator: Qml自定义等待指示器

![](https://github.com/zhengtianzuo/QtQuickExamples/blob/master/QmlBusyIndicator/show.gif?raw=true)


QmlCheckBox: Qml自定义复选框

![](https://github.com/zhengtianzuo/QtQuickExamples/blob/master/QmlCheckBox/show.gif?raw=true)





speech-demo
项目地址：https://github.com/w642833823/QT_Baidu_FM
一下是上传步骤过程实例（没有任何作用）

获取http://music.baidu.com/的歌曲

1、获取频道列表(一个频道的两个关键元素为频道id和频道名称)
const QString channelUrl = "http://fm.baidu.com/dev/api/?tn=channellist";
http://fm.baidu.com/dev/api/?tn=channellist
struct CHANNEL_INFO
{
    QString channelId;
    QString channelName;
};

2、根据频道id,获取某个频道下的歌曲列表(比如推荐频道public_tuijian_spring)
const QString playListUrl = "http://fm.baidu.com/dev/api/?tn=playlist&format=json&id=";
http://fm.baidu.com/dev/api/?tn=playlist&format=json&id=public_tuijian_spring
QList <QString> m_songIdList;//保存songID

3、根据songID(比如1615837),获取当前歌曲信息
const QString downLoadLinkUrl = "http://music.baidu.com/data/music/fmlink?type=mp3&rate=320&songIds=";
http://music.baidu.com/data/music/fmlink?type=mp3&rate=320&songIds=1615837
struct SONG_INFO
{
    QString songRealLink;//歌曲下载链接
    QString songName;    //歌名
    QString artistName;  //作者名
    QString songPicSmall;//歌手图片
    QString songPicRadio;//也是图片
    QString time;
    QString albumName;//专辑名
    QString lyricLink;//歌词下载地址
    QString size;
};

4、获取歌词
根据lyricLink就可以获取歌词了
http:\/\/musicdata.baidu.com\/data2\/lrc\/13902654\/13902654.lrc
http:\/\/musicdata.baidu.com\/data2\/lrc\/240377291\/240377291.lrc