#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T21:27:43
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = group_manager_system
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


SOURCES += main.cpp\
        mainwindow.cpp \
    dbconnt.cpp \
    user.cpp \
    group.cpp \
    student.cpp \
    department.cpp \
    studentdependence.cpp \
    teacher.cpp \
    root.cpp \
    registform.cpp \
    selectteacherform.cpp \
    teachermainwindow.cpp \
    groupmainwindow.cpp \
    rootmainwindow.cpp

HEADERS  += mainwindow.h \
    dbconnt.h \
    debugmode.h \
    user.h \
    group.h \
    student.h \
    department.h \
    studentdependence.h \
    teacher.h \
    root.h \
    registform.h \
    selectteacherform.h \
    teachermainwindow.h \
    groupmainwindow.h \
    rootmainwindow.h

FORMS    += mainwindow.ui \
    registform.ui \
    selectteacherform.ui \
    teachermainwindow.ui \
    groupmainwindow.ui \
    rootmainwindow.ui

RESOURCES += \
    res.qrc

CONFIG += resources_big
