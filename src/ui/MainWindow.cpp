//
// Created by KoTz on 10/06/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui__windows_.h" resolved


#include "ui/MainWindow.h"
#include <QDebug>
#include "../io/FileConverter.h"
#include "AvaliacaoDaPuc_autogen/include/ui_MainWindow.h"
#include "io/FileManager.h"

static bool max_ilimite_value(double n1,double n2) {
    if (n1 > 10.0 || n2 > 10.0) {
        return true;
    }
    return false;
}
void _windows_::Update_table_data() {
    if (ui->tableWidget->rowCount() == 0 && ui->tableWidget->columnCount() == 0) {
        return;
    }
    if (ui->tableWidget->rowCount() > 0) {
        for (int index_item = 0; index_item < ui->tableWidget->rowCount(); index_item++) {
            auto N1 = ui->tableWidget->item(index_item, 4)->text().toDouble();
            auto N2 = ui->tableWidget->item(index_item, 5)->text().toDouble();
            auto IA = ui->lineEdit->text().toFloat();
            auto Taught_Classes = ui->tableWidget->item(index_item, 2)->text().toInt();
            auto Attendance_Count = ui->tableWidget->item(index_item, 3)->text().toInt();
            if (this->system_notas != nullptr) {
                this->system_notas->sets_todas_atividades(0,Taught_Classes,Attendance_Count,N1,N2,IA);

                if (system_notas->Is_verify_grade_format(index_item))
                {
                    if (max_ilimite_value(N1,N2)) {
                        return;
                    }
                    this->system_notas->processGradeResult(index_item);
                }else {
                    Style_Table::Style::clear_table(ui->tableWidget,index_item,TYPE_GRADE::Resultado);
                    Style_Table::Style::clear_table(ui->tableWidget,index_item,TYPE_GRADE::Media);
                    Style_Table::Style::clear_table(ui->tableWidget,index_item,TYPE_GRADE::FALTA_MEDIA);
                }
                this->system_notas->clear_table_grade();
            }
        }
    }
}

/**
 * Inicializa os componentes principais da janela
 * 
 * Esta função realiza as seguintes inicializações:
 * - Cria e configura o controlador da interface gráfica
 * - Inicializa os elementos visuais da UI
 * - Configura os botões da interface
 * - Inicializa o gerenciador de arquivos
 * - Inicializa as variáveis globais
 */
void _windows_::initialize() {
    std::unique_ptr<ui_controller> controller_ui = std::make_unique<ui_controller>();
    ui_controller::Button(TYPE::MAIN_WINDOW,ui);
    //ui_controller::TableWidget(ui);
    FileManger::initialize_file_manager();
    GLOBAL::init_global(ui);
    ui_controller::WindowSystemTema();
}
/**
* Função que atualiza as notas na tabela
* Chamada periodicamente pelo timer para manter 
* a interface atualizada
*/
void _windows_::Update() {
    Update_table_data();
}
/**
 * Construtor da classe _windows_
 * Inicializa a interface gráfica, configura botões e timer
 * para atualização automática das notas
 * @param parent Widget pai (opcional)
 */
_windows_::_windows_(QWidget *parent) : QMainWindow(parent), ui(new Ui::_windows_) {
    ui->setupUi(this);
    initialize();
    FileManger::Load(GLOBAL::PATCH_FILE::CONFIG,GLOBAL::json);
    if (GLOBAL::json.empty() == false) {
        LanguageUI::initialize_language_ui(GLOBAL::json,this->ui,GLOBAL::idioma);
        UI_FONT::text(GLOBAL::json,ui);
    }


    system_notas = std::make_shared<GradeSystem>(ui->tableWidget);
    // system_notas = new GradeSystem(ui->tableWidget);
    this->timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start();
}
/**
 * Salva as informações da tabela em um arquivo
 *
 * Esta função coleta os dados de todas as linhas da tabela (nome, aulas previstas,
 * aulas ministradas, presenças e notas) e os salva em um arquivo JSON. O salvamento
 * pode ser feito de 3 formas diferentes:
 *
 * 1. Salvamento no arquivo atual (se houver um arquivo aberto)
 * 2. Salvamento com "Salvar como" em um novo arquivo (TYPE_SAVE::SAVE_AS)
 * 3. Salvamento no arquivo local padrão (TYPE_SAVE::SAVE_LOCAL_FILE)
 *
 * @param path Caminho do arquivo onde será salvo (usado apenas para SAVE_AS)
 * @param value Tipo de salvamento a ser realizado (SAVE_AS ou SAVE_LOCAL_FILE)
 *
 * @note A função atualiza um label na interface indicando sucesso ou falha do salvamento
 * @note Se a tabela estiver vazia, a função retorna sem fazer nada
 */
void _windows_::saveTableData(QString filePath_,SaveMode saveMode) {
    bool is_file_save = false;

    if (ui->tableWidget->rowCount() == 0) {
        return;
    }
    for (int index_item = 0; index_item < ui->tableWidget->rowCount(); index_item++) {
        auto nome = ui->tableWidget->item(index_item, 0)->text();
        auto aula_prevista = ui->tableWidget->item(index_item, 1)->text().toInt();
        auto aula_ministradas = ui->tableWidget->item(index_item, 2)->text().toInt();
        auto numero_presenca = ui->tableWidget->item(index_item, 3)->text().toInt();
        auto N1 = ui->tableWidget->item(index_item, 4)->text().toDouble();
        auto N2 = ui->tableWidget->item(index_item, 5)->text().toDouble();
        item_list_.push_back(Oitem(nome,aula_prevista,aula_ministradas,numero_presenca,N1,N2));
    }
    ui->label_3->clear();
    if (info_file.filePath.isEmpty() == false && is_file_open == true) {
        QFile outputFile(info_file.filePath);
        if (outputFile.exists() == true) {
            outputFile.remove();
        }
        is_file_save = FileManger::save(info_file.filePath,item_list_);
    }
    if (saveMode == SaveMode::SAVE_AS) {
        is_file_save = FileManger::save(filePath_,item_list_);
    }
    if (saveMode == SaveMode::SAVE_LOCAL_FILE) {
        is_file_save = FileManger::save(GLOBAL::PATCH_FILE::DATA,item_list_) ;
    }
    if (is_file_save) {
        ui->label_3->setText("Salvo !");
    }
    else {
        ui->label_3->setText("Falha de salvamento");
    }
    item_list_.clear();
}
void _windows_::on_actionOpition_triggered() {
        op = new option(this);
        op->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        op->show();
}
void _windows_::on_actionSalvar_como_triggered() {
    std::unique_ptr<QFileDialog> fileDialog = std::make_unique<QFileDialog>(this);
    auto selectedFile = fileDialog->getSaveFileName(this,"Salvar o arquivo","","");

    std::string filePath = selectedFile.toStdString();
    if (filePath.find(".json") == std::string::npos) {
         filePath = filePath += ".json";
         selectedFile = QString::fromStdString(filePath);
    }
    if (selectedFile!= nullptr && filePath.find(".json") != std::string::npos) {
         saveTableData(selectedFile,SAVE_AS);
    }else {
        ui->label_3->setText("Falha de salvamento necessario Json ");
    }
}
/**
 * Remove as aspas duplas (") de uma string
 * @param str String de entrada a ter as aspas removidas
 * @return String sem aspas duplas ou string vazia se a entrada for vazia
 */
QString removeDoubleQuotes(QString str) {
    if (str.isEmpty() == true) {
        return QString();
    }
    return str.remove('"');
}

/**
 * Função chamada quando a opção "Salvar" é acionada
 * Salva os dados da tabela em um arquivo texto formatado
 * com id, nome e notas de cada aluno
 */
void _windows_::on_actionSalvar_triggered() {
    if (is_file_open == true) {
        saveTableData(info_file.filePath,SAVE_AS);
        return;
    }
     saveTableData("",SAVE_LOCAL_FILE);
}
/**
 * Função chamada quando a opção "Abrir" é acionada
 * Abre uma janela de diálogo para selecionar um arquivo .txt
 * e carrega o seu conteúdo na tabela, populando nome e notas
 */
void _windows_::on_actionAbrir_triggered() {
    bool is_file_aluno = false;
    std::unique_ptr<QFileDialog> newDialog = std::make_unique<QFileDialog>(this);
    auto openFileUrl = newDialog->getOpenFileUrl(this, "Abrir VX", QUrl(), "Arquivos VX (*.vx)");
    nlohmann::json get_json = {};

    if (ui->tableWidget->rowCount() > 0) {
        for (int i = ui->tableWidget->rowCount()+1; i >= 0;i--) {
           ui->tableWidget->removeRow(i);
        }
    }
    bool isLoadSuccessful = false;
    if (openFileUrl.isValid() == true) {
        isLoadSuccessful = FileManger::Load(openFileUrl.toLocalFile(),get_json,is_file_open);
    }
     if (isLoadSuccessful == false) {
        return;
     }
          for (int a = 0; a < get_json.size();a++){
            ui->tableWidget->insertRow(0);
          }

    for (int b = 0; b < ui->tableWidget->rowCount();b++) {
        for (int a = 0; a < ui->tableWidget->columnCount();a++) {
            if (ui->tableWidget->item(b,a) == nullptr) {
                ui->tableWidget->setItem(b,a,new QTableWidgetItem());
            }
        }
    }

    try {
        int index = 0;
        for (auto & value : get_json ) {
            if (value.at("nome").is_string() == true
                    && value.at("aulas previstas").is_number() == true
                    && value.at("aulas ministradas").is_number() == true
                    && value.at("numero presenca").is_number() == true
                    && value.at("N1").is_number() == true
                    && value.at("N2").is_number() == true)
                {
                    auto nome =  to_string(value.at("nome"));
                    auto aulas_previstas = to_string(value.at("aulas previstas"));
                    auto aulas_ministradas = to_string(value.at("aulas ministradas"));
                    auto numeros_preseca = to_string(value.at("numero presenca"));
                    auto N1 = to_string(value.at("N1"));
                    auto N2 = to_string(value.at("N2"));
                    ui->tableWidget->item(index,0)->setText(removeDoubleQuotes(QString::fromStdString(nome)));
                    ui->tableWidget->item(index,1)->setText(removeDoubleQuotes(QString::fromStdString(aulas_previstas)));
                    ui->tableWidget->item(index,2)->setText(removeDoubleQuotes(QString::fromStdString(aulas_ministradas)));
                    ui->tableWidget->item(index,3)->setText(removeDoubleQuotes(QString::fromStdString(numeros_preseca)));
                    ui->tableWidget->item(index,4)->setText(removeDoubleQuotes(QString::fromStdString(N1)));
                    ui->tableWidget->item(index,5)->setText(removeDoubleQuotes(QString::fromStdString(N2)));
                
                    ui->tableWidget->verticalHeader()->setVisible(false);
                    index++;
                is_file_aluno = true;
            }
        }
    }catch (std::exception &e) {
        qDebug() << e.what();
    }
        if (is_file_aluno == true) {
             QString info = "Arquivo aberto: "+ openFileUrl.fileName();
             ui->info_arquivo->setText("Arquivo aberto: "+ openFileUrl.fileName());
             info_file.filePath = openFileUrl.toLocalFile();
             info_file.isOpen = is_file_open;
        }

}
void _windows_::on_actionNovo_triggered() {
    _windows_ *janela = new _windows_(this);
    janela->show();
}

_windows_::~_windows_() {
    delete is;
    delete ui;
}

/**
 * Função chamada quando o botão "Add" é clicado
 * Adiciona uma nova linha na tabela e inicializa suas células
 * com QTableWidgetItems vazios
 */
void _windows_::on_btn_add_clicked() {

    if (ui->tableWidget->rowCount() >= 12) {
        return;
    }

    ui->tableWidget->insertRow(0);
    for (int b = 0; b < ui->tableWidget->rowCount();b++) {
        for (int a = 0; a < ui->tableWidget->columnCount();a++) {
             if (ui->tableWidget->item(b,a) == nullptr) {
                 ui->tableWidget->setItem(b,a,new QTableWidgetItem);
                 QStringList labels;
                 labels << "";
                 ui->tableWidget->setVerticalHeaderLabels(labels);
                 ui->tableWidget->verticalHeader()->setVisible(false);
             }
        }
    }

    ui->tableWidget->item(0,6)->setFlags(Qt::ItemIsEnabled);
    ui->tableWidget->item(0,6)->setFlags(Qt::ItemIsEnabled);
    ui->tableWidget->item(0,7)->setFlags(Qt::ItemIsEnabled);
    ui->tableWidget->item(0,8)->setFlags(Qt::ItemIsEnabled);
}
/**
 * Função chamada quando o botão "Remover" é clicado
 * Remove a última linha da tabela
 */
void _windows_::on_btn_remover_clicked()
{
     std::set<int> listitem;
     for (auto & i : ui->tableWidget->selectedItems()) {
         listitem.insert(i->row());
     }
     for (auto i : listitem) {
        ui->tableWidget->removeRow(i);
     }
}
