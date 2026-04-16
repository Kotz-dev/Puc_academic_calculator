//
// Created by KoTz on 28/06/2025.
//

#include "core/GradeSystem.h"

void GradeSystem::calculateNeededGrade(bool n1IsLower, bool n2IsLower, bool areEqual, int row) {

    auto  N1 = this->N1;
    auto  N2 = this->N2;
    auto  NF = this->final_grade;

    const auto items = this->table_widget_->item(row,TYPE_GRADE::FALTA_MEDIA);
    if (n1IsLower == true) {
         for (double i = 0; i <= 10; i+=00.1) {
             computeFinalGrade(i, N2, NF);
             if (NF >= 6.0) {
                 items->setText(QString::fromStdString(fmt::format("N1 : {:-.1f} -> {:-.1f}",N1,i)));
                 return;
             }
             else {
                 items->setText("Não é possivel alcancar acima 6.0 do N1");
             }
         }
     }
     if (n2IsLower == true) {
             for (double i = 0; i <= 10; i+=00.1) {
                 computeFinalGrade(N1, i, NF);
                 if (NF >= 6) {
                     items->setText(QString::fromStdString(fmt::format("N2: {:-.1f} -> {:-.1f}",N2,i)));
                     return;
                 }
                 else {
                         items->setText("Não é possivel alcancar acima 6.0 do N2");
                 }
             }
     }
    if (areEqual == true) {
        for (double i =  N2; i <= 10; i+=00.1) {
            computeFinalGrade(i,i, NF);
            if (NF >= 6) {
                auto str = fmt::format("N1 ou N2 : {:-.1f} -> {:-.1f}",this->N1,i);
                items->setText(QString::fromStdString(str));
                return;
            }
        }
    }
}

void  GradeSystem::setGradeData(double n1,double n2,double IA) {
    this->N1 = n1;
    this->N2 = n2;

    this->IA = IA;
}

void GradeSystem::setGradeData(int plannedClasses, int taughtClasses, int attendanceCount, double n1, double n2, double IA) {
    this->taught_classes   = taughtClasses;
    this->planned_classes  = plannedClasses;
    this->attendance_count = attendanceCount;

    this->N1 = n1;
    this->N2 = n2;
    this->IA = IA;
}

void  GradeSystem::calculateAttendance(int index, QTableWidget *table) {
    if (table == nullptr) {
        return;
    }
     if (table->item(index, TYPE_GRADE::AULA_MINISTRADA)->text().isEmpty() == true ||
         table->item(index, TYPE_GRADE::NUMERO_PRESENCA)->text().isEmpty() == true) {
         return;
     }
     this->attendance_percentage = 0.0f;
     this->attendance_percentage = (double)this->attendance_count/(double)this->taught_classes*100;
}

void GradeSystem::checkNeededGrade(double n1, double n2, double finalGradeVal, int row) {
    bool n1_menor = false, n2_menor = false;

    // Se a nota final for maior ou igual a 6, limpa o texto e retorna

    if (finalGradeVal >= 6.0  || finalGradeVal >= 6.00 || finalGradeVal >= 6.0-1e-9) {
        table_widget_->item(row, TYPE_GRADE::FALTA_MEDIA)->setText("");  // limopar
        return;
    }
    if (is_rounded) {
        return;
    }
    auto item = this->table_widget_->item(row, 8);
    // Se o item for nulo, retorna
    if (item == nullptr) {
        return;
    }
    // Se ambas as notas forem zero, retorna
    if (n1 == 0.0f && n2 == 0.0f) {
        return;
    }
    // Verifica qual nota é menor
    if (n1 > n2) {
        n2_menor = true;
    }
    if (n2 > n1) {
        n1_menor = true;
    }

    this->calculateNeededGrade(n1_menor,n2_menor,n1 == n2,row);
}
/**
 * Calcula a nota final usando a fórmula: NF = 0.4*n1 + 0.6*n2
 * Se houver AI (Avaliação Individual), soma ao n2
 * @param n1 Nota 1
 * @param n2 Nota 2 
 * @param NF Nota Final (retornado por referência)
 * @param AI Avaliação Individual (opcional)
 */
void GradeSystem::computeFinalGrade(double n1, double n2, double &finalGrade, double AI) {
    if (n1 > 10.0 || n2 > 10.0) {
        return;
    }
    if (AI != 0.0f) {
        n2 = n2 + AI;
    }
    finalGrade = 0.4 * n1 + 0.6 * n2;
    if (finalGrade == 0.0f) {
        return;
    }
    this->final_grade = finalGrade;
}

StudentRecord GradeSystem::toRecord() const {
     return StudentRecord(this->Nome,
         this->planned_classes,
         this->taught_classes,
         this->attendance_count,
         this->N1,this->N2);
}
/**
 * Sobrecarga do método Formula_Avaliacao sem o parâmetro AI
 * Calcula a nota final usando a fórmula: NF = 0.4*n1 + 0.6*n2
 * @param n1 Nota 1
 * @param n2 Nota 2
 * @param NF Nota Final (retornado por referência)
 */
void GradeSystem::computeFinalGrade(double n1, double n2, double &finalGrade) {
    if (n1 >= 10.0 || n2 >= 10.0) {
        return;
    }
    finalGrade = 0.4 * n1 + 0.6 * n2;
    if (finalGrade == 0.0f) {
        return;
    }
    const auto get = fmt::format("{:-.2f}",finalGrade);
    finalGrade = QString::fromStdString(get).toDouble();
    this->final_grade = finalGrade;
}

/**
 * Limpa todas as variáveis do sistema, resetando-as para seus valores iniciais
 * - Notas N1, N2 e nota final são zeradas
 * - Contadores de aula e presenças são zerados 
 * - Médias e resultados são zerados
 * - Nota de IA (Avaliação Individual) é zerada
 */
void GradeSystem::reset() {
    N1 = 0.0f;
    N2 = 0.0f;
    planned_classes = 0;
    taught_classes = 0;
    attendance_count = 0;
    attendance_percentage = 0.0f;
    average_grade = 0.0f;
    final_grade = 0.0f;
    IA = 0.0f;
    is_rounded = false;
}
QString GradeSystem::roundGrade(double n) {
    if (n >= 5.8 - 1e-9 && n <= 5.99 - 1e-9) {
        is_rounded = true;
        return QString::fromStdString(fmt::format("{:.1f} -> {:.2f}",n,6.00));
    }
    return QString::fromStdString(fmt::format("{:.2f}",n));
}

/**
 * Processa o resultado da nota final (NF) e atualiza a tabela com o status do aluno
 * - Se NF == 0, retorna sem alterações
 * - Se NF <= 75, reprovado por falta
 * - Se NF >= 6, aprovado
 * - Se 0 < NF < 6, reprovado
 * @param indexItem Índice da linha na tabela
 */
void GradeSystem::processGradeResult(int indexItem) {
    if (indexItem < 0) {
        return;
    }
    double NF = 0.0f;
    computeFinalGrade(this->N1, this->N2, NF, this->IA);

    Style_Table::Style::clearCell(table_widget_, indexItem, TYPE_GRADE::Resultado);
    this->table_widget_->item(indexItem, TYPE_GRADE::Media)->setText(roundGrade(NF));
    calculateAttendance(indexItem, this->table_widget_);
    checkNeededGrade(this->N1, this->N2, NF, indexItem);

    if (NF == 0.0f ) {
        Style_Table::Style::clearCell(table_widget_, indexItem, TYPE_GRADE::Resultado);
        return;
    }
    if (is_rounded == true) {
        Style_Table::Style::setRowResult(table_widget_, indexItem, 1);
    }
    if (NF >= 6.0 || NF >= 6 || NF >= 6.0 - 1e-9 || is_rounded == true) {
        Style_Table::Style::setRowResult(table_widget_, indexItem, 1);
    }else if (NF < 6.0-1e-9 && NF > 0.0- 1e-9) {
        Style_Table::Style::setRowResult(table_widget_, indexItem, 2);
    }
    if (attendance_percentage != 0.0 || attendance_percentage != 0.0f) {
        if (this->attendance_percentage <= 75.0 - 1e-9 && this->attendance_percentage >= 0.0- 1e-9) {
            Style_Table::Style::setRowResult(table_widget_, indexItem, 0);
        }
    }
}

bool validate_entry(QString entry) {
    const std::vector<QString> invalidCharacters =
    {
        "-", "[", "]", "!", "@", "#",
        "$", "%", "^", "&",
        "*", "(", ")", "+", "=",
        "{", "}", "|", "\\",
        ";", ":", "'", "\"", ",",
        "<", ">", "?", "/", "~", "`",
        "_"
    };
    std::string input_n2 = entry.toStdString();
    for (auto & text : invalidCharacters) {
        if (input_n2.find(text.toStdString().c_str()) != std::string::npos) {
            return false;
        }
    }
    return true;
}

bool startsWithDot(QString input_str) {
    int value = -1;
    for (auto &i: input_str.toStdString()) {
        if (i == '.' && value == -1) {
            return true;
        }
        value++;
    }
    return !(value >= -1 );
}


bool GradeSystem::isValidGradeFormat(int row){
        int dotCountN1 = 0; int dotCountN2 = 0;

        auto firstInput_n1 = this->table_widget_->item(row, TYPE_GRADE::N1);
        auto firstInput_n2 = this->table_widget_->item(row, TYPE_GRADE::N2);

        if (firstInput_n1 == nullptr || firstInput_n2 == nullptr) {
            return false;
        }
        if (firstInput_n1->text().isEmpty() || firstInput_n2->text().isEmpty()) {
            return false;
        }
        for (auto &IP: firstInput_n1->text().toStdString()) {
            if (isalpha(IP)) {
                return false;
            }
        }
        for (auto &IP: firstInput_n2->text().toStdString()) {
            if (isalpha(IP)) {
                return false;
            }
        }
        std::string input_n1 = firstInput_n1->text().toStdString();
        std::string input_n2 = firstInput_n2->text().toStdString();

        if (startsWithDot(QString::fromStdString(input_n1)) || startsWithDot(QString::fromStdString(input_n2))) {
            return false;
        }
        for (int a = 0; a < input_n1.size(); a++) {

           if (input_n1[a] == '.') {
               dotCountN1++;
           }
        }for (int a = 0; a < input_n2.size(); a++) {
            if (input_n2[a] == '.') {
                dotCountN2++;
            }
        }
        if (validate_entry(firstInput_n1->text()) == false || validate_entry(firstInput_n2->text()) == false) {
            return false;
        }
    return !(dotCountN1 > 1 || dotCountN2 > 1);
}
GradeSystem::GradeSystem():
                 N1(0.0f),
                 N2(0.0f),planned_classes(0),
                 taught_classes(0),
                 attendance_count(0),
                 average_grade(0.0f),
                 final_grade(0.0f),
                 is_rounded(false),table_widget_(nullptr) {}

GradeSystem::GradeSystem(QTableWidget *obj):
                N1(0.0f),N2(0.0f),
                planned_classes(0),
                taught_classes(0),
                attendance_count(0),
                average_grade(0.0f),
                final_grade(0.0f),
                is_rounded(false),table_widget_(nullptr){
     if (obj != nullptr) {
        this->table_widget_ = obj;
     }
}
