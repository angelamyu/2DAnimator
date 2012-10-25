#ifndef BATCH_ADD_TEXT
#define BATCH_ADD_TEXT

#include <QLineEdit>
#include "sceneNode.h"
#include "rPolygon.h"

class batchAddText:public QLineEdit{
	Q_OBJECT

public:
	typedef QLineEdit super;
	batchAddText();
	batchAddText(QWidget*); 
	~batchAddText();

public slots:
	void gotClickedNumbers();
	void gotAnimatedNumberFrames();
	void gotSetSpeed();
signals:
	void batchAddNumbers(QString); 
	void animatedNumberFrames(int); 
	void userSpeed(int);
};

#endif