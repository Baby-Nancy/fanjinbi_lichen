#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
#include <QWidget>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);

    //btnImg表示传入的是金币/银币的路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag;//正反标志

    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    //金币翻转后，相应地属性要发生变化
    void changeFlag();
    //金币正在执行翻转操作的标志
    bool isAnimation=false;
    bool isWin=false;

    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYCOIN_H
