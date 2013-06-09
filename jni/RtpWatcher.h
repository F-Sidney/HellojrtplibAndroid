#ifndef _RTP_WATCHER_H_
#define _RTP_WATCHER_H_

typedef struct{
	JavaVM* mJavaVM;

	//Methods
	jmethodID MethodOnReceiveDataString;

	pthread_t mThread;
	int32_t mState;
} RTPWatcher;

#endif
