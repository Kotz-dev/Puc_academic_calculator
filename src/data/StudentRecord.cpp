//
// Created by KoTz on 23/07/2025.
//

#include "data/StudentRecord.h"



StudentRecord::StudentRecord() {}

StudentRecord::StudentRecord(QString nome ,int aula_prevista,int aula_ministradas,int numero_presenca, double N1,double N2) {
    this->name = nome;
    this->planned_classes = aula_prevista;
    this->taught_classes = aula_ministradas;
    this->attendance_count  = numero_presenca;
    this->N1 = N1;
    this->N2 = N2;
}