#ifndef _UI__H
#define _UI__H

#include <ui_MainWindow.h>
#include <QDir>

class MainWindow;
#include "io/FileManager.h"

#include "PreferencesWindow.h"
#include "ui_option.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class Style;}
QT_END_NAMESPACE

QString gets (std::string name);

static std::filesystem::path window_dark               = std::filesystem::current_path().remove_filename() / "resources/styles/window_dark.qss";
static std::filesystem::path window_light             = std::filesystem::current_path().remove_filename() / "resources/styles/window_white.qss";
static std::filesystem::path _PreferencesWindow_      = std::filesystem::current_path().remove_filename() / "resources/styles/PreferencesWindowStyles_white.qss";
static std::filesystem::path _PreferencesWindow_dark  = std::filesystem::current_path().remove_filename() / "resources/styles/PreferencesWindowStyles_dark.qss";

const std::array<std::filesystem::path, 8> style_sheet_paths =
    {
    window_dark,
    window_light,
    _PreferencesWindow_,
    _PreferencesWindow_dark
    };


namespace Style_Table {
        class Style {
        public :
            static void setRowResult(QTableWidget *table, int row, int status);
            static void clearCell(QTableWidget *table, int row, int column);
            Style();
    };

}
enum TYPE {
    MAIN_WINDOW = 0,
    PREFERENCE_SYSTEM = 1
};
class ui_controller {
public:
    static void applyDarkTheme(MainWindow * ui, PreferencesWindow *Prefe);
    static void applyLightTheme(MainWindow * ui,PreferencesWindow *op);

    static void applyTheme();
    static void applyTheme(QString themeName);
};
struct UI_FONT {
    static void text(QString fonte,Ui::PreferencesWindow * ui,Ui_MainWindow *win);
    static void text(nlohmann::json json,Ui_MainWindow * ui);
    static void text(nlohmann::json json, Ui::PreferencesWindow * ui);
};


#endif //_UI__H
