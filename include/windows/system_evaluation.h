//
// Created by KoTz on 20/04/2026.
//

#ifndef PUCSIMULATOR_SYSTEM_EVALUATION_H
#define PUCSIMULATOR_SYSTEM_EVALUATION_H

#include <QDialog>


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

private:
    Ui::evaluation_system *ui;
};


#endif //PUCSIMULATOR_SYSTEM_EVALUATION_H
