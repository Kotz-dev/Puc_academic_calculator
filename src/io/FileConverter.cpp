//
// Created by KoTz on 13/01/2026.
//

#include "FileConverter.h"
#include <FileManager.h>

int FileVx::converteJsonFromFileVX(QString Patch) {
    if (Patch.isEmpty()) {
        return 0;
    };
    if (Patch.contains(CONFIG_FILE_EXTENSION.c_str()) == true || Patch.contains(".vx") == true )  {
        return 2;
    }

    QFile file(Patch);
    auto Get_Patch = Patch;
    bool teste = false,test_ = false;
    if (Patch.contains(".json") == true) {
       auto get = Patch.remove(".json");
        get += ".vx";
        file.open(QFile::ReadOnly| QIODevice::Text);
        std::ofstream fileStream (get.toStdString(),std::ios::binary);
        fileStream << file.readAll().toStdString();
        if (fileStream.good() == true) {
            test_ = true;
            if (std::filesystem::remove(Get_Patch.toStdString())) {
                teste = true;
            };
        }
        if (fileStream.fail() == true) {
            return -2;
        }
        if (test_ == true && teste == true) {
            return 1;
        }
    }

    return -1;
}
