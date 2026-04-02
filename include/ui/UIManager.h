#ifndef _UI__H
#define _UI__H

#include <ui_MainWindow.h>
#include <QDir>
#include <nlohmann/adl_serializer.hpp>
#include "io/FileManager.h"

#include "PreferencesWindow.h"
#include "ui_option.h"

QT_BEGIN_NAMESPACE
namespace Ui { class _windows_; class Style;}
QT_END_NAMESPACE


#ifdef _WIN32
    static   std::filesystem::path ui_styles_ =  std::filesystem::current_path().remove_filename() / "styles//ui_styles.qss";
    static   std::filesystem::path ui_styles__ = std::filesystem::current_path().remove_filename() / "styles//ui_styles.qss";
    static   std::filesystem::path ui_styles_tabel_widget = std::filesystem::current_path().remove_filename() / "styles//styles_tabel_widget.qss";
    static   std::filesystem::path window_dark =std::filesystem::current_path().remove_filename() / "styles/ui_styles.qss";
    static   std::filesystem::path window_light =std::filesystem::current_path().remove_filename() / "styles/window_branco.qss";
#endif


#ifdef __linux__
    // static   std::filesystem::path ui_styles_ =  std::filesystem::current_path().remove_filename() / "styles\\ui_styles.qss";
    // static   QString ui_styles__;
    // static   QString ui_styles_tabel_widget;
    // static   QString window_light;
#endif




namespace Style_Table {
        class Style {
        public :
            static void table_result(QTableWidget *ui,int index,int pos);
            static void clear_table(QTableWidget *ui,int h,int colune);
            Style();
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
