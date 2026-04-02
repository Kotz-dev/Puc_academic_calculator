//
// Created by kotz on 19/09/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_option.h" resolved

#include "ui/PreferencesWindow.h"
#include <QFileDialog>
#include <fmt/base.h>
#include "JsonParser.h"
#include "ui_option.h"
#include "io/FileManager.h"
#include "utils/GlobalAccess.h"
#include "qwidget.h"
#include "UIManager.h"
#include <fmt/std.h>


void option::on_fontComboBox_currentIndexChanged(int index) {

}

//idioma
void option::on_comboBox_currentIndexChanged(int index) {
     is_seleciton_idioma = true;
}

void option::on_Combox_tema_currentIndexChanged(int index) {
   is_seleciton_theme = true;
}

option::option(QWidget *parent) : QMainWindow(parent), ui_option_(new Ui::option) {
    is_seleciton_idioma = false;
    is_seleciton_theme = false;
    is_seleciton_fonte = false;
    ui_option_->setupUi(this);
    GLOBAL::init_global(ui_option_);
    auto value = GLOBAL::json["Fonte"];
    ui_option_->fontComboBox->setCurrentFont(QString::fromStdString(nlohmann::to_string(value)));
    ui_option_->Combox_tema->setCurrentText(json_parser::GetFileJson_Str(GLOBAL::PATCH_FILE::CONFIG,"tema"));
    UI_FONT::text(GLOBAL::json,ui_option_);
    ui_option_->lineEdit->setEnabled(false);

   if (json_parser::GetFileJson(GLOBAL::PATCH_FILE::CONFIG,"config").is_null() == false) {

       auto get= QString::fromStdString(json_parser::GetFileJson(GLOBAL::PATCH_FILE::CONFIG,"config")).remove("'");
       QString GetData = QString::fromStdString(nlohmann::to_string(json_parser::GetFileJson(GLOBAL::PATCH_FILE::CONFIG,"inventario")));
       ui_option_->lineEdit->setText(QUrl{get}.fileName());
   }
    if (GLOBAL::idioma == "Ingles") {
            setWindowTitle(QString::fromStdString(LanguageUI::getLanguageJsonValue("en","Sistema de Preferencia"))
            .remove(""));
        auto i = LanguageUI::getLanguageJsonValue("en","Escuro");
        auto get = QString::fromStdString(nlohmann::to_string(i));
        json_parser::removeQuotes(get);
        ui_option_->Combox_tema->setItemText(0,get);
        LanguageUI::UpdateLanguage_UI(GLOBAL::idioma);
        ui_option_->comboBox->setCurrentIndex(1);
    }
    if (GLOBAL::idioma == "Português") {
        setWindowTitle(QString::fromStdString
            (LanguageUI::getLanguageJsonValue("Português","Preference System"))
            .remove(""));
        LanguageUI::UpdateLanguage_UI(GLOBAL::idioma);
        ui_option_->comboBox->setCurrentIndex(0);
    }
}


void option::set_setting (QString Theme,QString idioma,QString Fonte) {
     ui_option_->comboBox->setCurrentIndex(LanguageUI::IsLanguageValid(Theme));
     ui_option_->Combox_tema->setCurrentText(Theme);
     ui_option_->fontComboBox->setCurrentFont(Fonte);
}


void option::on_btn_search_paste_clicked() {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    QString fileName = fileDialog.getOpenFileName(this, tr("Open File"), GLOBAL::PATCH_FILE::CONFIG, tr(
        fmt::format("Arquivos Vx (*{})",CONFIG_FILE_EXTENSION).c_str()));
    if (fileName.isEmpty() == true) {
        return;
    }
    qDebug () << ui_option_->lineEdit->text();
    ui_option_->lineEdit->setText(QUrl(fileName).fileName());
    this->file_antigo = QUrl(fileName).fileName();
    std::vector<nlohmann::json> json_array;
    std::array<QString,3> text = {"idioma","Fonte","tema"};
    for (int i = 0; i < text.size(); i++) {
        json_array.push_back( json_parser::GetFileJson(fileName,text[i]));
        text[i] = QString::fromStdString(nlohmann::to_string(json_array[i]));
        json_parser::removeQuotes(text[i]);
    }
     set_setting(text[2],text[0],text[1]);
    LanguageUI::UpdateLanguage_UI(text[0]);

    UI_FONT::text(text[1],ui_option_,GLOBAL::WINDOW::UI);
    ui_controller::WindowSystemTema(text[2]);
    if (json_array.empty() == false) {
        json_array.clear();
    }
}
void option::on_btn_aplicar_clicked() {
    Json json,json_config;
    json_config = GLOBAL::json;
    auto idioma = ui_option_->comboBox->currentText();
    QString idi;
    QString Palavra_chave = "";
    UI_FONT::text(ui_option_->fontComboBox->currentText(),ui_option_,GLOBAL::WINDOW::UI);
    if (idioma == "Ingles") {
        Palavra_chave = "Sistema de Preferencia";
        idi = "en";
    }
    if (idioma == "Português") {
        Palavra_chave = "PreferenceSystem";
        idi = "Português";
    }
    if (is_seleciton_idioma == true) {
        LanguageUI::UpdateLanguage_UI(idioma);
        setWindowTitle(QString::fromStdString
          (LanguageUI::getLanguageJsonValue(idi,Palavra_chave))
          .remove(""));
    }
    if (is_seleciton_theme == true) {
        ui_controller::WindowSystemTema(ui_option_->Combox_tema->currentText());
    }
     is_seleciton_idioma = false;
     is_seleciton_theme = false;
}
void option::on_btn_salvar_clicked() {

    ApplicationConfig config;
    config.language    = ui_option_->comboBox->currentText();
    config.fontFamily     = ui_option_->fontComboBox->currentText();
    config.themeName     = ui_option_->Combox_tema->currentText();

    auto file_save = FileManger::save(GLOBAL::PATCH_FILE::CONFIG,config);
    if (file_save) {
        qDebug () << "Salvo com sucesso";
    }else {
        qDebug () << "Erro ao salvar";
    }
}

option::~option() {
    delete ui_option_;
    GLOBAL::is_close_window_option = true;
}