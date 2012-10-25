#ifndef QTREE_H
#define QTREE_H

#include <QTreeWidget>
#include "sceneNode.h"

class qTree:public QTreeWidget{
	Q_OBJECT

public:
	typedef QTreeWidget super;
	qTree();
	qTree(QWidget*);
	~qTree();
	void expandAll(sceneNode* root);

public slots:
	void putRoot(sceneNode* root){
		takeTopLevelItem(0); 
		super::addTopLevelItem(root);
		expandAll(root);
	}

	void putChild(sceneNode* parent, sceneNode* child){
		parent->addChild(child);
		expandAll(parent); 
	}

};

#endif