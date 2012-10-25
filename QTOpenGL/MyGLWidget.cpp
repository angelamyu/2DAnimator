#include "MyGLWidget.h"
#include <qtreeview.h>
#include <qstandarditemmodel.h>

#include <qDebug>

MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent) {
	//treeview = new QTreeView(this);
	//setCentralWidget(treeview);
	//We can set our vertex attributes rather than requesting their locations
	//I chose to do so in this constructor, maybe you would do it in your init().
	positionLocation = 0;
	colorLocation = 1;
}

MyGLWidget::~MyGLWidget() {
	//Release your resources, just like you'd delete pointers
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &ibo);

	//Tear down the shader program in reverse of building it
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

void MyGLWidget::initializeGL() {

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		qDebug() << "GLEW is not initialized!";
	}

	//Create the VBOs and IBO we'll be using to render images in OpenGL
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &ibo);

	//Everybody does this, clear the screen
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);

	//here is stuff for setting up our shaders
	const char* fragFile = "diffuseFrag.frag";
	const char* vertFile = "diffuseVert.vert";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	//load up the source, compile and link the shader program
	const char* vertSource = textFileRead(vertFile);
	const char* fragSource = textFileRead(fragFile);
	glShaderSource(vertexShader, 1, &vertSource, 0);
	glShaderSource(fragmentShader, 1, &fragSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//Check if everything is OK
	GLint compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(vertexShader);
	} 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(fragmentShader);
	} 

	//set the attribute locations for our shaders
	glBindAttribLocation(shaderProgram, positionLocation, "vs_position");
	glBindAttribLocation(shaderProgram, colorLocation, "vs_color");

	//finish shader setup
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//check for linking success
	GLint linked;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &linked);
	if (!linked) 
	{
		printLinkInfoLog(shaderProgram);
	}

	//Get the uniform locations for our shaders, unfortunately they can not be set by us, we have
	//to ask OpenGL for them
	u_scr_widthLocation = glGetUniformLocation(shaderProgram, "u_scr_width");
	u_scr_heightLocation = glGetUniformLocation(shaderProgram, "u_scr_height");
	u_modelMatrixLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");

	//Always remember that it doesn't do much good if you don't have OpenGL actually use the shaders
	glUseProgram(shaderProgram);

	cat = new Character();
	currentNode = cat->getRoot();
	nameChanged = false; 
	sidesChanged = false; 
}

void MyGLWidget::paintGL() {
	//Always and only do this at the start of a frame, it wipes the slate clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gMatrix3 g = cat->getRoot()->getTransfMatrixCalculated();
	cat->getRoot()->setText(0,cat->getRoot()->name);
	emit makeRoot(cat->getRoot());
	traverse(cat->getRoot(), g);
}


void MyGLWidget::traverse(sceneNode* root, gMatrix3 m){
	gMatrix3 t = m * root->getTransfMatrixCalculated();
	if(root->name.compare("asdf")==0){
		emit printWidget(QString("FOUND"));
		emit printWidget(QString("FOUND IN S1 widget %1").arg(root->getTranslateX()));

		emit printWidget(QString(" %1").arg(root->getTranslateY()));
	}
	if(root->hasGeometry() == true){
		rPolygon* shape = root->getGeometry(); 
		createPolygon(t,shape->getSides(), *shape);
	}
	if(root->hasChildren() == true){
		vector<sceneNode*> c = root->getChildren();
		vector<sceneNode*>::iterator it;
		for ( it=c.begin() ; it < c.end(); it++ ){
			sceneNode* temp = *it;
			temp->setText(0, temp->name);
			emit makeChild(root, temp);
			traverse(temp, t);
		}
	}
}


void MyGLWidget::createPolygon(gMatrix3 model, int sides, rPolygon& p) {
	float* pPoints = p.getPoints();
	float* pColors = p.getColors();
	unsigned short* pIndices = p.getIndices();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sides*3 * sizeof(float), pPoints, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, sides*3 * sizeof(float), pColors, GL_STREAM_DRAW);
	
	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	//glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 3 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*(sides-2) * sizeof(unsigned short), pIndices, GL_STATIC_DRAW);

	//set the model uniform
	//GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	//if the matrices you used is row major, change this parameter to GL_TRUE.
	glUniformMatrix3fv(u_modelMatrixLocation, 1, GL_TRUE, &model[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 3*(sides-2), GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::translateX(int x){
	if(cat->getRoot()->keyFrameCheck){
		currentNode->setTranslateX(x);
		emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
		updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::translateY(int y){
	if(cat->getRoot()->keyFrameCheck){
	currentNode->setTranslateY(y);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::rotation(int r){
	if(cat->getRoot()->keyFrameCheck){
	currentNode->setRotation(r);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::scaleX(int x){
	if(cat->getRoot()->keyFrameCheck){
	currentNode->setScaleX((float) x/10.0f);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::scaleY(int y){
	if(cat->getRoot()->keyFrameCheck){
	currentNode->setScaleY((float) y/10.0f);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::red(int r){
	if(cat->getRoot()->keyFrameCheck){
	rPolygon* t = currentNode->getGeometry();
	t->setRed((float) r/255.0f);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::green(int r){
	if(cat->getRoot()->keyFrameCheck){
	currentNode->getGeometry()->setGreen((float) r/255.0f);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit setFrameText(QString("KeyFrame")); 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::blue(int r){
	if(cat->getRoot()->keyFrameCheck){
	rPolygon* t = currentNode->getGeometry();
	t->setBlue((float) r/255.0f);
	emit editFrame(grabFrameBuffer(), cat->getRoot()->copy());
	updateGL();
	}
	else{
		cat->getRoot()->keyFrameCheck=true; 
		emit addOneKeyFrame(grabFrameBuffer(), cat->getRoot()->copy());
		emit setFrameText(QString("KeyFrame")); 
	}
}

void MyGLWidget::resetCharacter(){
	delete cat;
	cat = new Character();
	updateGL();
	currentNode = cat->getRoot();
}

void MyGLWidget::setCurrentNode(QTreeWidgetItem* i ,int z){
	currentNode = dynamic_cast<sceneNode*>(i); 
	//updateGL();
}

void MyGLWidget::deleteNode(){
	if(currentNode != cat->getRoot()){
		cat->getRoot()->deleteNode(currentNode);
	}
	else{
		vector<sceneNode*> children = cat->getRoot()->getChildren();
		for(int i = 0; i <children.size(); i++){
			delete children[i]; 
		}
		cat->getRoot()->resetNode();
	}
	currentNode = cat->getRoot();
	updateGL();
}

void MyGLWidget::addNodeName(QString n){
	name = n; 
	nameChanged = true;
	addNode();
}

void MyGLWidget::addNodeSides(QString s){
	sides = s.toInt();
	sidesChanged = true; 
	addNode();
}

void MyGLWidget::addNode(){
	if(sidesChanged && nameChanged){
		sidesChanged = false; 
		nameChanged = false; 
		if(sides>2){
			rPolygon* p;
			if(sides!=4){
				p = new rPolygon(sides, gVector3(1,1,1));
			}
			else{
				p = new Square( gVector3(1,1,1));
			}
			vector<sceneNode*> c; 
			sceneNode* temp = new sceneNode(gMatrix3().identity(), c, p);
			QString parentName = currentNode->name;
			temp->name = name; 
			traverse(cat->root,gMatrix3()); 
			
			///////////////////////////////////////////
			//currentNode->children.push_back(temp); //
			//currentNode->addChild(temp);           //
			///////////////////////////////////////////
			emit sendAddedNodeToFrames(sides,name,parentName);			
			//emit sides, added's name, parent's name

		}
		updateGL();
	}
}

void MyGLWidget::addQTFrame(){
	emit makeFrame(grabFrameBuffer(), cat->getRoot()->copy());
}


void MyGLWidget::makeQTFrameBehind(){
	emit makeFrameBehind(grabFrameBuffer(), cat->getRoot()->copy());
}

void MyGLWidget::makeQTFrameBefore(){
	emit makeFrameBefore(grabFrameBuffer(), cat->getRoot()->copy());
}

void MyGLWidget::editRepaint(sceneNode* r){
	cat->root=r;	
	updateGL();
	currentNode = cat->getRoot();
}

void MyGLWidget::makeInterpolatedQImage(sceneNode* inter, sceneNode* old, int i){
	cat->root=inter; 
	updateGL(); 
	
	emit sendInterpolatedQImage(grabFrameBuffer(),inter,i);
	cat->root=old; 
	updateGL();
	currentNode = cat->getRoot(); 
}

void MyGLWidget::makeEditSpecificQImage(int i,sceneNode* edited){
	sceneNode* old = cat->getRoot();
	cat->root=edited; 
	currentNode = cat->getRoot();
	updateGL(); 

	emit sendEditSpecificQImage(grabFrameBuffer(),i,edited);
	cat->root=old; 
	updateGL();
	currentNode = cat->getRoot(); 
	 
}

void MyGLWidget::resizeGL(int width, int height) {	
	//Thanks to Skiz for this function
	int side = qMin(width, height);  //finds the min of the width and height.  helpful for different distortions of the window
	glViewport((width - side) / 2, (height - side) / 2, side, side); //set the viewport

	// reset the view parameters if the openGL window is resized
	glUniform1f(u_scr_widthLocation, side);
	glUniform1f(u_scr_heightLocation, side);
}

//from swiftless.com
char* MyGLWidget::textFileRead(const char* fileName) {
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

void MyGLWidget::printLinkInfoLog(int prog) 
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}
}

void MyGLWidget::printShaderInfoLog(int shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		qDebug() << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}