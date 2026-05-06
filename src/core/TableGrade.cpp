//
// Created by KoTz on 05/05/2026.
//

#include "../../include/core/TableGrade.h"

#include <ui_AddSubjectDialog.h>

Ui::MainWindow* TableGrade::Main = nullptr;
std::shared_ptr<GradeSystem> TableGrade::system_notas = nullptr;
FileStatus TableGrade::info_file;
bool TableGrade::is_file_open = false;
std::vector<StudentRecord>  TableGrade::item_list_;
std::shared_ptr<addsubjectdialog> TableGrade::addsuject = nullptr;

void TableGrade::SaveTableData(QString filePath_, SaveMode saveMode) {
    bool is_file_save = false;

    if (Main->tableWidget->rowCount() == 0) {
        return;
    }
    for (int index_item = 0; index_item < Main->tableWidget->rowCount(); index_item++) {
        auto nome = Main->tableWidget->item(index_item, 0)->text();
        auto aula_prevista = Main->tableWidget->item(index_item, 1)->text().toInt();
        auto aula_ministradas = Main->tableWidget->item(index_item, 2)->text().toInt();
        auto numero_presenca = Main->tableWidget->item(index_item, 3)->text().toInt();
        auto N1 = Main->tableWidget->item(index_item, 4)->text().toDouble();
        auto N2 = Main->tableWidget->item(index_item, 5)->text().toDouble();
        item_list_.push_back(StudentRecord(nome,aula_prevista,aula_ministradas,numero_presenca,N1,N2));
    }
    Main->label_3->clear();
    if (info_file.filePath.isEmpty() == false && is_file_open == true) {
        QFile outputFile(info_file.filePath);
        if (outputFile.exists() == true) {
            outputFile.remove();
        }
        is_file_save = FileManager::save(info_file.filePath,item_list_);
    }
    if (saveMode == SaveMode::SAVE_AS) {
        is_file_save = FileManager::save(filePath_,item_list_);
    }
    if (saveMode == SaveMode::SAVE_LOCAL_FILE) {
        is_file_save = FileManager::save(GLOBAL::FILE_PATHS::DATA,item_list_) ;
    }
    if (is_file_save) {
        Main->label_3->setText("Salvo !");
        //QTimer::singleShot(2000, [](){ Main->label_3->clear(); });
    }
    else {
        Main->label_3->setText("Falha de salvamento");
       // QTimer::singleShot(2000, [](){ Main->label_3->clear(); });
    }
    item_list_.clear();
}

void TableGrade::reset() {
    TableGrade::addsuject.reset();
}

void TableGrade::setDataTable() {


}

void TableGrade::setMainWindow(Ui::MainWindow *ui) {
    Main = ui;
}

void TableGrade::setaddsubjectdialog(const std::shared_ptr<addsubjectdialog>  & addsubjectdialog_) {
    addsuject = addsubjectdialog_;
}


void TableGrade::Update() {
    if (Main != nullptr) {
        if (Main->tableWidget->rowCount() == 0 && Main->tableWidget->columnCount() == 0) {
            return;
        }
        if (Main->tableWidget->rowCount() > 0) {

        }

    }
}
