#include "managers/LanguageManager.h"
#include  <QDebug>

QString LanguageManager::Languagem() {

    auto languagem  = QString::fromStdString(readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"idioma"));
    std::vector<std::string> urlLanguagem = {"en.ivx","english.ivx","Ingles.ivx"};
    std::string Lag = "";
    if (languagem == "Ingles") {
        Lag = "en.ivx";
    }
    if (languagem == "Português") {
        Lag = "pt-br.ivx";
    }
    std::filesystem::path Path = "resources/i18n/";
    std::filesystem::path get = std::filesystem::current_path().remove_filename() / Path / Lag;
    return QString::fromStdString(get.string());
  }


void LanguageManager::TraduzirPrencesWindow() {
    nlohmann::json json;
    std::array<QString,10>  menu_option;
    json = LoadJson(Languagem()).json;

    //std::vector<QString>    menu_arquivos(GLOBAL::WINDOW::ui_PrenferecesWindow->ui()->comboBox->size());

    menu_option[0] = QString::fromStdString(json["PREF_LANGUAGE"]).remove('"');
    menu_option[1] = QString::fromStdString(json["BTN_APPLY"]).remove('"');
    menu_option[2] = QString::fromStdString(json["BTN_SAVE"]).remove('"');
    menu_option[3] = QString::fromStdString(json["PREF_THEME"]).remove('"');
    menu_option[4] = QString::fromStdString(json["PREF_FONT"]).remove('"');

    if (GLOBAL::WINDOW::ui_PrenferecesWindow != nullptr) {
        GLOBAL::WINDOW::ui_PrenferecesWindow->ui()->label->setText(menu_option[0]);
        GLOBAL::WINDOW::ui_PrenferecesWindow->ui()->btn_aplicar->setText(menu_option[1]);
        GLOBAL::WINDOW::ui_PrenferecesWindow->ui()->btn_salvar->setText(menu_option[2]);
        GLOBAL::WINDOW::ui_PrenferecesWindow->ui()->label_tema->setText(menu_option[3]);
    }
}

LAGUAGEM LanguageManager::getLanguage() {
    // auto languagem  = QString::fromStdString(readJsonKey(GLOBAL::FILE_PATHS::CONFIG,"idioma"));
    // std::vector<QString> idm {"Ingles","en","english","Pt-br","portugues brasileiro","portugues"};
    // for (auto & i : idm) {
    //
    // }

    return LAGUAGEM::English;

}

void LanguageManager::TraduzirMainWindow() {
     nlohmann::json json;

    json = LoadJson(Languagem()).json;

    if (GLOBAL::WINDOW::UI != nullptr) {
        std::vector<QString>    menu_arquivo(GLOBAL::WINDOW::UI->menuArquivos->actions().size()+1);
        std::vector<QString>    menu_ferramentas(GLOBAL::WINDOW::UI->menuFerramentas->actions().size()+1);
        std::vector<QString>    tabela_aluno(GLOBAL::WINDOW::UI->tableWidget->columnCount());

        menu_arquivo[0] = QString::fromStdString(json["FILE_MENU"]).remove('"');
        menu_arquivo[1] = QString::fromStdString(json["FILE_NEW"]).remove('"');
        menu_arquivo[2] = QString::fromStdString(json["FILE_OPEN"]).remove('"');
        menu_arquivo[3] = QString::fromStdString(json["FILE_SAVE"]).remove('"');
        menu_arquivo[4] = QString::fromStdString(json["FILE_SAVE_AS"]).remove('"');

        tabela_aluno[0] = QString::fromStdString(json["TABLE_NAME"]).remove('"');
        tabela_aluno[1] = QString::fromStdString(json["TABLE_PLANNED"]).remove('"');
        tabela_aluno[2] = QString::fromStdString(json["TABLE_TAUGHT"]).remove('"');
        tabela_aluno[3] = QString::fromStdString(json["TABLE_ATTENDANCE"]).remove('"');
        tabela_aluno[4] = QString::fromStdString(json["TABLE_AVERAGE"]).remove('"');
        tabela_aluno[5] = QString::fromStdString(json["TABLE_RESULT"]).remove('"');
        tabela_aluno[6] = QString::fromStdString(json["TABLE_MISS_AVG"]).remove('"');

        menu_ferramentas[0] = QString::fromStdString(json["TOOLS_MENU"]).remove('"');
        menu_ferramentas[1] = QString::fromStdString(json["TOOLS_PREFERENCES"]).remove('"');
        menu_ferramentas[2] = QString::fromStdString(json["HELP_MENU"]).remove('"');
        menu_ferramentas[3] = QString::fromStdString(json["TOOLS_EVALUATION"]).remove('"');



        GLOBAL::WINDOW::UI->menuArquivos->setTitle(menu_arquivo[0]);
        GLOBAL::WINDOW::UI->actionNovo->setText(menu_arquivo[1]);
        GLOBAL::WINDOW::UI->actionAbrir->setText(menu_arquivo[2]);
        GLOBAL::WINDOW::UI->actionSalvar->setText( menu_arquivo[3]);
        GLOBAL::WINDOW::UI->actionSalvar_como->setText(menu_arquivo[4]);

        GLOBAL::WINDOW::UI->tableWidget->setHorizontalHeaderLabels({
            tabela_aluno[0],
            tabela_aluno[1],
            tabela_aluno[2],
            tabela_aluno[3],
               "N1",
               "N2",
            tabela_aluno[4],
            tabela_aluno[5],
            tabela_aluno[6]
        });
        GLOBAL::WINDOW::UI->menuFerramentas->setTitle(menu_ferramentas[0]);
        GLOBAL::WINDOW::UI->actionOpition->setText(menu_ferramentas[1]);
        GLOBAL::WINDOW::UI->menuAjuda->setTitle(menu_ferramentas[2]);
        GLOBAL::WINDOW::UI->actionSdeAvaliacao->setText(menu_ferramentas[3]);
    }
}

void LanguageManager::initialize_language(){

    TraduzirMainWindow();
}
