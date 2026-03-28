//
// Created by KoTz on 23/10/2025.
//

#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H


#include <ui_MainWindow.h>
#include <nlohmann/json.hpp>
#include <ui_option.h>
#include <nlohmann/json_fwd.hpp>


enum TYPE_IDIOMA{
    IDIOMA_WINDOWS = 0,
    IDIOMA_OPTION = 1,
    IDIOMA_ALL    = 2
};


class LanguageUI {
public :
    LanguageUI();
    static void initialize_language_ui(nlohmann::json & get_json,Ui::_windows_ * ui_windows__,QString  & ui_language);
    static void UpdateLanguage_UI(QString & Language_Key);
    static nlohmann::json getLanguageJsonValue(QString language_keys,QString language_key);
    static int IsLanguageValid(QString language_key);
};


#endif //LANGUAGE_MANAGER_H