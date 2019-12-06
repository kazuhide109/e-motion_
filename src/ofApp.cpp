#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
     ofSetFrameRate(60);
     ofBackground(255);
//     ofSetBackgroundAuto(false);
     font20.loadFont("GillSans.ttc", 14);
     font8.loadFont("GillSans.ttc", 8);
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
     
     liveC.setup();
     outFbo.allocate(1920, 1080, GL_RGB);
     
}

//--------------------------------------------------------------
void ofApp::update(){
     ofSetWindowTitle(ofToString(ofGetFrameRate()));
     w = ofGetWidth();
     h = ofGetHeight();
     
     float whValue = 0.05;
     playAreaRect.set(w*whValue, h*whValue, w*(1-whValue*2), h*(1-whValue*2));
     
     TS_START("REACT");
//     if(polylineBrush[1].polyline.size()>0){
//          for(int i=0; i<polylineBrush[1].polyline.size(); i++){
//               for(int j=0; j<boxMake.sNum; j++){
//                    boxMake.update(j, setButton[i]);
//               }
//          }
//     }
          for(int i=0; i<pp.size(); i++){
               
               for(int j=0; j<13; j++){
                    if(j<3){
                         for(int k=0; k<boxMake.boxes[j].size(); k++){
                              if(setButton[i].inside(boxMake.boxes[j][k].getPosition())){
                                   boxMake.soundtruck(j);
                                   cout << "SS_1" << endl;
                              }
                         }
                    }
                    else{
                         for(int k=0; k<boxMake.model[j-3].size(); k++){
                              if(setButton[i].inside(boxMake.model[j-3][k].getPosition())){
                                   boxMake.soundtruck(j);
                                   cout << "SS_2" << endl;
                              }
                         }
                    }
                    
               }
          
          }
     TS_STOP("REACT");
     
     if(isCam){
           polyLight.setPosition(cam.getPosition());
     }else{
           polyLight.setPosition(0, 0, 800);
     }
     
     liveC.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
     
     if(liveC.beat%8 != 0) isChngeZoomOnece = true;
     
     
     if(isCam){
          cam.enableMouseInput();
          cam.begin();
          if(bMoveCam){
               phase+=0.01;
               if(liveC.beat%8 == 0 && isChngeZoomOnece){
                    radius = ofRandom(300, -1400);
                    isChngeZoomOnece = false;
               }
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
     
//     outFbo.begin();
//     ofClear(0);
     
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
     
     
     //箱が動く部分
     TS_START("MoveBox");
     if(polylineBrush[1].polyline.size()>0){
          
          for(int i=0; i<pp.size(); i++){
//               float speedRate = 0.5;
               if(isMoveMotionBox[i]){
                    //moveBoxのxy座標の決定
                    pp[i].x = pp[i].x + (polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].x - polylineBrush[1].polyline[i].getVertices()[positionNum[i]].x)*speedRate[i];
                    pp[i].y = pp[i].y + (polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].y - polylineBrush[1].polyline[i].getVertices()[positionNum[i]].y)*speedRate[i];
                    //
                    float thureshold = 1;
                    if(abs(pp[i].x -  polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].x) < thureshold && abs(pp[i].y -  polylineBrush[1].polyline[i].getVertices()[positionNum[i]+1].y) < thureshold){
                         positionNum[i]++;
                         pp[i].x = polylineBrush[1].polyline[i].getVertices()[positionNum[i]].x;
                         pp[i].y = polylineBrush[1].polyline[i].getVertices()[positionNum[i]].y;

                    }
                    setButton[i].setPosition(pp[i]);
                    motionBox[i].setPosition(pp[i]);
//                    positionNum[i] += 1.0;
                    if(positionNum[i] > polylineBrush[1].polyline[i].size()-2){
                         isMoveMotionBox[i] = false;
                         positionNum[i] = 0;
                         pp[i].set(polylineBrush[1].polyline[i].getVertices()[positionNum[i]]);
                    }
               }
               if(strMove[i]){
                    isMoveMotionBox[i] = true;
               }
               ofSetRectMode(OF_RECTMODE_CENTER);
               isMoveMotionBox[i] ? ofSetColor(200, 200, 50) :  ofSetColor(200);
               ofDrawRectangle(buttonRect[i]);
               ofNoFill();
               ofSetColor(255, 220, 220);
               ofDrawRectangle(buttonRect[i]);
               ofDrawRectangle(setButton[i]);
               ofFill();
               ofSetRectMode(OF_RECTMODE_CORNER);
               motionBox[i].draw();
               
               if(liveC.beat%8 == 0){
                    strMove[i] = true;
               }else{
                    strMove[i] = false;
               }
          }
     }
     TS_STOP("MoveBox");
     //箱書くやつ
     for(int i=0; i<soundNum; i++){
          ofSetColor(220);
          boxMake.draw(i, isCam);
     }
     
//     outFbo.end();
//     outFbo.draw(0,0);
     
     if(isCam)
     cam.end();
     
     //select
     if(isSoundSelect){
          ofSetColor(255, 200);
          ofBoxPrimitive box;
          box.setPosition(w*0.5, h*0.5, 0);
          box.set(w*0.5, w*0.5, w*0.01);
          box.draw();
          ofSetColor(255);
          boxMake.drawSingle(w*0.5, h*0.525, kind);
     }
     
     ofDisableLighting();
     ofDisableDepthTest();
     polyLight.disable();
     
     //Speed Control
     ofSetColor(100);
     ofDrawLine(w*0.97, h*0.1, w*0.97, h*0.35);
     font20.drawString("speed", w*0.97, h*0.09, 0, 0, UL2_TEXT_ALIGN_CENTER);
     if(pp.size()>0){
          ofDrawRectangle(rateBox[pp.size()-1]);
     }
     
     //Vers
     ofSetColor(100);
     font20.drawString("Vers", w*0.97, h*0.49, 0, 0, UL2_TEXT_ALIGN_CENTER);
     ofSetColor(220);
     for(int j=0; j<4; j++){
          ofDrawRectangle(w*0.96, h*0.5 + j*w*0.04, w*0.02, w*0.02);
     }
     
     //Sound Select Button
     ofSetColor(230);
     sSelectBtm.set(w*0.015, h*0.85, w*0.03, w*0.03);
     ofDrawRectangle(sSelectBtm);
     ofNoFill();
     isSoundSelect ? ofSetColor(200, 0, 0) : ofSetColor(20);
     ofDrawRectangle(sSelectBtm);
     ofFill();
     font20.drawString("select", w*0.03, h*0.84, 0, 0, UL2_TEXT_ALIGN_CENTER);
     
     //BPM
     for(int i=0; i<8; i++){
          i == liveC.beat%8 ? ofSetColor(100, 0, 0) : ofSetColor(200);
          ofDrawRectangle(w*0.02*(1 + i*1.5), h*0.955, w*0.016, w*0.016);
     }
     if(isDebug){
          ofSetColor(10);
          liveC.drawDebug();
     }
     
     //TEXT STATUS
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
     float whValue = 0.01;
     ofDrawRectangle(w*whValue, h*whValue, w*(1-whValue*2), h*(1-whValue*2));
     ofDrawRectangle(playAreaRect);
     ofFill();
     
     TS_START("Syphon");
//     server.publishTexture(&outFbo.getTexture());
     server.publishScreen();
     TS_STOP("Syphon");
}

void ofApp::eraseMoveBox(int num){
     if(polylineBrush[mode].polyline.size()>0 && num == pp.size()){
          cout << "side > 0" << endl;
          setButton.pop_back();
          motionBox.pop_back();
          isMoveMotionBox.pop_back();
          positionNum.pop_back();
          pp.pop_back();
          strMove.pop_back();
          speedRate.pop_back();
          rateBox.pop_back();
          buttonRect.pop_back();
     }else if(polylineBrush[mode].polyline.size()>0 && num != pp.size()){
          setButton.erase(setButton.begin() + num);
          motionBox.erase(motionBox.begin() + num);
          isMoveMotionBox.erase(isMoveMotionBox.begin() + num);
          positionNum.erase(positionNum.begin() + num);
          pp.erase(pp.begin() + num);
          strMove.erase(strMove.begin() + num);
          speedRate.erase(speedRate.begin() + num);
          rateBox.erase(rateBox.begin() + num);
          buttonRect.erase(buttonRect.begin() + num);
          cout << "erase, " << "size: " << pp.size() << endl;
     }else{
          cout << "side = 0" << endl;
          setButton.clear();
          motionBox.clear();
          isMoveMotionBox.clear();
          positionNum.clear();
          pp.clear();
          strMove.clear();
          speedRate.clear();
          rateBox.clear();
          buttonRect.clear();
     }
}

void ofApp::exit(){
     boxMake.liveSendOsc.setStop();
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
                    if(mode == 1){
                         eraseMoveBox(pp.size());
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
               boxMake.soundtruck(kind);
               break;
          case OF_KEY_RIGHT:
               if(kind > 0)
               kind--;
               boxMake.soundtruck(kind);
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
     if(key == 'd'){
          isDebug = !isDebug;
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
     
     if(rateBox.size() > 0){
          int num = rateBox.size()-1;
          if(rateBox[num].inside(x, y)){
               isMoveMotionBox[num] = false;
               float setY;
               setY = y > h*0.35 ? h*0.35 : (setY = y < h*0.1 ? h*0.1 : y);
               rateBox[num].setY(setY - rateBox[num].getWidth()/2);
               int sr = ofMap(setY, h*0.1, h*0.35, 1.0, 5.0);
               speedRate[num] = 1.0 / float(sr);
               cout << "rate: " << speedRate[num] << endl;
          }
     }
     
     if(!isCam && playAreaRect.inside(x, y)){
           if(tool == 0)polylineBrush[mode].mouseDragged(x, y, button);
     }
     
     
     
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     if(!isCam && playAreaRect.inside(x, y)){

          for(int i=0; i<buttonRect.size(); i++){
               if(buttonRect[i].inside(x, y)){
                    cout << "press" << endl;
                    eraseMoveBox(i);
                    polylineBrush[mode].erase(i);
                    inButton = true;
               }
          }
          if(!inButton){
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
                         positionNum.push_back(0);
                         strMove.push_back(true);
                         speedRate.push_back(0.5);
                         ofRectangle rateB;
                         rateB.set(w*0.96, h*0.225-w*0.01, w*0.02, w*0.02);
                         rateBox.push_back(rateB);
                    }
               }
               else if(tool == 1){
                    boxMake.plusModel(x, y, kind);
               }
          }
     }
     
     if(sSelectBtm.inside(x, y)){
          isSoundSelect = !isSoundSelect;
     }
     
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
     
      if(!isCam && playAreaRect.inside(x, y)){
           if(mode == 1 && tool == 0 && !inButton){
//                if(x ==  setButton.back().x){
//                     eraseMoveBox(pp.size());
//                }else{
                ofVec2f prepp;
                ofRectangle br;
                if( polylineBrush[1].polyline.back().size() > 0){
                     prepp.x = polylineBrush[1].polyline.back().getVertices()[0].x;
                     prepp.y = polylineBrush[1].polyline.back().getVertices()[0].y;
                     br.set(polylineBrush[1].polyline[pp.size()].getVertices()[0], w*0.01, w*0.01);
                }
                     pp.push_back(prepp);
                     isMoveMotionBox.push_back(true);
                     buttonRect.push_back(br);
//                }
                 if(x ==  setButton.back().x){
                      eraseMoveBox(pp.size());
                      polylineBrush[mode].toRedo();
                 }
           }
      }
     
     if(rateBox.size() > 0){
          int num = rateBox.size()-1;
          if(rateBox[num].inside(x, y)){
               isMoveMotionBox[num] = true;
               pp[num].set(polylineBrush[1].polyline[num].getVertices()[positionNum[num]]);
          }
     }
     
     inButton = false;

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
