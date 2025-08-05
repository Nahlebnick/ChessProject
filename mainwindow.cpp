#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_board = new board;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    m_board->draw(&painter);
}

void MainWindow::mousePressEvent(QMouseEvent *pe)
{
    if (pe->pos().x() < 512 && pe->pos().y() < 512 )
    {
        m_board->checkMouse(pe);
        this->repaint();
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << m_board->m_x_selected << m_board->m_y_selected;
}

