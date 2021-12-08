include(../../../qtproject.pri)

#---------
include(../../libs/connectionpool/connectionpool-include.pri)
include(../../libs/dbutil/dbutil-include.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app
TARGET = carmes
DESTDIR = $$IDE_APP_PATH

#CONFIG += c++11

HEADERS        =


SOURCES        = main.cpp


INCLUDEPATH += $$PWD

include($$SHARED_PATH/shared.pri)

LIBS *= \
    -l$$qtLibraryName(ConnectionPool) \
    -l$$qtLibraryName(DbUtil) \

copy_files.files = copy.bat copy.sh 
copy_files.path = $$IDE_APP_PATH
COPIES += copy_files

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(../../rpath.pri)

OTHER_FILES += $$PWD/res/config/plugins.json


