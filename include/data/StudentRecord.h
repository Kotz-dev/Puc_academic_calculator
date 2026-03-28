//
// Created by KoTz on 23/07/2025.
//

#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include <QString>

struct Oitem {
    uint id;
    QString name;
    int planned_classes;
    int taught_classes;
    int attendance_count;
    double N1;
    double N2;
    double IA;

    bool operator < (const Oitem &other) const {
        return id < other.id;
    }

     Oitem ();
     Oitem(QString nome ,int aula_prevista,int aula_ministradas,int numero_presenca, double N1,double N2);
};


#endif //STUDENT_RECORD_H
