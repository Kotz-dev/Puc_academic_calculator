//
// Created by KoTz on 30/06/2025.
//

#include "managers/UIManager.h"
#include "windows/MainWindow.h"
#include "GlobalAccess.h"
#include "JsonParser.h"

Style_Table::Style::Style() {
}
QString gets (std::string name ) {
    QString styleSheet;
    for (auto & i : style_sheet_paths) {
        if (i.string().find(name) != std::string::npos) {
            QFile f(i);
            f.open(QFile::ReadOnly);
            styleSheet = f.readAll();
        }
    }
    return styleSheet;
}

void Style_Table::Style::setRowResult(QTableWidget *table, int row, int status) {
     if (table != nullptr) {
         if (status == 0) {
             table->item(row,7)->setText("Reprovado por falta");
             table->item(row,7)->setBackground(QColor(Qt::red));
         }

         if (status == 1) {
             table->item(row,7)->setText("Aprovado");
             table->item(row,7)->setBackground(QColor(Qt::darkGreen));

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

void ui_controller::applyTheme(QString themeName) {

    if (themeName == "Claro") {
        applyLightTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
    if (themeName == "Escuro") {
        applyDarkTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
}

void ui_controller::applyTheme() {

    qDebug () << bool(GLOBAL::WINDOW::ui_PrenferecesWindow != nullptr);
    if ((JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"tema") == "Claro")) {
        qDebug () << "Claro";
       applyLightTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
    if ((JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"tema") == "Escuro")) {
        qDebug () << "Escuro";
        applyDarkTheme(GLOBAL::WINDOW::main,GLOBAL::WINDOW::ui_PrenferecesWindow);
    }
}
void ui_controller::applyLightTheme(MainWindow *ui,PreferencesWindow *op) {
    if (ui != nullptr ) {
        ui->setStyleSheet(gets("window_white.qss"));
    }
    if (op != nullptr) {
         op->setStyleSheet(gets("PreferencesWindowStyles_white.qss"));
    }
}
void ui_controller::applyDarkTheme(MainWindow *ui,PreferencesWindow *Prefe) {
    if (ui != nullptr ) {
        ui->setStyleSheet(gets("window_dark.qss"));
    }
    if (Prefe != nullptr) {
        Prefe->setStyleSheet(gets("PreferencesWindowStyles_dark.qss"));
    }
}
void UI_FONT::text(QString fonte,Ui::PreferencesWindow * ui,Ui_MainWindow *win) {
     if (ui == nullptr) {
         return;
     }
    ui->label_tema->setFont(QFont(fonte));
    ui->label_fonte->setFont(QFont(fonte));
    ui->comboBox->setFont(QFont(fonte));
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

void UI_FONT::text(nlohmann::json json, Ui::PreferencesWindow *ui) {
    if (ui != nullptr) {
        auto get = json["Fonte"];
        ui->label_tema->setFont(QString::fromStdString(get).remove("\\"));
        ui->label_fonte->setFont(QString::fromStdString(get).remove("\\"));
        ui->comboBox->setFont(QString::fromStdString(get).remove("\\"));
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

