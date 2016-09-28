#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMovie>
#include <QDebug>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private slots:
    void on_startGif_clicked();

    void on_stopGif_clicked();

private:
    Ui::about *ui;
    QMovie *movie;
};

#endif // ABOUT_H
