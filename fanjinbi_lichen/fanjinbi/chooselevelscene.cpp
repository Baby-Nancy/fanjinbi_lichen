#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <playscene.h>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(328,580);
    //设置窗口的图标
    this->setWindowIcon(QIcon("://image/coin1.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);

    //创建菜单
    QMenu *Menu=bar->addMenu("功能");

//    //创建开始菜单项
//    QAction *startAction=Menu->addAction("开始");
    //创建退出菜单项
    QAction *quitAction=Menu->addAction("退出");

    //点击退出，实现退出游戏
    connect(quitAction,&QAction::triggered,this,[=]()
    {
        this->close();
    });

    //设置一个返回按钮
    MyPushButton *btnBack=new MyPushButton("://image/back1 (1).png","://image/back1 (2).png");
    btnBack->setParent(this);
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //点击返回按钮
    connect(btnBack,&MyPushButton::clicked,this,[=]()
    {
        qDebug()<<"点击了返回按钮";
        //返回主窗口
        //点击返回按钮，发送一个信号，这个信号会被mainscene捕捉
        QTimer::singleShot(600,this,[=]()
        {
            emit chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        //加载按钮的图片
        MyPushButton *menuBtn=new MyPushButton("://image/level.png");
        menuBtn->setParent(this);
        menuBtn->move(35+i%4*70,150+i/4*70);

        //点击按钮，发送信号
        connect(menuBtn,&MyPushButton::clicked,this,[=]()
        {
            QString str=QString("您选择了第 %1 关").arg(i+1);
            qDebug()<<str;

            //隐藏选择关卡的界面
            this->hide();
            //跳转到游戏场景
            play=new PlayScene(i+1);
            //
            //play->setGeometry(this->geometry());
            //显示游戏场景
            play->show();

            //点击游戏场景中的返回按钮，发送信号到选择关卡的窗口
            connect(play,&PlayScene::chooseSceneBack,[=](){
                //this->setGeometry(play->geometry());
                //显示游戏关卡选择界面
                this->show();
                //delete掉游戏场景
                delete play;
                play = NULL;
            });
        });

        //加载关卡数字
        QLabel *label=new QLabel;
        label->setParent(this);
        //label的大小和图片的大小一致
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        //设置label中的数字
        label->setText(QString::number(i+1));
        //label的位置和图片位置的中间位置一致
        label->move(35+i%4*70,150+i/4*70);
        //设置label的对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //设置让鼠标穿透label，使得menubtn可以接收点击信号
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //绘制背景
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load("://image/3.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //绘制标题图片
    pixmap.load("://image/coinflip.png");
    pixmap=pixmap.scaled(pixmap.width()*0.1,pixmap.height()*0.1);
    painter.drawPixmap(110,90,pixmap);
}
