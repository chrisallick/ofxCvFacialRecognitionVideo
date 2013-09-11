#include "testApp.h"

using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){
    // setup face detection
	classifier.load(ofToDataPath("haarcascade_frontalface_alt.xml"));
    
    ofSetFrameRate(10);
    cam.initGrabber(320, 240);
    
    // load images from data directory
    ofDirectory dir;
    int num = dir.listDir("faces");
    for (int i=0; i<num; i++){
        // load into OF
        ofImage img;
        img.loadImage(dir.getPath(i));
        
        // convert into openCV, grayscale
        
        Mat color = ofxCv::toCv(img);
        Mat grey;
        cvtColor( color, grey, CV_RGB2GRAY);
        
        images.push_back( grey );
        
        // labels == who you are
        labels.push_back(i);
    }
    
    // use haar classifier to detect faces
    for (int i=0; i<images.size(); i++){
        
        // detect faces in image
        classifier.detectMultiScale(images[i], objects, 1.06, 1, 0);
        
        // if there are some faces
        if ( objects.size() > 0 ){
            // crops image to face rect
            Mat roi( images[i], objects[0]);
            
            // get everybody to the same size
            Mat smallMat;
            smallMat.create(100, 100, ofxCv::getCvImageType(roi));
            
            resize(roi, smallMat, smallMat.size(), 0, 0, INTER_LINEAR);
            
            faces.push_back(smallMat);
            
            ofImage toSave;
            ofxCv::toOf(smallMat, toSave);
            toSave.update();
            
            ofFaces.push_back(toSave);
        }
        
        objects.clear();
    }
    
    // load faces into trainer
    // The following lines create an Eigenfaces model for
    // face recognition and train it with the images and labels
    model = createEigenFaceRecognizer();
    model->train(faces, labels);
    
    currentTest = 0;
    currentResult = -1;
}

//--------------------------------------------------------------
void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
        //ofxCv::convertColor(cam, gray, CV_RGB2GRAY);
        Mat color = ofxCv::toCv(cam);
        Mat grey;
        cvtColor( color, grey, CV_RGB2GRAY);
        
        classifier.detectMultiScale(grey, objects, 1.06, 1, 0);
        
        if ( objects.size() > 0 ){
            // crops image to face rect
            Mat roi( grey, objects[0]);
            
            // get everybody to the same size
            Mat smallMat;
            smallMat.create(100, 100, ofxCv::getCvImageType(roi));
            
            resize(roi, smallMat, smallMat.size(), 0, 0, INTER_LINEAR);

            currentResult = model->predict(smallMat);
        }
        
	}
    //currentResult = model->predict(faces[currentTest]);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    cam.draw(0, 300);
    
    int x = 0;
    for (int i=0; i<ofFaces.size(); i++){
        if ( currentResult == i ){
            ofSetColor(150,0,0);
        } else {
            ofSetColor(255);
        }
        ofFaces[i].draw(x,0);
        if ( currentTest == i ){
            ofSetColor(255,0,0);
            ofDrawBitmapString("Test", x, ofFaces[i].height + 20);
        }
        x += ofFaces[i].width;
    }

    ofDrawBitmapString("Testing image "+ofToString(currentTest+1) + ", which I, the computer, think is image "+ofToString(currentResult+1), 20,200);
    
    //ofDrawBitmapString("result: "+ ofToString(result), 20,220);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == '+'){
        currentTest++;
        if ( currentTest >= faces.size()){
            currentTest = 0;
        }
    } else if ( key =='-'){
        currentTest--;
        if ( currentTest < 0){
            currentTest = faces.size() - 1;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}