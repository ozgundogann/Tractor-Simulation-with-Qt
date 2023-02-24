#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QPixmap>
#include <Qpen>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //virtual void paintEvent(QPaintEvent *event);

private slots:

    void updateItem();

    void updateItemSecondTime();

    void updateItemThirdTime();

    void updateItemFourthTime();

    void updateItemFifthTime();

    void on_pushButton_plan_clicked();

    void on_pushButton_simulation_clicked();

    void on_actionInfo_hovered();

    void on_actionHelp_hovered();

    void on_actionCL_hovered();

    void on_actionReset_hovered();

    void on_actionBack_hovered();

    void on_actionForward_hovered();

    void on_lineEdit_width_textEdited(const QString &arg1);

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scence;
    QPropertyAnimation *animation;
    QPropertyAnimation *paintAnim;
    QTimer *timer;
    QLabel *label_pic;
    QLabel *label_paint;
    int labelPaintCounter;
    int w,h,e, currTour, period;


    //QImage *sourceImage;
};
#endif // MAINWINDOW_H
