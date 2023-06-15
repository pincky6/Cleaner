QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApplicationManager/applicationinfoitem.cpp \
    ApplicationManager/applicationinfowidget.cpp \
    ApplicationManager/applicationmanager.cpp \
    ApplicationManager/applicationmanagerworker.cpp \
    BrowserManager/browserinfoitem.cpp \
    BrowserManager/browserinfowidget.cpp \
    BrowserManager/browsermanager.cpp \
    BrowserManager/browsermanagerworker.cpp \
    MultithreadTask/taskqueue.cpp\
    abstractcheckablemanager.cpp \
    abstractinfowidget.cpp \
    abstractmanager.cpp \
    abstractworker.cpp \
    main.cpp \
    cleanerwindow.cpp \
    registryquery.cpp \
    searchwidget.cpp\
    tasks.cpp

HEADERS += \
    ApplicationManager/applicationinfoitem.h \
    ApplicationManager/applicationinfowidget.h \
    ApplicationManager/applicationmanager.h \
    ApplicationManager/applicationmanagerworker.h \
    BrowserManager/browserinfoitem.h \
    BrowserManager/browserinfowidget.h \
    BrowserManager/browsermanager.h \
    BrowserManager/browsermanagerworker.h \
    MultithreadTask/taskqueue.h\
    MultithreadTask/task.h\
    abstractcheckablemanager.h \
    abstractinfoitem.h \
    abstractinfowidget.h \
    abstractmanager.h \
    abstractworker.h \
    cleanerwindow.h \
    registryquery.h \
    searchwidget.h \
    tasks.h

FORMS += \
    abstractinfowidget.ui \
    abstractmanager.ui \
    cleanerwindow.ui \
    searchwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
