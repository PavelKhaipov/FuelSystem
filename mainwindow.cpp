#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setLayout(ui->verticalLayout);
    ui->vlView->addWidget(&view);

    // Сигналы изменения значений спинбоксов
    connect(ui->dsbV1, SIGNAL(valueChanged(double)), this, SLOT(valueChanged()));
    connect(ui->dsbV2, SIGNAL(valueChanged(double)), this, SLOT(valueChanged()));

    // Диапазон спинбоксов
    ui->dsbV1->setRange(0, MAX_VALUE);
    ui->dsbV2->setRange(0, MAX_VALUE);

    resize(600, 450);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::valueChanged()
{
    view.set(ui->dsbV1->value(), ui->dsbV2->value());
}


void MainWindow::on_pbRandom_clicked()
{
    // Заполнить случайными значениями
    ui->dsbV1->setValue((double)rand() / RAND_MAX * MAX_VALUE);
    ui->dsbV2->setValue((double)rand() / RAND_MAX * MAX_VALUE);
}
