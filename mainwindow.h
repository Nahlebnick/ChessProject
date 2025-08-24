#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void UpdateTimerSlot();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;

    board* m_board;
    QTimer *white_player_timer;
    QTimer *black_player_timer;
    QTimer *m_timer;
    QVBoxLayout *m_layout;

    QLabel *m_white_player_timer_label;
    QLabel *m_black_player_timer_label;

    bool player;
};
#endif // MAINWINDOW_H
