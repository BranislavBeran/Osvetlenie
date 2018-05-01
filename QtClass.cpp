#include "QtClass.h"

QtClass::QtClass(QWidget *parent)
	: QWidget(parent)
{

}
QtClass::~QtClass()
{
}
QColor QtClass::Phong(QVector3D q)
{
	QColor Amb, Dif, Zrk, I;
	int r, g, b;
	QVector3D S(zdroj.x() - q.x(), zdroj.y() - q.y(), zdroj.z() - q.z());
	QVector3D V(pozorovatel.x() - q.x(), pozorovatel.y() - q.y(), pozorovatel.z() - q.z());
	S = S.normalized();
	V = V.normalized();
	QVector3D R = 2 * (S*N)*N - S;
	R.normalized();

	

	Amb = QColor(objekt.red()*ra.x(), objekt.green()*ra.y(), objekt.blue()*ra.z());

	r = round(svetlo.red()*(QVector3D::dotProduct(S,N)*rd.x()));
	if (r> 255) r = 255;
	else if (r < 0) r = 0;
	g = round(svetlo.green()*(QVector3D::dotProduct(S, N)*rd.y()));
	if (g > 255) g = 255;
	else if (g < 0) g = 0;
	b = round(svetlo.blue()*(QVector3D::dotProduct(S, N)*rd.z()));
	if (b > 255) b = 255;
	else if (b < 0) b = 0;
	Dif = QColor(r, g, b);

	r = round(svetlo.red()*(QVector3D::dotProduct(R, V)*rs.x()));
	if (r > 255) r = 255;
	else if (r <0) r = 0;
	g = round(svetlo.green()*(QVector3D::dotProduct(R, V)*rs.y()));
	if (g > 255) g = 255;
	else if (g <0) g = 0;
	b = round(svetlo.blue()*(QVector3D::dotProduct(R, V)*rs.z()));
	if (b> 255) b = 255;
	else if (b <0) b = 0;
	Zrk = QColor(r, g, b);

	r = Zrk.red() + Dif.red() + Amb.red();
	g = Zrk.green() + Dif.green() + Amb.green();
	b = Zrk.blue() + Dif.blue() + Amb.blue();

	if (r > 255)  r = 255;	
	if (g > 255)  g = 255;
	if (b > 255) b = 255;
	
	return QColor(abs(r), abs(g), abs(b));
}
QColor QtClass::tienovanie(QVector3D A, QVector3D B, QVector3D C, int x, int y,int a)
{
	if (a == 0) {
		double v1, v2, v3;
		QVector3D A1, B1, C1, D = QVector3D(x, y, 0);
		A.setZ(0);
		B.setZ(0);
		C.setZ(0);


		A1 = (A - D);
		v1 = A1.length();
		A1 = (B - D);
		v2 = A1.length();
		A1 = (C - D);
		v3 = A1.length() ;


		if (v1 > v2) {
			if (v2 > v3) {
				return Phong3;
			}
			
			return Phong2;
			
		}
		else{
			if (v1 > v3) {
				return Phong3;
			}
			return Phong1;
		}

	}
	else {
		double plocha, plocha1, plocha2, plocha3;
		QVector3D A1, B1, C1, D = QVector3D(x, y, 0);
		int r,g,b;
		A.setZ(0);
		B.setZ(0);
		C.setZ(0);

		A1 = (A - B);
		B1 = (B - C);
		C1=QVector3D::crossProduct(A1, B1);
		plocha = C1.length() / 2.0;
		A1 = (A - D);
		B1 = (B - D);
		C1 = QVector3D::crossProduct(A1, B1);
		plocha1 = C1.length() / 2.0;
		A1 = (C - D);
		B1 = (B - D);
		C1 = QVector3D::crossProduct(A1, B1);
		plocha2 = C1.length() / 2.0;
		A1 = (A - D);
		B1 = (C - D);
		C1 = QVector3D::crossProduct(A1, B1);
		plocha3 = C1.length() / 2.0;

		r = (Phong3.red()*plocha3 + Phong2.red()*plocha2 + Phong1.red()*plocha1) / plocha;
		g = (Phong3.green()*plocha3 + Phong2.green()*plocha2 + Phong1.green()*plocha1) / plocha;
		b = (Phong3.blue()*plocha3 + Phong2.blue()*plocha2 + Phong1.blue()*plocha1) / plocha;

		if (r > 255)r = 255;
		if (g > 255)g = 255;
		if (b > 255)b = 255;

		return QColor(r,g,b);

	}
}
void QtClass::alokuj()
{

	zbufferBody = new double*[1000];
	zbufferFarby = new QColor*[1000];
	for (int i = 0; i < 1000; i++) {
		zbufferBody[i] = new double[800];
		zbufferFarby[i] = new QColor[800];
	}
	
}
void QtClass::zapisHranySfera(int x, int y, int z, double difR, double difG, double difB, double ambR, double ambG, double ambB, double zrkR, double zrkG, double zrkB, int ztko, int a)
{	
	QVector3D u, v;
	int dx, dy;
	double w;

	zdroj = QVector3D(x, y, z);
	pozorovatel = QVector3D(0, 0, ztko);
	rs = QVector3D(zrkR,zrkG,zrkB);
	ra = QVector3D(ambR,ambG,ambB);
	rd = QVector3D(difR,difG,difB);

	
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 800; j++) {
			zbufferBody[i][j] = -INFINITY;
			zbufferFarby[i][j] = Qt::white;
		}
	}

	for (int i = 0; i < useckySfera.size(); i++) {
		dy = bodyTransformovane[useckySfera[i].x()].y() - bodyTransformovane[useckySfera[i].y()].y();
		dx = bodyTransformovane[useckySfera[i].x()].x() - bodyTransformovane[useckySfera[i].y()].x();
		if (dy != 0) {
			
			w = dx / (double)dy;
			if (bodyTransformovane[useckySfera[i].x()].y() < bodyTransformovane[useckySfera[i].y()].y()) {
				
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].x()].x(), bodyTransformovane[useckySfera[i].x()].y(), bodyTransformovane[useckySfera[i].y()].y()));
			}
			else if (bodyTransformovane[useckySfera[i].x()].y() > bodyTransformovane[useckySfera[i].y()].y()) {
		
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].y()].x(), bodyTransformovane[useckySfera[i].y()].y(), bodyTransformovane[useckySfera[i].x()].y()));
			}
		}
		dy = bodyTransformovane[useckySfera[i].y()].y() - bodyTransformovane[useckySfera[i].z()].y();
		dx = bodyTransformovane[useckySfera[i].y()].x() - bodyTransformovane[useckySfera[i].z()].x();
		if (dy != 0) {
			w = dx / (double)dy;
			if (bodyTransformovane[useckySfera[i].y()].y() < bodyTransformovane[useckySfera[i].z()].y()) {
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].y()].x(), bodyTransformovane[useckySfera[i].y()].y(), bodyTransformovane[useckySfera[i].z()].y()));
			}
			else if (bodyTransformovane[useckySfera[i].y()].y() > bodyTransformovane[useckySfera[i].z()].y()) {
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].z()].x(), bodyTransformovane[useckySfera[i].z()].y(), bodyTransformovane[useckySfera[i].y()].y()));
			}
		}
		dy = bodyTransformovane[useckySfera[i].x()].y() - bodyTransformovane[useckySfera[i].z()].y();
		dx = bodyTransformovane[useckySfera[i].x()].x() - bodyTransformovane[useckySfera[i].z()].x();
		if (dy != 0) {
			w = dx / (double)dy;
			if (bodyTransformovane[useckySfera[i].x()].y() < bodyTransformovane[useckySfera[i].z()].y()) {
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].x()].x(), bodyTransformovane[useckySfera[i].x()].y(), bodyTransformovane[useckySfera[i].z()].y()));
			}
			else if (bodyTransformovane[useckySfera[i].x()].y() > bodyTransformovane[useckySfera[i].z()].y()) {
				lines.push_back(vytvorHranu(w, bodyTransformovane[useckySfera[i].z()].x(), bodyTransformovane[useckySfera[i].z()].y(), bodyTransformovane[useckySfera[i].x()].y()));
			}
		}
		
		u.setX(bodyTransformovane[useckySfera[i].x()].x() - bodyTransformovane[useckySfera[i].y()].x());
		u.setY(bodyTransformovane[useckySfera[i].x()].y() - bodyTransformovane[useckySfera[i].y()].y());
		u.setZ(bodyTransformovane[useckySfera[i].x()].z() - bodyTransformovane[useckySfera[i].y()].z());

		v.setX(bodyTransformovane[useckySfera[i].y()].x() - bodyTransformovane[useckySfera[i].z()].x());
		v.setY(bodyTransformovane[useckySfera[i].y()].y() - bodyTransformovane[useckySfera[i].z()].y());
		v.setZ(bodyTransformovane[useckySfera[i].y()].z() - bodyTransformovane[useckySfera[i].z()].z());

		N.setX(u.y()*v.z() - u.z()*v.y());
		N.setY(u.z()*v.x() - u.x()*v.z());
		N.setZ(u.x()*v.y() - u.y()*v.x());

		N.normalize();
		
		Phong1 = Phong(bodyTransformovane[useckySfera[i].x()]);
		Phong2 = Phong(bodyTransformovane[useckySfera[i].y()]);
		Phong3 = Phong(bodyTransformovane[useckySfera[i].z()]);

		scanLine(bodyTransformovane[useckySfera[i].x()], bodyTransformovane[useckySfera[i].y()], bodyTransformovane[useckySfera[i].z()],useckySfera[i].z(),a);

		lines.clear();
		activeLines.clear();
	}
	for (int i=0 ; i < 1000; i++) {
		for (int j = 0; j < 800; j++) {
			setPixel(i, j, zbufferFarby[i][j]);
		}
	}
	update();
}
void QtClass::Z_buffer(double z, QColor color, int i, int j)
{
	if (z >= zbufferBody[i][j]) {
		zbufferBody[i][j] = z;
		zbufferFarby[i][j] = color;
	}
}
void QtClass::farbaSvetla()
{
	svetlo = QColorDialog::getColor(Qt::white, this, "farba svetla", QColorDialog::DontUseNativeDialog);
}
void QtClass::farbaObjektu()
{
	objekt = QColorDialog::getColor(Qt::white, this, "farba okolia", QColorDialog::DontUseNativeDialog);
}
line QtClass::vytvorHranu(double w, int xz, int yz, int yk)
{
	line p;

	p.w = w;
	p.xZ = xz;
	p.yZ = yz;
	p.yK = yk-1;
	return p;
}
activeLine QtClass::vytvorAL(int ind, double xi)
{
	activeLine l;

	l.index = ind;
	l.xi = xi;

	return l;
}
void QtClass::scanLine(QVector3D A, QVector3D B, QVector3D C,double z,int a)
{
	int aktivne = 0;
	int ymin = 999, ymax = 0, xi2;
	std::vector<int> deactivate;
	z = (A.z() + B.z() + C.z()) / 3;
	std::sort(lines.begin(), lines.end());
	ymin = lines[0].yZ;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].yK > ymax) {
			ymax = lines[i].yK;
		}
	}
	if (lines.size() == 2)ymax++;
	for (int i = ymin; i < ymax; i++) {
		
		for (int j = aktivne; j < lines.size(); j++) {	
			if (i == lines[j].yZ) {
				activeLines.push_back(vytvorAL(j, (lines[j].xZ - (i - lines[j].yZ)*lines[j].w)));
				aktivne++;
			}
		}

		std::sort(activeLines.begin(), activeLines.end());	
		for (int j = 0; j < activeLines.size() -1; j=j+2) {
			for (double q = activeLines[j].xi -0.5; q < activeLines[j + 1].xi +0.5; q++) {
				
				Z_buffer(z,tienovanie(A,B,C,(int)q,i,a),(int)q,i);
			}
		}
		for (int j = 0; j < activeLines.size(); j++) {
			activeLines[j].xi += lines[activeLines[j].index].w;
		}
		for (int k = 0; k < activeLines.size(); k++) {
			if (i == lines[activeLines[k].index].yK) {
				deactivate.push_back(k);								
			}											
		}
		for (int j = 0; j < deactivate.size(); j++) {
			activeLines.erase(activeLines.begin() + (deactivate[j] - j));
		}
		deactivate.clear();
		
		
	}

	drawLine(A, B, z);
	drawLine(C, B, z);
	drawLine(A, C, z);

	update();

	lines.clear();
	activeLines.clear();


}
void QtClass::drawLine(QVector3D A, QVector3D B,double z)
{
	double m, x, y;
	int dx, dy;
	QVector3D C;

	dy = B.y() - A.y();
	dx = B.x() - A.x();
	m = dy / (double)dx;
	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			Z_buffer(z,Qt::black,x, (int)y);
		}

	}
	else {
		if (A.y() > B.y()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + (1 /(double) m);
			y = y + 1;
			Z_buffer(z, Qt::black,(int)x, y);
		}

	}


	update();
}
void QtClass::drawLine2(QVector3D A, QVector3D B)
{
	double m, x, y;
	int dx, dy;
	QVector3D C;

	dy = B.y() - A.y();
	dx = B.x() - A.x();
	m = dy / (double)dx;
	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			setPixel(x, (int)y,Qt::black);
		}

	}
	else {
		if (A.y() > B.y()) {
			C = B;
			B = A;
			A = C;
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + (1 / (double)m);
			y = y + 1;
			setPixel( (int)x, y,Qt::black);
		}

	}


	update();
}
void QtClass::initImage()
{
	this->resize(obrazok->size());
	this->setMinimumSize(obrazok->size());

	row = obrazok->bytesPerLine() / 4;
	data = (QRgb *)obrazok->bits();
}
void QtClass::setPixel(int x, int y, QColor color)
{


 	data[x + y*row] = color.rgb();
}
void QtClass::rovnobezne(double alfa, double beta)
{
	while (bodyTransformovane.size() != 0) {
		bodyTransformovane.pop_back();
	}

	alfa = (M_PI*alfa) / 180;
	beta = (M_PI*beta) / 180;
	
	X = QVector3D(sin(alfa)*cos(beta), sin(alfa)*sin(beta), cos(alfa));
	Z = QVector3D(sin(alfa + (M_PI / 2))*cos(beta), sin(alfa + (M_PI / 2))*sin(beta), cos(alfa+(M_PI/2)));
	Y = QVector3D(X.y()*Z.z() - X.z()*Z.y(), X.z()*Z.x() - X.x()*Z.z(), X.x()*Z.y() - X.y()*Z.x());
	

	for (int i = 0; i < bodySfera.size(); i++) {
		bodyTransformovane.push_back(QVector3D((int)((bodySfera[i].x()*X.x() + bodySfera[i].y()*X.y() + bodySfera[i].z()*X.z()) * 200) + 300,(int)((bodySfera[i].x()*Y.x() + bodySfera[i].y()*Y.y() + bodySfera[i].z()*Y.z()) * 200) + 300, bodySfera[i].x()*Z.x() + bodySfera[i].y()*Z.y() + bodySfera[i].z()*Z.z() + 300));
		
	}
}
void QtClass::perspektivne(double alfa, double beta,double d)
{
	while (bodyTransformovane.size() != 0) {
		bodyTransformovane.pop_back();
	}
	double x, y, z;
	alfa = (M_PI*alfa) / 180;
	beta = (M_PI*beta) / 180;
	
	X = QVector3D(sin(alfa)*cos(beta), sin(alfa)*sin(beta), cos(alfa));
	Z = QVector3D(sin(alfa + (M_PI / 2))*cos(beta), sin(alfa + (M_PI / 2))*sin(beta), cos(alfa + (M_PI / 2)));
	Y = QVector3D(X.y()*Z.z() - X.z()*Z.y(), X.z()*Z.x() - X.x()*Z.z(), X.x()*Z.y() - X.y()*Z.x());

	for (int i = 0; i < bodySfera.size(); i++) {
		x = bodySfera[i].x()*X.x() + bodySfera[i].y()*X.y() + bodySfera[i].z()*X.z();
		y = bodySfera[i].x()*Y.x() + bodySfera[i].y()*Y.y() + bodySfera[i].z()*Y.z();
		z = bodySfera[i].x()*Z.x() + bodySfera[i].y()*Z.y() + bodySfera[i].z()*Z.z();

		bodyTransformovane.push_back(QVector3D((int)(200 * d*x / (d - 200*z)) + 300,(int)(200 * d*y / (d - 200*z)) + 300,200*(d/(d-z))));
		
	}
}
void QtClass::nacitaj2()
{
	QFile file("sphere_1.vtk");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);
	QString riadok;
	QStringList riadok2;
	int riadky;

	for (int i = 0; i < 4; i++) {
		riadok = in.readLine();
	}
	riadok = in.readLine();
	riadok2 = riadok.split(' ');
	riadky = riadok2[1].toInt();
	
	for (int i = 0; i <riadky; i++) {
		riadok = in.readLine();
		riadok2 = riadok.split(' ');
		bodySfera.push_back(QVector3D(riadok2[0].toDouble(), riadok2[1].toDouble(), riadok2[2].toDouble()));
		
	}
	riadok = in.readLine();
	riadok = in.readLine();
	riadok2 = riadok.split(' ');
	riadky = riadok2[1].toInt();
	
	for (int i = 0; i < riadky; i++) {
		riadok = in.readLine();
		riadok2 = riadok.split(' ');
		useckySfera.push_back(QVector3D(riadok2[1].toFloat(), riadok2[2].toFloat(), riadok2[3].toFloat()));
		
	}

	file.close();
}

void QtClass::clear()
{
	obrazok->fill(Qt::white);
	update();
}
void QtClass::vykresli()
{
	int x, y, z;

	for (int i = 0; i < useckySfera.size(); i++) {
			x = useckySfera[i].x();
			y = useckySfera[i].y();
			z = useckySfera[i].z();
			drawLine2(bodyTransformovane[x], bodyTransformovane[y]);
			drawLine2(bodyTransformovane[y], bodyTransformovane[z]);
			drawLine2(bodyTransformovane[x], bodyTransformovane[z]);
	}
	
	update();
}
void QtClass::newImage(int x, int y)
{
	obrazok = new QImage(x, y, QImage::Format_RGB32);
	obrazok->fill(Qt::white);
	
	this->setMinimumSize(obrazok->size());

	update();
}
void QtClass::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *obrazok, area);
}
void QtClass::SaveImg(QString menoSuboru)
{
	if (obrazok->save(menoSuboru, "png"))
		qDebug() << "ulozene";
	else
		qDebug() << "zlyhalo";
}
