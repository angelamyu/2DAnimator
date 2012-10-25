#include "qTree.h"
#include "sceneNode.h"


qTree::qTree(){
	QTreeWidget::setColumnCount(1);
}
qTree::qTree(QWidget* parent) : QTreeWidget(parent){
	QTreeWidget::setColumnCount(1);
}
qTree::~qTree(){

}

void qTree::expandAll(sceneNode* root){
	expandItem(root); 
	vector<sceneNode*>::iterator it;
	vector<sceneNode*> children = root->getChildren();
	for(it = children.begin(); it< children.end(); it++)
	{
		expandAll(*it);
	}
}