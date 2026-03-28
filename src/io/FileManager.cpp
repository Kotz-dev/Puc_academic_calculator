//
// Created by KoTz on 25/07/2025.
//
#include "io/FileManager.h"

#include <iostream>
#include "FileConverter.h"
#include "JsonParser.h"


enum OS {
    LINUX = 1,
    WINDOWS = -1
};
FileSystemInfo FileManger::info_file_system(FileType type) {
    FileSystemInfo Cfile
    {
        "",
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
        if (FileType::FILE_IDIOMA == type)  {
            try {
                for (auto & i : std::filesystem::recursive_directory_iterator( QDir::homePath().toStdString() + "/Documents")) {
                    if (i.path().string().find("idioma.ivx") != std::string::npos) {
                        Cfile.file_idioma = i.path().string();
                        break;
                    }
                }
            }catch (std::filesystem::filesystem_error &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    if (Cfile.file_.empty() == false) {
        Cfile.exist = std::filesystem::exists(Cfile.file_);
    }
    return Cfile;
}
const ApplicationConfig info
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
void FileManger::initialize_file_manager() {
    if (info_file_system(FileType::PUCSimulador).exist == false){
        std::filesystem::create_directories(info_file_system(FileType::PUCSimulador).file_);
    }
    GLOBAL::PATCH_FILE::CONFIG =   std::move(QString::fromStdString(info_file_system(FileType::CONFIG).file_.string()));
    GLOBAL::PATCH_FILE::LANGUAGE = std::move(QString::fromStdString(info_file_system(FileType::FILE_IDIOMA).file_idioma.string()));
    if (info_file_system(FileType::CONFIG).exist == false) {
        save(GLOBAL::PATCH_FILE::CONFIG, info);
    }
}


bool FileManger::is_null_fileJson(QString path) {
     QFile file(path);
     file.open(QFile::ReadOnly | QFile::Text);
     nlohmann::json json = {};
    try {
        json = nlohmann::json::parse(file.readAll().toStdString());
    }catch (nlohmann::json::exception & e) {
        return true;
    }
     return false;
}


bool FileManger::Load(QString path,Json & get_json) {
    if (path.isEmpty() == true) {
        return false;
    }
    QFile file(path);
    if (file.exists() == false) {
        return false;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    try {
        get_json = nlohmann::json::parse(file.readAll().toStdString());

    }catch (nlohmann::json::exception & e) {
        qDebug() << QObject::tr("Error reading file %1").arg(path);
    }
    return true;
}

bool FileManger::Load(const QString path,Json & get_json,bool & is_open) {

    if (path.isEmpty() == true) {
        return false;
    }
      QFile file(path);
      file.open(QFile::ReadWrite | QFile::WriteOnly  | QFile::Text);
      is_open = file.isOpen();
      get_json = nlohmann::json::parse(file.readAll().toStdString());
      return true;
}

FileStatus FileManger::is_open(QString path) {
    QFile file(path);
    bool is_open = file.open(QFile::Text | QFile::ReadOnly);
    FileStatus obj = {is_open, path};
    return obj;
}
bool FileManger::save(QString path, std::variant<item_vector_array, ApplicationConfig> obj) {
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
        if (std::holds_alternative<ApplicationConfig>(obj)) {
            // nlohmann::json json = {
            //     {"idioma" ,    std::get<info_config_list>(obj).idioma.toStdString()},
            //     {"config",     GLOBAL::PATCH_FILE::CONFIG.toStdString()},
            //     {"tema",       std::get<info_config_list>(obj).Theme.toStdString()},
            //     {"Fonte",      std::get<info_config_list>(obj).fonte.toStdString()},
            // };

           auto  json = json_parser::info_file(
                             INFO{std::get<ApplicationConfig>(obj).language.toStdString(),
                                   GLOBAL::PATCH_FILE::CONFIG.toStdString(),
                                    std::get<ApplicationConfig>(obj).themeName.toStdString(),
                                   std::get<ApplicationConfig>(obj).fontFamily.toStdString()});
            file << json.dump(2);
        }
       auto value = FileVx::converteJsonFromFileVX(QString::fromStdString(path.toStdString()));
        if (value == 0 || value == -2 || value == -1) {
            return false;
        }
        if (value == 1 || value == 2) {
            return true;
        }
    }
    return false;
}
FileManger::FileManger() {}
