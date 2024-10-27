#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ticketQueue(100)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , timeRemaining(60)
    , currentInterval(60)
    , ticketCounter(1)
{
    ui->setupUi(this);

    setWindowTitle("Olivia Rodrigo Concert Ticketing System");
    setWindowIcon(QIcon(":/new/img/icon.jpg"));

    QPalette palette = ui->lcdNumberTimer->palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    ui->lcdNumberTimer->setPalette(palette);

    dequeuetimer = new QTimer(this);
    connect(dequeuetimer, &QTimer::timeout, this, &MainWindow::autoDequeue);
    dequeuetimer->start(currentInterval * 1000); // 1 minute interval

    displayTimer = new QTimer(this);
    connect(displayTimer, &QTimer::timeout, this, &MainWindow::updateTimer);
    displayTimer->start(1000); // Update every second

    ui->lcdNumberTimer->display(timeRemaining);

    player->setAudioOutput(audioOutput);

    player->setSource(QUrl("qrc:/new/music/good4u.mp3"));

    audioOutput->setVolume(1);
    player->setLoops(QMediaPlayer::Infinite);
    player->play();

    connect(ui->lineEditName, &QLineEdit::returnPressed, this, &MainWindow::on_enQueue_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete audioOutput;
    delete dequeuetimer;
    delete displayTimer;
}

void MainWindow::updateQueueListWidget()
{
    ui->listWidgetQueue->clear();
    for (int i = 0; i < ticketQueue.size(); ++i) {
        Person p = ticketQueue.peek();
        QString itemText = QString("%1. - Ticket #%2 - %3").arg(i + 1).arg(p.getTicketNumber(), 3, 10, QChar('0')).arg(p.getName());
        ui->listWidgetQueue->addItem(itemText);
        ticketQueue.enqueue(ticketQueue.dequeue()); // Rotate the queue to maintain order
    }
}

void MainWindow::on_enQueue_clicked()
{
    QString name = ui->lineEditName->text();
    if (name.isEmpty()) {
        ui->nameWarning->setText("Please enter a name!");
        return;
    } else {
        ui->nameWarning->setText("Enter name:");
    }

    ui->lineEditName->clear();

    int ticket_number = ticketCounter++;
    Person person(name, ticket_number);
    ticketQueue.enqueue(person);
    ui->labelTicketAdded->setText(QString("%1 added (#%2)").arg(person.getName()).arg(person.getTicketNumber(), 3, 10, QChar('0')));

    updateQueueListWidget();
}

void MainWindow::autoDequeue()
{
    if (!ticketQueue.isEmpty()) {
        Person dequeuedPerson = ticketQueue.dequeue();
        ui->statusbar->showMessage("Dequeued: " + dequeuedPerson.getName() + QString("(Ticket #%1").arg(dequeuedPerson.getTicketNumber(), 3, 10, QChar('0')) + ")");
        ui->labelTicketReceived->setText(QString("%1 received a ticket (Ticket #%2)").arg(dequeuedPerson.getName()).arg(dequeuedPerson.getTicketNumber(), 3, 10, QChar('0')));
        ui->labelTicketReceived->setStyleSheet("background-color: #592693;"
                                               "padding: 5px; color: white;"
                                               "font-weight: bold;"
                                               "border: 2px solid black;"
                                               "border-radius: 10px;");

        updateQueueListWidget();

        if (!ticketQueue.isEmpty()) {
            Person nextPerson = ticketQueue.peek();
            ui->labelNextInLine->setText(QString("Next in line: %1 (#%2)").arg(nextPerson.getName()).arg(nextPerson.getTicketNumber(), 3, 10, QChar('0')));
        } else {
            ui->labelNextInLine->setText("No one in line.");
        }
        ui->labelNextInLine->setStyleSheet("background-color: #592693;"
                                           "padding: 5px; color: white;"
                                           "font-weight: bold;"
                                           "border: 2px solid black;"
                                           "border-radius: 10px;");
        // Reset the timer
        timeRemaining = currentInterval;
        ui->lcdNumberTimer->display(timeRemaining);
    } else {
        ui->labelTicketReceived->setText("The queue is empty.");
        ui->labelTicketReceived->setStyleSheet("background-color: #592693;"
                                               "padding: 5px; color: white;"
                                               "font-weight: bold;"
                                               "border: 2px solid black;"
                                               "border-radius: 10px;");
    }
}

void MainWindow::updateTimer()
{
    if (timeRemaining > 0) {
        timeRemaining--;
    } else {
        timeRemaining = currentInterval;
    }
    ui->lcdNumberTimer->display(timeRemaining);
}

void MainWindow::on_action10s_triggered()
{
    dequeuetimer->stop();
    currentInterval = 10;
    dequeuetimer->start(currentInterval * 1000);
    timeRemaining = currentInterval;
    ui->lcdNumberTimer->display(timeRemaining);
    ui->statusbar->showMessage("Timer set to 10 seconds.");
}

void MainWindow::on_action30s_triggered()
{
    dequeuetimer->stop();
    currentInterval = 30;
    dequeuetimer->start(currentInterval * 1000);
    timeRemaining = currentInterval;
    ui->lcdNumberTimer->display(timeRemaining);
    ui->statusbar->showMessage("Timer set to 30 seconds.");
}

void MainWindow::on_action60s_triggered()
{
    dequeuetimer->stop();
    currentInterval = 60;
    dequeuetimer->start(currentInterval * 1000);
    timeRemaining = currentInterval;
    ui->lcdNumberTimer->display(timeRemaining);
    ui->statusbar->showMessage("Timer set to 60 seconds.");
}
