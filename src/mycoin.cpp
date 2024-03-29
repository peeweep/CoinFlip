#include "mycoin.h"
#include <QString>
#include <QTimer>
MyCoin::MyCoin(QString btnImg) {
  QPixmap pix;
  bool    ret = pix.load(btnImg);
  if (!ret) {
    return;
  }
  //  this->setFixedSize(pix.width(), pix.height());
  this->setFixedSize(51, 51);
  this->setStyleSheet("QPushButton{border}:0px;");
  this->setIcon(pix);
  //  this->setIconSize(QSize(pix.width(), pix.height()));
  this->setIconSize(QSize(51, 51));
  // 初始化定时器对象
  timer1 = new QTimer(this);
  timer2 = new QTimer(this);
  // 监听正面翻反面的信号，并且反转金币
  connect(timer1, &QTimer::timeout, [=]() {
    QPixmap pix;
    QString str = QString(":/coin000%1.png").arg(this->min++);
    pix.load(str);
    this->setFixedSize(51, 51);
    this->setStyleSheet("QPushButton{border}:0px;");
    this->setIcon(pix);
    this->setIconSize(QSize(51, 51));
    // 判断  如果翻完了，将min 重置为1
    if (this->min > this->max) {
      this->min   = 1;
      isAnimation = false;
      timer1->stop();
    }
  });
  // 反面翻正面
  connect(timer2, &QTimer::timeout, [=]() {
    QPixmap pix;
    QString str = QString(":/coin000%1.png").arg(this->max--);
    pix.load(str);
    this->setFixedSize(51, 51);
    this->setStyleSheet("QPushButton{border}:0px;");
    this->setIcon(pix);
    this->setIconSize(QSize(51, 51));
    // 判断  如果翻完了，将min 重置为1
    if (this->max < this->min) {
      this->max   = 8;
      isAnimation = false;
      timer2->stop();
    }
  });
}
void MyCoin::mousePressEvent(QMouseEvent* e) {
  if (this->isAnimation || this->isWin) {
    return;
  } else {
    QPushButton::mousePressEvent(e);
  }
}
// 改变正反面标志的方法
void MyCoin::changeFlag() {
  if (this->flag)  // 如果是正面，翻成反面
  {
    timer1->start(30);
    isAnimation = true;
    this->flag  = false;
  } else {
    timer2->start(30);
    isAnimation = true;
    this->flag  = true;
  }
}
