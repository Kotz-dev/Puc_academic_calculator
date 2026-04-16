//
// Created by KoTz on 17/04/2026.
//

#ifndef PUCSIMULATOR_ABOUTDIALOG_H
#define PUCSIMULATOR_ABOUTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AboutDialog; }
QT_END_NAMESPACE

class AboutDialog : public QDialog {
Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog() override;
private slots:
    void on_btn_Github_clicked();

private:
    Ui::AboutDialog *ui;
};


#endif //PUCSIMULATOR_ABOUTDIALOG_H
