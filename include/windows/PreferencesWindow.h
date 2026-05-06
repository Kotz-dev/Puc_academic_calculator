//
// Created by kotz on 19/09/2025.
//

#ifndef PREFERENCES_WINDOW_H
#define PREFERENCES_WINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class PreferencesWindow;
}

QT_END_NAMESPACE

class PreferencesWindow : public QMainWindow {
    Q_OBJECT

private slots:
    void on_btn_aplicar_clicked();
    void on_btn_salvar_clicked();
    void on_btn_search_paste_clicked();
    void on_Combox_tema_currentIndexChanged(int index);
    void on_Combox_Language_currentIndexChanged(int index);
    void on_fontComboBox_currentIndexChanged(int index);
    void set_setting (QString Theme,QString idioma,QString Fonte);
public:
    explicit PreferencesWindow(QWidget *parent = nullptr);
    ~PreferencesWindow() override;
    Ui::PreferencesWindow* ui() { return ui_preferences_window_; }

private:
    Ui::PreferencesWindow *ui_preferences_window_;
     bool has_selected_theme;
     bool has_selected_idiom;
};


#endif //PREFERENCES_WINDOW_H