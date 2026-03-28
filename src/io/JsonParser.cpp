//
// Created by KoTz on 20/11/2025.
//

#include "../../include/io/JsonParser.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <nlohmann/json.hpp>
#include <fstream>


void json_parser::removeQuotes(QString  & str) {
    if (str.isEmpty()) {
        return;
    }
    if (str.contains("\"")) {
        str.remove("\"");
    }
}


bool json_parser::WriteFileJson(QString pathc,std::string chave,std::string text) {
    if (pathc.isEmpty() == false) {
        QFile filew{pathc};
        filew.open(QFile::ReadOnly | QFile::Text | QFile::WriteOnly);
        nlohmann::json json = nlohmann::json::parse(filew.readAll().toStdString());
        json[chave] = text;
        std::ofstream teste(pathc.toStdString());
        teste << std::setw(2) << json << std::endl;
        teste.close();
        filew.close();
        return true;
    }
    return false;
}


nlohmann::json json_parser::info_file(INFO obj) {
    nlohmann::json json = {
        {"idioma" ,      obj.idioma},
        {"config",       obj.config},
        {"tema",         obj.tema},
        {"Fonte",        obj.fonte},
    };
    return json;
}


QString json_parser::GetFileJson_Str(QString patch, QString key) {
    nlohmann::json json;
    QString get;
    QFile filew{patch};
    filew.open(QFile::ReadOnly | QFile::Text);
    try {
        json = nlohmann::json::parse(filew.readAll().toStdString());
    }catch (nlohmann::json::exception & e) {
        qDebug () << e.what();
        return "Error";
    }
    get = QString::fromStdString(json[key.toStdString()]).remove("'").remove("\\");
    return get;
}
nlohmann::json json_parser::GetFileJson(QString Patch, QString key) {
    nlohmann::json json;
    QFile filew{Patch};
    filew.open(QFile::ReadOnly | QFile::Text);
    try {
        json = nlohmann::json::parse(filew.readAll().toStdString());
    }catch (nlohmann::json::exception & e) {
        qDebug () << e.what();
        return nlohmann::json {};
    }
    return json[key.toStdString()];
}
json_parser::json_parser() {

}
