package org.cocos.fbtutorial;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.android.AsyncFacebookRunner;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.FacebookDialog.PendingCall;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;

public class FacebookPostPlugin {
	private static final String TAG = "FacebookPostPlugin";
	private static FacebookPostPlugin instance;
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback statusCallback = new SessionStatusCallback();
	private Activity activity;
	private Handler handler;

	static public String name = null;
	static public String caption = null;
	static public String description = null;
	static public String link = null;
	static public String picture = null;

	
	
	public FacebookPostPlugin(Activity activity) 
	{
		this.activity = activity;
		instance = this;
		uiHelper = new UiLifecycleHelper(activity, statusCallback);
		handler = new Handler()
		{
			@Override
			public void handleMessage(Message msg) 
			{
				super.handleMessage(msg);
				switch(msg.what)
				{
				case 1:
					postStatus_();
					break;
				default:
					break;
				}
			}
		};
	}

	public static void postStatus(int cbIndex,String aName,String aCaption,String aDescription,String aLink,String aPicture)
	{
		name = aName;
		caption = aCaption;
		description = aDescription;
		link = aLink;
		picture = aPicture;
		
		Message message = Message.obtain();
		message.what = 1;
		instance.handler.sendMessage(message);
		//instance.postStatus_();
	}

	public void postStatus_() {
		
		if (FacebookDialog.canPresentShareDialog(
				activity.getApplicationContext(),
				FacebookDialog.ShareDialogFeature.SHARE_DIALOG)) {
			Log.i(TAG, "canPresent");
			// Publish the post using the Share Dialog
			FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(
					activity)
					.setLink("https://developers.facebook.com/android").build();
			uiHelper.trackPendingDialogCall(shareDialog.present());

		} else {
			// Fallback. For example, publish the post using the Feed Dialog
			Log.i(TAG, "webdialog");
			publishFeedDialog();
		}

	}

	private void publishFeedDialog() {
		Bundle params = new Bundle();

		Log.i("name", name);
		Log.i("caption",caption);
		Log.i("description",description);
		Log.i("link",link);
		Log.i("picture",picture);
		
		params.putString("name", name);
		params.putString("caption",caption);
		params.putString("description",description);
		params.putString("link",link);
		params.putString("picture",picture);
		
		/*
		params.putString("name", "Facebook SDK for Android");
		params.putString("caption",
				"Build great social apps and get more installs.");
		
		params.putString(
				"description",
				"The Facebook SDK for Android makes it easier and faster to develop Facebook integrated Android apps.");
		params.putString("link", "https://developers.facebook.com/android");
		
		
		params.putString("picture",	"//https://raw.github.com/fbsamples/ios-3.x-howtos/master/Images/iossdk_logo.png");
*/
		
		/*
		 params.putString("method", "photos.upload");
		 
		byte[] data = null;
		
		AssetManager am = activity.getAssets();
		try 
		{
			InputStream is = am.open("CloseSelected.png");
			Bitmap bi=BitmapFactory.decodeStream(is);
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			bi.compress(Bitmap.CompressFormat.JPEG, 100, baos);
			data = baos.toByteArray();
			params.putByteArray("picture", data);
			Log.i("10000","innnnnnnn");
		} 
		catch (IOException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	*/

		WebDialog feedDialog = (new WebDialog.FeedDialogBuilder(activity,
				Session.getActiveSession(), params)).setOnCompleteListener(
				new OnCompleteListener() {

					@Override
					public void onComplete(Bundle values,
							FacebookException error) {
						if (error == null) {
							// When the story is posted, echo the success
							// and the post Id.
							final String postId = values.getString("post_id");
							if (postId != null) {
								Toast.makeText(activity,
										"Posted story, id: " + postId,
										Toast.LENGTH_SHORT).show();
							} else {
								// User clicked the Cancel button
								Toast.makeText(
										activity.getApplicationContext(),
										"Publish cancelled", Toast.LENGTH_SHORT)
										.show();
							}
						} else if (error instanceof FacebookOperationCanceledException) {
							// User clicked the "x" button
							Toast.makeText(activity.getApplicationContext(),
									"Publish cancelled", Toast.LENGTH_SHORT)
									.show();
						} else {
							// Generic, ex: network error
							Toast.makeText(activity.getApplicationContext(),
									"Error posting story", Toast.LENGTH_SHORT)
									.show();
						}
					}

				}).build();
		feedDialog.show();
	}

	private class SessionStatusCallback implements Session.StatusCallback,
			FacebookDialog.Callback {
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			// Respond to session state changes, ex: updating the view
			onSessionStateChange(session, state, exception);
		}

		@Override
		public void onComplete(PendingCall pendingCall, Bundle data) {
			// TODO Auto-generated method stub
			Log.i(TAG, "ShareDialog onComplete");
			boolean didCancel = FacebookDialog.getNativeDialogDidComplete(data);
			String completionGesture = FacebookDialog
					.getNativeDialogCompletionGesture(data);
			String postId = FacebookDialog.getNativeDialogPostId(data);
			Log.i(TAG, "didCancel:" + didCancel + "completionGesture:"
					+ completionGesture + "postId:" + postId);
		}

		@Override
		public void onError(PendingCall pendingCall, Exception error,
				Bundle data) {
			// TODO Auto-generated method stub
			Log.i(TAG, "ShareDialog onError");
			boolean didCancel = FacebookDialog.getNativeDialogDidComplete(data);
			String completionGesture = FacebookDialog
					.getNativeDialogCompletionGesture(data);
			String postId = FacebookDialog.getNativeDialogPostId(data);
			Log.i(TAG, "didCancel:" + didCancel + "completionGesture:"
					+ completionGesture + "postId:" + postId);

		}
	}

	private void onSessionStateChange(Session session, SessionState state,
			Exception exception) {
		if (state.isOpened()) {
			Log.i(TAG, "Logged in...");
		} else if (state.isClosed()) {
			Log.i(TAG, "Logged out...");
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
		uiHelper.onActivityResult(requestCode, resultCode, data, dialogCallback);
	}

	public void onSaveInstanceState(Bundle outState) {
		uiHelper.onSaveInstanceState(outState);
	}

	public void onDestory() {
		uiHelper.onDestroy();
	}

	private FacebookDialog.Callback dialogCallback = new FacebookDialog.Callback() {
		@Override
		public void onError(FacebookDialog.PendingCall pendingCall,
				Exception error, Bundle data) {
			Log.d("HelloFacebook", String.format("Error: %s", error.toString()));
		}

		@Override
		public void onComplete(FacebookDialog.PendingCall pendingCall,
				Bundle data) {
			Log.d("HelloFacebook", "Success!");
		}
	};
}
