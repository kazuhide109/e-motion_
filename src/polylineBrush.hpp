//
//  polylineBrush.hpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/20.
//
#include "ofMain.h"

class PolylineBrush{
     
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
     
     float brushSize = 2;
     vector<ofPolyline> polyline;
     
     void toRedo();
     
};
