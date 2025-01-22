#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->cmd->currentText();
    QString msg;

    extern void test_fs_cmd_exec(QString &s, QString &msg);

    if (!text.isEmpty())
    {
        test_fs_cmd_exec(text, msg);

        ui->msg->appendPlainText(msg);
    }
}

