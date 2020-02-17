#include "util.h"

#include <jni.h>
#include <tox/tox.h>

extern "C" {

T4K(jlong, versionMajor)(JNIEnv *, jobject) {
    return tox_version_major();
}
T4K(jlong, versionMinor)(JNIEnv *, jobject) {
    return tox_version_minor();
}
T4K(jlong, versionPatch)(JNIEnv *, jobject) {
    return tox_version_patch();
}
T4K(jboolean, versionIsCompatible)(JNIEnv *, jobject, jlong major, jlong minor, jlong patch) {
    if (major < 0 || minor < 0 || patch < 0) return static_cast<jboolean>(false);
    return static_cast<jboolean>(tox_version_is_compatible(
            static_cast<uint32_t>(major),
            static_cast<uint32_t>(minor),
            static_cast<uint32_t>(patch)));
}

}
