//
// Created by kotz on 28/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddSubjectDialog .h" resolved

#include "../../include/windows/AddSubjectDialog.h"
#include "ui_AddSubjectDialog.h"
#include <FileManager.h>
addsubjectdialog::addsubjectdialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::addsubjectdialog) {
    ui->setupUi(this);


    for (size_t value = 1; value < 11; value++) {
      ui->combox_list_semestre->insertItem(value,QString::number(value) + "º Semestre");
    }

    setStyleSheet(loadStyleSheet("AddSubjectDialogStyle_dark.qss",PATCH_TYPE_::FILE_styles));
}

void addsubjectdialog::on_btn_btn_2_avaliacoes_clicked() {

}

void addsubjectdialog::on_btn_btn_3_avaliacoes_clicked() {

}
void addsubjectdialog::on_btn_regular_clicked() {

}

void addsubjectdialog::closeEvent(QCloseEvent *event) {

}

void addsubjectdialog::on_btn_estagio_tcc_clicked() {
    qDebug () << "tesste";
}

void addsubjectdialog::on_btn_cancel_clicked() {
    close();
}

void addsubjectdialog::on_btn_save_clicked() {

}

void addsubjectdialog::on_btn_close_clicked() {
    close();
}

addsubjectdialog::~addsubjectdialog() {
    delete ui;
}
