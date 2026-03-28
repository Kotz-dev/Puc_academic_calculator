//
// Created by KoTz on 28/06/2025.
//

#include "core/GradeSystem.h"

void GradeSystem::FormulaParaMedia(bool N1_menor, bool n2_menor, bool iguais,int row) {

    auto  N1 = this->N1;
    auto  N2 = this->N2;
    auto  NF = this->nota_final;

    QString is = "";
    const auto items = this->table_widget_->item(row,TYPE_GRADE::FALTA_MEDIA);
    std::string teste;
    if (N1_menor == true) {
         for (double i = 0; i <= 10; i+=00.1) {
             Formula_Avaliacao(i, N2, NF);
             if (NF >= 6.0) {
                 items->setText(QString::fromStdString(fmt::format("N1 : {:-.1f} -> {:-.1f}",N1,i)));
                 return;
             }
             else {
                 items->setText("Não é possivel alcancar acima 6.0 do N1");
             }
         }
     }
     if (n2_menor == true) {
             QString str_n2 = "";
             for (double i = 0; i <= 10; i+=00.1) {
                 Formula_Avaliacao(N1, i, NF);
                 if (NF >= 6) {
                     items->setText(QString::fromStdString(fmt::format("N2: {:-.1f} -> {:-.1f}",N2,i)));
                     return;
                 }
                 else {
                         items->setText("Não é possivel alcancar acima 6.0 do N2");
                 }
             }
     }
    if (iguais == true) {
        for (double i =  N2; i <= 10; i+=00.1) {
            Formula_Avaliacao(i,i, NF);
            if (NF >= 6) {
                auto str = fmt::format("N1 ou N2 : {:-.1f} -> {:-.1f}",this->N1,i);
                items->setText(QString::fromStdString(str));
                return;
            }
        }
           std::array<int,20> teste = {};
    }
}

void  GradeSystem::sets_todas_atividades(double n1,double n2,double IA) {
    this->N1 = n1;
    this->N2 = n2;

    this->IA = IA;
}

void GradeSystem::sets_todas_atividades(int aula_prevista, int aula_ministradas, int numero_presenca,double n1,double n2,double IA) {
    this->aula_ministradas = aula_ministradas;
    this->aula_prevista    = aula_prevista;
    this->numero_presenca  = numero_presenca;

    this->N1 = n1;
    this->N2 = n2;

    this->IA = IA;
}

void  GradeSystem::Quantidade_faltas(int index,QTableWidget *ui) {
    if (ui == nullptr) {
        return;
    }
     if (ui->item(index, TYPE_GRADE::AULA_MINISTRADA)->text().isEmpty() == true ||
         ui->item(index, TYPE_GRADE::NUMERO_PRESENCA)->text().isEmpty() == true) {
         return;
     }
     this->result_presenca = 0.0f;
     this->result_presenca = (double)this->numero_presenca/(double)this->aula_ministradas*100;
}

void GradeSystem::FaltouMedia(double n1, double n2, double NFs, int row) {
    bool n1_menor = false, n2_menor = false;

    // Se a nota final for maior ou igual a 6, limpa o texto e retorna

    if (NFs >= 6.0  || NFs >= 6.00 || NFs>= 6.0-1e-9) {
        table_widget_->item(row, TYPE_GRADE::FALTA_MEDIA)->setText("");  // limopar
        return;
    }
    if (is_arrenado) {
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

    this->FormulaParaMedia(n1_menor,n2_menor,n1 == n2,row);
}
/**
 * Calcula a nota final usando a fórmula: NF = 0.4*n1 + 0.6*n2
 * Se houver AI (Avaliação Individual), soma ao n2
 * @param n1 Nota 1
 * @param n2 Nota 2 
 * @param NF Nota Final (retornado por referência)
 * @param AI Avaliação Individual (opcional)
 */
void GradeSystem::Formula_Avaliacao(double n1, double n2 , double  &NF, double  AI) {
    if (n1 > 10.0 || n2 > 10.0) {
        return;
    }
    if (AI != 0.0f) {
        n2 = n2 + AI;
    }
    NF = 0.4 * n1 + 0.6 * n2;
    if (NF == 0.0f) {
        return;
    }
    this->nota_final = NF;
}

Oitem GradeSystem::Get_All() const {
     return Oitem(this->Nome,
         this->aula_prevista,
         this->aula_ministradas,
         this->numero_presenca,
         this->N1,this->N2);
}
/**
 * Sobrecarga do método Formula_Avaliacao sem o parâmetro AI
 * Calcula a nota final usando a fórmula: NF = 0.4*n1 + 0.6*n2
 * @param n1 Nota 1
 * @param n2 Nota 2
 * @param NF Nota Final (retornado por referência)
 */
void GradeSystem::Formula_Avaliacao(double  n1, double  n2, double  &NF) {
    if (n1 >= 10.0 || n2 >= 10.0) {
        return;
    }
    NF = 0.4 * n1 + 0.6 * n2;
    if (NF == 0.0f) {
        return;
    }
    const auto get = fmt::format("{:-.2f}",NF);
    NF = QString::fromStdString(get).toDouble();
    this->nota_final = NF;
}

/**
 * Limpa todas as variáveis do sistema, resetando-as para seus valores iniciais
 * - Notas N1, N2 e nota final são zeradas
 * - Contadores de aula e presenças são zerados 
 * - Médias e resultados são zerados
 * - Nota de IA (Avaliação Individual) é zerada
 */
void GradeSystem::clear_table_grade() {
    N1 = 0.0f;
    N2 = 0.0f;
    aula_prevista = 0;
    aula_ministradas = 0;
    numero_presenca = 0;
    result_presenca = 0.0f;
    media = 0.0f;
    nota_final = 0.0f;
    IA = 0.0f;
    is_arrenado = false;
}
QString GradeSystem::is_arredonar(double n) {
    if (n >= 5.8 - 1e-9 && n <= 5.99 - 1e-9) {
        is_arrenado = true;
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
    Formula_Avaliacao(this->N1, this->N2, NF, this->IA);

    Style_Table::Style::clear_table(table_widget_, indexItem, TYPE_GRADE::Resultado);
    this->table_widget_->item(indexItem, TYPE_GRADE::Media)->setText(is_arredonar(NF));
    Quantidade_faltas(indexItem, this->table_widget_);
    FaltouMedia(this->N1, this->N2, NF, indexItem);

    if (NF == 0.0f ) {
        Style_Table::Style::clear_table(table_widget_, indexItem, TYPE_GRADE::Resultado);
        return;
    }
    if (is_arrenado == true) {
        Style_Table::Style::table_result(table_widget_, indexItem, 1);
    }
    if (NF >= 6.0 || NF >= 6 || NF >= 6.0 - 1e-9 || is_arrenado == true) {
        Style_Table::Style::table_result(table_widget_, indexItem, 1);
    }else if (NF < 6.0-1e-9 && NF > 0.0- 1e-9) {
        Style_Table::Style::table_result(table_widget_, indexItem, 2);
    }
    if (result_presenca != 0.0 || result_presenca != 0.0f) {
        if (this->result_presenca <= 75.0 - 1e-9 && this->result_presenca >= 0.0- 1e-9) {
            Style_Table::Style::table_result(table_widget_, indexItem, 0);
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


bool GradeSystem::Is_verify_grade_format(int grade_values){
        int dotCountN1 = 0; int dotCountN2 = 0;

        auto firstInput_n1 = this->table_widget_->item(grade_values, TYPE_GRADE::N1);
        auto firstInput_n2 = this->table_widget_->item(grade_values, TYPE_GRADE::N2);

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
                 N2(0.0f),aula_prevista(0),
                 aula_ministradas(0),
                 numero_presenca(0),
                 media(0.0f),
                 nota_final(0.0f),
                 is_arrenado(false),table_widget_(nullptr) {}

GradeSystem::GradeSystem(QTableWidget *obj):
                N1(0.0f),N2(0.0f),
                aula_prevista(0),
                aula_ministradas(0),
                numero_presenca(0),
                media(0.0f),
                nota_final(0.0f),
                is_arrenado(false),table_widget_(nullptr){
     if (obj != nullptr) {
        this->table_widget_ = obj;
     }
}
