//
// Created by kotz on 28/04/2026.
//

#ifndef EDUMETRICS_ADDSUBJECTDIALOG_H
#define EDUMETRICS_ADDSUBJECTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class addsubjectdialog; }
QT_END_NAMESPACE

class addsubjectdialog : public QDialog {
Q_OBJECT

public:
    explicit addsubjectdialog(QWidget *parent = nullptr);
    ~addsubjectdialog() override;

    private slots:
        void closeEvent(QCloseEvent *event) override;
        void on_btn_close_clicked();
        void on_btn_save_clicked();
        void on_btn_cancel_clicked();
        void on_btn_btn_3_avaliacoes_clicked();
        void on_btn_btn_2_avaliacoes_clicked();
        void on_btn_regular_clicked();
        void on_btn_estagio_tcc_clicked();
private:
    Ui::addsubjectdialog *ui;
};


#endif //EDUMETRICS_ADDSUBJECTDIALOG_H
