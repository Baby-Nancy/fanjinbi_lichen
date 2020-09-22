#ifndef MYPUSHBUTTON_H     //代码主要用于对于点击按钮的动态实现
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QDebug>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr);

    //默认鼠标点击时为空，构造函数点击鼠标时动态显示图片
    //构造函数正常显示图片路径
    //按下鼠标显示的图片路径
    MyPushButton(QString zc,QString anxia="");

    //成员属性
    //用户传入的默认显示路径
    QString zcl;
    //按下后显示的图片路径
    QString anxial;

    //设置弹跳效果
    //向上弹跳
    void jumpup();
    //向下弹跳
    void jumpdow();

  /*  //鼠标按下和释放事件，主要用于返回按钮的使用
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
**/
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
