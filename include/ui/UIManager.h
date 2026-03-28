#ifndef _UI__H
#define _UI__H

#include <ui_MainWindow.h>
#include <QDir>
#include <nlohmann/adl_serializer.hpp>

#include "PreferencesWindow.h"
#include "ui_option.h"

const QString ui_styles_ = QDir::homePath() + "/Documents/GitHub/puc-grade-calculator/styles/ui_styles.qss";
const QString ui_styles__ =  "/home/kotz/Documentos/GitHub/puc-grade-calculator/styles/ui_styles.qss";
const QString ui_styles_tabel_widget = "C:\\Users\\KoTz\\Documents\\GitHub\\puc-grade-calculator\\styles\\styles_tabel_widget.qss";
const QString window_light = "C:\\Users\\KoTz\\Documents\\GitHub\\puc-grade-calculator\\styles\\window_branco.qss";

QT_BEGIN_NAMESPACE
namespace Ui { class _windows_; class Style;}
QT_END_NAMESPACE

namespace Style_Table {
        class Style {
        public :
            static void table_result(QTableWidget *ui,int index,int pos);
            static void clear_table(QTableWidget *ui,int h,int colune);
    };

}
enum TYPE {
    MAIN_WINDOW = 0,
    PREFERENCE_SYSTEM = 1
};
class ui_controller {
public:
    static void TableWidget(Ui__windows_ * ui);
    static void Button(TYPE,Ui__windows_ * ui);
    static void Window_Dark(Ui__windows_ * ui);
    static void Window_Light(Ui__windows_ * ui,Ui::option *op);

    static void WindowSystemTema();
    static void WindowSystemTema(QString tema);
};
struct UI_FONT {
    static void text(QString fonte,Ui::option * ui,Ui__windows_ *win);
    static void text(nlohmann::json json,Ui__windows_ * ui);
    static void text(nlohmann::json json, Ui::option * ui);
};


#endif //_UI__H
