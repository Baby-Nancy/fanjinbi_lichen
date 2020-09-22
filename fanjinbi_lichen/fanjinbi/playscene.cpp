#include "playscene.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include "mycoin.h"
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "guize.h"
#include <QPaintEvent>
#include<QWidget>
#include <QPixmap>

PlayScene::PlayScene(int levelNum)
{
    //初始化游戏场景
    qDebug() << "进入了第 "<<levelNum<<"关";
    this->levelIndex = levelNum;

    //设置固定大小
    this->setFixedSize(328,580);

    //设置图标
    this->setWindowIcon(QPixmap(":/image/coin1.png"));

    //设置标题
    this->setWindowTitle("游戏场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * Menu = bar->addMenu("功能");

    //创建 菜单项
    QAction *  quitAction = Menu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //创建规则菜单项
    QAction *  quitAction2 = Menu->addAction("规则");

    connect(quitAction2,&QAction::triggered,[=](){
        x.show();
    });


    //翻金币音效
    QSound *flipSound = new QSound(":/image/ConFlipSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton("://image/back1 (1).png" , "://image/back1 (2).png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        QTimer::singleShot(500,this,[=]()
        {
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);

    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);

    //将字体设置到标签控件中
    label->setFont(font);
    label->setText( str1);
    label->setGeometry(QRect( 30, this->height() - 50,140, 50));

    //初始化游戏中的二维数据
    recoin();

    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            //绘制背景图片
            QLabel* bg = new QLabel(this);
            QPixmap pix;
            bool ret=pix.load(":/image/BoardNode.png");
            if(!ret)
            {
                qDebug()<<"加载金币背景图片失败";
            }
            bg->setGeometry(0,0,pix.width(),pix.height());
            bg->setPixmap(pix);
            bg->move(57 + i*50,200+j*50);

            //金币对象
            QString str;

            //区分金银币
            if(this->gameArray[i][j] == 1)
            {
                str = "://image/coin1.png";
            }
            else
            {
                str = "://image/coin8.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag = this->gameArray[i][j]; //记录正反标志
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=]()
            {
                //一旦点击一个币，就禁用所有金币按钮
                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                //翻被点击的硬币
                flipSound->play();
                coin->changeFlag();
                gameArray[i][j] = gameArray [i][j] == 0?1:0;

                //延时翻周围的硬币
                QTimer::singleShot(300, this,[=]()
                {
                    if(coin->posX+1 <=3)//右边金币
                    {coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)//左边金币
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)//上方金币
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)//下方金币
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    this->isWin = true;

                    //释放所有金币按钮
                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                        if(this->isWin==false)
                        {
                            for(int i=0;i<4;i++)
                            {
                                for(int j=0;j<4;j++)
                                {
                                    coinBtn[i][j]->isWin=false;
                                }
                            }
                            break;
                        }
                    }

                  //判断是否胜利
                    if(this->isWin==true)
                   {
                       qDebug()<<"游戏胜利";
                        for(int i=0;i<4;i++)
                       {
                           for(int j=0;j<4;j++)
                                coinBtn[i][j]->isWin=true;
                            }
                       }
                   }
                    checkWin();
                });

            });
        }
    }

}
