//
// Created by KoTz on 05/05/2026.
//

#ifndef EDUMETRICS_TABLEGRADE_H
#define EDUMETRICS_TABLEGRADE_H

#include <windows/MainWindow.h>
#include <windows/AddSubjectDialog.h>

class MainWindow;


class TableGrade  {
private :
     static std::vector<StudentRecord>  item_list_;
     static bool is_file_open;
     static FileStatus info_file;
     static std::shared_ptr<GradeSystem> system_notas;

     static std::shared_ptr<addsubjectdialog> addsuject;
     static Ui::MainWindow *Main;
public :
      static void reset();
public:
     static void setaddsubjectdialog(const std::shared_ptr<addsubjectdialog> & addsubjectdialog_);
     static void setMainWindow(Ui::MainWindow *ui);
public slots :
     static void Update();
public :
     static void SaveTableData(QString filePath_,SaveMode saveMode);
     static void setDataTable();
};


#endif //EDUMETRICS_TABLEGRADE_H
