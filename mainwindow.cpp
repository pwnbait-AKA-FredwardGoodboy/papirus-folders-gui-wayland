#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include "help.h"
#include <QInputDialog>
#include "papirus.h"
#include "polkit.h"
#include "filemanager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    x = new QProcess (this);

    connect(x, &QProcess::errorOccurred, this, &MainWindow::processError);
    connect(x, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::processFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processError(QProcess::ProcessError error)
{
    qDebug() << "Process error:" << error;
    qDebug() << "Process error string:" << x->errorString();
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Process finished with exit code:" << exitCode;
    qDebug() << "Process exit status:" << exitStatus;
    qDebug() << "Process stdout:" << x->readAllStandardOutput();
    qDebug() << "Process stderr:" << x->readAllStandardError();
}

void MainWindow::runPapirusFolders(const QString& color)
{
    QString program = "pkexec";
    QStringList arguments;
    arguments << "env"
              << QString("WAYLAND_DISPLAY=%1").arg(qgetenv("WAYLAND_DISPLAY"))
              << QString("XDG_RUNTIME_DIR=%1").arg(qgetenv("XDG_RUNTIME_DIR"))
              << "papirus-folders"
              << "-C"
              << color;
    x->start(program, arguments);
}

void MainWindow::on_black_clicked()
{
    runPapirusFolders("black");
}

void MainWindow::on_blue_clicked()
{
    runPapirusFolders("blue");
}

void MainWindow::on_bluegrey_clicked()
{
    runPapirusFolders("bluegrey");
}

void MainWindow::on_breeze_clicked()
{
    runPapirusFolders("breeze");
}

void MainWindow::on_brown_clicked()
{
    runPapirusFolders("brown");
}

void MainWindow::on_carmine_clicked()
{
    runPapirusFolders("carmine");
}

void MainWindow::on_cyan_clicked()
{
    runPapirusFolders("cyan");
}

void MainWindow::on_deeporange_clicked()
{
    runPapirusFolders("deeporange");
}

void MainWindow::on_green_clicked()
{
    runPapirusFolders("green");
}

void MainWindow::on_grey_clicked()
{
    runPapirusFolders("grey");
}

void MainWindow::on_indigo_clicked()
{
    runPapirusFolders("indigo");
}

void MainWindow::on_magenta_clicked()
{
    runPapirusFolders("magenta");
}

void MainWindow::on_nordic_clicked()
{
    runPapirusFolders("nordic");
}

void MainWindow::on_orange_clicked()
{
    runPapirusFolders("orange");
}

void MainWindow::on_palebrown_clicked()
{
    runPapirusFolders("palebrown");
}

void MainWindow::on_paleorange_clicked()
{
    runPapirusFolders("paleorange");
}

void MainWindow::on_pink_clicked()
{
    runPapirusFolders("pink");
}

void MainWindow::on_red_clicked()
{
    runPapirusFolders("red");
}

void MainWindow::on_teal_clicked()
{
    runPapirusFolders("teal");
}

void MainWindow::on_violet_clicked()
{
    runPapirusFolders("violet");
}

void MainWindow::on_white_clicked()
{
    runPapirusFolders("white");
}

void MainWindow::on_yaru_clicked()
{
    runPapirusFolders("yaru");
}

void MainWindow::on_yellow_clicked()
{
    runPapirusFolders("yellow");
}

void MainWindow::on_revert_clicked()
{
    QString program = "pkexec";
    QStringList arguments;
    arguments << "env"
              << QString("WAYLAND_DISPLAY=%1").arg(qgetenv("WAYLAND_DISPLAY"))
              << QString("XDG_RUNTIME_DIR=%1").arg(qgetenv("XDG_RUNTIME_DIR"))
              << "papirus-folders"
              << "-D";
    x->start(program, arguments);
}

void MainWindow::on_kill_clicked()
{
    x->start("killall caja dolphin nautilus nemo pcmanfm spacefm thunar Thunar");
}

void MainWindow::on_help_triggered()
{
    help help;
    help.setModal(true);
    help.exec();
}


void MainWindow::on_about_triggered()
{
    secDialog secdialog;
    secdialog.setModal(true);
    secdialog.exec();
}


void MainWindow::on_filemanager_triggered()
{
    filemanager filemanager;
    filemanager.setModal(true);
    filemanager.exec();
}


void MainWindow::on_polkit_triggered()
{
    polkit polkit;
    polkit.setModal(true);
    polkit.exec();
}


void MainWindow::on_papirus_triggered()
{
    papirus papirus;
    papirus.setModal(true);
    papirus.exec();
}

void MainWindow::on_dark_cyan_clicked()
{
    runPapirusFolders("darkcyan");
}