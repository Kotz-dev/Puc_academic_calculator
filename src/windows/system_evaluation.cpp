//
// Created by KoTz on 20/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_system_evaluation .h" resolved

#include "system_evaluation.h"
#include "ui_system_evaluation.h"
#include <io/FileManager.h>
#include <item_system_evaluation.h>
#include "UIManager.h"




enum UNIVERSIDADE {
    PUC = 0,
    UNIVERSO = 1,
    PERSONALIZADO = 2
};

QString indexImage(UNIVERSIDADE Un) {
     std::vector<std::filesystem::path> list =
         {
         "Logo_PUC.png",
         "Logo_UNIV.png",
         "Logo_personalizado.png"
         };
    return FileManager::getResourcePath(list[Un].string(),FILE_IMAGE).To_String_;
}


void init(Ui::evaluation_system *ui) {

    if (ui != nullptr) {
        std::array<ITEM,3> list =
            {
               ITEM{indexImage(PUC),"PUC","PUC (Pontifícia Universidade Católica)"},
               ITEM{indexImage(UNIVERSO),"UNIVERSO","UNIVERSO"},
               ITEM{indexImage(PERSONALIZADO),"Personlizado","Perzolizado"},
            };
        for (auto & i : list) {
             QPixmap imagem(i.getLogoUniversidade());
            imagem.scaled(QSize(30,30));
            QIcon icon(imagem);
            QListWidgetItem *ts = new QListWidgetItem(icon,i.getListNomeUniversidade());
            ts->setSizeHint(QSize(50,50));
            ui->logo_a2->setPixmap(indexImage(PUC));
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
    setStyleSheet(loadStyleSheet("system_evaluation_dark.qss"));
}

evaluation_system::~evaluation_system() {
    delete ui;
}

void evaluation_system::on_list_faculdade_currentRowChanged(int currentRow) {

}

void evaluation_system::on_btn_close_window_clicked() {
    close();
}

void evaluation_system::on_btn_apply_system_clicked() {

}