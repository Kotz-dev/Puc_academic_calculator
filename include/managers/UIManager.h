#ifndef _UI__H
#define _UI__H

#include <ui_MainWindow.h>
#include <QDir>
#include <io/PatchImagem.h>

class MainWindow;
#include "io/FileManager.h"

#include "PreferencesWindow.h"
#include "ui_option.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class Style;}
QT_END_NAMESPACE

QString gets (std::string name);

const std::array<std::filesystem::path, 8> style_sheet_paths =
    {
      PatchImagem::path_("window_dark.qss",FILE_styles),
      PatchImagem::path_("window_white.qss",FILE_styles),
      PatchImagem::path_("PreferencesWindowStyles_white.qss",FILE_styles),
      PatchImagem::path_("PreferencesWindowStyles_dark.qss",FILE_styles),
      PatchImagem::path_("system_evaluation_dark.qss",FILE_styles),
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
