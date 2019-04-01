#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDebug>

#define test


using namespace Qt;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictHeight = 370;
    pictWidth = 540;
    step = 0.1;
    leftX = -100; rightX = 100;
    leftY = -100; rightY = 100;
    drawGraph();

    list = new QPushButton("Выбрать функцию",this);
    menu = new QMenu(list);
    menu->addAction("y = k*x + b", this, SLOT(on_1stLine_clicked()));
    menu->addAction("y = x^a + b",this,SLOT(on_2ndLine_clicked()));
    menu->addAction("y = 1/x^a + b", this, SLOT(on_3rdLine_clicked()));
    menu->addAction("y = pow(pow(x,a), b)", this, SLOT(on_4thLine_clicked()));
    menu->addAction("y = a^x", this, SLOT(on_5thLine_clicked()));

    list->setMenu(menu);
    ui->verticalLayout->addWidget(list);

    clearData();
    recountPixels();
    getData();
    drawGraph(true);
}

void MainWindow::callDial()
{
    dial = new Dialog(this);
    dial->show();
    dial->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(double x)
{
    return log(x)*(-1);
}

double MainWindow::f1(double x)
{
    return sin(x)*(-1);
}

double MainWindow::f2(double x)
{
    return cos(x)*(-1);
}

double MainWindow::f3(double x)
{
    return sin(1.0/x)*(-1);
}

double MainWindow::f4(double x)
{
    x *= -1;
    return k*x + b;
}

double MainWindow::f5(double x)
{
    x *= -1;
    return pow(x, a_f5) + b_f5;
}

double MainWindow::f6(double x)
{
    x *= -1;
    return 1/pow(x, a_f6) + b_f6;
}

double MainWindow::f7(double x)
{
    x *= -1;
    return pow(pow(x,1/a_f7), b_f7) + k_f7 ;
}

double MainWindow::f8(double x)
{
    x *= -1;
    return pow(a_f8, x) + b_f8;
}

void MainWindow::clearData()
{
    leftX = 0;           leftX_af = 0;
    rightX = 0;         rightX_af = 0;
    leftY = 0;           leftY_af = 0;
    rightY = 0;         rightY_af = 0;
    step = 0;            b_f6 = 0;
    a_f8 = 0;            a_f6 = 0;
    b_f8 = 0;            b_f5 = 0;
    a_f7 = 0;            a_f5 = 0;
    b_f7 = 0;            k = 0;
    k_f7 = 0;            b = 0;
}

void MainWindow::recountPixels()
{
    onePixelX = 540.0/(rightX - leftX);
    onePixelY = 370.0/(rightY - leftY);
    Ox = fabs(leftX); Oy = rightY;

    onePixelX_af = 540/(rightX_af - leftX_af);
    onePixelY_af = 370/(rightY_af - leftY_af);
    Ox_af = fabs(leftX_af); Oy_af = rightY_af;
}

void MainWindow::on_clear_clicked()
{
    clearData();
    drawGraph();
}

void MainWindow::on_draw_clicked()
{
    getData();
    recountPixels();
    drawGraph(1);
}

void MainWindow::getData()
{
    leftX = ui->inputLeftX->text().toDouble();             leftX_af = ui->inputLeftX->text().toDouble();
    rightX = ui->inputRightX->text().toDouble();         rightX_af = ui->inputRightX->text().toDouble();
    leftY = ui->inputLeftY->text().toDouble();             leftY_af = ui->inputLeftY->text().toDouble();
    rightY = ui->inputRightY->text().toDouble();         rightY_af = ui->inputRightY->text().toDouble();
    step = 1.0/ui->inputAccuracy->text().toDouble();
}

void MainWindow::drawGraph(bool notEmpty)
{
    graph = new QPixmap(540,370);
    paint = new QPainter;
    paint->begin(graph);
    paint->eraseRect(0,0,540,370);
    paint->drawLine(Ox*onePixelX,0,Ox*onePixelX,pictHeight);                     // отрисовка осей Ox Oy
    paint->drawLine(0,Oy*onePixelY,pictWidth,Oy*onePixelY);

    paint->setPen(QPen(Qt::black,3));
    for(double i = leftX;i<=rightX;i+=10.0)
        paint->drawPoint((i+Ox)*onePixelX,Oy*onePixelY);                              // отрисовка точек на осях с интервалом 10
    for(double i = leftY;i<=rightY;i+=10.0)
        paint->drawPoint(Ox*onePixelX,(i+Oy)*onePixelY);

    if(!notEmpty)                                                                                            // если в параметрах "0", то отрисовка заканчиватся
    {
        paint->end();
        ui->outputGraph->setPixmap(*graph);
        return;

    }

    paint->setPen(QPen(Qt::green, 1, Qt::SolidLine));
    paint->setRenderHint(QPainter::Antialiasing, true);

    first = new bool[9];
    path = new QPainterPath;
    p = new QPainterPath[8];

    for(double i = (double)leftX + step;  i <= (double)rightX; i += step)
    {
        if (ui->main->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f(i)))
            {
                if(first[0])
                {
                    path->moveTo((i+Ox) * onePixelX, (f(i) + Oy) * onePixelY);
                    first[0] = false;
                }
                else
                    path->lineTo((i + Ox) * onePixelX, (f(i) + Oy) * onePixelY);
            }
        }


        if (ui->sin->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f1(i)))
            {
                if(first[1])
                {
                    p[0].moveTo((i + Ox) * onePixelX, (f1(i) + Oy) * onePixelY);
                    first[1] = false;
                }
                else
                    p[0].lineTo((i + Ox) * onePixelX,(f1(i) + Oy) * onePixelY);
            }
        }

        if (ui->cos->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f2(i)))
            {
                if(first[2])
                {
                    p[1].moveTo((i + Ox) * onePixelX,(f2(i) + Oy) * onePixelY);
                    first[2] = false;
                }
                else
                    p[1].lineTo((i + Ox) * onePixelX,(f2(i) + Oy) * onePixelY);
            }
        }

        if (ui->tg->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f3(i)))
            {
                if(first[3])
                {
                    p[2].moveTo((i + Ox) * onePixelX,(f3(i) + Oy) * onePixelY);
                    first[3] = false;
                }
                else
                    p[2].lineTo((i + Ox)*onePixelX,(f3(i) + Oy) * onePixelY);
            }
        }

        if (ui->checkBox->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f4(i)))
            {
                if(first[4])
                {
                    p[3].moveTo((i+Ox_af) * onePixelX_af, (f4(i) + Oy_af) * onePixelY_af);
                    first[4] = false;
                }
                else
                    p[3].lineTo((i+Ox_af)*onePixelX_af,(f4(i)+Oy_af)*onePixelY_af);
            }
        }

        if (ui->checkBox->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f5(i)))
            {
                if(first[5])
                {
                    p[4].moveTo((i+Ox_af) * onePixelX_af, (f5(i) + Oy_af) * onePixelY_af);
                    first[5] = false;
                }
                else
                    p[4].lineTo((i+Ox_af)*onePixelX_af,(f5(i)+Oy_af)*onePixelY_af);
            }
        }

        if (ui->checkBox->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f6(i)))
            {
                if(first[6])
                {
                    p[5].moveTo((i+Ox_af) * onePixelX_af, (f6(i) + Oy_af) * onePixelY_af);
                    first[6] = false;
                }
                else
                    p[5].lineTo((i+Ox_af)*onePixelX_af,(f6(i)+Oy_af)*onePixelY_af);
            }
        }

        if (ui->checkBox->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f7(i)))
            {
                if(first[7])
                {
                    p[6].moveTo((i+Ox_af) * onePixelX_af, (f7(i) + Oy_af) * onePixelY_af);
                    first[7] = false;
                }
                else
                    p[6].lineTo((i+Ox_af)*onePixelX_af,(f7(i)+Oy_af)*onePixelY_af);
            }
        }
        if (ui->checkBox->checkState() == Qt::CheckState::Checked)
        {
            if(!isnan(f8(i)))
            {
                if(first[8])
                {
                    p[7].moveTo((i+Ox_af) * onePixelX_af, (f8(i) + Oy_af) * onePixelY_af);
                    first[8] = false;
                }
                else
                    p[7].lineTo((i+Ox_af)*onePixelX_af,(f8(i)+Oy_af)*onePixelY_af);
            }
        }
    }

    if(ui->main->checkState() == Qt::CheckState::Checked) {
        paint->setPen(QPen(Qt::blue, 1, Qt::SolidLine));
        paint->drawPath(*path);
    }

    if(ui->sin->checkState() == Qt::CheckState::Checked) {
        paint->setPen(QPen(Qt::green, 1, Qt::SolidLine));
        paint->drawPath(p[0]);
    }

    if(ui->cos->checkState() == Qt::CheckState::Checked) {
        paint->setPen(QPen(Qt::red, 1, Qt::SolidLine));
        paint->drawPath(p[1]);
    }

    if(ui->tg->checkState() == Qt::CheckState::Checked) {
        paint->setPen(QPen(Qt::darkMagenta, 1, Qt::SolidLine));
        paint->drawPath(p[2]);
    }

    if((ui->checkBox->checkState() == Qt::CheckState::Checked) && (this->k != NULL || this->b != NULL))
    {
        paint->setPen(QPen(Qt::red,1,Qt::SolidLine));
        paint->drawPath(p[3]);
    }

    if((ui->checkBox->checkState() == Qt::CheckState::Checked) && (this->a_f5 != NULL || this->b_f5 != NULL))
    {
        paint->setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint->drawPath(p[4]);
    }

    if((ui->checkBox->checkState() == Qt::CheckState::Checked) && (this->a_f6 != NULL || this->b_f6 != NULL))
    {
        paint->setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint->drawPath(p[5]);
    }

    if((ui->checkBox->checkState() == Qt::CheckState::Checked) && (this->a_f7 != NULL || this->b_f7 != NULL || this->k_f7 != NULL))
    {
        paint->setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint->drawPath(p[6]);
    }

    if((ui->checkBox->checkState() == Qt::CheckState::Checked) && (this->a_f8 != NULL || this->b_f8 != NULL))
    {
        paint->setPen(QPen(Qt::green,1,Qt::SolidLine));
        paint->drawPath(p[7]);
    }

    paint->end();
    ui->outputGraph->setPixmap(*graph);

    return;
}

void MainWindow::on_save_clicked()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString name;
   if(date.day()<10)
        name += "0";
    name += QString::number(date.day())+".";
    if(date.month()<10)
        name += "0";
    name += QString::number(date.month())+".";
    name += QString::number(date.year())+"_";
    if(time.hour()<10)
        name += "0";
    name += QString::number(time.hour())+"-";
    if(time.minute()<10)
        name += "0";
    name += QString::number(time.minute())+"-";
    if(time.second()<10)
        name += "0";
    name += QString::number(time.second());
    QFile file(name+".png");
    qDebug() << name;
    file.open(QIODevice::WriteOnly);
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    if(ui->outputGraph->pixmap()->save(&file,"PNG")) {
        msgBox.setText("Saved to program folder with name: "+name+".png");
        msgBox.setWindowTitle("Saved!");
    }
    else {
        msgBox.setText("Error saving.");
        msgBox.setWindowTitle("Error!");
    }
    msgBox.exec();
}

// y = k*x + b func ///////////////////////////////////////////////////////////////////

void MainWindow::on_1stLine_clicked()
{
    set = new QDialog(this);
    set->setGeometry(600, 600, 250,100);

    QLabel *lbl = new QLabel("Значение K: ", set);
    lbl->setGeometry(10,5,60,17);
     for_k = new QLineEdit(set);
    for_k->setGeometry(10,25,60,17);

    QLabel *lblb = new QLabel("Значение b: ", set);
    lblb->setGeometry(10,40,60,17);
    for_b = new QLineEdit(set);
    for_b->setGeometry(10,60,60,17);

    ok = new QPushButton("Подтвердить", set);
    ok->setGeometry(120, 60, 120, 30);


    QPushButton* ok1 = new QPushButton("Set", set);
    ok1->setGeometry(80,24,25,19);
    QPushButton* ok2 = new QPushButton("Set", set);
    ok2->setGeometry(80,59,25,19);

    connect(ok1, SIGNAL(clicked()), this, SLOT(fork1()));
    connect(ok2, SIGNAL(clicked()), this, SLOT(fork2()));
    connect(ok, SIGNAL(clicked()), this, SLOT(forOK()));

    set->show();
    set->exec();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::fork1()
{
    forK = for_k->text();
    for_k->setDisabled(true);
}

void MainWindow::fork2()
{
    forB = for_b->text();
    for_b->setDisabled(true);
}

void MainWindow::forOK()
{
    this->k = forK.toDouble();
    this->b = forB.toDouble();
     set->close();
}

//////////////////////////////////////////////////////////////////////

// y = k^a + b func //////////////////////////////////////////////////////////////////

void MainWindow::on_2ndLine_clicked()
{
    set_f5 = new QDialog(this);
    set_f5->setGeometry(600, 600, 250,100);

    QLabel *lbl = new QLabel("Значение a: ", set_f5);
    lbl->setGeometry(10,5,60,17);
    for_a = new QLineEdit(set_f5);
    for_a->setGeometry(10,25,60,17);

    QLabel *lblb = new QLabel("Значение b: ", set_f5);
    lblb->setGeometry(10,40,60,17);
    for_b_f5 = new QLineEdit(set_f5);
    for_b_f5->setGeometry(10,60,60,17);


    ok = new QPushButton("Подтвердить", set_f5);
    ok->setGeometry(120, 60, 120, 30);


    QPushButton* ok1 = new QPushButton("Set", set_f5);
    ok1->setGeometry(80,24,25,19);

    QPushButton* ok2 = new QPushButton("Set", set_f5);
    ok2->setGeometry(80,59,25,19);


    connect(ok1, SIGNAL(clicked()), this, SLOT(forA_F5()));
    connect(ok2, SIGNAL(clicked()), this, SLOT(forB_F5()));
    connect(ok, SIGNAL(clicked()), this, SLOT(forOK_F5()));

    set_f5->show();
    set_f5->exec();
}

void MainWindow::forB_F5()
{
    forBf5 = for_b_f5->text();
    for_b_f5->setEnabled(false);
}

void MainWindow::forA_F5()
{
    forA = for_a->text();
    for_a->setEnabled(false);
}

void MainWindow::forOK_F5()
{
    this->a_f5 = forA.toDouble();
    this->b_f5 = forBf5.toDouble();
    set_f5->close();
}

//////////////////////////////////////////////////////////////////////


//  y = 1/x^a + b //////////////////////////////////////////////////////////////////////

void MainWindow::on_3rdLine_clicked()
{
    set_f6 = new QDialog(this);
    set_f6->setGeometry(600,600, 250,100);

    QLabel *lbl = new QLabel("Значение A: ", set_f6);
    lbl->setGeometry(10,5,60,17);
    for_a_f6 = new QLineEdit(set_f6);
    for_a_f6->setGeometry(10,25,60,17);

    QLabel *lblb = new QLabel("Значение B: ", set_f6);
    lblb->setGeometry(10,40,60,17);
    for_b_f6 = new QLineEdit(set_f6);
    for_b_f6->setGeometry(10,60,60,17);

    ok = new QPushButton("Подтвердить", set_f6);
    ok->setGeometry(120, 60, 120, 30);


    QPushButton* ok1 = new QPushButton("Set", set_f6);
    ok1->setGeometry(80,24,25,19);
    QPushButton* ok2 = new QPushButton("Set", set_f6);
    ok2->setGeometry(80,59,25,19);

    connect(ok1, SIGNAL(clicked()), this, SLOT(forA_F6()));
    connect(ok2, SIGNAL(clicked()), this, SLOT(forB_F6()));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept_F6()));

    set_f6->show();
    set_f6->exec();
}

void MainWindow::forA_F6()
{
    forA_f6 = for_a_f6->text();
    for_a_f6->setEnabled(false);
}

void MainWindow::forB_F6()
{
    forB_f6 = for_b_f6->text();
    for_b_f6->setEnabled(false);
}

void MainWindow::accept_F6()
{
    this->a_f6 = forA_f6.toDouble();
    this->b_f6 = forB_f6.toDouble();
    set_f6->close();
}

//////////////////////////////////////////////////////////////////////


// y = pow(pow(x,a), b) ///////////////////////////////////////////////////////////

void MainWindow::on_4thLine_clicked()
{
    for_f7 = new QDialog(this);
    for_f7->setGeometry(600,600, 250,150);

    QLabel *lbl = new QLabel("Значение A: ", for_f7);
    lbl->setGeometry(10,5,60,17);
    for_a_f7 = new QLineEdit(for_f7);
    for_a_f7->setGeometry(10,25,60,17);

    QLabel *lblb = new QLabel("Значение B: ", for_f7);
    lblb->setGeometry(10,40,60,17);
    for_b_f7 = new QLineEdit(for_f7);
    for_b_f7->setGeometry(10,60,60,17);

    QLabel *lblK = new QLabel("Значение К:", for_f7);
    lblK->setGeometry(10,75,60,17);
    for_k_f7 = new QLineEdit(for_f7);
    for_k_f7->setGeometry(10,95,60,17);


    ok = new QPushButton("Подтвердить", for_f7);
    ok->setGeometry(120, 100, 120, 30);


    QPushButton* ok1 = new QPushButton("Set", for_f7);
    ok1->setGeometry(80,24,25,19);
    QPushButton* ok2 = new QPushButton("Set", for_f7);
    ok2->setGeometry(80,59,25,19);
    QPushButton* ok3 = new QPushButton("Set", for_f7);
    ok3->setGeometry(80,94,25,19);

    connect(ok1, SIGNAL(clicked()), this, SLOT(forA_F7()));
    connect(ok2, SIGNAL(clicked()), this, SLOT(forB_F7()));
    connect(ok3, SIGNAL(clicked()), this, SLOT(forK_F7()));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept_F7()));

    for_f7->show();
    for_f7->exec();
}

void MainWindow::forK_F7()
{
    forK_f7 = for_k_f7->text();
    for_k_f7->setEnabled(false);
}

void MainWindow::forA_F7()
{
    forA_f7 = for_a_f7->text();
    for_a_f7->setEnabled(false);
}

void MainWindow::forB_F7()
{
    forB_f7 = for_b_f7->text();
    for_b_f7->setEnabled(false);
}

void MainWindow::accept_F7()
{
    a_f7 = forA_f7.toDouble();
    b_f7 = forB_f7.toDouble();
    k_f7 = forK_f7.toDouble();
    for_f7->close();
}

///////////////////////////////////////////////////////////////////////

// y = pow(a_f8, x) + b_f8 //////////////////////////////////////////////////////

void MainWindow::on_5thLine_clicked()
{
    for_f8 = new QDialog(this);
    for_f8->setGeometry(600, 600, 250,100);

    QLabel *lbl = new QLabel("Значение a: ", for_f8);
    lbl->setGeometry(10,5,60,17);
    for_a_f8 = new QLineEdit(for_f8);
    for_a_f8->setGeometry(10,25,60,17);

    QLabel *lblb = new QLabel("Значение b: ", for_f8);
    lblb->setGeometry(10,40,60,17);
    for_b_f8 = new QLineEdit(for_f8);
    for_b_f8->setGeometry(10,60,60,17);


    ok = new QPushButton("Подтвердить", for_f8);
    ok->setGeometry(120, 60, 120, 30);


    QPushButton* ok1 = new QPushButton("Set", for_f8);
    ok1->setGeometry(80,24,25,19);

    QPushButton* ok2 = new QPushButton("Set", for_f8);
    ok2->setGeometry(80,59,25,19);


    connect(ok1, SIGNAL(clicked()), this, SLOT(forA_F8()));
    connect(ok2, SIGNAL(clicked()), this, SLOT(forB_F8()));
    connect(ok, SIGNAL(clicked()), this, SLOT(accept_F8()));

    for_f8->show();
    for_f8->exec();
}

void MainWindow::forA_F8()
{
    forA_f8 = for_a_f8->text();
    for_a_f8->setEnabled(false);
}

void MainWindow::forB_F8()
{
    forB_f8 = for_b_f8->text();
    for_b_f8->setEnabled(false);
}

void MainWindow::accept_F8()
{
    a_f8 = forA_f8.toDouble();
    b_f8 = forB_f8.toDouble();
    for_f8->close();
}

// исследовать main
void MainWindow::on_main_1_clicked()
{
    callDial();
}

//  исследовать sin(x)
void MainWindow::on_main_2_clicked()
{
    foundingF1();
}

// исследовать cos(x)
void MainWindow::on_main_3_clicked()
{
    foundingF2();
}

// исследовать tg(x)
void MainWindow::on_main_4_clicked()
{
    foundingF3();
}

/*protected*/ void MainWindow::mousePressEvent(QMouseEvent *pe)
{
    if(path->contains(pe->pos()))
    {
#ifdef test
        count++;
        QString str;
        qDebug() << "tapped main" + str.number(count);
#endif // !test
        //foundingF();
    }

//    if (p[0].contains(pe->pos()))
//    {
//#ifdef test
//        qDebug() << "tapped sin";
//#endif // !test
//         foundingF1();
//    }

//    if (p[1].contains(pe->pos()))
//    {
//#ifdef test
//        qDebug() << "tapped cos";
//#endif // !test

//        foundingF2();
//    }

//        if (p[2].contains(pe->pos()))
//        {
//#ifdef test
//            qDebug() << "tapped sin(1/x)";
//#endif // !test

//            foundingF3();
//        }
}

void MainWindow::foundingF()
{
    QDialog *dial = new QDialog(this);
    dial->setGeometry(400,350,640,555);

    QPixmap *pix = new QPixmap("/img/лог.PNG");
    QBrush brush;
    brush.setTexture(*pix);

    QPalette pal;
    pal.setBrush(dial->backgroundRole(), brush);
    dial->setPalette(pal);
    dial->setAutoFillBackground(true);

    dial->show();
}

void MainWindow::foundingF1()
{
    QDialog *dial = new QDialog(this);
    dial->setGeometry(400,350,640,555);

    QPixmap *pix = new QPixmap(":/img/син.PNG");
    QBrush brush;
    brush.setTexture(*pix);

    QPalette pal;
    pal.setBrush(dial->backgroundRole(), brush);
    dial->setPalette(pal);
    dial->setAutoFillBackground(true);

    dial->show();
}

void MainWindow::foundingF2()
{
    QDialog *dial = new QDialog(this);
    dial->setGeometry(400,350,640,555);

    QPixmap *pix = new QPixmap("qrc:/img/лог.PNG");
    QBrush brush;
    QImage image("qrc:/img/лог.PNG");
    brush.setTextureImage(image);

    QPalette pal;
    pal.setBrush(dial->backgroundRole(), brush);
    dial->setPalette(pal);
    dial->setAutoFillBackground(true);

    QLabel lbl;
    lbl.setPixmap(*pix);

    QHBoxLayout lay(dial);
    lay.addWidget(&lbl);

    dial->setLayout(&lay);

    dial->show();
}

void MainWindow::foundingF3()
{
    QDialog *dial = new QDialog(this);
    dial->setGeometry(400,350,640,555);

    QPixmap *pix = new QPixmap(":/img/тг.PNG");
    QBrush brush;
    brush.setTexture(*pix);

    QPalette pal;
    pal.setBrush(dial->backgroundRole(), brush);
    dial->setPalette(pal);
    dial->setAutoFillBackground(true);

    dial->show();
}
