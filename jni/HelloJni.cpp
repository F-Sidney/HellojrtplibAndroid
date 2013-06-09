#include "cn_nickwar_MainActivity.h"
#include <string.h>
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtppacket.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "jrtplib3/rtpsourcedata.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include <stdlib.h>
#include <unistd.h>
//#include <pthread.h>
#include <android/log.h>
#include "RtpWatcher.h"

using namespace jrtplib;

static JavaVM *g_jvm = NULL;
static jobject g_jobj = NULL;

//uint16_t portbase=8000,destport=9000;
//std::string ipstr="192.168.1.102";
//uint32_t destip=inet_addr(ipstr.c_str());
//int status,i,num;
//
//RTPSession session;
//RTPSessionParams sessionparams;
//RTPUDPv4TransmissionParams transparams;
//RTPIPv4Address addr;
bool m_bExitApp = false;

static jmethodID rtpresultFromJNI = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	g_jvm = vm;
	return JNI_VERSION_1_4;
}

void threadworker(JNIEnv* env, jobject obj)
{
//	while(!m_bExitApp)
//	{
//		session.BeginDataAccess();
//
//		unsigned char *buff = NULL;
//		if (session.GotoFirstSourceWithData())
//		{
//			do
//			{
//				RTPPacket *pack;
//				while((pack = session.GetNextPacket()) !=NULL)
//				{
//					__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "got packet!\n");
//					//					char message[26];
//					//					sprintf(message, "got packet");
//					jstring messageString = env->NewStringUTF("got packet");
//					env->CallVoidMethod(obj, rtpresultFromJNI, messageString);
//
//					if (NULL != env->ExceptionOccurred()) {
//						//						break;
//						continue;
//					}
//					if (pack->GetPayloadLength()>0) {
//						buff = pack->GetPayloadData();
//						__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "packt data:%s",buff);
//					}
//					session.DeletePacket(pack);
//				}
//			}
//			while(session.GotoNextSourceWithData());
//		}
//
//		session.EndDataAccess();
//		//
//#ifndef RTP_SUPPORT_THREAD
//		status = sess.Poll();
//		if (status<0) {
//			session.Destroy();
//			return;
//		}
//#endif
//
//		RTPTime::Wait(RTPTime(0,5000));
//	}
//
//	session.Destroy();
//	return;
}

void *thread_fun(void *arg)
{
	JNIEnv *env;
	if (0 == g_jvm->AttachCurrentThread(&env, NULL))
	{
		threadworker(env, g_jobj);
		g_jvm->DetachCurrentThread();
	}

	return (void*) 1;
}

void Java_cn_nickwar_MainActivity_setJNIEnv(JNIEnv* env, jobject obj) {
	if (NULL == g_jobj) {
		g_jobj = env->NewGlobalRef(obj);

		if (NULL == g_jobj) {
			goto exit;
		}
	}

	if (NULL == rtpresultFromJNI) {
		jclass clazz = env->GetObjectClass(obj);

		rtpresultFromJNI = env->GetMethodID(clazz,
				"rtpresultFromJNI",
				"(Ljava/lang/String;)V");
	}

	if (NULL == rtpresultFromJNI) {
		jclass exceptionClazz = env->FindClass("java/lang/RuntimeException");
		env->ThrowNew(exceptionClazz, "Unable to find method onNativeMessage");
	}

	//	if (destip == INADDR_NONE) {
	//		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "Bad IP address specified");
	//	}
	//
	//	destip = ntohl(destip);
	//
	//	num = 40;
	//
	//	sessionparams.SetOwnTimestampUnit(1.0/10.0);
	//	sessionparams.SetAcceptOwnPackets(true);
	//
	//	transparams.SetPortbase(portbase);
	//
	//	addr.SetIP(destip);
	//	addr.SetPort(destport);

	exit:
	return;
}


void create_session()
{
//	status = session.Create(sessionparams,&transparams);
//
//	if (status<0) {
//		std::string tmp = "Create:";
//		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", (tmp+RTPGetErrorString(status)).c_str());
//	}
//	status = session.AddDestination(addr);
//	if (status<0) {
//		std::string tmp = "AddDestination:";
//		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", (tmp+RTPGetErrorString(status)).c_str());
//	}
}

JNIEXPORT jstring JNICALL Java_cn_nickwar_MainActivity_stringFromJni
(JNIEnv *env, jobject obj)
{
	//	pthread_t pt;
	//	m_bExitApp = false;
	//	create_session();

	//	pthread_create(&pt, NULL, &thread_fun, (void *)1);
	return (env)->NewStringUTF("succeed!!");
}

void Java_cn_nickwar_MainActivity_exit_1rtp(JNIEnv* env, jobject obj) {
	Java_cn_nickwar_MainActivity_stop_1rtp(env, obj);
	if (NULL != g_jobj) {
		env->DeleteGlobalRef(g_jobj);
		g_jobj = NULL;
	}
}

void Java_cn_nickwar_MainActivity_stop_1rtp(JNIEnv* env, jobject ojb) {
	m_bExitApp = true;
}

void Java_cn_nickwar_MainActivity_nativeWorker(JNIEnv* env, jobject obj) {
	uint16_t portbase=8000,destport=9000;
	std::string ipstr="192.168.1.102";
	uint32_t destip=inet_addr(ipstr.c_str());
	int status,i,num;

	RTPSession session;
	RTPSessionParams sessionparams;
	RTPUDPv4TransmissionParams transparams;
	RTPIPv4Address addr;

	if (destip == INADDR_NONE) {
		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "Bad IP address specified");
	}

	destip = ntohl(destip);

	num = 40;

	sessionparams.SetOwnTimestampUnit(1.0/10.0);
	sessionparams.SetAcceptOwnPackets(true);

	transparams.SetPortbase(portbase);

	addr.SetIP(destip);
	addr.SetPort(destport);

	status = session.Create(sessionparams,&transparams);

	if (status<0) {
		std::string tmp = "Create:";
		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", (tmp+RTPGetErrorString(status)).c_str());
	}
	status = session.AddDestination(addr);
	if (status<0) {
		std::string tmp = "AddDestination:";
		__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", (tmp+RTPGetErrorString(status)).c_str());
	}

	while(!m_bExitApp)
	{
		session.BeginDataAccess();

		unsigned char *buff = NULL;
		if (session.GotoFirstSourceWithData())
		{
			do
			{
				RTPPacket *pack;
				while((pack = session.GetNextPacket()) !=NULL)
				{
					__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "got packet!\n");
					char message[26];
					sprintf(message, "got packet");
					jstring messageString = env->NewStringUTF(message);
					env->CallVoidMethod(obj, rtpresultFromJNI, messageString);

					if (NULL != env->ExceptionOccurred()) {
						//						break;
						continue;
					}
					if (pack->GetPayloadLength()>0) {
						buff = pack->GetPayloadData();
						__android_log_print(ANDROID_LOG_DEBUG, "pspm.native", "packt data:%s",buff);
					}
					session.DeletePacket(pack);
				}
			}
			while(session.GotoNextSourceWithData());
		}

		session.EndDataAccess();
		//
#ifndef RTP_SUPPORT_THREAD
		status = sess.Poll();
		if (status<0) {
			session.Destroy();
			return;
		}
#endif

		RTPTime::Wait(RTPTime(0,5000));
	}

	session.Destroy();
	return;
}
