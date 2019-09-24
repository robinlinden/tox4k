#include <jni.h>
#include <tox/tox.h>

extern "C" {

// API version
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

// Numeric constants
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_publicKeySize(JNIEnv *, jobject) {
    return tox_public_key_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_secretKeySize(JNIEnv *, jobject) {
    return tox_secret_key_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_conferenceUidSize(JNIEnv *, jobject) {
    return tox_conference_uid_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_conferenceIdSize(JNIEnv *, jobject) {
    return tox_conference_id_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_nospamSize(JNIEnv *, jobject) {
    return tox_nospam_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_addressSize(JNIEnv *, jobject) {
    return tox_address_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxNameLength(JNIEnv *, jobject) {
    return tox_max_name_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxStatusMessageLength(JNIEnv *, jobject) {
    return tox_max_status_message_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxFriendRequestLength(JNIEnv *, jobject) {
    return tox_max_friend_request_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxMessageLength(JNIEnv *, jobject) {
    return tox_max_message_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxCustomPacketSize(JNIEnv *, jobject) {
    return tox_max_custom_packet_size();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_hashLength(JNIEnv *, jobject) {
    return tox_hash_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_fileIdLength(JNIEnv *, jobject) {
    return tox_file_id_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxFilenameLength(JNIEnv *, jobject) {
    return tox_max_filename_length();
}
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_maxHostnameLength(JNIEnv *, jobject) {
    return tox_max_hostname_length();
}

}
