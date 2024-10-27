#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QTimer>
#include <QtMultimedia/QtMultimedia>
#include <QLCDNumber>
#include "queue.h"

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
    void on_enQueue_clicked();
    void autoDequeue();
    void updateTimer();
    void on_action10s_triggered();
    void on_action30s_triggered();
    void on_action60s_triggered();
    void on_searchTextChanged(const QString &text); // Add this line

private:
    Ui::MainWindow *ui;
    Queue ticketQueue;
    QTimer *dequeuetimer;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QTimer *displayTimer;
    int timeRemaining;
    int currentInterval;
    int ticketCounter;

    void updateQueueListWidget();
    void updateFilteredQueueListWidget(const QString &filter); // Add this line
};

#endif // MAINWINDOW_H
