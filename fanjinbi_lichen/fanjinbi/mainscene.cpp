#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //主场景的设置
    //设置窗口大小
    setFixedSize(328,580);
    //设置窗口标题
    setWindowTitle("COINFLIP");
    //设置窗口图标
    setWindowIcon(QIcon(":/image/coin1.png"));


    //点击退出按钮
    connect(ui->actionback,&QAction::triggered,this,[=]()
    {
        this->close();
        //实现保存游戏数据的功能
    });

    //创建开始按钮
    MyPushButton *btnStart=new MyPushButton("://image/start.png");
    btnStart->setParent(this);
    btnStart->move(this->width()*0.5-btnStart->width()*0.5,this->height()*0.3);

    //点击开始按钮
    connect(btnStart,&MyPushButton::clicked,this,[=]()
    {
        qDebug()<<"开始游戏";

        //点击按钮之后，弹起特效
        btnStart->jumpdow();
        btnStart->jumpup();


    });
}

void MainScene::paintEvent(QPaintEvent *){
    //绘制背景图片
    //指定this，在当前窗口画画
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load("://image/1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //绘制标题图片
    pixmap.load("://image/coinflip.png");
    pixmap=pixmap.scaled(pixmap.width()*0.1,pixmap.height()*0.1);
    painter.drawPixmap(110,90,pixmap);
}

MainScene::~MainScene()
{
    delete ui;
}
