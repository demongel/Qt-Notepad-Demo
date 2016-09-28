#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->movie=new QMovie(":/anim/anim/kuma.gif");
    qDebug()<<"this gif has "<<this->movie->frameCount()<<" frame";
    ui->gifLabel->setMovie(movie);
    this->movie->start();
}

about::~about()
{
    delete ui;
}

void about::on_startGif_clicked()
{
  this->movie->start();
}

void about::on_stopGif_clicked()
{
      this->movie->stop();
}
