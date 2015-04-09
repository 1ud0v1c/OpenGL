#include "editorwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QLayoutItem>

EditorWindow::EditorWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget* centralWidget = new QWidget;
    _mainLayout = new QVBoxLayout;
    setCentralWidget(centralWidget);
    centralWidget->setLayout(_mainLayout);
    QHBoxLayout* headerPanel = new QHBoxLayout;
    QLabel *hallLabel =  new QLabel("Nombre de couloirs");
    _hall = new QSpinBox();
    _hall->setMinimum(3);
    _hall->setMaximum(MAXHALLLENGTH);
    QLabel *hallLengthLabel = new QLabel("Taille d'un couloir");
    _hallSpinBoxLength = new QSpinBox();
    _hallSpinBoxLength->setMinimum(15);
    _hallSpinBoxLength->setMaximum(MAXHALLLENGTH);

    headerPanel->addWidget(hallLabel);
    headerPanel->addWidget(_hall);
    headerPanel->addWidget(hallLengthLabel);
    headerPanel->addWidget(_hallSpinBoxLength);

    _gridPanel = new QGridLayout;
    grid();

    QHBoxLayout* footerPanel = new QHBoxLayout;
    _writeResult = new QPushButton("Ecrire");
    _quit = new QPushButton("Quitter");
    footerPanel->addWidget(_writeResult);
    footerPanel->addWidget(_quit);

    _mainLayout->addLayout(headerPanel);
    _mainLayout->addLayout(_gridPanel);
    _mainLayout->addLayout(footerPanel);

    connect(_hall, SIGNAL(valueChanged(int)), this,SLOT(handleHallValue(int)));
    connect(_hallSpinBoxLength, SIGNAL(valueChanged(int)), this,SLOT(handleHallLengthValue(int)));
    connect(_writeResult, SIGNAL(clicked()), this, SLOT(writeFile()));
    connect(_quit, SIGNAL(clicked()), this, SLOT(close()));
}

void EditorWindow::grid() {
    _nbHalls = _hall->value();
    _hallLength = _hallSpinBoxLength->value();

    for (int i = 0; i < _nbHalls; ++i) {
        for (int j = 0; j < _hallLength; ++j) {
            _spins[i][j] = new QSpinBox();
            _gridPanel->addWidget(_spins[i][j],i,j);
        }
    }
}

void EditorWindow::emptyGrid() {
    while( _gridPanel->count()) {
        QWidget* widget = _gridPanel->itemAt(0)->widget();
        if(widget) {
            _gridPanel->removeWidget(widget);
            delete widget;
        }
    }
}

void EditorWindow::handleHallValue(int val) {
    emptyGrid();
    _nbHalls = val;
    grid();
}

void EditorWindow::handleHallLengthValue(int val) {
    emptyGrid();
    _hallLength = val;
    grid();
}

void EditorWindow::writeFile() {
    saveFile();
}


void EditorWindow::saveFile() {
    QString filename = _filename;
    if (filename.isEmpty()) {
        saveAs();
    } else {
        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << _nbHalls << " " << _hallLength << "\n";
        for (int i = 0; i < _nbHalls; ++i) {
            for (int j = 0; j < _hallLength; ++j) {
                out << _spins[i][j]->value() << " ";
            }
            out << "\n";
        }
        file.close();
    }
}

void EditorWindow::saveAs() {
    _filename = QFileDialog::getSaveFileName(this, "Save File", QString(), "All Files (*)");

    if (!_filename.isEmpty()) {
        QFile file(_filename);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Erreur lors de l'ecriture du fichier";
        } else {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << _nbHalls << " " << _hallLength << "\n";
            for (int i = 0; i < _nbHalls; ++i) {
                for (int j = 0; j < _hallLength; ++j) {
                    out << _spins[i][j]->value() << " ";
                }
                out << "\n";
            }
            file.close();
        }
    } else {
        qDebug() << "Erreur lors de l'ecriture du fichier";
    }
}
