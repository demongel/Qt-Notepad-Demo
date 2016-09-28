#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

#include <QUrl>
#include <QDesktopServices>// 桌面服务
#include "about.h"

#include <QMovie>
#include <QtMultimedia/QMediaPlayer>
#include <ActiveQt/QAxObject>
#include <QSplashScreen>
// 关闭事件都是受保护的。
#include <QCloseEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected :
    void closeEvent(QCloseEvent *event);

private slots:
    void newFileSlot();
    void openFileSlot();
    bool saveAsFileSlot();// 另存为
    bool saveFileSlot();// 直接保存
    void printSlot();

    void setFontSlot();
    void setColorSlot();
    void setCurrentDateTimeSlot();
    void aboutWebSlot();
    void aboutSoftwareSlot();

public slots:
    void checkModifySlot();// 关闭前检查


//    void on_MainWindow_destroyed();

private:
    Ui::MainWindow *ui;
    QString saveFilePath;
};

#endif // MAINWINDOW_H
