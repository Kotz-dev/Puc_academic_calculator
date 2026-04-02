//
// Created by KoTz on 25/07/2025.
//

#ifndef FILEMANGER_H
#define FILEMANGER_H

#include <QFile>
#include "data/StudentRecord.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <QDebug>
#include <QDir>
#include <qurl.h>
#include "GlobalAccess.h"

typedef std::vector<Oitem> item_vector_array;

struct ApplicationConfig {
    QString language;
    QString appVersion;
    QString fontFamily;
    QString themeName;
};
const std::string CONFIG_FILE_EXTENSION = ".cfgVx";

enum SaveFileType {
    SAVE_FILE_JSON_ALUNO = 0,
    SAVE_FILE_JSON_SISTEMA = 1
};
enum SaveMode {
    SAVE_AS = 0,
    SAVE_LOCAL_FILE = 1

};
enum FileType {
    DATE   = 0x1475,
    CONFIG = 0x1010,
    PUCSimulador = 0x145,
    FILE_IDIOMA = 0x117,
    FILE_Desgin = 0x147

};
struct FileSystemInfo {
    std::filesystem::path file_;
    std::filesystem::path file_idioma;
    bool exist;
};

inline int getOperatingSystem () {
#ifdef __linux__
    return 1;
#endif

#ifdef  _WIN32
    return -1;
#endif

 return 0;
}

using Json = nlohmann::json;

struct  FileStatus {
     bool isOpen   = false;
     QString filePath = "";
};
class FileManger {
private :
    QFile file;
    static bool fileIsOpen;
private :
    static FileSystemInfo info_file_system(FileType type);
public :
    static void initialize_file_manager();
    static FileStatus is_open( QString filePath);
    static bool is_null_fileJson(QString filePath);
    static bool Load( QString filePath, Json &jsonOutput);
    static bool Load( QString filePath, nlohmann::json &jsonOutput, bool &isOpen);
    static bool save( QString filePath, std::variant<item_vector_array, ApplicationConfig> dataObject);
    FileManger();
};
#endif //FILEMANGER_H
