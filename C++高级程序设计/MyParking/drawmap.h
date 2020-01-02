#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <QWidget>
#include<QPainter>
#include"dataBase.h"
namespace Ui {
class drawMap;
}

class drawMap : public QWidget
{
    Q_OBJECT

public:
    explicit drawMap(QWidget *parent = nullptr);
    ~drawMap()override;
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onDrawClick();
private:
    int row,col;
    QPainter painter;
    Ui::drawMap *ui;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
};

#endif // DRAWMAP_H
