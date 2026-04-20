//
// Created by KoTz on 20/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_system_evaluation .h" resolved

#include "system_evaluation.h"
#include "ui_system_evaluation.h"
#include <io/FileManager.h>

#include "UIManager.h"


void init(Ui::evaluation_system *ui) {
    if (ui != nullptr) {
        std::array<QString,3> list = {"PUC",
            "UNIVERSO",
            "Personalizado"
        };

        for (auto & i : list) {
            QPixmap imagem("C:\\Users\\KoTz\\CLionProjects\\Puc_academic_calculator\\resources\\images\\Logo_PUC.png");
            imagem.scaled(QSize(30,30));
            QIcon icon(imagem);
            QListWidgetItem *ts = new QListWidgetItem(icon,i);
            ts->setSizeHint(QSize(50,50));
            ui->list_faculdade->setSpacing(1);
            ui->list_faculdade->setIconSize(QSize(40,40));
            ui->list_faculdade->addItem(ts);
            ui->list_faculdade->setFocusPolicy(Qt::NoFocus);
        }
    }
    ui->list_faculdade->setCurrentItem(ui->list_faculdade->item(0));
}

evaluation_system::evaluation_system(QWidget *parent) :
    QDialog(parent), ui(new Ui::evaluation_system) {
    ui->setupUi(this);
    init(ui);
    setStyleSheet(gets("system_evaluation_dark.qss"));
}

evaluation_system::~evaluation_system() {
    delete ui;
}


void evaluation_system::on_btn_close_window_clicked() {
    close();
}

void evaluation_system::on_btn_apply_system_clicked() {

}