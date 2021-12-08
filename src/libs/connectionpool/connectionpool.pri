QT += sql
# Enable verbose behavior in debug mode
CONFIG(debug, debug|release) {
    DEFINES += VERBOSE
}

DEFINES += CONNECTIONPOOL_LIBRARY

HEADERS += \
    $$PWD/connectionpool_global.h \
    $$PWD/poolconfig.h \
    $$PWD/databaseconfig.h \
    $$PWD/connectionpool.h \
    $$PWD/connectionpoolprivate.h \
    $$PWD/connection.h \
    $$PWD/poolStats.h

SOURCES += \
    $$PWD/poolconfig.cpp \
    $$PWD/databaseconfig.cpp \
    $$PWD/connectionpool.cpp \
    $$PWD/connectionpoolprivate.cpp \
    $$PWD/connection.cpp

DBFILE = db.json
DISTFILES += $$DBFILE

# 拷贝 db 配置文件
copy_files.files = $$DBFILE
copy_files.path = $$IDE_BIN_PATH
COPIES += copy_files
