#ifndef  __INTERFACE_FACEBOOK_H_
#define  __INTERFACE_FACEBOOK_H_

#include "string"

class FacebookInterface
{
public:
    //for callback
    static void callbackJs(int cbIndex, const char* params);
    
    static void login(int cbIndex,const char* scope);
	static void logout(int cbIndex);
    static const char* getStatus(int cbIndex);
    static void pickFriend(int cbIndex);
    static void postStatus(int cbIndex,const char* name,const char* caption,const char* description,const char* link,const char* picture);
    static void sendRequests(int cbIndex);
};
#endif  //__INTERFACE_FACEBOOK_H_
