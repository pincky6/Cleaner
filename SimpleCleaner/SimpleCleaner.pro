QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApplicationManager/applicationinfowidget.cpp \
    ApplicationManager/applicationmanager.cpp \
    searchwidget.cpp \
    main.cpp \
    cleanerwindow.cpp \
    ApplicationManager/applicationInfoItem.cpp \
    ApplicationManager/registryapplicationquery.cpp \
    MultithreadTasks/taskqueue.cpp

HEADERS += \
    ApplicationManager/applicationinfowidget.h \
    ApplicationManager/applicationmanager.h \
    MultithreadTasks/Task.h \
    searchwidget.h\
    cleanerwindow.h\
    ApplicationManager/applicationInfoItem.h \
    ApplicationManager/registryapplicationquery.h \
    MultithreadTasks/taskqueue.h

FORMS += \
    ApplicationManager/applicationinfowidget.ui \
    ApplicationManager/applicationmanager.ui \
    ApplicationManager/searchwidget.ui \
    cleanerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
