#include <jni.h>
#include <tox/tox.h>

extern "C" {

JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionMajor(JNIEnv *, jobject) {
    return tox_version_major();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionMinor(JNIEnv *, jobject) {
    return tox_version_minor();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionPatch(JNIEnv *, jobject) {
    return tox_version_patch();
}
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_versionIsCompatible(
        JNIEnv *, jobject,
        jlong major, jlong minor, jlong patch) {
    if (major < 0 || minor < 0 || patch < 0) return static_cast<jboolean>(false);
    return static_cast<jboolean>(tox_version_is_compatible(
            static_cast<uint32_t>(major),
            static_cast<uint32_t>(minor),
            static_cast<uint32_t>(patch)));
}

}
