#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_board = new board;
    player = true;
    m_layout = new QVBoxLayout(centralWidget);

    QHBoxLayout *m_board_layout = new QHBoxLayout;
    m_board_layout->addWidget(m_board);

    QFont font("Times", 28, QFont::Bold);
    QHBoxLayout *m_white_player_info_layout = new QHBoxLayout;
    m_white_player_timer_label = new QLabel;
    m_white_player_timer_label->setFont(font);
    m_white_player_info_layout->addWidget(m_white_player_timer_label);

    QHBoxLayout *m_black_player_info_layout = new QHBoxLayout;
    m_black_player_timer_label = new QLabel;
    m_black_player_timer_label->setFont(font);
    m_black_player_info_layout->addWidget(m_black_player_timer_label);

    m_layout->addLayout(m_black_player_info_layout);
    m_layout->addLayout(m_board_layout);
    m_layout->addLayout(m_white_player_info_layout);
    m_layout->addWidget(ui->pushButton);



    setFixedSize(600, 600);
    white_player_timer = new QTimer;
    white_player_timer->start(600000);
    m_white_player_timer_label->setText(QString::number(white_player_timer->remainingTime()/60));

    black_player_timer = new QTimer;
    black_player_timer->start(600000);
    m_black_player_timer_label->setText(QString::number(black_player_timer->remainingTime()/60));

    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &MainWindow::UpdateTimerSlot);
    m_timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::UpdateTimerSlot()
{
    if (player)
    {
        m_white_player_timer_label->setText(QString::number(white_player_timer->remainingTime()/60));
    }
    else
    {
        m_black_player_timer_label->setText(QString::number(black_player_timer->remainingTime()/60));
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{


}

