#include "mainscene.h"
#include <QAction>
#include <QPainter>
#include <QSound>
#include <QTimer>
#include "ui_mainscene.h"
#include "mypushbutton.h"
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainScene) {
  ui->setupUi(this);
  // 配置主场景
  // 设置固定大小
  setFixedSize(320, 588);
  // 设置图标
  setWindowIcon(QIcon(":/coin0001.png"));
  setWindowTitle("翻金币主场景");
  // 退出按钮实现
  connect(ui->actionQuit, &QAction::triggered, [=]() { this->close(); });
  // 准备开始按钮音效
  QSound *startSound = new QSound(":/go-head.wav", this);
  // 开始按钮
  MyPushButton *startBtn = new MyPushButton(":/start_normal.jpg");
  startBtn->setParent(this);
  startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5,
                 this->height() * 0.7);
  // 实例化选择关卡场景
  chooseScene = new ChooseLevelScene;
  // 监听选择关卡的返回按钮的信号
  connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=]() {
    chooseScene->hide();
    this->show();
    this->setGeometry(chooseScene->geometry());
  });
  connect(startBtn, &QPushButton::clicked, [=]() {
    // 播放开始音效资源
    startSound->play();
    // 弹起特效
    startBtn->zoom1();
    startBtn->zoom2();
    // 延时 进入到选择关卡的场景中
    QTimer::singleShot(500, this, [=]() {
      // 设置chooseScene 场景的位置
      chooseScene->setGeometry(this->geometry());
      // 自身隐藏
      this->hide();
      // 显示选择关卡场景
      chooseScene->show();
    });
  });
}
MainScene::~MainScene() { delete ui; }
void MainScene::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  QPixmap  pix;
  pix.load(":/playscene.jpg");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
  // 画背景上图标
  pix.load(":/title.png");
  pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
  painter.drawPixmap(5, 30, pix);
}
