#include <jni.h>
#include <tox/tox.h>

#include <sstream>

extern "C" JNIEXPORT jstring JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::stringstream ss;
    ss << "Linked against c-toxcore " << tox_version_major() << "."
        << tox_version_minor() << "." << tox_version_patch();
    return env->NewStringUTF(ss.str().c_str());
}
