#include "mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <string>
#include <iostream>
#include <filesystem>
#include <QDir>
#include <QInputDialog>
#include "cmp3info.h"
#include "workerthread.h"
#include "./ui_mainwindow.h"

namespace fs = std::filesystem;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workerThread(nullptr)
{

    path = QInputDialog::getText(this, "Enter Path", "Enter the path to your mp3 files:").toStdString();

    ui->setupUi(this);


    QString names[1000];

    int j = 0;
    for(const auto & entry : fs::directory_iterator(path)) {
        QString noPathMp3 = QString::fromStdString(entry.path().filename().stem().string());
        fileMap[noPathMp3] = CMP3Info(QString::fromStdString(entry.path().filename().stem().string()), QString::fromStdString(entry.path().string()));
        names[j] = QString::fromStdString(entry.path().filename().stem().string());
        ui->listWidgetsong->addItem(QString::fromStdString(entry.path().filename().stem().string()));

        j++;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleResults(const QString &result)
{

}

void MainWindow::startWorkInAThread(QProcess* process, QString parameter)
{

    workerThread->setParameter(process, parameter);
    // Start the worker thread
    workerThread->start();
}



//void MainWindow::on_pushButtonPlay_2_pressed()
//{
//    QMessageBox::StandardButton reply;
//    QListWidgetItem* item = ui->listWidgetSongs_2->currentItem();

//    if (item == nullptr) {
//        // do nothing because no song is selected
//    } else {

//        std::string stdStringMpg123 = "mpg123 \"" + fileMap[item->text()].getPath().toStdString() + "\"";
//        QProcess* p = new QProcess;
//        QString tmp = QString::fromStdString(stdStringMpg123);



//        if (workerThread != nullptr) {
//            if (workerThread->isRunning()) {
//                workerThread->stop();
//                ui->listWidgetCurrent_2->clear();

//                ui->listWidgetCurrent_2->addItem(fileMap[item->text()].getTitle());

//                // Create worker thread
//                workerThread = new WorkerThread(this);

//                // Connect signals and slots
//                connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
//                connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//                connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

//                // Start work in a thread
//                startWorkInAThread(p, tmp);

//            } else {
//                ui->listWidgetCurrent_2->clear();

//                ui->listWidgetCurrent_2->addItem(fileMap[item->text()].getTitle());


//                // Create worker thread
//                workerThread = new WorkerThread(this);

//                // Connect signals and slots
//                connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
//                connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//                connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

//                // Start work in a thread
//                startWorkInAThread(p, tmp);

//            }
//        } else {
//            ui->listWidgetCurrent_2->clear();

//            ui->listWidgetCurrent_2->addItem(fileMap[item->text()].getTitle());

//            // Create worker thread
//            workerThread = new WorkerThread(this);

//            // Connect signals and slots
//            connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
//            connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//            connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

//            // Start work in a thread
//            startWorkInAThread(p, tmp);
//        }
//    }
//}


//void MainWindow::on_pushButtonStop_2_pressed()
//{
//    ui->listWidgetCurrent_2->clear();
//    workerThread->stop();
//    workerThread = nullptr;
//}


void MainWindow::on_pushButtonstart_pressed()
{
        QMessageBox::StandardButton reply;
        QListWidgetItem* item = ui->listWidgetsong->currentItem();

        if (item == nullptr) {
            // do nothing because no song is selected
        } else {

            std::string stdStringMpg123 = "mpg123 \"" + fileMap[item->text()].getPath().toStdString() + "\"";
            QProcess* p = new QProcess;
            QString tmp = QString::fromStdString(stdStringMpg123);



            if (workerThread != nullptr) {
                if (workerThread->isRunning()) {
                    workerThread->stop();
                    ui->listWidgetcurr->clear();

                    ui->listWidgetcurr->addItem(fileMap[item->text()].getTitle());

                    // Create worker thread
                    workerThread = new WorkerThread(this);

                    // Connect signals and slots
                    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
                    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
                    connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

                    // Start work in a thread
                    startWorkInAThread(p, tmp);

                } else {
                    ui->listWidgetcurr->clear();

                    ui->listWidgetcurr->addItem(fileMap[item->text()].getTitle());


                    // Create worker thread
                    workerThread = new WorkerThread(this);

                    // Connect signals and slots
                    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
                    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
                    connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

                    // Start work in a thread
                    startWorkInAThread(p, tmp);

                }
            } else {
                ui->listWidgetcurr->clear();

                ui->listWidgetcurr->addItem(fileMap[item->text()].getTitle());

                // Create worker thread
                workerThread = new WorkerThread(this);

                // Connect signals and slots
                connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
                connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
                connect(workerThread, &WorkerThread::stop, workerThread, &WorkerThread::terminateProcess);

                // Start work in a thread
                startWorkInAThread(p, tmp);
            }
        }
}


void MainWindow::on_pushButtonstop_pressed()
{
            ui->listWidgetcurr->clear();
            workerThread->stop();
            workerThread = nullptr;
}

