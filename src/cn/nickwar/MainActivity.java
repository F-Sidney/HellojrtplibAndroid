package cn.nickwar;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	private TextView hello=null;
	private TextView mTvOutput = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		setJNIEnv();
		mTvOutput = (TextView)findViewById(R.id.output_text);
		((Button) findViewById(R.id.start_rtp)).setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				//				hello = (TextView)findViewById(R.string.helloTxt);
				//				hello.setText(stringFromJni());
				startThreads();
			}
		});

		((Button) findViewById(R.id.stop_rtp)).setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				stop_rtp();
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	private void fromJNI(int i)
	{
		Log.v("Java--->", ""+i);
	}

	private void rtpresultFromJNI(final String rtpdata)
	{
		runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				mTvOutput.append(rtpdata);
				mTvOutput.append("\n");
			}
		});
	}

	private void startThreads() {
		// We will be implementing this method as we
		// work through the chapter
		javaThreads();
//		posixThreads(threads, iterations);
	}
	/**
	 * Using Java based threads.
	 *
	 */
	private void javaThreads() {
		// Create a Java based thread for each worker
		Thread thread = new Thread() {
			public void run() {
				nativeWorker();
			}
		};
		thread.start();
	}

	public native String stringFromJni();
	public native void setJNIEnv();
	public native void stop_rtp();
	public native void exit_rtp();
	public native void nativeWorker();

	static {
		System.loadLibrary("HelloJni");
	}

	@Override
	protected void onDestroy() {
		exit_rtp();
		super.onDestroy();
	}
}
