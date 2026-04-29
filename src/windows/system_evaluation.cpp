//
// Created by KoTz on 20/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_system_evaluation .h" resolved

#include "system_evaluation.h"
#include "ui_system_evaluation.h"
#include <io/FileManager.h>
#include <item_system_evaluation.h>
#include "UIManager.h"




QString converter (std::filesystem::path path) {
    return QString::fromStdString(path.string());
}

QString indexImage(UNIVERSIDADE Un) {
     std::vector<std::filesystem::path> list = {"Logo_PUC.png","Logo_UNIV.png","Logo_personalizado.png"};
    return loadStyleSheet(list[Un].string(),FILE_IMAGE);
}
void evaluation_system::on_list_faculdade_currentRowChanged(int currentRow) {
    if (list_items_.size() > currentRow) {
        ui->logo_a2->setPixmap(list_items_[currentRow].getLogoUniversidade());
        ui->Label_name->setText(list_items_[currentRow].getNomeUniversidade());
        ui->double_freq_min->setValue(list_items_[currentRow].getFrequenciaMinima());
    }
}

void evaluation_system::init() {

    std::vector<ITEM> item_vector =
    {
        ITEM{indexImage(PUC),"PUC",
            "PUC (Pontifícia Universidade Católica)",75},
        ITEM{indexImage(UNIVERSO),"UNIVERSO","UNIVERSO",75},
        ITEM{indexImage(PERSONALIZADO),"Personlizado","Perzolizado",75},
     };

    if (ui != nullptr) {
        for (auto & i : item_vector) {
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
    this->list_items_ = item_vector;
}

evaluation_system::evaluation_system(QWidget *parent) :
    QDialog(parent), ui(new Ui::evaluation_system) {
    ui->setupUi(this);
    init();
    setStyleSheet(loadStyleSheet("system_evaluation_dark.qss",PATCH_TYPE_::FILE_styles));
}

evaluation_system::~evaluation_system() {
    delete ui;
}


void evaluation_system::on_btn_close_window_clicked() {
    close();
}

void evaluation_system::on_btn_apply_system_clicked() {

}