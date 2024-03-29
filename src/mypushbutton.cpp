#include "mypushbutton.h"
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg, QString pressImg) {
  this->nomalImgPath = normalImg;
  this->pressImgPath = pressImg;
  QPixmap pix;
  bool    ret = pix.load(normalImg);
  if (!ret) {
    return;
  }
  // 设置图片固定大小
  this->setFixedSize(pix.width(), pix.height());
  // 设置不规则图片样式
  this->setStyleSheet("QPushButton{border:0px}");
  // 设置图标
  this->setIcon(pix);
  // 设置图标大小
  this->setIconSize(QSize(pix.width(), pix.height()));
}
void MyPushButton::zoom1() {
  // 创建动画对象
  QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
  // 设置动画时间间隔
  animation->setDuration(200);
  // 起始位置
  animation->setStartValue(
      QRect(this->x(), this->y(), this->width(), this->height()));
  // 结束位置
  animation->setEndValue(
      QRect(this->x(), this->y() + 10, this->width(), this->height()));
  // 设置弹跳曲线
  animation->setEasingCurve(QEasingCurve::OutBounce);
  // 执行动画
  animation->start();
}  // 向下跳
void MyPushButton::zoom2() {
  // 创建动画对象
  QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
  // 设置动画时间间隔
  animation->setDuration(200);
  // 起始位置
  animation->setStartValue(
      QRect(this->x(), this->y() + 10, this->width(), this->height()));
  // 结束位置
  animation->setEndValue(
      QRect(this->x(), this->y(), this->width(), this->height()));
  // 设置弹跳曲线
  animation->setEasingCurve(QEasingCurve::OutBounce);
  // 执行动画
  animation->start();
}  // 向上跳
void MyPushButton::mousePressEvent(QMouseEvent* e) {
  if (this->pressImgPath !=
      "")  // 传入的按下图片不为空，说明需要有按下的状态 切换图片
  {
    QPixmap pix;
    bool    ret = pix.load(this->pressImgPath);
    if (!ret) {
      return;
    }
    // 设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    // 设置图标
    this->setIcon(pix);
    // 设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
  }
  // 让父类执行其他内容
  return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* e) {
  if (this->pressImgPath !=
      "")  // 传入的按下图片不为空，说明需要有按下的状态 切换初始图片
  {
    QPixmap pix;
    bool    ret = pix.load(this->nomalImgPath);
    if (!ret) {
      return;
    }
    // 设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    // 设置图标
    this->setIcon(pix);
    // 设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
  }
  // 让父类执行其他内容
  return QPushButton::mouseReleaseEvent(e);
}
