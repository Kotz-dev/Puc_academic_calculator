//
// Created by KoTz on 25/07/2025.
//
#include "io/FileManager.h"

#include <iostream>
#include "JsonParser.h"

std::vector<std::filesystem::path> ListFiles(std::filesystem::path is) {
    std::vector<std::filesystem::path> style_sheet_paths;
    if (is.empty() == false) {
        for (auto & i : std::filesystem::recursive_directory_iterator(is)) {
            style_sheet_paths.push_back(i.path());
        }
    }
    return style_sheet_paths;
}

QString loadStyleSheet (std::string name,PATCH_TYPE_ type) {
    QString styleSheet;

    std::string Path = "";
    if (type == FILE_styles) {
        Path = "resources/styles/";
        std::filesystem::path get = std::filesystem::current_path().remove_filename() / Path;
        for (auto & i :  ListFiles(get)) {
            if (i.string().find(name) != std::string::npos) {
                QFile f(i);
                f.open(QFile::ReadOnly);
                styleSheet = f.readAll();
            }
        }
       return styleSheet;
    }
    if (type == FILE_IMAGE) {
        Path = "resources/images/";
        auto c = std::filesystem::current_path().remove_filename() / Path / name;
        QString teste = QString::fromStdString(c.string());
        return teste;
    }
    return "";
}

enum OS {
    LINUX = 1,
    WINDOWS = -1
};
FileSystemInfo FileManager::resolveFilePaths(FileType type) {
    FileSystemInfo Cfile
    {
        "",
        false
    };

    if (getOperatingSystem() == OS::LINUX) {
        if (FileType::PUCSimulador == type) {
            Cfile.file_ = "/home/" + QDir::home().dirName().toStdString() + "/Documentos/PUCSimulador";
        }
        if (FileType::CONFIG == type) {
            Cfile.file_ = "/home/" + QDir::home().dirName().toStdString() + "/Documentos/PUCSimulador/config.cfgVx";
        }
    }
    if (getOperatingSystem() == OS::WINDOWS) {
        if (FileType::PUCSimulador == type) {
            Cfile.file_ = QDir::homePath().toStdString() + "/Documents/PUCSimulador";
        }
        if (FileType::CONFIG == type) {
            Cfile.file_ = QDir::homePath().toStdString() + "/Documents/PUCSimulador/config.cfgVx";
        }
    }
    if (Cfile.file_.empty() == false) {
        Cfile.exist = std::filesystem::exists(Cfile.file_);
    }
    return Cfile;
}
const ApplicationConfig defaultConfig
{
    "Português", // Idioma padrão
    "0.1", // Versão
    "Arial", // Fonte padrão
    "Claro" // Tema padrão
};

/**
 * Inicializa o sistema de gerenciamento de arquivos configurando diretórios e arquivo de configuração
 *
 * Esta função:
 * 1. Cria um diretório para a aplicação na pasta Documentos do usuário
 * 2. Verifica se o arquivo config.json existe e é válido
 * 3. Se o arquivo de configuração não existir ou for inválido, cria um novo com configurações padrão
 */
void FileManager::initialize() {
    if (resolveFilePaths(FileType::PUCSimulador).exist == false){
        std::filesystem::create_directories(resolveFilePaths(FileType::PUCSimulador).file_);
    }
    GLOBAL::FILE_PATHS::CONFIG   = std::move(QString::fromStdString(resolveFilePaths(FileType::CONFIG).file_.string()));

    if (resolveFilePaths(FileType::CONFIG).exist == false) {
        save(GLOBAL::FILE_PATHS::CONFIG, defaultConfig);
    }
}


bool FileManager::isJsonFileEmpty(QString path) {
    return JsonParser::LoadJson(path).json.empty();
}

bool isFile (std::fstream & file) {
    if (file.good()) {
        file.close();
        return true;
    }
    if (file.fail()) {
        return false;
    }
    return false;
}

bool FileManager::Load(QString path,Json & get_json) {
    if (!path.isEmpty() && std::filesystem::exists(path.toStdString())) {
        get_json = JsonParser::LoadJson(path).json;
        return true;
    }
    return false;
}

bool FileManager::Load(const QString path,Json & get_json,bool & is_open) {

    if (path.isEmpty() == true) {
        return false;
    }
      file_ file =  JsonParser::LoadJson(path);
      get_json = file.json;
      is_open = file.isOpen;
      return true;
}

FileStatus FileManager::checkFileStatus(QString path) {
    QFile file(path);
    return {file.open(QFile::Text | QFile::ReadOnly), path};
}
bool FileManager::save(QString path, std::variant<item_vector_array, ApplicationConfig> obj) {
    if (path.isEmpty() == true) {
        return false;
    }
    QFile filew(path);
    if (filew.exists() == true) {
        filew.remove();
    }
    nlohmann::ordered_json json_;

    std::fstream file(path.toStdString(),std::ios::app);
    if (file.is_open() == true) {
        if (std::holds_alternative<item_vector_array>(obj)) {
            if (std::get<item_vector_array>(obj).empty() == false) {
                nlohmann::ordered_json json = nlohmann::ordered_json::array();
                for (auto & value : std::get<item_vector_array>(obj)) {
                    nlohmann::ordered_json basic_json = {
                        {"nome",value.name.toStdString()},
                        {"aulas previstas",value.planned_classes},
                        {"aulas ministradas",value.taught_classes},
                        {"numero presenca",value.attendance_count},
                        {"N1",value.N1},
                        {"N2",value.N2},
                    };
                    json.push_back(basic_json);
                }
                file << json.dump(4);
            }
        }
        if (std::holds_alternative<ApplicationConfig>(obj))
        {
            auto  json = JsonParser::buildConfigJson(
                              ConfigFileData{std::get<ApplicationConfig>(obj).language.toStdString(),
                                    GLOBAL::FILE_PATHS::CONFIG.toStdString(),
                                     std::get<ApplicationConfig>(obj).themeName.toStdString(),
                                    std::get<ApplicationConfig>(obj).fontFamily.toStdString()});
            file << json.dump(2);
        }
    }
   return isFile(file);
}
FileManager::FileManager() {}
