//
// Created by kotz on 28/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddSubjectDialog .h" resolved

#include "../../include/windows/AddSubjectDialog.h"
#include "ui_AddSubjectDialog.h"
#include <FileManager.h>
#include <QButtonGroup>
addsubjectdialog::addsubjectdialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::addsubjectdialog) {
    ui->setupUi(this);
    ui->btn_regular->setCheckable(true);
    ui->btn_estagio_tcc->setCheckable(true);
    ui->btn_regular->setChecked(true);
    setStyleSheet(loadStyleSheet("AddSubjectDialogStyle_dark.qss",PATCH_TYPE_::FILE_styles));
}
void addsubjectdialog::on_btn_regular_clicked() {

    ui->btn_apto->hide();
    ui->btn_inapto->hide();
    ui->label_situacao->hide();
}

void addsubjectdialog::closeEvent(QCloseEvent *event) {

}

Ui::addsubjectdialog *addsubjectdialog::_ui_() const {
    return ui;
}

void addsubjectdialog::on_btn_estagio_tcc_clicked() {
    ui->btn_regular->setCheckable(false);
    ui->btn_estagio_tcc->setChecked(true);
    ui->btn_estagio_tcc->setCheckable(true);

    ui->btn_apto->show();
    ui->btn_inapto->show();
    ui->label_situacao->show();
}
void addsubjectdialog::on_btn_cancel_clicked() {
    close();
}

void addsubjectdialog::on_btn_save_clicked() {
   close();
}

void addsubjectdialog::on_btn_close_clicked() {
    close();
}

addsubjectdialog::~addsubjectdialog() {
    delete ui;
}
