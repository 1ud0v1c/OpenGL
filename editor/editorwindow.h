#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include "imagewidget.h"

#define MAXHALLLENGTH 50

class EditorWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit EditorWindow(QWidget *parent = 0);
        void grid();
        void saveFile();
        void saveAs();
        void emptyGrid();
        void emptyGrid(QGridLayout *grid);
        void gridPreviews();

    private:
        int _nbHalls, _hallLength;
        QVBoxLayout *_mainLayout;
        QGridLayout *_gridPanel, *_previewPanel;
        QString _filename;

        ImageWidget* _images[MAXHALLLENGTH][MAXHALLLENGTH];
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
