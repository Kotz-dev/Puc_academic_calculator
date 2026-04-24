//
// Created by KoTz on 24/10/2025.
//

#include "utils/GlobalAccess.h"




namespace GLOBAL {
    QString idioma;
    bool is_aplica;
    bool is_close_window_option;
    int janela_vez;
    namespace WINDOW {
        Ui::MainWindow * UI;
        PreferencesWindow *ui_PrenferecesWindow;
        MainWindow *main;
    }
    nlohmann::json json;
    void init_global(Ui::MainWindow * windows) {
        if (windows != nullptr) {
            WINDOW::UI = windows;
        }
    }
    void init_global( PreferencesWindow * option) {
        if (option != nullptr) {
            WINDOW::ui_PrenferecesWindow = option;
        }
    }
}
