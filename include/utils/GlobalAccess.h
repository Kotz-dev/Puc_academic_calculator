//
// Created by KoTz on 24/10/2025.
//

#ifndef AVALIACAODAPUC_GLOBAL_ACESS_H
#define AVALIACAODAPUC_GLOBAL_ACESS_H

#include  <QString>
#include  "managers/LanguageManager.h"
#include  "windows/PreferencesWindow.h"
#include <io/FileManager.h>
#include <QDir>

class MainWindow;


namespace GLOBAL {
     extern   QString idioma;
     extern   bool is_aplica;
     extern   bool is_close_window_option;
     extern    int janela_vez;
     namespace WINDOW {
          extern   Ui::MainWindow * UI;
          extern   MainWindow *main;
          extern   PreferencesWindow *ui_PrenferecesWindow;
     }
     extern   nlohmann::json json;

     namespace FILE_PATHS {
          inline    QString DATA;
          inline    QString LANGUAGE;
          inline   QString CONFIG;
     }
     extern   void init_global(Ui::MainWindow * windows);
     extern   void init_global(PreferencesWindow * option);
}


#endif //AVALIACAODAPUC_GLOBAL_ACESS_H