#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
     ofSetFrameRate(60);
     ofBackground(255);
//     ofSetBackgroundAuto(false);
     font20.loadFont("GillSans.ttc", 14);
     ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
     ofHideCursor();
     
     // open an outgoing connection to HOST:PORT
     
     polylineBrush.resize(2);
     
     cam.setFov(50);
     cam.setPosition(0, 800, -1000);
     cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
     
     boxMake.setup();
     
     polyLight.setAmbientColor(ofFloatColor(0,0, 0));
     polyLight.setDiffuseColor( ofFloatColor(.85, .85, .85) );
     polyLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
     
     polyLight.setPosition(0, 0, 800);
}

//--------------------------------------------------------------
void ofApp::update(){
     ofSetWindowTitle(ofToString(ofGetFrameRate()));
     w = ofGetWidth();
     h = ofGetHeight();
     
     TS_START("REACT");
     if(polylineBrush[1].polyline.size()>0){
          for(int i=0; i<polylineBrush[1].polyline.size(); i++){
               for(int j=0; j<boxMake.sNum; j++){
                    boxMake.update(j, setButton[i]);
               }
          }
     }
     TS_STOP("REACT");
     
     if(isCam){
           polyLight.setPosition(cam.getPosition());
     }else{
           polyLight.setPosition(0, 0, 800);
     }
}

//--------------------------------------------------------------
void ofApp::draw(){
     
     if(isCam){
          cam.enableMouseInput();
          cam.begin();
          if(bMoveCam){
               phase+=0.01;
               if(ofGetFrameNum()%240 == 0) radius = ofRandom(300, -1400);
               cam.setPosition(cos(phase)*radius, sin(phase)*radius, -200);
               cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 0, -1));
          }
     }else{
          cam.disableMouseInput();
     }
//     ofDrawGrid(100, 10);
//     ofDrawAxis(500);
     
     ofEnableDepthTest();
#ifndef TARGET_PROGRAMMABLE_GL
     glShadeModel(GL_SMOOTH); //some model / light stuff
#endif
     ofEnableLighting();
     polyLight.enable();
     
     if(isCam){
          ofTranslate(-w/2, -h/2);
     }
     
     TS_START("model");
     for(int i=0; i<polylineBrush.size(); i++){
          if(i==0) ofSetColor(10);
          else if(i==1) ofSetColor(200, 0, 0);
          polylineBrush[i].draw();
     }
     TS_STOP("model");
     
     if(polylineBrush[1].polyline.size()>0){
//          for(auto sb : setButton){
//               ofNoFill();
//               ofDrawRectangle(sb);
//               ofFill();
//          }
          for(int i=0; i<motionBox.size(); i++){
               float speedRate = 0.5;
               if(isMoveMotionBox[i]){
                    pp[i].x = pp[i].x + (polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].x - polylineBrush[1].polyline[i].getVertices()[positionNum[i]].x)*speedRate;
                    pp[i].y = pp[i].y + (polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].y - polylineBrush[1].polyline[i].getVertices()[positionNum[i]].y)*speedRate;
                    
                    if(abs(pp[i].x -  polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].x) < 0.1 && abs(pp[i].y -  polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].y) < 0.1){
                         positionNum[i]++;
                         pp[i].x = polylineBrush[1].polyline[i].getVertices()[positionNum[i]].x;
                         pp[i].y = polylineBrush[1].polyline[i].getVertices()[positionNum[i]].y;
                         
                    }
                    setButton[i].setPosition(pp[i]);
                    motionBox[i].setPosition(pp[i]);
//                    positionNum[i]+=0.5;
                    if(positionNum[i] > polylineBrush[1].polyline[i].size()-2){
                         positionNum[i] = 0;
                         pp[i].set(polylineBrush[1].polyline[i].getVertices()[positionNum[i]]);
                    }
               }
               ofSetColor(255, 220, 220);
               ofSetRectMode(OF_RECTMODE_CENTER);
               ofNoFill();
               ofDrawRectangle(setButton[i]);
               ofFill();
               ofSetRectMode(OF_RECTMODE_CORNER);
               motionBox[i].draw();
          }
     }
     //箱書くやつ
     for(int i=0; i<soundNum; i++){
          ofSetColor(220);
          boxMake.draw(i, isCam);
     }
     
     if(isCam)
     cam.end();
     
     ofDisableDepthTest();
     ofDisableLighting();
     ofDisableLighting();
     polyLight.disable();
     
     ofSetColor(40);
     std::stringstream time;
     time << "Elapsed Time:  ";
     time << std::fixed << std::setprecision(2) << ofGetElapsedTimef();
     font20.drawString(time.str(), w*0.98, h*0.98, 0, 0, UL2_TEXT_ALIGN_RIGHT);
     stringstream data01;
     data01 << "TOOL: " << toolName[tool];
//     font20.drawString(data01.str(), w*0.02, h*0.04, 0, 0, UL2_TEXT_ALIGN_LEFT);
//     stringstream data02;
     data01 << "  /  " << "BRUSH MODE: " << brushName[mode];
//     font20.drawString(data02.str(), w*0.15, h*0.04, 0, 0, UL2_TEXT_ALIGN_LEFT);
//     stringstream data03;
     data01 << "  /  " << "SOUND TYPE: " << kindName[kind];
     font20.drawString(data01.str(), w*0.02, h*0.04, 0, 0, UL2_TEXT_ALIGN_LEFT);
     
     //ガイド
     ofNoFill();
     ofSetLineWidth(1);
     ofSetColor(10);
     ofDrawCircle(mouseX, mouseY, polylineBrush[mode].brushSize);
     ofSetLineWidth(2);
     ofSetColor(60);
     float whValue = 0.05;
     ofDrawRectangle(w*whValue, h*whValue, w*(1-whValue*2), h*(1-whValue*2));
     whValue = 0.01;
     ofDrawRectangle(w*whValue, h*whValue, w*(1-whValue*2), h*(1-whValue*2));
     ofFill();
     
     server.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     switch (key) {
          case OF_KEY_UP:
               if(mode < polylineBrush.size()-1)
               mode++;
               break;
          case OF_KEY_DOWN:
               if(mode > 0)
               mode--;
               break;
          case 13:
               if(tool == 0){
                    polylineBrush[mode].toRedo();
                    if(mode == 1 && polylineBrush[mode].polyline.size()>0){
                         setButton.pop_back();
                         motionBox.pop_back();
                         isMoveMotionBox.pop_back();
                         positionNum.pop_back();
                         pp.pop_back();
                    }
               }else if(tool == 1){
                    boxMake.reDo(kind);
               }
               
               break;
               
          case OF_KEY_PAGE_UP:
               if(tool < 1)
               tool++;
               break;
          case OF_KEY_PAGE_DOWN:
               if(tool > 0)
               tool--;
               break;
          case OF_KEY_LEFT:
               if(kind < soundNum-1)
               kind++;
               break;
          case OF_KEY_RIGHT:
               if(kind > 0)
               kind--;
               break;
          case ' ':
               isCam = !isCam;
               break;
          case 'm':
               bMoveCam = !bMoveCam;
               break;
               
          default:
               break;
     }
     
     if(key == 'a' || key == 'A'){
          boxMake.liveSendOsc.setPlay();
     }
     if(key == 'q' || key == 'q'){
          boxMake.liveSendOsc.setStop();
     }
     if(key == 'z'){
          boxMake.liveSendOsc.setTruckClip(4,2);
     }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
     
     if(tool == 0 && !isCam)polylineBrush[mode].mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     if(!isCam){
          if(tool == 0){
               polylineBrush[mode].mousePressed(x, y, button);
               if(mode == 1){
                    ofRectangle bb;
                    float bbSize = w*0.02;
                    bb.set(x, y, bbSize, bbSize);
                    setButton.push_back(bb);
                    ofBoxPrimitive mbb;
                    float mbSize = w*0.012;
                    mbb.set(mbSize, mbSize, mbSize);
                    mbb.setPosition(x, y, 0);
                    motionBox.push_back(mbb);
                    bool isMMB;
                    isMoveMotionBox.push_back(isMMB);
                    positionNum.push_back(0);
               }
          }
          else if(tool == 1){
               boxMake.plusModel(x, y, kind);
          }
     }
     
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
     
     if(mode == 1 && tool == 0){
          if(x ==  setButton.back().x){
               setButton.pop_back();
               motionBox.pop_back();
               isMoveMotionBox.pop_back();
               positionNum.pop_back();
               polylineBrush[mode].toRedo();
          }else{
               isMoveMotionBox.back() = true;
               ofVec2f prepp;
               prepp.x = polylineBrush[1].polyline.back().getVertices()[0].x;
               prepp.y = polylineBrush[1].polyline.back().getVertices()[0].y;
               pp.push_back(prepp);
          }
     }

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
