#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxTrueTypeFontUL2.h"
#include "ofxOsc.h"
#include "boxMake.hpp"
#include "polylineBrush.hpp"

#include "liveClientOsc.hpp"
#include "ofxTktrPerformanceTuning.h"

//#define soundNum 13

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
     
     float w;
     float h;
     vector<ofVec2f> lines;
     ofxTrueTypeFontUL2 font20;
      ofxTrueTypeFontUL2 font8;
     int page;
     int mode;
     int tool;
     ofxOscReceiver sender;
     
     vector<ofBoxPrimitive> motionBox;
     vector<bool> isMoveMotionBox;
     vector<float> positionNum;
     vector<ofVec2f> pp;
     
     vector<PolylineBrush> polylineBrush;
     vector<ofRectangle> setButton;
     string brushName[2] = {"FREE DRAWING", "MOTION DRAWING"};
     string toolName[2] = {"BRUSH", "SETSOUND"};
     string kindName[13] = {"CIBE01", "CUBE02", "CUBE03", "DEER", "CAT", "TREE01", "TREE02", "COW", "LAMP", "WOLF",  "BIG DEER", "CACTUS", "PIG"};
     BoxMake boxMake;
    
     
     ofEasyCam cam;
     bool isCam;
     int kind = 0;
     
     ofxSyphonServer server;

     ofLight polyLight;
     
     bool bMoveCam;
     float phase;
     float radius = 1200;
     
     LiveClientOsc liveC;
     bool isDebug;
     vector<bool> strMove;
     int loopVer[4] = {4, 8, 12, 16};
     vector<float> speedRate;
     
};
