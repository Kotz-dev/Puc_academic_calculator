//
// Created by KoTz on 24/10/2025.
//

#include "utils/GlobalAccess.h"


namespace GLOBAL {
    QString idioma;
    bool is_aplica;
    bool is_close_window_option;
    namespace WINDOW {
        Ui::_windows_ * UI;
        Ui::option    *_ui_option;
    }
    nlohmann::json json;
    void init_global(Ui::_windows_ * windows) {
        if (windows != nullptr) {
            WINDOW::UI = windows;
        }
    }
    void init_global( Ui::option * option) {
        if (option != nullptr) {
            WINDOW::_ui_option = option;
        }
    }
    namespace ARRAY {
        namespace LOG {
            std::vector<DataInfoLog> log_array;
        }
    }
}
