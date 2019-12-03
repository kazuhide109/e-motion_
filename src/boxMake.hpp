//
//  boxMake.hpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/19.
//
#include "ofMain.h"
#include "liveSendOsc.hpp"
#include "ofxAssimpModelLoader.h"

#define soundNum 13

class BoxMake{
          
     public:
          void setup();
          void update(int kind, ofRectangle rect);
          void draw(int kind, bool isCam);
          
          void keyPressed(int key);
          void keyReleased(int key);
          void mouseMoved(int x, int y );
          void mouseDragged(int x, int y, int button);
          void mousePressed(int x, int y, int button);
          void mouseReleased(int x, int y, int button);
          void mouseEntered(int x, int y);
          void mouseExited(int x, int y);
     
     void plusModel(int x, int y, int kind);
     void reDo(int kind);
     
     vector<vector<ofBoxPrimitive>> boxes;
     
     vector<vector<ofxAssimpModelLoader>> model;
     vector<ofBoxPrimitive> boxes5;
     vector<ofBoxPrimitive> boxes6;
     vector<ofBoxPrimitive> boxes7;
     vector<ofBoxPrimitive> boxes8;
     vector<ofBoxPrimitive> boxes9;
     vector<ofBoxPrimitive> boxes10;
     vector<ofBoxPrimitive> boxes11;
     vector<ofBoxPrimitive> boxes12;
     vector<ofBoxPrimitive> boxes13;
     
     
      LiveSendOsc liveSendOsc;
      vector<ofPoint> TruckClip;
     
     int sNum = soundNum;
     vector<ofxAssimpModelLoader> loadModel;
     
};
