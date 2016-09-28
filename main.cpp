#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //    a.connect(&a,&QApplication::quit,&w,&MainWindow::checkModifySlot);
    // FIXME 关闭前主程序会弹出窗口 但主窗口还是会关闭。。。。
    // 而且会有两次退出提示
    //    a.connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(checkModifySlot()));

    // 添加启动画面
    QPixmap pixmap(":/images/images/loading gif.gif");
    QSplashScreen splash(pixmap);
    // 显示信息 支持部分html标签 可以居中
    splash.showMessage("<h1>please wait....<h1>",Qt::AlignHCenter);
    splash.show();

    for(int i =0;i<500000000;i++)
    {
        // show SplashScreen
    }

    // 打开时播放音频
    //    QMediaPlayer *player = new QMediaPlayer();
    //    player->setMedia(QUrl("http://media.shanbay.com/audio/us/hello.mp3"));
    //    player->play();

    //    // 测试播放中文
    //    QAxObject *speech= new QAxObject();
    //    speech->setControl("SAPI.SpVoice");
    //    speech->dynamicCall("Speak(QString,uint)",QStringLiteral("大家好"),1);

    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
