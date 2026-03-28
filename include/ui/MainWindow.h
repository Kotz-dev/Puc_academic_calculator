#ifndef _WINDOWS__H
#define _WINDOWS__H

#include <QTimer>
#include "core/GradeSystem.h"
#include "ui/UIManager.h"
#include "data/StudentRecord.h"
#include "ui/PreferencesWindow.h"
#include <string>
#include <fmt/core.h>
#include <QFileDialog>
#include "io/FileManager.h"
#include "utils/GlobalAccess.h"
#include "ui/LanguageManager.h"
#include <QDir>
#include <QKeyEvent>
#include <QLocale>

QT_BEGIN_NAMESPACE
namespace Ui { class _windows_; }
QT_END_NAMESPACE


struct index_window {
     int window_janela_opition = 0;
     int window_janela_info = 0;
};

class _windows_ : public QMainWindow  {
    Q_OBJECT

    public:
    explicit _windows_(QWidget *parent = nullptr);
    ~_windows_() override;

private slots:
    void on_btn_add_clicked();
    void on_btn_remover_clicked();
    void Update();
    void Update_table_data();
    void on_actionAbrir_triggered();
    void on_actionNovo_triggered();
    void on_actionSalvar_triggered();
    void on_actionSalvar_como_triggered();
    void on_actionOpition_triggered();

    void initialize ();
    void saveTableData(QString filePath_,SaveMode saveMode);
private:
    Ui::_windows_ *ui;
    QTimer *timer;
    std::shared_ptr<GradeSystem> system_notas;
    ui_controller *is;
    FileManger file;
    std::vector<Oitem>  item_list_;

    QString patch_load;
    FileStatus info_file;
    option *op;
    bool is_file_open = false;

    index_window index_window_info;

};
#endif //_WINDOWS__H