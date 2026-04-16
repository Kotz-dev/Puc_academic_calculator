//
// Created by KoTz on 20/11/2025.
//

#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <nlohmann/json.hpp>
#include <QString>


struct ConfigFileData {
     std::string idioma;
     std::string config;
     std::string tema;
     std::string fonte;
};

struct file_ {
     nlohmann::json json;
     bool isOpen;
     bool exist;
};


class JsonParser {
public :
     static file_ LoadJson(QString filePath);
     static nlohmann::json buildConfigJson(ConfigFileData obj);
     static QString readJsonKeyAsString(QString filePath, QString key);
     static nlohmann::json readJsonKey(QString filePath, QString key);
     static bool writeJsonKey(QString filePath, std::string key, std::string value);
     static void removeQuotes(QString & str);
     JsonParser();
};


#endif //JSON_PARSER_H