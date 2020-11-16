#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <QJsonObject>

// Declaration
namespace global
{
    extern QJsonObject configObject;
}

QJsonObject openConfigFile(QString path);
#endif // GLOBAL_H
