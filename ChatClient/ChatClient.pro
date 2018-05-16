#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T18:10:12
#
#-------------------------------------------------

QT       += core gui network sql

QT += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(YLLoginPanel/YLLoginPanel.pri)
include(YLBasicWidget/YLBasicWidget.pri)
include(YLCommonControl/YLCommonControl.pri)
include(YLNetWork/YLNetWork.pri)
include(YLChatWidget/YLChatWidget.pri)
include(YLMainFrame/YLMainFrame.pri)
include(YLEntityObject/YLEntityObject.pri)
include(protobuf/protobuf.pri)
include(YLTray/YLTray.pri)
include(YLAddFriendWidgets/YLAddFriendWidgets.pri)
include(YLDataBase/YLDataBase.pri)
include(YLFileTransfer/YLFileTransfer.pri)

SOURCES += \
        main.cpp \
    yllocalsettings.cpp \
    globaldata.cpp \
    signalforward.cpp

INCLUDEPATH += /usr/local/include

LIBS += -lprotobuf \
        -llog4cxx

HEADERS += \
    yllocalsettings.h \
    globaldata.h \
    signalforward.h

RESOURCES += \
    resource.qrc

FORMS +=
