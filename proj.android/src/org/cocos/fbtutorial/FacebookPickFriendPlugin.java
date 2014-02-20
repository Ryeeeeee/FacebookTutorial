package org.cocos.fbtutorial;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;

public class FacebookPickFriendPlugin {
	private static final int PICK_FRIENDS_ACTIVITY = 1;
	private static final String TAG = "FacebookPlugin";
	private static FacebookPickFriendPlugin instance;
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback statusCallback = new SessionStatusCallback();
	private Activity activity;
	boolean pickFriendsWhenSessionOpened;

	public static void pickFriend(int cbIndex) {
		instance.pickFriend_();
	}

	public FacebookPickFriendPlugin(Activity activity) {
		this.activity = activity;
		instance = this;
		uiHelper = new UiLifecycleHelper(activity, statusCallback);
	}
	
	public void pickFriend_() {
		if (ensureOpenSession()) {
			Intent intent = new Intent(activity, PickFriendsActivity.class);
			// Note: The following line is optional, as multi-select behavior is
			// the default for
			// FriendPickerFragment. It is here to demonstrate how parameters
			// could be passed to the
			// friend picker if single-select functionality was desired, or if a
			// different user ID was
			// desired (for instance, to see friends of a friend).
			PickFriendsActivity.populateParameters(intent, null, true, true);
			activity.startActivityForResult(intent, PICK_FRIENDS_ACTIVITY);
		} else {
			pickFriendsWhenSessionOpened = true;
		}
	}

	private boolean ensureOpenSession() {
		if (Session.getActiveSession() == null
				|| !Session.getActiveSession().isOpened()) {
			Session.openActiveSession(activity, true, statusCallback);
			return false;
		}
		return true;
	}

	private class SessionStatusCallback implements Session.StatusCallback {
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			// Respond to session state changes, ex: updating the view
			onSessionStateChange(session, state, exception);
		}
	}

	private void onSessionStateChange(Session session, SessionState state,
			Exception exception) {
		if (state.isOpened()) {
			Log.i(TAG, "Logged in...");
		} else if (state.isClosed()) {
			Log.i(TAG, "Logged out...");
		}
		if (pickFriendsWhenSessionOpened && state.isOpened()) {
			pickFriendsWhenSessionOpened = false;
			pickFriend_();
		}
	}
	public void onCreate(Bundle savedInstanceState) {
		uiHelper.onCreate(savedInstanceState);
	}
	
	public void onResume() {
		// For scenarios where the main activity is launched and user
		// session is not null, the session state change notification
		// may not be triggered. Trigger it if it's open/closed.
		Session session = Session.getActiveSession();
		if (session != null && (session.isOpened() || session.isClosed())) {
			onSessionStateChange(session, session.getState(), null);
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

	/*
	 * -------------------------
	 * 
	 * @Override public void onActivityResult(int requestCode, int resultCode,
	 * Intent data) { switch (requestCode) { case PICK_FRIENDS_ACTIVITY:
	 * displaySelectedFriends(resultCode); break; default:
	 * Session.getActiveSession().onActivityResult(this, requestCode,
	 * resultCode, data); break; } } --------------------------------
	 */
}
