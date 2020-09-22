#ifndef GUIZE_H
#define GUIZE_H

#include <QWidget>
class guize : public QWidget
{
    Q_OBJECT
public:

    explicit guize(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);//用于绘图

signals:

public slots:

private:


};

#endif // GUIZE_H
