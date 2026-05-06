//
// Created by KoTz on 28/06/2025.
//

#ifndef SYSTEM_NOTA_H
#define SYSTEM_NOTA_H

#include <QTableWidget>
#include <fmt/format.h>
#include "managers/UIManager.h"
#include "data/StudentRecord.h"


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
    int planned_classes;
    int taught_classes;
    int attendance_count;
    double attendance_percentage{};
    double average_grade;
    double final_grade;

    double IA{};
    bool is_rounded;

QTableWidget *table_widget_;
public :
      void processGradeResult(int indexItem);
      bool isValidGradeFormat(int row);
      void computeFinalGrade(double n1, double  n2, double  &finalGrade, double  IA);
      void computeFinalGrade(double n1, double  n2, double  &finalGrade);
      void checkNeededGrade(double  n1, double  n2, double  finalGrade, int row);
      QString roundGrade(double n);
      void calculateAttendance(int index, QTableWidget *table);

      void calculateNeededGrade(bool n1IsLower, bool n2IsLower, bool areEqual, int row);

       void setGradeData(int plannedClasses, int taughtClasses, int attendanceCount, double n1, double n2, double IA);
       void setGradeData(double n1, double n2, double IA);


       StudentRecord toRecord() const;

       void reset();


      GradeSystem();
      GradeSystem(QTableWidget * obj);

};



#endif //SYSTEM_NOTA_H
