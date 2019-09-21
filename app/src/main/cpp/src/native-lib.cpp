#include <jni.h>
#include <tox/tox.h>

extern "C" {

JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionMajor(JNIEnv *env, jobject) {
    return tox_version_major();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionMinor(JNIEnv *env, jobject) {
    return tox_version_minor();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionPatch(JNIEnv *env, jobject) {
    return tox_version_patch();
}

}
