#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidget(&this->widgetNaKreslenie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);

	
	widgetNaKreslenie.alokuj();
	widgetNaKreslenie.nacitaj2();
	widgetNaKreslenie.farbaSvetla();
	widgetNaKreslenie.farbaObjektu();


	widgetNaKreslenie.newImage(1000, 1000);
	widgetNaKreslenie.initImage();
}

void Grafika::on_actionSave_triggered()
{
	widgetNaKreslenie.SaveImg("GrafikaKreslenieCiary.png");
}

void Grafika::vykresli()
{
	widgetNaKreslenie.clear();
	
	
	if (ui.rovnobezna->isChecked()) {
		ui.vzdialenost->setDisabled(1);
		widgetNaKreslenie.rovnobezne(ui.alfa->value(), ui.beta->value());
		if (ui.wireframe->isChecked()) {
			widgetNaKreslenie.vykresli();
		}
		else{
			widgetNaKreslenie.zapisHranySfera(ui.xSvetlo->value(), ui.ySvetlo->value(), ui.zSvetlo->value(), ui.difuznaR->value(), ui.difuznaG->value(), ui.difuznaB->value(), ui.ambientnaR->value(), ui.ambientnaG->value(), ui.ambientnaB->value(), ui.zrkadlovaR->value(), ui.zrkadlovaG->value(), ui.zrkadlovaB->value(), ui.z->value(), ui.tienovanie->currentIndex());
		}
		
	}
	else if (ui.perspektivna->isChecked()) {
		ui.vzdialenost->setDisabled(0);
		widgetNaKreslenie.perspektivne(ui.alfa->value(), ui.beta->value(), ui.vzdialenost->value());
		if (ui.wireframe->isChecked()) {
			widgetNaKreslenie.vykresli();
		}
		else {
			widgetNaKreslenie.zapisHranySfera(ui.xSvetlo->value(), ui.ySvetlo->value(), ui.zSvetlo->value(), ui.difuznaR->value(), ui.difuznaG->value(), ui.difuznaB->value(), ui.ambientnaR->value(), ui.ambientnaG->value(), ui.ambientnaB->value(), ui.zrkadlovaR->value(), ui.zrkadlovaG->value(), ui.zrkadlovaB->value(), ui.z->value(), ui.tienovanie->currentIndex());
		}
	}
	
}

void Grafika::vymaz()
{
	widgetNaKreslenie.clear();
	
}

void Grafika::on_alfa_sliderMoved(int i)
{
	vykresli();
}

void Grafika::on_beta_sliderMoved(int i)
{
	vykresli();
}

void Grafika::on_vzdialenost_sliderMoved(int i)
{
	vykresli();
}

void Grafika::on_dieliky_sliderMoved(int i)
{
	vykresli();
}


