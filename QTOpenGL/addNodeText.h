#ifndef ADD_NODE_TEXT
#define ADD_NODE_TEXT

#include <QLineEdit>
#include "sceneNode.h"
#include "rPolygon.h"

class addNodeText:public QLineEdit{
	Q_OBJECT

public:
	typedef QLineEdit super;
	addNodeText();
	addNodeText(QWidget*); 
	~addNodeText();

public slots:
	void gotClickedSides();
	void gotClickedName();
signals:
	void signalS(QString); 
	void signalN(QString); 
};

#endif