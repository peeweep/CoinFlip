#include "playscene.h"
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSound>
#include <QTimer>
#include "leveldataconfig.h"
#include "mycoin.h"
#include "mypushbutton.h"
PlayScene::PlayScene(int levelNum) {
  QString str = QString("进入了第 %1 关").arg(levelNum);
  qDebug() << str;
  this->levelIndex = levelNum;
  // 初始化游戏场景
  // 设定固定大小
  this->setFixedSize(320, 588);
  // 设定图标
  this->setWindowIcon(QPixmap(":/resource/coin0001.png"));
  // 设定标题
  this->setWindowTitle("翻金币场景");
  // 创建菜单栏
  QMenuBar *bar = menuBar();
  setMenuBar(bar);
  // 创建开始菜单
  QMenu *startMenu = bar->addMenu("开始");
  // 创建退出的菜单项
  QAction *quitAction = startMenu->addAction("退出");
  // 点击退出 实现退出游戏
  connect(quitAction, &QAction::triggered, [=]() { this->close(); });
  // 返回音效
  QSound *backSound = new QSound(":/resource/all-right.wav");
  // 翻金币音效
  QSound *flipSound = new QSound(":/resource/aahhh.wav");
  // 胜利音效
  QSound *winSound = new QSound(":/resource/dinner-is-served.wav");
  // 返回按钮
  MyPushButton *backBtn = new MyPushButton(":/resource/backbutton_press.png",
                                           ":/resource/backbutton_release.png");
  backBtn->setParent(this);
  backBtn->move(this->width() - backBtn->width(),
                this->height() - backBtn->height());
  // 点击返回
  connect(backBtn, &QPushButton::clicked, [=]() {
    //    qDebug() << "翻金币场景点击了返回按钮";
    // 播放返回音效
    backSound->play();
    // 告诉主场景 我返回了 主场景监听ChooseLevelScene的返回按钮
    QTimer::singleShot(500, this, [=]() { emit this->chooseSceneBack(); });
  });
  // 显示当前关数
  QLabel *label = new QLabel;
  label->setParent(this);
  QFont font;
  font.setFamily("DejaVuSansMono Nerd Font");
  font.setPointSize(10);
  QString str1 = QString("Level: %1").arg(this->levelIndex);
  // 将字体设置到标签控件去
  label->setFont(font);
  label->setText(str1);
  label->setGeometry(0, this->height() - 50, 120, 50);
  dataConfig config;
  // 初始化每个关卡的二维数组
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
    }
  }
  // 胜利图片显示
  QLabel *successLabel = new QLabel;
  QPixmap pix_s;
  pix_s.load(":/resource/success.png");
  pix_s = pix_s.scaled(pix_s.width() * 0.6, pix_s.height() * 0.5);
  successLabel->setGeometry(QRect(0, 0, pix_s.width(), pix_s.height()));
  successLabel->setParent(this);
  successLabel->setPixmap(pix_s);
  successLabel->move((this->width() - pix_s.width()) * 0.5, -pix_s.height());
  // 显示金币背景图案
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      // 绘制背景图片
      QLabel *label = new QLabel;
      QPixmap pix   = QPixmap(":/resource/coinBord.png");
      label->setGeometry(0, 0, pix.width(), pix.height());
      label->setPixmap(pix);
      label->setParent(this);
      label->move(57 + i * 50, 200 + j * 50);
      // 创建金币
      //      if (this->gameArray[i][j] == 1) {
      //        // 显示金币
      //        str = ":/resource/coin0001.png";
      //      } else {
      //        // 显示银币
      //        str = ":/resource/coin0008.png";
      //      }
      str = this->gameArray[i][j] == 1 ? ":/resource/coin0001.png"
                                       : ":/resource/coin0008.png";
      MyCoin *coin = new MyCoin(str);
      coin->setParent(this);
      coin->move(59 + i * 50, 204 + j * 50);
      // 给金币属性赋值
      coin->posX = i;
      coin->posY = j;
      coin->flag = this->gameArray[i][j];  // 1 正 0 反
      // 将金币放入到金币的二维数组里 以便于后期的维护
      coinBtn[i][j] = coin;
      // 点击金币 进行翻转
      connect(coin, &MyCoin::clicked, [=]() {
        // 播放翻金币的音效
        flipSound->play();
        // 点击按钮 将所有按钮先禁用
        for (int i = 0; i < 4; ++i) {
          for (int j = 0; j < 4; ++j) {
            this->coinBtn[i][j]->isWin = true;
          }
        }
        coin->changeFlag();
        this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
        // 反转周围硬币 延时翻转
        QTimer::singleShot(300, this, [=]() {
          if (coin->posX + 1 <= 3)  // 右侧金币翻转
          {
            coinBtn[coin->posX + 1][coin->posY]->changeFlag();
            this->gameArray[coin->posX + 1][coin->posY] =
                this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
            //            if (this->gameArray[coin->posX + 1][coin->posY] == 0)
            //            {
            //              this->gameArray[coin->posX + 1][coin->posY] = 1;
            //            } else {
            //              this->gameArray[coin->posX + 1][coin->posY] = 0;
            //            }
          }
          if (coin->posY + 1 <= 3)  // 下侧金币翻转
          {
            coinBtn[coin->posX][coin->posY + 1]->changeFlag();
            this->gameArray[coin->posX][coin->posY + 1] =
                this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
          }
          if (coin->posX - 1 >= 0)  // 左侧金币翻转
          {
            coinBtn[coin->posX - 1][coin->posY]->changeFlag();
            this->gameArray[coin->posX - 1][coin->posY] =
                this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
          }
          if (coin->posY - 1 >= 0)  // 上侧金币翻转
          {
            coinBtn[coin->posX][coin->posY - 1]->changeFlag();
            this->gameArray[coin->posX][coin->posY - 1] =
                this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
          }
          // 接触按钮禁用
          for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
              this->coinBtn[i][j]->isWin = false;
            }
          }
          // 判断是否胜利
          this->isWin = true;
          for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
              if (coinBtn[i][j]->flag == false) {
                this->isWin = false;
                break;
              }
            }
          }
          if (this->isWin == true) {
            //            qDebug() << "胜利";
            // 添加胜利音效
            QTimer::singleShot(1000, this, [=]() { winSound->play(); });
            // 将所有按钮的胜利标志改为 true
            for (int i = 0; i < 4; ++i) {
              for (int j = 0; j < 4; ++j) {
                coinBtn[i][j]->isWin = true;
              }
            }
            // 将胜利的图片移动下来
            QPropertyAnimation *animation =
                new QPropertyAnimation(successLabel, "geometry");
            animation->setDuration(1000);
            // 设置开始位置
            animation->setStartValue(QRect(successLabel->x(), successLabel->y(),
                                           successLabel->width(),
                                           successLabel->height()));
            // 设置结束位置
            animation->setEndValue(
                QRect(successLabel->x(), successLabel->y() + 114,
                      successLabel->width(), successLabel->height()));
            // 设置缓和曲线
            animation->setEasingCurve(QEasingCurve::OutBounce);
            // 执行动画
            animation->start();
          }
        });
      });
    }
  }
}
void PlayScene::paintEvent(QPaintEvent *) {
  // 加载背景
  QPainter painter(this);
  QPixmap  pix;
  pix.load(":/resource/background1.png");
  painter.drawPixmap(0, 0, this->width(), this->height(), pix);
  // 加载标题
  pix.load(":/resource/title.png");
  pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
  painter.drawPixmap(5, 30, pix);
}
