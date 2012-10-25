#include "addNodeText.h"


addNodeText::addNodeText(){

}

addNodeText::addNodeText(QWidget* parent) : QLineEdit(parent){

}

addNodeText::~addNodeText(){

}

void addNodeText::gotClickedName(){
	emit signalN(text());
}

void addNodeText::gotClickedSides(){
	emit signalS(text());
}