#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    cocos2d::CCLabelTTF * statusLabel;
    
    static bool isCallBack;
    
    static int  pressedButtonNum;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    
    static void CallFunctionName(int cbIndex,std::string tstr);
    
    void FacebookCallback(float dt);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
