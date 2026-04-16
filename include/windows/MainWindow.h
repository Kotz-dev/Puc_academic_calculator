#ifndef _WINDOWS__H
#define _WINDOWS__H

#include <QTimer>
#include "core/GradeSystem.h"
#include "managers/UIManager.h"
#include "data/StudentRecord.h"
#include "windows/PreferencesWindow.h"
#include <string>
#include <fmt/core.h>
#include <QFileDialog>
#include "io/FileManager.h"
#include "utils/GlobalAccess.h"
#include "managers/LanguageManager.h"
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow  {
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

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

    void on_actionSobre_triggered();

    void initialize ();
    void saveTableData(QString filePath_,SaveMode saveMode);
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    std::shared_ptr<GradeSystem> system_notas;
    FileManager file;
    std::vector<StudentRecord>  item_list_;

    QString patch_load;
    FileStatus info_file;
    PreferencesWindow *window_PreferencesWindow;
    bool is_file_open = false;

};
#endif //_WINDOWS__H