#include <jni.h>
#include <sodium.h>

#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_ltd_evilcorp_tox4k_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++\n";
    hello.append(std::to_string(randombytes_random()));
    return env->NewStringUTF(hello.c_str());
}
