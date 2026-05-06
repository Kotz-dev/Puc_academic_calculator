//
// Created by KoTz on 30/06/2025.
//

#include "managers/UIManager.h"

#include <fmt/chrono.h>

#include "windows/MainWindow.h"
#include "GlobalAccess.h"
#include "JsonParser.h"

Style_Table::Style::Style() {}


void Style_Table::Style::setRowResult(QTableWidget *table, int row, int status) {
     if (table != nullptr) {
         if (status == 0) {
             table->item(row,7)->setText("Reprovado por falta");
             table->item(row,7)->setBackground(QColor(Qt::red));
         }

         if (status == 1) {
             // table->setIconSize(QSize(table->rowHeight(row),table->columnWidth(7)));
             // table->item(row, 7)->setIcon(QPixmap(get).scaled(table->rowHeight(row),table->columnWidth(7),Qt::KeepAspectRatio,Qt::SmoothTransformation));
         }

         if (status == 2) {
             table->item(row,7)->setText("Reprovado");
             table->item(row,7)->setBackground(QColor(Qt::red));
         }
     }

    return;
}
void Style_Table::Style::clearCell(QTableWidget *table, int row, int column) {
    table->item(row,column)->setText("");
    table->item(row, column)->setBackground(QColor::fromRgb(44,44,44,44));
}

void ui_styles_::applyTheme(QString themeName) {

    if (themeName == "Claro") {
        applyLightTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
    if (themeName == "Escuro") {
        applyDarkTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
}

void ui_styles_::applyTheme() {
    if ((JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"tema") == "Claro")) {
       applyLightTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
    if ((JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"tema") == "Escuro")) {
        applyDarkTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
}
void ui_styles_::applyLightTheme(MainWindow *ui,PreferencesWindow *op) {
    if (ui != nullptr ) {
        ui->setStyleSheet(loadStyleSheet("window_white.qss",PATCH_TYPE_::FILE_styles));
    }
    if (op != nullptr) {
         op->setStyleSheet(loadStyleSheet("PreferencesWindowStyles_white.qss",PATCH_TYPE_::FILE_styles));
    }
}
void ui_styles_::applyDarkTheme(MainWindow *ui,PreferencesWindow *Prefe) {
    if (ui != nullptr ) {
        ui->setStyleSheet(loadStyleSheet("window_dark.qss",PATCH_TYPE_::FILE_styles));
    }
    if (Prefe != nullptr) {
        Prefe->setStyleSheet(loadStyleSheet("PreferencesWindowStyles_dark.qss",PATCH_TYPE_::FILE_styles));
    }
}
void UI_FONT::text(QString fonte, frw obj) {
    if (fonte.isEmpty()) {
        return;
    }
    if (obj.ui_main_window == nullptr && obj.ui_preferences_window == nullptr) {
        return;
    }

     obj.ui_preferences_window->label_tema->setFont(QFont(fonte));
     obj.ui_preferences_window->label_fonte->setFont(QFont(fonte));
     obj.ui_preferences_window->Combox_Language->setFont(QFont(fonte));
     obj.ui_preferences_window->fontComboBox->setFont(QFont(fonte));
     obj.ui_preferences_window->Combox_tema->setFont(QFont(fonte));
     obj.ui_preferences_window->lineEdit->setFont(QFont(fonte));
     obj.ui_preferences_window->btn_search_paste->setFont(QFont(fonte));
     obj.ui_preferences_window->btn_aplicar->setFont(QFont(fonte));
     obj.ui_preferences_window->btn_salvar->setFont(QFont(fonte));
     obj.ui_preferences_window->label->setFont(QFont(fonte));

    obj.ui_main_window->menuArquivos->setFont(QFont(fonte));
    obj.ui_main_window->menuFerramentas->setFont(QFont(fonte));
    obj.ui_main_window->tableWidget->setFont(QFont(fonte));

    for (int a =0; a < obj.ui_main_window->tableWidget->columnCount();a++) {
        for (int b = 0; b < obj.ui_main_window->tableWidget->rowCount();b++) {
            obj.ui_main_window->tableWidget->item(b,a)->setFont(QFont(fonte));
        }
        obj.ui_main_window->tableWidget->horizontalHeaderItem(a)->setFont(QFont(fonte));
    }
    obj.ui_main_window->label->setFont(QFont(fonte));


}

void UI_FONT::text(QString fonte,Ui::PreferencesWindow * ui,Ui_MainWindow *win) {
     if (ui == nullptr) {
         return;
     }
    ui->label_tema->setFont(QFont(fonte));
    ui->label_fonte->setFont(QFont(fonte));
    ui->Combox_Language->setFont(QFont(fonte));
    ui->fontComboBox->setFont(QFont(fonte));
    ui->Combox_tema->setFont(QFont(fonte));
    ui->lineEdit->setFont(QFont(fonte));
    ui->btn_search_paste->setFont(QFont(fonte));
    ui->btn_aplicar->setFont(QFont(fonte));
    ui->btn_salvar->setFont(QFont(fonte));
    ui->label->setFont(QFont(fonte));

    win->menuArquivos->setFont(QFont(fonte));
    win->menuFerramentas->setFont(QFont(fonte));
    win->tableWidget->setFont(QFont(fonte));

    for (int a =0; a < win->tableWidget->columnCount();a++) {
        for (int b = 0; b < win->tableWidget->rowCount();b++) {
            win->tableWidget->item(b,a)->setFont(QFont(fonte));
        }
        win->tableWidget->horizontalHeaderItem(a)->setFont(QFont(fonte));
    }
   win->label->setFont(QFont(fonte));
}


void UI_FONT::text(frw obj) {
    auto get = obj.json["Fonte"];
    if (obj.ui_preferences_window != nullptr) {
        obj.ui_preferences_window->label_tema->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->label_fonte->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->Combox_Language->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->fontComboBox->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->Combox_tema->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->lineEdit->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->btn_search_paste->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->btn_aplicar->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->btn_salvar->setFont(QString::fromStdString(get).remove("\\"));
        obj.ui_preferences_window->label->setFont(QString::fromStdString(get).remove("\\"));
    }
     if (obj.ui_main_window != nullptr) {
             obj.ui_main_window->menuArquivos->setFont(QFont(QString::fromStdString(get).remove("\\")));
             obj.ui_main_window->menuFerramentas->setFont(QFont(QString::fromStdString(get).remove("\\")));
             obj.ui_main_window->tableWidget->setFont(QFont(QString::fromStdString(get).remove("\\")));
             for (int a =0; a < obj.ui_main_window->tableWidget->columnCount();a++) {
                 obj.ui_main_window->tableWidget->horizontalHeaderItem(a)->setFont(QString::fromStdString(get).remove("\\"));
             }
     }
}


void UI_FONT::text(nlohmann::json json, Ui::PreferencesWindow *ui) {
    if (ui != nullptr) {
        auto get = json["Fonte"];
        ui->label_tema->setFont(QString::fromStdString(get).remove("\\"));
        ui->label_fonte->setFont(QString::fromStdString(get).remove("\\"));
        ui->Combox_Language->setFont(QString::fromStdString(get).remove("\\"));
        ui->fontComboBox->setFont(QString::fromStdString(get).remove("\\"));
        ui->Combox_tema->setFont(QString::fromStdString(get).remove("\\"));
        ui->lineEdit->setFont(QString::fromStdString(get).remove("\\"));
        ui->btn_search_paste->setFont(QString::fromStdString(get).remove("\\"));
        ui->btn_aplicar->setFont(QString::fromStdString(get).remove("\\"));
        ui->btn_salvar->setFont(QString::fromStdString(get).remove("\\"));
        ui->label->setFont(QString::fromStdString(get).remove("\\"));
    }
}
 void UI_FONT::text(nlohmann::json json,Ui_MainWindow * ui) {
    if (ui != nullptr) {
        auto get = json["Fonte"];
        ui->menuArquivos->setFont(QFont(QString::fromStdString(get).remove("\\")));
        ui->menuFerramentas->setFont(QFont(QString::fromStdString(get).remove("\\")));
        ui->tableWidget->setFont(QFont(QString::fromStdString(get).remove("\\")));
        for (int a =0; a < ui->tableWidget->columnCount();a++) {
            ui->tableWidget->horizontalHeaderItem(a)->setFont(QString::fromStdString(get).remove("\\"));
        }
    }
}

