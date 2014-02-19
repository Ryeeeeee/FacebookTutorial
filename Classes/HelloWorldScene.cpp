#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "FacebookInterface.h"
#endif

USING_NS_CC;

using namespace std;

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
    
    CCMenu* pMenu = CCMenu::create(NULL);
    pMenu->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(pMenu, 1);
    
    
    vector<string> menuVect;
    menuVect.push_back("login");
    menuVect.push_back("logout");
    menuVect.push_back("getStatus");
    
    
    for (int i = 0; i<menuVect.size(); i++)
    {
        CCMenuItemFont * ItemFont = CCMenuItemFont::create(menuVect[i].c_str(), this, menu_selector(HelloWorld::menuCloseCallback));
        ItemFont->setFontSize(100);
        ItemFont->setTag(i);
        pMenu->addChild(ItemFont);
    }
    pMenu->alignItemsVerticallyWithPadding(30);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    if (0)
    {
        FacebookInterface::login(13, "publish_actions");
    }
    
#endif
}

void HelloWorld::CallFunctionName(int cbIndex,string tstr)
{
    CCLOG("%s",tstr.c_str());
}
