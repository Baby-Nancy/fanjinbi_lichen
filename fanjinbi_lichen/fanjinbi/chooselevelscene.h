#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include <playscene.h>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene * play=NULL;

signals:
    //自定义信号只需要声明，不需要实现
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
