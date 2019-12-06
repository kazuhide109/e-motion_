//
//  boxMake.cpp
//  e-motion_
//
//  Created by LIFE_MAC_46 on 2019/09/19.
//

#include "boxMake.hpp"

void BoxMake::setup(){
     boxes.resize(3);
     
     liveSendOsc.setup();
     TruckClip.push_back(ofPoint(1,2));
     TruckClip.push_back(ofPoint(2,2));
     TruckClip.push_back(ofPoint(3,2));
     TruckClip.push_back(ofPoint(4,2));
     TruckClip.push_back(ofPoint(5,2));
     TruckClip.push_back(ofPoint(6,2));
     TruckClip.push_back(ofPoint(7,2));
     TruckClip.push_back(ofPoint(8,2));
     TruckClip.push_back(ofPoint(9,2));
     TruckClip.push_back(ofPoint(10,2));
     TruckClip.push_back(ofPoint(11,2));
     TruckClip.push_back(ofPoint(12,2));
     TruckClip.push_back(ofPoint(13,2));
     
     model.resize(10);
     isPlayClip.resize(soundNum);
     
     loadModel.resize(10);
     loadModel[0].loadModel("deer_col.obj", false);
     loadModel[0].setScale(0.1, 0.1, 0.1);
     loadModel[1].loadModel("cat_col.obj", false);
     loadModel[1].setScale(0.1, 0.1, 0.1);
     loadModel[2].loadModel("lowpolytree_col.obj", false);
     loadModel[2].setScale(0.15, 0.15, 0.15);
     loadModel[3].loadModel("MapleTreeStem_col.obj", false);
     loadModel[3].setScale(0.16, 0.16, 0.16);
     loadModel[4].loadModel("cow_col.obj", false);
     loadModel[4].setScale(0.1, 0.1, 0.1);
     loadModel[5].loadModel("Lamp_col.obj", false);
     loadModel[5].setScale(0.1, 0.1, 0.1);
     loadModel[6].loadModel("wolf_col.obj", false);
     loadModel[6].setScale(0.1, 0.1, 0.1);
     loadModel[7].loadModel("deer_col.obj", false);
     loadModel[7].setScale(0.16, 0.16, 0.16);
     loadModel[8].loadModel("Cactus_col.obj", false); //
     loadModel[8].setScale(0.1, 0.1, 0.1);
     loadModel[9].loadModel("Pig_col.obj", false); //
     loadModel[9].setScale(0.1, 0.1, 0.1);
}

void BoxMake::update(int kind, ofRectangle rect){
     if(kind < 3){
          for(auto cp : boxes[kind]){
               if(rect.inside(cp.getX()+rect.getWidth()/2, cp.getY()+rect.getWidth()/2)){
                    if(isPlayClip[kind]){
                         liveSendOsc.setTruckClip(TruckClip[kind].x, TruckClip[kind].y);
                         isPlayClip[kind] = false;
                    }
               }else{
                    isPlayClip[kind] = true;
                    cout << "IN" << endl;
               }
          }
     }else{
          for(auto cp : model[kind-3]){
               if(rect.inside(cp.getPosition().x + rect.getWidth()/2, cp.getPosition().y + rect.getWidth()/2)){
                    if(isPlayClip[kind]){
                         liveSendOsc.setTruckClip(TruckClip[kind].x, TruckClip[kind].y);
                         isPlayClip[kind] = false;
                    }
               }else{
                    isPlayClip[kind] = true;
               }
          }
     }
     
}

void BoxMake::draw(int kind, bool isCam){
      if(kind < 3){
           for(auto box : boxes[kind]){
                box.draw();
           }
      }else{
           for(auto box2 : model[kind-3]){
                if(!isCam) box2.setRotation(0, 90, 1, 0, 0);
                box2.drawFaces();
           }
      }
     
//     model.drawFaces();
//     model.drawWireframe();
}

void BoxMake::drawSingle(int x, int y, int kind){
     if(kind < 3){
          ofBoxPrimitive box;
          box.setPosition(x, y, 500);
          box.rotate(45, 1, 1, 0);
          box.set(50, 50, 50);
          box.draw();
     }
     else{
          loadModel[kind-3].setPosition(x, y, 500);
//          loadModel[kind-3].setRotation(0, 90, 0, 1, 0);
          loadModel[kind-3].setRotation(0, -45, 0, 1, 0);
          loadModel[kind-3].drawFaces();
     }
     
}

void BoxMake::reDo(int kind){
      if(kind < 3){
           if(boxes[kind].size() > 0)
           boxes[kind].pop_back();
      }else{
           if(model[kind-3].size() > 0)
           model[kind-3].pop_back();
      }
}

void BoxMake::plusModel(int x, int y, int kind){
     if(kind < 3){
          ofBoxPrimitive box;
          box.setPosition(x, y, 0);
          box.set(20, 20, 20);
          boxes[kind].push_back(box);
          cout << "boxNum:" << boxes[kind].size() << endl;
     }
     else{
          loadModel[kind-3].setPosition(x, y, 0);
          loadModel[kind-3].setRotation(0, -90, 1, 0, 0);
          model[kind-3].push_back(loadModel[kind-3]);
          cout << "boxNum:" <<  model[kind-3].size() << endl;
     }
     
     liveSendOsc.setTruckClip(TruckClip[kind].x, TruckClip[kind].y);
}

void BoxMake::soundtruck(int kind){
     liveSendOsc.setTruckClip(TruckClip[kind].x, TruckClip[kind].y);
}
