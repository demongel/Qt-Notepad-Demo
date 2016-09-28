#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //    a.connect(&a,&QApplication::quit,&w,&MainWindow::checkModifySlot);
    // FIXME 关闭前主程序会弹出窗口 但主窗口还是会关闭。。。。
    // 而且会有两次退出提示
//    a.connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(checkModifySlot()));

    return a.exec();
}
