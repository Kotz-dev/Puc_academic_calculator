//
// Created by KoTz on 30/06/2025.
//

#include "ui/UIManager.h"

#include "GlobalAccess.h"
#include "JsonParser.h"

void Style_Table::Style::table_result(QTableWidget *ui,int index,int ps) {
     if (ui != nullptr) {
         if (ps == 0) {
             ///ui->item(index,7)->setBackground(QColor(Qt::black));
             ui->item(index,7)->setText("Reprovado por falta");
             ui->item(index,7)->setBackground(QColor(Qt::red));
         }

         if (ps == 1) {
             ui->item(index,7)->setText("Aprovado");
             ui->item(index,7)->setBackground(QColor(Qt::darkGreen));

         }

         if (ps == 2) {
             ui->item(index,7)->setText("Reprovado");
             ui->item(index,7)->setBackground(QColor(Qt::red));
         }
     }

    return;
}
void Style_Table::Style::clear_table(QTableWidget *ui,int h,int colune) {
    ui->item(h,colune)->setText("");
    ui->item(h, colune)->setBackground(QColor::fromRgb(44,44,44,44));
}

void ui_controller::WindowSystemTema(QString tema) {
    if (tema == "Claro") {
        Window_Light(GLOBAL::WINDOW::UI,nullptr);
    }
    if (tema == "Escuro") {
        Window_Dark(GLOBAL::WINDOW::UI);
    }
}

void ui_controller::WindowSystemTema() {
    if ((json_parser::GetFileJson(GLOBAL::PATCH_FILE::CONFIG,"tema") == "Claro")) {
       Window_Light(GLOBAL::WINDOW::UI,nullptr);
    }
    if ((json_parser::GetFileJson(GLOBAL::PATCH_FILE::CONFIG,"tema") == "Escuro")) {
        Window_Dark(GLOBAL::WINDOW::UI);
    }
}

void ui_controller::Window_Light(Ui__windows_ *ui, Ui::option *op) {
    QFile filew{window_light};
    if (ui != nullptr) {
        filew.open(QFile::ReadOnly);
        QString styleSheet = filew.readAll();
        ui->tableWidget->setStyleSheet(styleSheet);
        ui->menuBar->setStyleSheet("background-color: #ededed;color: #000000;");
        ui->frame->setStyleSheet("background-color: rgb(255, 255, 255);color: #000000;");
        ui->centralwidget->setStyleSheet("background-color: rgb(255, 255, 255);color: #000000;");
    }
}


void ui_controller::TableWidget(Ui__windows_ *ui) {
    QFile filew{ui_styles_tabel_widget};
    if (ui != nullptr) {
        filew.open(QFile::ReadOnly);
        QString styleSheet = filew.readAll();
        ui->tableWidget->setStyleSheet(styleSheet);
    }
}

void ui_controller::Window_Dark(Ui__windows_ *ui) {
    QFile filew{window_light};
    if (ui != nullptr) {
        filew.open(QFile::ReadOnly);
        QString styleSheet = filew.readAll();
        ui->tableWidget->setStyleSheet("");
        ui->menuBar->setStyleSheet("");
        ui->frame->setStyleSheet("");
        ui->centralwidget->setStyleSheet("");
    }
}

void ui_controller::Button(TYPE TY,Ui__windows_ * ui) {
    QFile filew{ui_styles_};
   if (TY == TYPE::MAIN_WINDOW) {
       if (filew.open(QFile::ReadOnly)) {
           QString styleSheet = filew.readAll();
           ui->btn_add->setStyleSheet(styleSheet);
           ui->btn_remover->setStyleSheet(styleSheet);
           filew.close();
       } else {
           qDebug() << "Erro ao abrir o arquivo de estilo:" << filew.errorString();
       }
   }
}
void UI_FONT::text(QString fonte,Ui::option * ui,Ui__windows_ *win) {
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

void UI_FONT::text(nlohmann::json json, Ui::option *ui) {
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
 void UI_FONT::text(nlohmann::json json,Ui__windows_ * ui) {
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

