#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HelloWorldScene.h"
#include "FacebookInterface.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

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
		, FBJavaClassName
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


std::string FacebookInterface::api(const char* graphPath,const char* method,const char* params,int cbIndex){
	std::string errorRet;
	/*
	JniMethodInfo t;
	

	if (JniHelper::getStaticMethodInfo(t
		, FBJavaClassName
		, "api"
		, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)Ljava/lang/String;"))
	{
		jstring jgraphPath = t.env->NewStringUTF(graphPath);
		jstring jmethod = NULL;
		if(method)
			jmethod = t.env->NewStringUTF(method);
		jstring jparams = NULL;
		if(params)
			jparams = t.env->NewStringUTF(params);
		
		jstring ret = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID, jgraphPath,jmethod,jparams,cbIndex));
		t.env->DeleteLocalRef(jgraphPath);
		if(method)
			t.env->DeleteLocalRef(jmethod);
		if(params)
			t.env->DeleteLocalRef(jparams);
		t.env->DeleteLocalRef(t.classID);

		if (ret != NULL)
			errorRet = JniHelper::jstring2string(ret);				
	} 
	*/

	return errorRet;
}

void FacebookInterface::ui(const char* params,int cbIndex){
	
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaClassName
		, "ui"
		, "(Ljava/lang/String;I)V"))
	{
		jstring jparams = t.env->NewStringUTF(params);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jparams,cbIndex);
		t.env->DeleteLocalRef(jparams);
		t.env->DeleteLocalRef(t.classID);
	}  

}

#endif
