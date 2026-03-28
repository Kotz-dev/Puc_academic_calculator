//
// Created by KoTz on 20/11/2025.
//

#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <nlohmann/json.hpp>
#include <QString>


struct  INFO {
     std::string idioma;
     std::string config;
     std::string tema;
     std::string fonte;
};


class json_parser {
public :
     static nlohmann::json info_file(INFO obj);
     static QString GetFileJson_Str(QString patch,QString key);
     static nlohmann::json GetFileJson(QString Patch,QString key);
     static bool WriteFileJson(QString Patch,std::string chave,std::string text);
     static void removeQuotes(QString & str);
     json_parser();
};


#endif //JSON_PARSER_H