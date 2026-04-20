//
// Created by KoTz on 17/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AboutDialog.h" resolved

#include "../../include/windows/aboutdialog.h"
#include "ui_AboutDialog.h"
#include <QDesktopServices>
#include <QUrl>


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);
}

AboutDialog::~AboutDialog() {
    delete ui;
}

void AboutDialog::on_btn_Github_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Kotz-dev/EduMetrics"));
}
