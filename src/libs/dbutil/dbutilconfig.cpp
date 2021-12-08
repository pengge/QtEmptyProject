#include "dbutilconfig.h"

#include <QFile>
#include <QJsonObject>
#include <QDir>
#include <QFileInfoList>

DbUtilConfig::DbUtilConfig()
    : debug(false)
    , sqlFiles()
{
    QJsonDocument jsonConfig = readConfigFile(":res/dbutil.json");
    readJsonConfig(jsonConfig);
}

QJsonDocument DbUtilConfig::readConfigFile(const QString& configFilePath)
{
    QJsonDocument jsonConfig;

    QFile file(configFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("DbUtilConfig: Config file '%s' cannot be opened", qPrintable(configFilePath));
        jsonConfig = QJsonDocument();
    } else {
        jsonConfig = QJsonDocument::fromJson(file.readAll());
    }
    file.close();

    return jsonConfig;
}


void DbUtilConfig::readJsonConfig(const QJsonDocument& jsonConfig)
{
    QVariantMap configMap = jsonConfig.object().toVariantMap();
    QVariantMap dbutilConfig = configMap.value("dbutil", QVariantMap()).toMap();

    this->debug = dbutilConfig.value("debug", false).toBool();
//    this->sqlFiles = dbutilConfig.value("sqlFiles", QStringList()).toStringList();
    //直接读取资源路径下的所有sql配置文件
    QDir dir(":/res/sqls");
    foreach(QFileInfo info, dir.entryInfoList()) {
        this->sqlFiles<<info.filePath();
    }
}

QStringList DbUtilConfig::getSqlFiles() const
{
    return sqlFiles;
}

void DbUtilConfig::setSqlFiles(const QStringList &value)
{
    sqlFiles = value;
}

DbUtilConfig &DbUtilConfig::instance()
{
    static DbUtilConfig instance;//静态局部变量，内存中只有一个，且只会被初始化一次
    return instance;
}

bool DbUtilConfig::getDebug() const
{
    return debug;
}

void DbUtilConfig::setDebug(bool value)
{
    debug = value;
}
