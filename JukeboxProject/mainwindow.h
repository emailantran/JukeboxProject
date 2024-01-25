#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cmp3info.h"
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WorkerThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::string path;
    std::map<QString, CMP3Info> fileMap;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleResults(const QString &result);
    void startWorkInAThread(QProcess* process, QString parameter);

private slots:

    void on_pushButtonstop_pressed();

    void on_pushButtonstart_pressed();

private:
    Ui::MainWindow *ui;
    WorkerThread *workerThread;
};
#endif // MAINWINDOW_H
