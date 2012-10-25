#ifndef SLIDER_WRAPPER
#define SLIDER_WRAPPER

#include <QSlider>
#include "sceneNode.h"
#include "rPolygon.h"

class sliderWrapper:public QSlider{
	Q_OBJECT

public:
	typedef QLineEdit super;
	sliderWrapper();
	sliderWrapper(QWidget*); 
	~sliderWrapper();

public slots:
	void setTheRange(int);
	void getPosition(int); 
	void setTheValue(int a);
signals:
	void printSlider(QString); 
};

#endif