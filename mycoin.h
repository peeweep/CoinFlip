#ifndef MYCOIN_H
#define MYCOIN_H
#include <QPushButton>
#include <QString>
#include <QTimer>
class MyCoin : public QPushButton {
  Q_OBJECT
 public:
  //    explicit MyCoin(QWidget *parent = nullptr);
  // 参数代表传入的金币路径还是银币路径
  MyCoin(QString btnImg);
  // 金币的属性
  int  posX, posY;  // 坐标
  bool flag;        // 正反标示
  // 改变标志的方法
  void    changeFlag();
  QTimer* timer1;  // 正面翻反面
  QTimer* timer2;  // 反面翻正面
  int     min = 1;
  int     max = 8;
  // 执行动画的标志
  bool isAnimation = false;
  // 重写 按下和释放
  void mousePressEvent(QMouseEvent* e);
  // 是否胜利的标志
  bool isWin = false;
 signals:
 public slots:
};
#endif  // MYCOIN_H
