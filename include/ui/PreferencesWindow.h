//
// Created by kotz on 19/09/2025.
//

#ifndef PREFERENCES_WINDOW_H
#define PREFERENCES_WINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class option;
}

QT_END_NAMESPACE

 struct info_save_automatico {
     int intervalo = 0;
     int ligado    = 0;
};


class option : public QMainWindow , public info_save_automatico {
    Q_OBJECT

private slots:
    void on_btn_aplicar_clicked();
    void on_btn_salvar_clicked();
    void on_btn_search_paste_clicked();
    void set_setting (QString Theme,QString idioma,QString Fonte);
public:
    explicit option(QWidget *parent = nullptr);

    ~option() override;

private:
    Ui::option *ui_option_;

    QString file_antigo;
};


#endif //PREFERENCES_WINDOW_H