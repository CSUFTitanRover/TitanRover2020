#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include "global.h"

namespace global
{
    QJsonObject configObject = openConfigFile("../config.json");
}

QJsonObject openConfigFile(QString path) {
    QFile jsonFile(path);
    jsonFile.open(QFile::ReadOnly);
    // close file stream
    QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonFile.readAll());
    return jsonResponse.object();
}
