//
// Created by KoTz on 28/06/2025.
//

#ifndef SYSTEM_NOTA_H
#define SYSTEM_NOTA_H

#include <QTableWidget>
#include <fmt/format.h>
#include "ui/UIManager.h"
#include "data/StudentRecord.h"
#include <ui/LanguageManager.h>


enum TYPE_GRADE {
    NAME = 0,
    AULA_PREVISTA = 1,
    AULA_MINISTRADA = 2,
    NUMERO_PRESENCA = 3,
    N1 = 4,
    N2 = 5,
    Media = 6,
    Resultado = 7,
    FALTA_MEDIA = 8
};
class GradeSystem {
private :
    QString Nome;
    double N1;
    double N2;
    int aula_prevista;
    int aula_ministradas;
    int numero_presenca;
    double result_presenca{};
    double media;
    double nota_final;

    double IA{};
    bool is_arrenado;

     int x = 0;

QTableWidget *table_widget_;
public :
      void processGradeResult(int indexItem);
      bool Is_verify_grade_format(int grade_values);
      void Formula_Avaliacao(double n1, double  n2, double  &NF,double  AI);
      void Formula_Avaliacao(double n1, double  n2, double  &NF);
      void FaltouMedia(double  n1,double  n2,double  NF,int row);
      QString is_arredonar(double n);
      void Quantidade_faltas(int index,QTableWidget *ui);

      void FormulaParaMedia(bool N1_Menor,bool N2_Menor, bool iguais,int row);

       void sets_todas_atividades(int aula_prevista,int aula_ministradas,int numero_presenca,double n1,double n2,double IA);
       void sets_todas_atividades(double n1,double n2,double IA);


       Oitem Get_All() const;

       void clear_table_grade();


      GradeSystem();
      GradeSystem(QTableWidget * obj);

};



#endif //SYSTEM_NOTA_H
