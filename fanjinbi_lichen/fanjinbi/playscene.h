#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mycoin.h>
#include <guize.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;
    bool isWin=true;
    int gameArray[4][4];//维护每关的金币银币数据
    MyCoin *coinBtn[4][4];//维护创建的币对象
    PlayScene *play=NULL;

    void paintEvent(QPaintEvent *);
    //重置金币正反面
    void recoin();
    void checkWin();
    guize x;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
