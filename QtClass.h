#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>
#include <vector>
#include <QColorDialog>

struct line {

	double w;
	int xZ, yZ, yK;
	double q;
	bool operator <(const line& ln)
	{
		if (yZ < ln.yZ) {
			return true;
		}
		else if (yZ > ln.yZ) {
			return false;

		}
		else if (yZ == ln.yZ) {
			if (xZ < ln.xZ) {
				return true;
			}
			else if (xZ > ln.xZ) {
				return false;
			}
			else if (xZ == ln.xZ) {
				if (w < ln.w) {
					return true;
				}
				else if (w > ln.w) {
					return false;
				}
				else {
					return false;
				}
			}
		}
	}
	void pocitajq() { if (w != 0)q = yZ - (xZ / w); else q = xZ; }
};

struct activeLine {
	int index;
	double xi;
	bool operator <(const activeLine& ln)
	{
		if (xi < ln.xi) {
			return true;
		}
		else if (xi > ln.xi) {
			return false;
		}
		else {
			return false;
		}
	}
};

class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	std::vector<QVector3D> bodySfera;
	std::vector<QVector3D> useckySfera;
	QVector3D X, Y, Z;
	std::vector<double> z_buffer;
	std::vector<QVector3D> bodyTransformovane;
	std::vector<line> lines;
	std::vector<activeLine> activeLines;
	int p;
	QColor color;
	std::vector<QColor> colors;
	QRgb* data;
	int row;
	QColor colorLines = Qt::red;
	QColor colorInside = Qt::blue;
	int* vzdialenost;
	QVector3D zdroj,pozorovatel;
	QColor svetlo, objekt;
	QVector3D N;
	QVector3D rs, ra, rd;
	QColor Phong1, Phong2, Phong3;
	double **zbufferBody;
	QColor **zbufferFarby;

public:
	QtClass(QWidget *parent = Q_NULLPTR);
	~QtClass();
	void rovnobezne(double alfa, double beta);
	void perspektivne(double alfa, double beta, double d);
	void nacitaj2();
	void newImage(int x, int y);
	QImage *obrazok;
	void SaveImg(QString menoSuboru);
	void clear();
	void vykresli();
	void drawLine2(QVector3D A, QVector3D B);
	void drawLine(QVector3D A, QVector3D B,double z); 
	void initImage();
	void setPixel(int x, int y, QColor color);
	void scanLine(QVector3D A, QVector3D B, QVector3D C,double z,int a);
	line vytvorHranu(double w, int xz, int yz, int yk);
	activeLine vytvorAL(int ind, double xi);
	void zapisHranySfera(int x, int y, int z, double difR, double difG, double difB, double ambR, double ambG, double ambB, double zrkR, double zrkG, double zrkB, int ztko,int a);
	void Z_buffer(double z, QColor color, int i, int j);
	void farbaSvetla();
	void farbaObjektu();
	QColor Phong(QVector3D q);
	QColor tienovanie(QVector3D A, QVector3D B, QVector3D C, int x, int y,int a);
	void alokuj();
};
