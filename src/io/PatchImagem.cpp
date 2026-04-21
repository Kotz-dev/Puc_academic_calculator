//
// Created by KoTz on 20/04/2026.
//

#include "../../include/io/PatchImagem.h"

#include <filesystem>


QString PatchImagem::FromStr(std::filesystem::path path) {
    return QString::fromStdString(path.string());
}
std::filesystem::path PatchImagem::path_(std::string name,type type) {

    std::string Path;
    if (type == FILE_styles) {
        Path = "resources/styles/";
    }
    if (type == FILE_IMAGE) {
        Path = "resources/images/";
    }

    return std::filesystem::current_path().remove_filename() / Path / name;
}

void PatchImagem::LoadImagen(QString path) {

}
