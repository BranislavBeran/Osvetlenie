#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include <math.h>
#include "QtClass.h"
#include <QMessageBox>
#include <vector>

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);
public slots:
	void on_actionSave_triggered();

private:
	
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie;
	public slots:
	void vykresli();
	void vymaz();
	void on_alfa_sliderMoved(int i);
	void on_beta_sliderMoved(int i);
	void on_vzdialenost_sliderMoved(int i);
	void on_dieliky_sliderMoved(int i);
};
