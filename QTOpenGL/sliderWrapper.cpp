#include "sliderWrapper.h"


sliderWrapper::sliderWrapper(){

}

sliderWrapper::sliderWrapper(QWidget* parent) : QSlider(parent){

}

sliderWrapper::~sliderWrapper(){

}



void sliderWrapper::setTheRange(int a){
	setRange(1,a);
	setMaximum(a); 
	//emit printSlider(QString("slide %1").arg(a)); 
	setValue(1);
}

void sliderWrapper::getPosition(int a){
	//emit printSlider(QString("pos %1").arg(a)); 
}

void sliderWrapper::setTheValue(int a){
	setValue(a); 
}