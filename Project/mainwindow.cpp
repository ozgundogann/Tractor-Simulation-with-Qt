#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currTour(0)
    , labelPaintCounter(0)
{
    ui->setupUi(this);

    ui->toolBar_Left->setStyleSheet("QToolBar{background: rgb(240,238,173)}");
    ui->toolBar_Right->setStyleSheet("QToolBar{background: rgb(240,238,173)}");
    ui->statusbar->setStyleSheet("background: rgb(51,75,91); color:white");

    QLabel* label_GPS = new QLabel(this);
    QMovie* movieGPS = new QMovie(":/signalIcons/img/Signal Icons/Signals.gif");
    label_GPS->setMovie(movieGPS);
    ui->toolBar_Left->addWidget(label_GPS);
    movieGPS->start();

    QLabel* label_USB = new QLabel(this);
    QMovie* movieUSB = new QMovie(":/signalIcons/img/Signal Icons/USB signals.gif");
    label_USB->setMovie((movieUSB));
    ui->toolBar_Left->addWidget(label_USB);
    movieUSB->start();

    ui->pushButton_simulation->hide();
    ui->pushButton_clear->hide();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_plan_clicked()
{
    w = ui->lineEdit_width->text().toInt();
    h = ui->lineEdit_Height->text().toInt();
    e = ui->lineEdit_Equipment->text().toInt();
    period = w/e/2;


    QPainter painter(this);

    scence=new QGraphicsScene;
    ui->graphicsView->setScene(scence);

    QBrush brush = Qt::Dense2Pattern;
    QColor color = Qt::black;
    brush.setColor("#23B24B");

    QRect rect;
    rect.setRect(20,20,w,h);
    scence->addRect(rect, color, brush);

    QPainterPath path;

    for(int i = 20 + e/2 ; i <= w + 20; i += e){
        path.moveTo(i, 20);
        path.lineTo(i,20+h);
    }
    for(int i = 20 + e/2 ; i < w + 20 - e ; i += 2 * e){
        path.moveTo(i, 20);
        path.cubicTo(i,20,i+(e/2),20-2*e,i+e,20);

    }

    for(int i = 20 + 3*e/2 ; i < 20 + w - e; i += 2 * e){
       path.moveTo(i, 20 + h);
       path.cubicTo(i,20 + h,i+(e/2),20+h+2*e,i+e,20 + h);
    }

    scence->addPath(path);

    label_pic = new QLabel;
    label_pic->setStyleSheet("background-color : transparent");
    QPixmap pixMap (":/image/img/tractor.png");
    label_pic->setPixmap(pixMap.scaled(e,e,Qt::KeepAspectRatio));
    scence->addWidget(label_pic);
    label_pic->setGeometry(20,20+h-e,e,e);

    currTour = 0;
    ui->pushButton_simulation->show();
}


void MainWindow::updateItem(){
    if (label_pic->geometry().center().x() + e >= 20 + w)
        return;

    QPixmap pixMap(":/image/img/tractor90.png");
    label_pic->setPixmap(pixMap.scaled(e,e,Qt::KeepAspectRatio));
    delete animation;
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(2500);
    animation->setStartValue(QRect(currTour * 2 * e + 20 + e/2,20 - e,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20 + e, 20-3*e/2 ,e,e));
    animation->start();
    QTimer::singleShot(2500,this,SLOT(updateItemSecondTime()));

}

void MainWindow::updateItemSecondTime(){

    QPixmap pixMap(":/image/img/tractor180.png");
    label_pic->setPixmap(pixMap.scaled(e,e,Qt::KeepAspectRatio));
    delete animation;
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(2500);
    //animation->setStartValue(QRect(20 + e, 20-3*e/2 ,e,e));
    animation->setStartValue(QRect(currTour * 2 * e + 20 + e/2, 20 - e ,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20 + e ,20,e,e));
    animation->start();
    QTimer::singleShot(2500,this,SLOT(updateItemThirdTime()));

}

void MainWindow::updateItemThirdTime()
{
    label_paint = new QLabel;
    label_paint->setStyleSheet("background-color: #F3E144");
    scence->addWidget(label_paint);

    paintAnim = new QPropertyAnimation(label_paint,"geometry");
    paintAnim->setDuration(5000);
    paintAnim->setStartValue(QRect(currTour * 2 * e + 20 + e,20,e,0));
    paintAnim->setEndValue(QRect(currTour * 2 * e + 20 + e,20,e,h));
    paintAnim->start();

    delete animation;
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(5000);
    animation->setStartValue(QRect(currTour * 2 * e + 20 + e,20,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20 + e,20 + h,e,e));
    animation->start();



    QTimer::singleShot(5000,this,SLOT(updateItemFourthTime()));

}

void MainWindow::updateItemFourthTime()
{
    if (label_pic->geometry().center().x() + e >= 20 + w)
        return;
    QPixmap pixMap(":/image/img/tractor90.png");
    label_pic->setPixmap(pixMap.scaled(e,e,Qt::KeepAspectRatio));
    delete animation;
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(2500);
    animation->setStartValue(QRect(currTour * 2 * e + 20 + 3 * e / 2,20 + h,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20 + 2 * e,20 + e / 2 + h,e,e));
    animation->start();
    QTimer::singleShot(2500,this,SLOT(updateItemFifthTime()));
}

void MainWindow::updateItemFifthTime()
{
    QPixmap pixMap(":/image/img/tractor.png");
    label_pic->setPixmap(pixMap.scaled(e,e,Qt::KeepAspectRatio));
    delete animation;
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(2500);

    animation->setStartValue(QRect(currTour * 2 * e + 20 + 3 * e / 2,20 + h,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20 + 2 * e, 20 + h - e,e,e));
    animation->start();
    currTour++;
    QTimer::singleShot(2500,this,SLOT(on_pushButton_simulation_clicked()));

}


void MainWindow::on_pushButton_simulation_clicked()
{
    animation = new QPropertyAnimation(label_pic, "geometry");
    animation->setDuration(5000);
    animation->setStartValue(QRect(currTour * 2 * e + 20,20+h-e,e,e));
    animation->setEndValue(QRect(currTour * 2 * e + 20,20-e,e,e));
    animation->start();


    label_paint = new QLabel;
    label_paint->setStyleSheet("background-color: #F3E144");
    scence->addWidget(label_paint);

    paintAnim = new QPropertyAnimation(label_paint,"geometry");
    paintAnim->setDuration(5000);
    paintAnim->setStartValue(QRect(currTour * 2 * e + 20,20+h,e,0));
    paintAnim->setEndValue(QRect(currTour * 2 * e + 20,20,e,h));
    paintAnim->start();

    QTimer::singleShot(5000,this,SLOT(updateItem()));

    ui->pushButton_plan->hide();
    ui->pushButton_simulation->hide();
    ui->pushButton_clear->show();

}

void MainWindow::on_actionInfo_hovered()
{
    ui->statusbar->showMessage("Info");
}


void MainWindow::on_actionHelp_hovered()
{
    ui->statusbar->showMessage("Help");
}


void MainWindow::on_actionCL_hovered()
{
    ui->statusbar->showMessage("Coverage Logging");
}


void MainWindow::on_actionReset_hovered()
{
    ui->statusbar->showMessage("Reset");
}


void MainWindow::on_actionBack_hovered()
{
    ui->statusbar->showMessage("Back");
}


void MainWindow::on_actionForward_hovered()
{
    ui->statusbar->showMessage("Forward");
}

void MainWindow::on_lineEdit_width_textEdited(const QString &arg1)
{
    ui->pushButton_simulation->hide();
}


void MainWindow::on_pushButton_clear_clicked()
{
    delete animation;
    delete paintAnim;
    delete label_pic;
    delete label_paint;
    delete scence;
    ui->lineEdit_Equipment->setText(QString(""));
    ui->lineEdit_Height->setText(QString(""));
    ui->lineEdit_width->setText(QString(""));
    ui->pushButton_plan->show();
    ui->pushButton_simulation->show();
    ui->pushButton_clear->hide();
}

