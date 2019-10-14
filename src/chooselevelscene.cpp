#include "chooselevelscene.h"
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QSound>
#include <QTimer>
#include "mainscene.h"
#include "mypushbutton.h"
#include "playscene.h"
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent) {
  // 配置选择关卡场景
  this->setFixedSize(320, 588);
  // 设置图标
  this->setWindowIcon(QPixmap(":/coin0001.png"));
  // 设置标题
  this->setWindowTitle("选择关卡场景");
  // 创建菜单栏
  QMenuBar *bar = menuBar();
  setMenuBar(bar);
  // 创建开始菜单
  QMenu *startMenu = bar->addMenu("开始");
  // 创建退出的菜单项
  QAction *quitAction = startMenu->addAction("退出");
  // 点击退出 实现退出游戏
  connect(quitAction, &QAction::triggered, [=]() { this->close(); });
  // 选择关卡按钮音效
  QSound *chooseSound = new QSound(":/go-go-go.wav", this);
  // 返回音效
  QSound *backSound = new QSound(":/all-right.wav");
  // 返回按钮
  MyPushButton *backBtn =
      new MyPushButton(":/backbutton_press.png", ":/backbutton_release.png");
  backBtn->setParent(this);
  backBtn->move(this->width() - backBtn->width(),
                this->height() - backBtn->height());
  // 点击返回
  connect(backBtn, &QPushButton::clicked, [=]() {
    // 播放返回音效
    backSound->play();
    // 告诉主场景 我返回了 主场景监听ChooseLevelScene的返回按钮
    QTimer::singleShot(500, this, [=]() { emit this->chooseSceneBack(); });
  });
  // 创建选择关卡的按钮
  for (int i = 0; i < 20; ++i) {
    MyPushButton *menuBtn = new MyPushButton(":/levelbord.png");
    menuBtn->setParent(this);
    menuBtn->move(33 + (i % 4) * 70, 130 + (i / 4) * 75);
    // 监听每个按钮的点击事件
    connect(menuBtn, &MyPushButton::clicked, [=]() {
      // 选择关卡的音效
      chooseSound->play();
      // 进入到游戏场景
      this->hide();  // 将玄关场景隐藏掉
      play = new PlayScene(i + 1);
      // 设置游戏场景初始位置
      play->setGeometry(this->geometry());
      play->show();  //显示游戏场景
      connect(play, &PlayScene::chooseSceneBack, [=]() {
        this->setGeometry(play->geometry());
        this->show();
        delete play;
        play = NULL;
      });
    });
    QLabel *label = new QLabel;
    label->setParent(this);
    label->setFixedSize(menuBtn->width(), menuBtn->height());
    label->setText(QString::number(i + 1));
    label->move(33 + (i % 4) * 70, 130 + (i / 4) * 75);
    // 设置label 上的文字对齐方式 水平居中和垂直居中
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // 设置让鼠标进行穿透 51号属性
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
  }
}
void ChooseLevelScene::paintEvent(QPaintEvent *) {
  // 加载背景
  QPainter painter(this);
  QPixmap  pix;
  pix.load(":/background1.png");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
  // 加载标题
  pix.load(":/title.png");
  pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
  painter.drawPixmap(5, 30, pix);
}