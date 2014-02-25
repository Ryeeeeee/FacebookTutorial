#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HelloWorldScene.h"
#include "FacebookInterface.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
const char* FBJavaFriendClassName = "org/cocos/fbtutorial/FacebookPickFriendPlugin";
const char* FBJavaLoginClassName = "org/cocos/fbtutorial/FacebookConnectPlugin";
const char* FBJavaPostClassName = "org/cocos/fbtutorial/FacebookPostPlugin";
const char* FBJavaSendRequestsClassName = "org/cocos/fbtutorial/FacebookSendRequestsPlugin";
const char* FBJavaClassName = "org/cocos/fbtutorial/FacebookConnectPlugin";
extern "C"
{
    void Java_org_cocos_fbtutorial_FacebookConnectPlugin_nativeCallback(JNIEnv*  env, jobject thiz, jint cbIndex,jstring params)
    {
        
        if (params != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(params, 0);
        	std::string tstr(str);
			HelloWorld::CallFunctionName(cbIndex,tstr);
		}
		else
		{
			std::string tstr = "";
			HelloWorld::CallFunctionName(cbIndex,tstr);
		}
    }
};
void FacebookInterface::login(int cbIndex,const char* scope){
	
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaLoginClassName
                                                , "login"
                                                , "(ILjava/lang/String;)V"))
	{
		if (scope)
		{
			jstring jeventId = t.env->NewStringUTF(scope);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,jeventId);
			t.env->DeleteLocalRef(jeventId);
		}
		else
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,NULL);
		}
		t.env->DeleteLocalRef(t.classID);
	}
}

void FacebookInterface::logout(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaClassName
                                                , "logout"
                                                , "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}
}

const char* FacebookInterface::getStatus(int cbIndex){
	
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaClassName
                                                , "getStatus"
                                                , "(I)Ljava/lang/String;"))
	{
		jstring ret = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID,cbIndex));
        t.env->DeleteLocalRef(t.classID);
        const char* aStr = " ";
        aStr = t.env->GetStringUTFChars(ret, false);
        return aStr;
	}  
}

void FacebookInterface::pickFriend(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaFriendClassName
		, "pickFriend"
        , "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}
}

void FacebookInterface::postStatus(int cbIndex,const char* name,const char* caption,const char* description,const char* link,const char* picture){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaPostClassName
		, "postStatus"
		, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
	{
		CCLOG("ajhsdkjahdkjahkjsdhakjsdhajksd");
		if (name && caption && description && link && picture)
		{
			jstring nameId = t.env->NewStringUTF(name);
			jstring captionId = t.env->NewStringUTF(caption);
			jstring descriptionId = t.env->NewStringUTF(description);
			jstring linkId = t.env->NewStringUTF(link);
			jstring pictureId = t.env->NewStringUTF(picture);

			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,nameId,captionId,descriptionId,linkId,pictureId);
			t.env->DeleteLocalRef(nameId);
			t.env->DeleteLocalRef(captionId);
			t.env->DeleteLocalRef(descriptionId);
			t.env->DeleteLocalRef(linkId);
			t.env->DeleteLocalRef(pictureId);
		}
		else
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,NULL);
		}
		
		t.env->DeleteLocalRef(t.classID);
	}   
}

void FacebookInterface::sendRequests(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaSendRequestsClassName
		, "sendRequests"
		, "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}   
}
#endif
