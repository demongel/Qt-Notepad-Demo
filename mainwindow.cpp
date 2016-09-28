#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("无标题-记事本"));
    // 引用资源文件无效时  qmake一下
    this->setWindowIcon(QIcon(":/ccat/cat/21.png"));
    // 设置默认字体，微软雅黑，12号
    ui->textEdit->setFont(QFont("Microsoft YaHei",12));


    // -------------------------文件菜单------------------------------
    // 关联新建Action
    connect(ui->newAction,&QAction::triggered,this,&MainWindow::newFileSlot);
    // 关联打开Action
    connect(ui->openAction,&QAction::triggered,this,&MainWindow::openFileSlot);
    // 关联另存为操作
    connect(ui->saveasAction,&QAction::triggered,this,&MainWindow::saveAsFileSlot);
    // 关联保存操作
    connect(ui->saveAction,&QAction::triggered,this,&MainWindow::saveFileSlot);
    // 打印相关
    connect(ui->printAction,&QAction::triggered,this,&MainWindow::printSlot);
    // 退出相关  退出前判断文本是否被改变
    connect(ui->exitAction,&QAction::triggered,this,&MainWindow::checkModifySlot);

    // -------------------------编辑菜单------------------------------
    // textEdit已经实现了对应的槽函数
    connect(ui->undoAction,&QAction::triggered,ui->textEdit,&QTextEdit::undo);
    connect(ui->redoAction,&QAction::triggered,ui->textEdit,&QTextEdit::redo);
    connect(ui->copyAction,&QAction::triggered,ui->textEdit,&QTextEdit::copy);
    connect(ui->pasteAction,&QAction::triggered,ui->textEdit,&QTextEdit::paste);
    connect(ui->cutAction,&QAction::triggered,ui->textEdit,&QTextEdit::cut);
    connect(ui->selectAllAction,&QAction::triggered,ui->textEdit,&QTextEdit::selectAll);

    //-------------------------格式菜单------------------------------
    connect(ui->fontAction,&QAction::triggered,this,&MainWindow::setFontSlot);
    connect(ui->colorAction,&QAction::triggered,this,&MainWindow::setColorSlot);
    connect(ui->datetimeAction,&QAction::triggered,this,&MainWindow::setCurrentDateTimeSlot);

    //-------------------------帮助------------------------------
    connect(ui->aboutQtAction,&QAction::triggered,qApp,&QApplication::aboutQt);
    connect(ui->aboutWebAction,&QAction::triggered,this,&MainWindow::aboutWebSlot);
    connect(ui->aboutSoftAction,&QAction::triggered,this,&MainWindow::aboutSoftwareSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 如果当前文本被改变
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<QStringLiteral("被改变");
        QMessageBox::StandardButton button=QMessageBox::information(this,QStringLiteral("记事本"),QStringLiteral("是否保存"),QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);

        if(button==QMessageBox::Save)
        {
            bool result=saveFileSlot();
            if(result)// 保存成功则关闭 不成功不关闭
            {
                event->accept();
            }else
            {
                event->ignore();
            }
        }else if(button==QMessageBox::No)
        {
           event->accept();
        }else if(button==QMessageBox::Cancel)
        {
            event->ignore();// 忽略事件
        }
    }else
    {
        event->accept();
    }
}
// 新建
void MainWindow::newFileSlot()
{
    // 如果当前文本被改变
    if(ui->textEdit->document()->isModified())
    {
        //        qDebug()<<ui->textEdit->toPlainText();
        qDebug()<<QStringLiteral("被改变");
        QMessageBox::StandardButton button=QMessageBox::information(this,QStringLiteral("记事本"),QStringLiteral("是否保存"),QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);
        qDebug()<<button;

        if(button==QMessageBox::Save)
        {
            saveFileSlot();
        }else if(button==QMessageBox::No)
        {
            ui->textEdit->clear();
            this->setWindowTitle(QStringLiteral("无标题-记事本"));
            saveFilePath="";// 新建时默认路径置空
        }else if(button==QMessageBox::Cancel)
        {
            return;
        }
    }else
    {
        ui->textEdit->clear();
        this->setWindowTitle(QStringLiteral("无标题-记事本"));
        saveFilePath="";// 新建时默认路径置空
    }
}

// 打开文件
void MainWindow::openFileSlot()
{
    QString filepath=QFileDialog::getOpenFileName(this,"Open",QDir::currentPath());
    qDebug()<<filepath;

    if(filepath.isEmpty())
    {
        QMessageBox::information(this,"Info","please select a file");
        return;
    }
    // 打开时将路径设置为默认保存路径
    saveFilePath=filepath;

    // 读取文件
    QFile *file=new QFile(filepath);
    bool ok=file->open(QIODevice::ReadOnly);

    if(ok)
    {
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());// 读取所有的内容

        file->close();
        delete file;// 析构
    }else
    {
        QMessageBox::information(this,"Info","File open fail"+file->errorString());
        return;
    }
}

// 保存文件  另存为操作
bool MainWindow::saveAsFileSlot()
{
    // 类型过滤使用 ;; 分开
    QString filepath=QFileDialog::getSaveFileName(this,"save",QDir::currentPath(),"Text files(*.txt);;All files(*.*)");
    if(filepath.isEmpty())
    {
        QMessageBox::information(this,"Info","please select a file");
        return false;
    }
    // 默认保存路径设置为保存路径
    saveFilePath=filepath;

    QFileInfo info=QFileInfo(filepath);

    QFile *file=new QFile(filepath);
    bool ok=file->open(QIODevice::WriteOnly);

    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        //        qDebug()<<file->fileName();
        qDebug()<<info.baseName();// 不带后缀
        qDebug()<<info.fileName();// 带后缀
        this->setWindowTitle(info.fileName());
        // 保存后 设置未修改
        ui->textEdit->document()->setModified(false);
        file->close();
        delete file;
        return true;
    }else
    {
        QMessageBox::information(this,"Info","File save fail"+file->errorString());
        return false;
    }
}

//  直接保存
bool MainWindow::saveFileSlot()
{
    if(saveFilePath.isEmpty())
    {
        return saveAsFileSlot();
    }else
    {
        QFileInfo info=QFileInfo(saveFilePath);

        QFile *file=new QFile(saveFilePath);
        bool ok=file->open(QIODevice::WriteOnly);

        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();
            //        qDebug()<<file->fileName();
            qDebug()<<info.baseName();// 不带后缀
            qDebug()<<info.fileName();// 带后缀
            this->setWindowTitle(info.fileName());
            // 保存后 设置未修改   此时点击新建不会提示保存
            ui->textEdit->document()->setModified(false);
            file->close();
            delete file;
            return true;
        }else
        {
            QMessageBox::information(this,"Info","File save fail"+file->errorString());
            return false;
        }
    }
}

// 打印
void MainWindow::printSlot()
{
    // 打印机对象
    QPrinter prt;
    // 打印对话框
    QPrintDialog dlg(&prt,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        //  Convenience function to print the text edit's document to the given printer.
        ui->textEdit->print(&prt);
    }
}

// 设置字体
void MainWindow::setFontSlot()
{
    /*
     *
      bool ok;
      QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
      if (ok) {
          // font is set to the font the user selected
      } else {
          // the user canceled the dialog; font is set to the initial
          // value, in this case Times, 12.
      }
     */
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if (ok) {
        ui->textEdit->setFont(font);
    } else {
        //        QMessageBox::information(this,"Info","font set fail");
        //        return;
    }

}

// 设置颜色
void MainWindow::setColorSlot()
{
    /*QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

          if (color.isValid()) {
              colorLabel->setText(color.name());
              colorLabel->setPalette(QPalette(color));
              colorLabel->setAutoFillBackground(true);
          }*/
    // 默认颜色是初始被选择的颜色
    QColor color=QColorDialog::getColor(Qt::black,this,"Select Color");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }else
    {
        //        QMessageBox::information(this,"Info","color set fail");
        //        return;
    }
}

//添加当前时间
void MainWindow::setCurrentDateTimeSlot()
{
    QDateTime currentDateTime=QDateTime::currentDateTime();
    QString dateTime=currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
    ui->textEdit->append(dateTime);
}

// 桌面服务跳转
void MainWindow::aboutWebSlot()
{
    // 会使用默认浏览器打开
    QDesktopServices::openUrl(QUrl("www.baidu.com"));
}

// 版权信息
void MainWindow::aboutSoftwareSlot()
{
    about *a=new about;
    a->setWindowTitle("about ccnote");
//    a->exec();// modal dialog
    a->show();// unmodal dialog 可以操纵后面的窗口
}

// 用于退出时的检查  对mainwindow有效  对程序关闭无效 需改善
// FIXME 直接调用closeEvent？
void MainWindow::checkModifySlot()
{
    // 如果当前文本被改变
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<QStringLiteral("被改变");
        QMessageBox::StandardButton button=QMessageBox::information(this,QStringLiteral("记事本"),QStringLiteral("是否保存"),QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);
        qDebug()<<button;

        if(button==QMessageBox::Save)
        {
            saveFileSlot();
        }else if(button==QMessageBox::No)
        {
            qApp->quit();//退出程序
//            this->close();// 会进入 closeEvent中判断
        }else if(button==QMessageBox::Cancel)
        {
            return;
        }
    }else
    {
        this->close();// 因为未修改  所以进入closeEvent也是退出
    }
}





