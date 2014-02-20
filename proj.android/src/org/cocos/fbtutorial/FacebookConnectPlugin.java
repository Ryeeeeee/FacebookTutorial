package org.cocos.fbtutorial;

import java.util.Arrays;

import com.facebook.Request;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class FacebookConnectPlugin {
	private static final String TAG = "FacebookPlugin";
	private static FacebookConnectPlugin instance;
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback statusCallback = new SessionStatusCallback();
	private Activity activity;
	private static int callIndex;
	public FacebookConnectPlugin(Activity activity) {
		this.activity = activity;
		instance = this;
		uiHelper = new UiLifecycleHelper(activity, statusCallback);
	}

	public void onCreate(Bundle savedInstanceState) {
		uiHelper.onCreate(savedInstanceState);
	}

	public static void login(int cbIndex, String scope) {
		instance.login_();
		callIndex = cbIndex;
	}
	
	public void login_() {
		
		Session session = Session.getActiveSession();
		if (!session.isOpened() && !session.isClosed()) {
			session.openForRead(new Session.OpenRequest(activity).setPermissions(
					Arrays.asList("basic_info")).setCallback(statusCallback));
		} else {
			Session.openActiveSession(activity, true, statusCallback);
		}
	}
	public static void logout(int cbIndex) {
		instance.logout_();
		callIndex = cbIndex;
	}
	
	public void logout_() {
		 Session session = Session.getActiveSession();
	        if (!session.isClosed()) {
	            session.closeAndClearTokenInformation();
	        }
	}
	public static String getStatus(int cbIndex) {
		
		callIndex = cbIndex;
		
		return instance.getStatus_();
	}
	
	public String getStatus_() {
		
		Session session = Session.getActiveSession();
	
		if (session.getState().equals(SessionState.CREATED))
		{
			return "CREATED";
		}
		else if (session.getState().equals(SessionState.CREATED_TOKEN_LOADED))
		{
			return "CREATED_TOKEN_LOADED";
		}
		else if (session.getState().equals(SessionState.OPENING))
		{
			return "OPENING";
		}
		else if (session.getState().equals(SessionState.OPENED))
		{
			return "OPENED";
		}
		else if (session.getState().equals(SessionState.OPENED_TOKEN_UPDATED))
		{
			return "OPENED_TOKEN_UPDATED";
		}
		else if (session.getState().equals(SessionState.CLOSED_LOGIN_FAILED))
		{
			return "CLOSED_LOGIN_FAILED";
		}
		else if (session.getState().equals(SessionState.CLOSED))
		{
			return "CLOSED";
		}
		
		return "";
	}
	public void onResume() {
		// For scenarios where the main activity is launched and user
		// session is not null, the session state change notification
		// may not be triggered. Trigger it if it's open/closed.
		Session session = Session.getActiveSession();
		if (session != null && (session.isOpened() || session.isClosed())) {
			onSessionStateChange(session, session.getState(), null);
		}
		if(uiHelper == null){
			Log.i(TAG, "ddd");
		}
		uiHelper.onResume();
	}

	public void onPause() {
		uiHelper.onPause();
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		uiHelper.onActivityResult(requestCode, resultCode, data);
	}

	public void onSaveInstanceState(Bundle outState) {
		uiHelper.onSaveInstanceState(outState);
	}

	public void onDestory() {
		uiHelper.onDestroy();
	}

	private void onSessionStateChange(Session session, SessionState state,
			Exception exception) {
		if (state.isOpened()) {
			Log.i(TAG, "Logged in...");
		} else if (state.isClosed()) {
			Log.i(TAG, "Logged out...");
		}
	}
	private static native void nativeCallback(int cbIndex, String params);
	private class SessionStatusCallback implements Session.StatusCallback {
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			// Respond to session state changes, ex: updating the view
			onSessionStateChange(session, state, exception);
			
			nativeCallback(callIndex,"");
		}
	}
}
