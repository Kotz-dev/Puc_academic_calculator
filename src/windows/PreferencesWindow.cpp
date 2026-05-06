//
// Created by kotz on 19/09/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_option.h" resolved

#include "windows/PreferencesWindow.h"
#include <QFileDialog>
#include <fmt/base.h>
#include "JsonParser.h"
#include "ui_option.h"
#include "io/FileManager.h"
#include "utils/GlobalAccess.h"
#include "qwidget.h"
#include "UIManager.h"
#include <fmt/std.h>
#include <LanguageManager.h>


void PreferencesWindow::on_fontComboBox_currentIndexChanged(int index) {

}

void PreferencesWindow::on_Combox_Language_currentIndexChanged(int index) {
     has_selected_idiom = true;
}

void PreferencesWindow::on_Combox_tema_currentIndexChanged(int index) {
   has_selected_theme = true;
}

PreferencesWindow::PreferencesWindow(QWidget *parent) : QMainWindow(parent), ui_preferences_window_(new Ui::PreferencesWindow) {
    has_selected_idiom = false;
    has_selected_theme = false;
    GLOBAL::WINDOW::ui_PrenferecesWindow = this;
    ui_preferences_window_->setupUi(this);
    LanguageManager::TraduzirPrencesWindow();
    ui_styles_::applyTheme();
    auto value = GLOBAL::json["Fonte"];
    ui_preferences_window_->fontComboBox->setCurrentFont(QString::fromStdString(nlohmann::to_string(value)));
    ui_preferences_window_->Combox_tema->setCurrentText(JsonParser::readJsonKeyAsString(GLOBAL::FILE_PATHS::CONFIG,"tema"));
    UI_FONT::text(GLOBAL::json,ui_preferences_window_);
    ui_preferences_window_->lineEdit->setEnabled(false);

   if (JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"config").is_null() == false) {

       auto get= QString::fromStdString(JsonParser::readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"config")).remove("'");
       ui_preferences_window_->lineEdit->setText(QUrl{get}.fileName());
   }
}


void PreferencesWindow::set_setting (QString Theme,QString idioma,QString Fonte) {
     ui_preferences_window_->Combox_tema->setCurrentText(Theme);
     ui_preferences_window_->fontComboBox->setCurrentFont(Fonte);
}


void PreferencesWindow::on_btn_search_paste_clicked() {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    QString fileName = fileDialog.getOpenFileName(this, tr("Open File"), GLOBAL::FILE_PATHS::CONFIG, tr(
        fmt::format("Arquivos Vx (*{})",CONFIG_FILE_EXTENSION).c_str()));
    if (fileName.isEmpty() == true) {
        return;
    }
    ui_preferences_window_->lineEdit->setText(QUrl(fileName).fileName());
    std::vector<nlohmann::json> json_array;
    std::array<QString,3> text = {"idioma","Fonte","tema"};
    for (int i = 0; i < text.size(); i++) {
        json_array.push_back( JsonParser::readJsonKey(fileName,text[i]));
        text[i] = QString::fromStdString(nlohmann::to_string(json_array[i]));
        JsonParser::removeQuotes(text[i]);
    }
     set_setting(text[2],text[0],text[1]);
   // UI_FONT::text(text[1],ui_preferences_window_,GLOBAL::WINDOW::UI);
    ui_styles_::applyTheme(text[2]);
    if (json_array.empty() == false) {
        json_array.clear();
    }
}
void PreferencesWindow::on_btn_aplicar_clicked() {
    UI_FONT::text(ui_preferences_window_->fontComboBox->currentText(),ui_preferences_window_,GLOBAL::WINDOW::UI);
    if (has_selected_theme == true) {
        ui_styles_::applyTheme(ui_preferences_window_->Combox_tema->currentText());
    }
     has_selected_idiom = false;
     has_selected_theme = false;
}
void PreferencesWindow::on_btn_salvar_clicked() {

    ApplicationConfig config;
    config.language    = ui_preferences_window_->Combox_Language->currentText();
    config.fontFamily     = ui_preferences_window_->fontComboBox->currentText();
    config.themeName     = ui_preferences_window_->Combox_tema->currentText();

    auto file_save = FileManager::save(GLOBAL::FILE_PATHS::CONFIG,config);
    if (file_save) {
        qDebug () << "Salvo com sucesso";
    }else {
        qDebug () << "Erro ao salvar";
    }
}

PreferencesWindow::~PreferencesWindow() {
    delete ui_preferences_window_;
    GLOBAL::is_close_window_option = true;
    GLOBAL::WINDOW::ui_PrenferecesWindow = nullptr;
}
