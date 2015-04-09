#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

#define MAXHALLLENGTH 50

class EditorWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit EditorWindow(QWidget *parent = 0);
        void grid();
        void saveFile();
        void saveAs();
        void emptyGrid();

    private:
        int _nbHalls, _hallLength;
        QVBoxLayout *_mainLayout;
        QGridLayout *_gridPanel;
        QString _filename;

        QSpinBox* _spins[MAXHALLLENGTH][MAXHALLLENGTH];
        QSpinBox *_hall;
        QSpinBox *_hallSpinBoxLength;
        QPushButton *_writeResult;
        QPushButton *_quit;

    public slots:
        void handleHallValue(int val);
        void handleHallLengthValue(int val);
        void writeFile();

};

#endif // EDITORWINDOW_H
