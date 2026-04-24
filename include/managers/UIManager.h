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


/// Desgin
class ui_styles_ {
public:
    static void applyDarkTheme(MainWindow * ui, PreferencesWindow *Prefe);
    static void applyLightTheme(MainWindow * ui,PreferencesWindow *op);

    static void applyTheme();
    static void applyTheme(QString themeName);
};

class frw {
public :
    static inline  nlohmann::json json;
    static inline Ui_PreferencesWindow *ui_preferences_window;
    static inline Ui_MainWindow *ui_main_window;
};


/// FONTE
struct UI_FONT {
    static void text(QString fonte,Ui::PreferencesWindow * ui,Ui_MainWindow *win);
    static void text(nlohmann::json json,Ui_MainWindow * ui);
    static void text(nlohmann::json json, Ui::PreferencesWindow * ui);
    static void  text(QString fonte,frw obj); // Prefemce e ui_main
    static void  text(frw obj); // json e ui ou prefe
};


#endif //_UI__H
