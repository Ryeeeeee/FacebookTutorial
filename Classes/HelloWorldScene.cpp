#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "FacebookInterface.h"
#endif

USING_NS_CC;

using namespace std;


bool HelloWorld::isCallBack = false;
int  HelloWorld::pressedButtonNum = -1;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    
    statusLabel = CCLabelTTF::create("LogIn", "Arial", 100);
    statusLabel->setColor(ccBLUE);
    statusLabel->setPosition(ccp(origin.x + statusLabel->getContentSize().width/2,
                            origin.y + visibleSize.height - statusLabel->getContentSize().height));
    
    this->addChild(statusLabel, 1);
    
    CCMenu* pMenu = CCMenu::create(NULL);
    pMenu->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(pMenu, 1);
    
    // add Facebook1
    vector<string> menuVect;
    menuVect.push_back("login");
    menuVect.push_back("logout");
    menuVect.push_back("getStatus");
    menuVect.push_back("post");
    menuVect.push_back("pickFriend");
    menuVect.push_back("sendRequests");
    
    for (int i = 0; i<menuVect.size(); i++)
    {
        CCMenuItemFont * ItemFont = CCMenuItemFont::create(menuVect[i].c_str(), this, menu_selector(HelloWorld::menuCloseCallback));
        ItemFont->setFontSize(30);
        ItemFont->setTag(i);
        pMenu->addChild(ItemFont);
    }
    
    pMenu->alignItemsVerticallyWithPadding(30);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HelloWorld::FacebookCallback), this, 1.0, false);

    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCMenuItemFont * ItemFont =  (CCMenuItemFont *) pSender;
    
    HelloWorld::pressedButtonNum = ItemFont->getTag();
    
    switch (HelloWorld::pressedButtonNum)
    {
        case 0:
        {
            FacebookInterface::login(0, "login");
        }
        break;
        // add Facebook2
        case 1:
        {
            FacebookInterface::logout(1);
        }
        break;
        case 3:
            FacebookInterface::postStatus(3);
            break;
        case 4:
            FacebookInterface::pickFriend(4);
            break;
        case 5:
            FacebookInterface::sendRequests(5);
        break;
        default:
        break;
    }
#endif
}

void HelloWorld::CallFunctionName(int cbIndex,string tstr)
{
    isCallBack = true;
    HelloWorld::pressedButtonNum = cbIndex;
   // CCLOG("%s",tstr.c_str());
}
void HelloWorld::FacebookCallback(float dt)
{
    if (!isCallBack)
    {
        return;
    }
    switch (HelloWorld::pressedButtonNum)
    {
        // add Facebook3
        case 0:
        {
            statusLabel->setString("logout");
        }
        break;
        
        default:
        break;
    }
}


