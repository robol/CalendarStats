#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();

    void on_countButton_clicked();

private:
    Ui::MainWindow *ui;

    void populateDefaultValues();
};

#endif // MAINWINDOW_H
