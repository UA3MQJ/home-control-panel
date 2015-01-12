#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    QVector<double> x,y,x_red,y_red; //Инициализируем четыре вектора

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_dial_valueChanged();

private:
    Ui::MyWidget *ui;



};

#endif // MYWIDGET_H
