//
//  polylineBrush.cpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/20.
//

#include "polylineBrush.hpp"

void PolylineBrush::setup(){
     
}

void PolylineBrush::update(){
     
}

void PolylineBrush::draw(){
     ofSetLineWidth(brushSize);
          if(polyline.size()>0){
               for(auto lines :  polyline){
                    lines.draw();
               }
          }
}

void PolylineBrush::mousePressed(int x, int y, int button){
     ofPolyline line;
     polyline.push_back(line);
     
}

void PolylineBrush::mouseDragged(int x, int y, int button){
     ofPoint pt;
     pt.set(x,y);
     polyline.back().addVertex(pt);
}



void PolylineBrush::toRedo(){
     if(polyline.size()>0){
          polyline.pop_back();
     }
}
