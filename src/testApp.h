#pragma once

#include "ofMain.h"
#include "ofxCv.h"

using namespace cv;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        vector<cv::Rect> objects;
        CascadeClassifier classifier;
        Ptr<FaceRecognizer> model;
    
        ofImage graySmall;
    
        vector<cv::Mat> images, faces;
        vector<ofImage> ofFaces;
        vector<int> labels;
    
        int currentTest, currentResult;
    
        int result;
    
        ofVideoGrabber cam;
        ofPixels gray;
};
