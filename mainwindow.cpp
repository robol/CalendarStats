#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icscalendar.h"
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Fill in the default values in the field
    populateDefaultValues();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::populateDefaultValues()
{
    ui->yearSpinBox->setValue(QDateTime::currentDateTime().date().year());
}

void MainWindow::on_browseButton_clicked()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Select the calendar"), getenv("HOME"), "Calendar (*.ics)");
    if (! selectedFile.isEmpty()) {
        ui->ICSpathLineEdit->setText(selectedFile);
    }
}

void MainWindow::on_countButton_clicked()
{
    if (ui->ICSpathLineEdit->text().isEmpty()) {
        QMessageBox::critical(this, tr("Select a valid calendar"), tr("Please select a valid calendar file."));
        return;
    }

    ICSCalendar calendar(ui->ICSpathLineEdit->text());

    if (! calendar.isValid()) {
        QMessageBox::critical(this, tr("Select a valid calendar"),
                              tr("The specified ICS file is not valid, and has not been parsed correctly."));
        return;
    }

    int year = ui->yearSpinBox->value();

    QString message = tr("Total number of events: %1\n\n").arg(calendar.countEvents(QDateTime(QDate(year, 1, 1)), QDateTime(QDate(year, 12, 31))));

    message += tr("January: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 1, 1)), QDateTime(QDate(year, 1, 31))));
    message += tr("February: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 2, 1)), QDateTime(QDate(year, 2, 29))));
    message += tr("March: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 3, 1)), QDateTime(QDate(year, 3, 31))));
    message += tr("April: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 4, 1)), QDateTime(QDate(year, 4, 30))));
    message += tr("May: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 5, 1)), QDateTime(QDate(year, 5, 31))));
    message += tr("June: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 6, 1)), QDateTime(QDate(year, 6, 30))));
    message += tr("July: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 7, 1)), QDateTime(QDate(year, 7, 31))));
    message += tr("August: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 8, 1)), QDateTime(QDate(year, 8, 31))));
    message += tr("September: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 9, 1)), QDateTime(QDate(year, 9, 30))));
    message += tr("October: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 10, 1)), QDateTime(QDate(year, 10, 31))));
    message += tr("November: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 11, 1)), QDateTime(QDate(year, 11, 30))));
    message += tr("December: %1 events\n").arg(calendar.countEvents(
        QDateTime(QDate(year, 12, 1)), QDateTime(QDate(year, 12, 31))));

    QMessageBox::information(this, tr("Calendar Statistics"), message);
}
