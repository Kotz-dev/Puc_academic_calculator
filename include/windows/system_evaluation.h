//
// Created by KoTz on 20/04/2026.
//

#ifndef PUCSIMULATOR_SYSTEM_EVALUATION_H
#define PUCSIMULATOR_SYSTEM_EVALUATION_H

#include <QDialog>
#include <vector>
#include "item_system_evaluation.h"

enum UNIVERSIDADE {
    PUC = 0,
    UNIVERSO = 1,
    PERSONALIZADO = 2
};

QString indexImage(UNIVERSIDADE Un);

QT_BEGIN_NAMESPACE
namespace Ui { class evaluation_system; }
QT_END_NAMESPACE

class evaluation_system : public QDialog {
    Q_OBJECT

    public:
    explicit evaluation_system(QWidget *parent = nullptr);
    ~evaluation_system() override;
private slots :
    void on_btn_apply_system_clicked();
    void on_btn_close_window_clicked();
    void on_list_faculdade_currentRowChanged(int currentRow);

private:
    void init();
    std::vector<ITEM> list_items_ = {};
    Ui::evaluation_system *ui;
};


#endif //PUCSIMULATOR_SYSTEM_EVALUATION_H