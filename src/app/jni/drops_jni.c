#include <jni.h>
#include "drops.h"

JNIEXPORT jlong JNICALL
Java_theedg_es_DropsJNI_start(JNIEnv* env, jobject obj, jstring jdirectory) {
  const char* directory = (*env)->GetStringUTFChars(env, jdirectory, NULL);
  jlong drops = (jlong) drops_new(directory);
  (*env)->ReleaseStringUTFChars(env, jdirectory, directory);

  return drops;
}

JNIEXPORT void JNICALL
Java_theedg_es_DropsJNI_stop(JNIEnv* env, jobject obj, jlong jdrops) {
  drops_t* drops = (drops_t*) jdrops;
  drops_destroy(&drops);
}
