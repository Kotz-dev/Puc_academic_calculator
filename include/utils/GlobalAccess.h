//
// Created by KoTz on 24/10/2025.
//

#ifndef AVALIACAODAPUC_GLOBAL_ACESS_H
#define AVALIACAODAPUC_GLOBAL_ACESS_H

#include  <QString>
#include  "ui/LanguageManager.h"
#include  "ui/PreferencesWindow.h"
#include <io/FileManager.h>

#include <QDir>

#include "ErrorLog.h"

namespace GLOBAL {
     extern   QString idioma;
     extern   bool is_aplica;
     extern   bool is_close_window_option;
     namespace WINDOW {
          extern   Ui::_windows_ * UI;
          extern   Ui::option   *_ui_option;
     }
     extern   nlohmann::json json;

     namespace PATCH_FILE {
          const    QString DATA;
          inline    QString LANGUAGE;
          inline   QString CONFIG;
     }

     extern   void init_global(Ui::_windows_ * windows);
     extern   void init_global(Ui::option  * option);
     namespace ARRAY {
         namespace LOG {
              extern std::vector<DataInfoLog> log_array;

         }
     }
}


#endif //AVALIACAODAPUC_GLOBAL_ACESS_H