//
// Created by KoTz on 10/06/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui__windows_.h" resolved

#include  "exprtk.hpp"
#include "windows/MainWindow.h"
#include <QDebug>
#include <ui_aboutdialog.h>
#include <windows/aboutdialog.h>

#include "ui_MainWindow.h"
#include "io/FileManager.h"

#include <windows/system_evaluation.h>

#include <windows/aboutdialog.h>
#include "AddSubjectDialog.h"
#include <version.h>

#include <TableGrade.h>
#include <LanguageManager.h>

static bool isGradeOutOfRange(double n1,double n2) {
    if (n1 > 10.0 || n2 > 10.0) {
        return true;
    }
    return false;
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
void MainWindow::initialize() {
    ui->label_version->setText(EduMestrics::VERSION);
    GLOBAL::WINDOW::main = this;
    std::unique_ptr<ui_styles_> controller_ui = std::make_unique<ui_styles_>();
    FileManager::initialize();
    TableGrade::setMainWindow(ui);
    GLOBAL::WINDOW::UI = ui;
    ui_styles_::applyTheme();
    LanguageManager::initialize_language();
}



/**
 * Construtor da classe _windows_
 * Inicializa a interface gráfica, configura botões e timer
 * para atualização automática das notas
 * @param parent Widget pai (opcional)
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    initialize();
    FileManager::Load(GLOBAL::FILE_PATHS::CONFIG,GLOBAL::json);
    if (GLOBAL::json.empty() == false) {
        UI_FONT::text(GLOBAL::json,ui);
    }
    system_notas = std::make_shared<GradeSystem>(ui->tableWidget);
    this->timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, &QTimer::timeout, &TableGrade::Update);
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
void MainWindow::saveTableData(QString filePath_,SaveMode saveMode) {
    // bool is_file_save = false;
    //
    // if (ui->tableWidget->rowCount() == 0) {
    //     return;
    // }
    // for (int index_item = 0; index_item < ui->tableWidget->rowCount(); index_item++) {
    //     auto nome = ui->tableWidget->item(index_item, 0)->text();
    //     auto aula_prevista = ui->tableWidget->item(index_item, 1)->text().toInt();
    //     auto aula_ministradas = ui->tableWidget->item(index_item, 2)->text().toInt();
    //     auto numero_presenca = ui->tableWidget->item(index_item, 3)->text().toInt();
    //     auto N1 = ui->tableWidget->item(index_item, 4)->text().toDouble();
    //     auto N2 = ui->tableWidget->item(index_item, 5)->text().toDouble();
    //     item_list_.push_back(StudentRecord(nome,aula_prevista,aula_ministradas,numero_presenca,N1,N2));
    // }
    // ui->label_3->clear();
    // if (info_file.filePath.isEmpty() == false && is_file_open == true) {
    //     QFile outputFile(info_file.filePath);
    //     if (outputFile.exists() == true) {
    //         outputFile.remove();
    //     }
    //     is_file_save = FileManager::save(info_file.filePath,item_list_);
    // }
    // if (saveMode == SaveMode::SAVE_AS) {
    //     is_file_save = FileManager::save(filePath_,item_list_);
    // }
    // if (saveMode == SaveMode::SAVE_LOCAL_FILE) {
    //     is_file_save = FileManager::save(GLOBAL::FILE_PATHS::DATA,item_list_) ;
    // }
    // if (is_file_save) {
    //     ui->label_3->setText("Salvo !");
    //     QTimer::singleShot(2000, this, [this]() { ui->label_3->clear(); });
    //
    // }
    // else {
    //     ui->label_3->setText("Falha de salvamento");
    //     QTimer::singleShot(2000, this, [this]() { ui->label_3->clear(); });
    //
    // }
    // item_list_.clear();
}
void MainWindow::on_actionOpition_triggered() {

    if (GLOBAL::WINDOW::ui_PrenferecesWindow != nullptr) {
        delete GLOBAL::WINDOW::ui_PrenferecesWindow;
    }
    window_PreferencesWindow = new PreferencesWindow(this);
    GLOBAL::WINDOW::ui_PrenferecesWindow = window_PreferencesWindow;
    window_PreferencesWindow->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    window_PreferencesWindow->setWindowModality(Qt::WindowModal);
    window_PreferencesWindow->show();
}
void MainWindow::on_actionSalvar_como_triggered() {
    std::unique_ptr<QFileDialog> fileDialog = std::make_unique<QFileDialog>(this);
    auto selectedFile = fileDialog->getSaveFileName(this,"Salvar o arquivo","data.vx","Arquivos VX (*.vx)");
    std::string filePath = selectedFile.toStdString();
    if (selectedFile.isEmpty() == false && filePath.find(".vx") != std::string::npos) {
        saveTableData(selectedFile,SAVE_AS);
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
void MainWindow::on_actionSalvar_triggered() {
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
void MainWindow::on_actionAbrir_triggered() {
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
        isLoadSuccessful = FileManager::Load(openFileUrl.toLocalFile(),get_json,is_file_open);
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
             ui->info_arquivo->setText("Aberto: "+ openFileUrl.fileName());
             info_file.filePath = openFileUrl.toLocalFile();
             info_file.isOpen = is_file_open;
        }

}
void MainWindow::on_actionNovo_triggered() {
    MainWindow *newWindow = new MainWindow(this);
    newWindow->show();
}

MainWindow::~MainWindow() {
    delete ui;
}

bool  MainWindow::showAddSubjectDialog() {
    std::shared_ptr<addsubjectdialog> janela = std::make_shared<addsubjectdialog>(this);
    janela->setWindowModality(Qt::WindowModal);
    janela->setWindowFlags(Qt::Window| Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
   TableGrade::setaddsubjectdialog(janela);
    auto get =  janela->exec();

    if (get == QDialog::Rejected) {
        TableGrade::reset();
        return true;
    }
    return false;
}

/**
 * Função chamada quando o botão "Add" é clicado
 * Adiciona uma nova linha na tabela e inicializa suas células
 * com QTableWidgetItems vazios
 */
void MainWindow::on_btn_add_clicked() {

    if (showAddSubjectDialog()) {
        return;
    }

    if (ui->tableWidget->rowCount() >= 12) {
        return;
    }

    ui->tableWidget->insertRow(0);

    if (ui->tableWidget->rowCount() )

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

    ui->label_total_mat->setText(QString::number(ui->tableWidget->rowCount()) + " disciplinas");
}

/**
 * Função chamada quando o botão "Remover" é clicado
 * Remove a última linha da tabela
 */
void MainWindow::on_btn_remover_clicked()
{
    int coluna = 0;
   for (int a = 0; a < ui->tableWidget->rowCount();a++) {
       while (coluna < ui->tableWidget->columnCount()) {
           if (ui->tableWidget->item(a,coluna) != nullptr ) {
               if (ui->tableWidget->item(a,coluna)->text() == "") {
                   ui->tableWidget->removeRow(a);
                   a--;
               }
           }
           coluna++;
       }
   }
     std::set<int> listitem;
     for (auto & i : ui->tableWidget->selectedItems()) {
         listitem.insert(i->row());
     }
     for (auto i : listitem) {
        ui->tableWidget->removeRow(i);
     }

    ui->label_total_mat->setText(QString::number(ui->tableWidget->rowCount()) +" disciplinas");
}

void MainWindow::on_actionSobre_triggered() {
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->show();
}

void MainWindow::on_actionSdeAvaliacao_triggered() {
   evaluation_system *janela = new evaluation_system(this);
    janela->setWindowModality(Qt::WindowModal);
    janela->setWindowFlags(Qt::Window| Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
   janela->show();
}
