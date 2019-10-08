#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T12:51:04
#
#-------------------------------------------------
QT       +=network
QT       += core gui
QT       += multimedia
QT       += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = getMusic
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp\
        getpixmap.cpp\
        downloadfile.cpp\
        file_info.cpp\
        getlrc.cpp

HEADERS  += widget.h\
                           getpixmap.h\
                           downloadfile.h\
                           file_info.h\
                           getlrc.h
#将图片编译到程序中
RESOURCES     += image.qrc

###指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录       
MOC_DIR=$$PWD/../temp/moc
RCC_DIR=$$PWD/../temp/rcc
UI_DIR=$$PWD/../temp/ui
OBJECTS_DIR=$$PWD/../temp/obj
DESTDIR=$$PWD/../temp/bin