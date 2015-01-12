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


private slots:
    void onPushButton_2_clicked();
    void onPushButton_3_clicked();
    void onPushButton_4_clicked();
    void onDial_valueChanged();

private:
    Ui::MyWidget *ui;



};

#endif // MYWIDGET_H
