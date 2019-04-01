#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <QObject>

class Dialog;

namespace Ui {
class MainWindow;
}


//class FilterMouse : public QObject
//{
//protected:
//    virtual  bool eventFilter(QObject *pobj, QEvent *pe);

//public:
//    FilterMouse(QObject* pobj = nullptr);
//};

//FilterMouse::FilterMouse(QObject* pobj /*= 0*/)
//{
//    pobj = new QObject;
//}

//bool FilterMouse::eventFilter(QObject *pobj, QEvent *pe)
//{
//    if (pe->type() == QEvent::MouseButtonPress)
//    {
//        if (static_cast<QMouseEvent*>(pe)->button() == Qt::LeftButton)
//        {
//            QString str = pobj->metaObject()->className();
//            QMessageBox::information(0, "Class Name is: ", str);
//            return true;
//        }
//    }
//    return false;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
protected:
    virtual void mousePressEvent(QMouseEvent*);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawGraph(bool notEmpty = 0);
    void recountPixels();
    void getData();
    void clearData();
    double f(double x); // y = log(x)
    double f1(double x); // y = sin(x)
    double f2(double x); // y = cos(x)
    double f3(double x); // y = sin(1/x)
    double f4(double x); // y = k*x + b
    double f5(double x); // y = x^a + b <---- указать b and cтепень (а)
    double f6(double x); // y = 1/x^2
    double f7(double x); // y = pow(pow(x,a), b)
    double f8(double x); // y = 1/x



private:

    void foundingF();    // исследование функций
    void foundingF1();
    void foundingF2();
    void foundingF3();

private slots:

    void on_5thLine_clicked();

    void on_3rdLine_clicked();

    void on_2ndLine_clicked();

    void on_clear_clicked();

    void on_draw_clicked();

    void on_save_clicked();

    void on_1stLine_clicked();

    void on_pushButton_clicked();

    void fork1();

    void fork2();

    void forOK();

    //////////////////////////////////////////////////////////////////

    void forB_F5();

    void forA_F5();

    void forOK_F5();

    //////////////////////////////////////////////////////////////////

    void forA_F6();

    void forB_F6();

    void accept_F6();

    //////////////////////////////////////////////////////////////////

    void on_4thLine_clicked();

    void forA_F7();

    void forB_F7();

    void forK_F7();

    void accept_F7();

    //////////////////////////////////////////////////////////////////

    void forA_F8();

    void forB_F8();

    void accept_F8();

    //////////////////////////////////////////////////////////////////

    void on_main_1_clicked();

    void on_main_2_clicked();

    void on_main_3_clicked();

    void on_main_4_clicked();

    void callDial();

private:
    QWidget *foundF;
    bool* first;
    QPainterPath *path;
    QPainterPath *p;

    Ui::MainWindow *ui;
    QPushButton *list;                                 // Кнопка для хранения списка
    QMenu *menu;                                      // Здесь хранятся варианты для всплывающего списка с выбором ф-ций
    QPushButton *ok;                                 // Кнопка Ок

    QVBoxLayout *checkBoxCustom;
    QCheckBox *cb;
    QLabel *custom;

    // global sets
    double leftX,rightX;
    double leftY,rightY;
    int pictWidth,pictHeight;
    double step;
    double onePixelX, onePixelY;
    double Ox,Oy;
    /////////////////////////////////////////////////



//    QPainterPath path,p[4];                       // Переменная path Хранит в себе данные о координатах каждой точки каждой функции
                                                                  // Для удобства все последующие переменные хранятся в массиве
                                                                  // По сути - множество этих точек и есть тот самый путь отрисовки какой-либо ф-ции

//    bool first[5] = {1,1,1,1,1};                   // Необходимая Булева переменная для работы логики построения точек



    int count = 0;
// drawing added Funcs
    /////////////////////////////////////////////////
        double leftX_af, rightX_af;
        double leftY_af, rightY_af;

        double onePixelX_af, onePixelY_af;
        double Ox_af, Oy_af;

        //drawing 1st
        QPixmap *graph;
        QPainter *paint;
/////////////////////////////////////////////////


// for f4(double)
    /////////////////////////////////////////////////
    double k = NULL;
    double b = NULL;

    QString forK; // y = k*x + b
    QString forB; // y = k*x + b
    /////////////////////////////////////////////////

//setters Box f5()
    /////////////////////////////////////////////////

    // setter Box f4()
    QLineEdit* for_k;
    QLineEdit* for_b;
    QDialog *set;

// setter Box f5()
    /////////////////////////////////////////////////
    QLineEdit* for_b_f5;
    QLineEdit* for_a;
    QDialog* set_f5;
    /////////////////////////////////////////////////
    double a_f5 = NULL;
    double b_f5 = NULL;
    /////////////////////////////////////////////////
    QString forA;
    QString forBf5;
/////////////////////////////////////////////////



 // setter Box f6()
        /////////////////////////////////////////////////
        QLineEdit* for_a_f6;
        QLineEdit* for_b_f6;
        QDialog* set_f6;
        /////////////////////////////////////////////////
        double a_f6 = NULL;
        double b_f6 = NULL;
        /////////////////////////////////////////////////
        QString forA_f6;
        QString forB_f6;
/////////////////////////////////////////////////



// setter Box f7() y = pow(pow( x, 1/3?), 2?)
        /////////////////////////////////////////////////
        QLineEdit* for_a_f7;
        QLineEdit* for_k_f7;
        QLineEdit* for_b_f7;
        QDialog *for_f7;
        /////////////////////////////////////////////////
        double a_f7 = 0;
        double b_f7 = 0;
        double k_f7 = 0;
        /////////////////////////////////////////////////
        QString forA_f7;
        QString forB_f7;
        QString forK_f7;
/////////////////////////////////////////////////

// setter Box f8() y = 1?/x + b
        /////////////////////////////////////////////////
        QLineEdit* for_a_f8;
        QLineEdit* for_b_f8;
        QDialog* for_f8;
        /////////////////////////////////////////////////
        double a_f8 = 0;
        double b_f8 = 0;
        /////////////////////////////////////////////////
        QString forA_f8;
        QString forB_f8;
/////////////////////////////////////////////////

        friend Dialog;

        Dialog *dial = new Dialog(this);

};

#endif // MAINWINDOW_H
