#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>


namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    bool isOkay() const;
protected:
    void keyPressEvent(QKeyEvent *);
private:
   QWidget *m_mainWidget;
   QVBoxLayout *m_mainLayout;

   std::vector<QMediaPlayer*> m_sounds;

   bool m_isOkay;
   int m_firstKey;
   int m_lastKey;
};

#endif // MAINWINDOW_H

