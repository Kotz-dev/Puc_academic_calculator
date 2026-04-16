//
// Created by KoTz on 20/11/2025.
//

#include "../../include/io/JsonParser.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <nlohmann/json.hpp>
#include <fstream>


void JsonParser::removeQuotes(QString  & str) {
    if (str.isEmpty()) {
        return;
    }
    if (str.contains("\"")) {
        str.remove("\"");
    }
}

bool JsonParser::writeJsonKey(QString filePath,std::string key,std::string value) {
    if (filePath.isEmpty() == false) {
        nlohmann::json json = LoadJson(filePath).json;
        json[key] = value;
        std::ofstream outFile(filePath.toStdString());
        outFile << std::setw(2) << json << std::endl;
        outFile.close();
        return true;
    }
    return false;
}


nlohmann::json JsonParser::buildConfigJson(ConfigFileData obj) {
    nlohmann::json json = {
        {"idioma" ,      obj.idioma},
        {"config",       obj.config},
        {"tema",         obj.tema},
        {"Fonte",        obj.fonte},
    };
    return json;
}


QString JsonParser::readJsonKeyAsString(QString patch, QString key) {
    return QString::fromStdString(LoadJson(patch).json[key.toStdString()]).remove("'").remove("\\");;
}

file_ JsonParser::LoadJson(QString filePath) {
    QFile filew{filePath};;
    nlohmann::json json = {};
    bool exist = filew.exists();
    bool is_open = filew.open(QFile::ReadOnly | QFile::Text | QFile::WriteOnly);
    try {
        json = nlohmann::json::parse(filew.readAll().toStdString());
    }catch (nlohmann::json::exception & e) {
        qDebug () << e.what();
        return file_{json,false};
    }
    return file_{json,is_open,exist};
}

nlohmann::json JsonParser::readJsonKey(QString Patch, QString key) {
    return LoadJson(Patch).json[key.toStdString()];
}
JsonParser::JsonParser() {}
