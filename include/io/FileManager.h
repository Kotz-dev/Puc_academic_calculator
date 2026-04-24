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
#include <filesystem>
#include "utils/GlobalAccess.h"

typedef std::vector<StudentRecord> item_vector_array;

// configuracao padrão
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

enum PATCH_TYPE_ {
    FILE_styles = 0,
    FILE_IMAGE = 1,
    FILE_IDIOMA_ = 2
};

struct FileSystemInfo {
    std::filesystem::path file_;
    std::filesystem::path file_idioma;
    bool exist;
};
QString loadStyleSheet (std::string name );

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

static bool isFile(std::fstream & file);

struct  FileStatus {
     bool isOpen   = false;
     QString filePath = "";
};

struct cnd {
public :
    std::filesystem::path ToFileSystemPath;
    QString To_String_;
};


class FileManager {
private :
    QFile file;
    static bool fileIsOpen;
private :
    static FileSystemInfo resolveFilePaths(FileType type);
public :
    static void initialize();
    static FileStatus checkFileStatus(QString filePath);
    static bool isJsonFileEmpty(QString filePath);
    static bool Load( QString filePath, Json &jsonOutput);
    static bool Load( QString filePath, nlohmann::json &jsonOutput, bool &isOpen);
    static bool save( QString filePath, std::variant<item_vector_array, ApplicationConfig> dataObject);
    static cnd getResourcePath (std::string name,PATCH_TYPE_ type);
    FileManager();
};
const std::array<std::filesystem::path, 8> style_sheet_paths =
{
    FileManager::getResourcePath("window_dark.qss",FILE_styles).ToFileSystemPath,
    FileManager::getResourcePath("window_white.qss",FILE_styles).ToFileSystemPath,
    FileManager::getResourcePath("PreferencesWindowStyles_white.qss",FILE_styles).ToFileSystemPath,
    FileManager::getResourcePath("PreferencesWindowStyles_dark.qss",FILE_styles).ToFileSystemPath,
    FileManager::getResourcePath("system_evaluation_dark.qss",FILE_styles).ToFileSystemPath,
  };
#endif //FILEMANGER_H
