#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file...");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "...", "file not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "...", "file not open");
        on_actionSave_as_triggered();
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "...", "file not open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_mNotepad_triggered()
{
    QMessageBox::about(this, "About mNotepad", "This is a mini Notepad powered by Qt.");
}

void MainWindow::on_actionQuit_triggered()
{
    // on_actionSave_triggered();
    close();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if (ok)
        ui->textEdit->setFont(font);
    else
        return;
}

void MainWindow::on_actionText_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Set Text Color");
    if (color.isValid())
        ui->textEdit->setTextColor(color);
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("printer name");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}
