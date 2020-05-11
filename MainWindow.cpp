#include "MainWindow.h"
#include <QCoreApplication>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QKeyEvent>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_isOkay(false),
      m_firstKey(Qt::Key_0),
      m_lastKey(Qt::Key_Z)
{
    m_sounds.resize(m_lastKey - m_firstKey + 1);

    m_mainWidget = new QWidget();
    m_mainLayout = new QVBoxLayout();
    setCentralWidget(m_mainWidget);
    m_mainWidget->setLayout(m_mainLayout);
    QString wrongFormat(tr("The format of the mapping file is:\n"
                           "key1:file_path1\nkey2:file_path2\n...\n"
                           "with keyX being 1-0a-z"));

    // Read the mapping file
    QFileInfo filepath(
                QFileDialog::getOpenFileName(this, tr("Open mapping file")));
    QDir dir(filepath.dir());
    QFile file(filepath.filePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(
                    this, tr("File not found"), tr("File could not be opened"));
        return;
    }
    while (!file.atEnd()) {
        // Open the file
        QString line = file.readLine();
        QStringList lineSplit = line.split(
                    QRegExp("[:]"), QString::SkipEmptyParts);
        if (lineSplit.size() != 2 || lineSplit[0].size() != 1){
            QMessageBox::critical(
                        this, tr("Wrong format for the mapping file"),
                        wrongFormat);
            return;
        }

        // Check the key asked (1-0a-z)
        QKeySequence idx(lineSplit[0].toLower());
        if (idx < m_firstKey || idx > m_lastKey){
            QMessageBox::critical(
                        this, tr("Wrong format for the mapping file"),
                        wrongFormat);
            return;
        }

        // Read the sound file
        lineSplit[1] = lineSplit[1].trimmed();
        QFileInfo filePath(dir, lineSplit[1]);
        if (!filePath.exists()){
            QMessageBox::critical(
                        this, tr("File not found"),
                        tr("The file\n\"") + lineSplit[0] + tr(":")
                    + lineSplit[1] + tr("\"\ncannot be found"));
            return;
        }
        QMediaPlayer * player = new QMediaPlayer();
        player->setMedia(QUrl::fromLocalFile(filePath.absoluteFilePath()));
        m_sounds[idx[0] - m_firstKey] = player;

        // Make the button associated to that sound
        QPushButton * button = new QPushButton(
                    lineSplit[0].toLower() + tr(" : ") + filePath.baseName());
        button->connect(button,  &QPushButton::clicked, [this, idx]() {
            QKeyEvent event(
                        QEvent::KeyPress,
                        idx[0],
                        Qt::KeyboardModifier::NoModifier);
            keyPressEvent(&event);
        });
        m_mainLayout->addWidget(button);

    }
    m_isOkay = true;
}

bool MainWindow::isOkay() const
{
    return m_isOkay;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int idx(event->key() - m_firstKey);
    if (idx >= 0 && idx <= m_lastKey - m_firstKey){
        if (m_sounds[idx]){
            m_sounds[idx]->play();
        }
    }
}
