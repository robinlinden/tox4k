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


// Startup options

// Ipv6
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetIpv6Enabled(JNIEnv *, jobject, jlong options) {
    return tox_options_get_ipv6_enabled((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetIpv6Enabled(JNIEnv *, jobject, jlong options, jboolean enabled) {
    tox_options_set_ipv6_enabled((struct Tox_Options *)options, enabled);
}

// Udp
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetUdpEnabled(JNIEnv *, jobject, jlong options) {
    return tox_options_get_udp_enabled((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetUdpEnabled(JNIEnv *, jobject, jlong options, jboolean enabled) {
    tox_options_set_udp_enabled((struct Tox_Options *)options, enabled);
}

// LocalDiscovery
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetLocalDiscoveryEnabled(JNIEnv *, jobject, jlong options) {
    return tox_options_get_local_discovery_enabled((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetLocalDiscoveryEnabled(JNIEnv *, jobject, jlong options, jboolean enabled) {
    tox_options_set_local_discovery_enabled((struct Tox_Options *)options, enabled);
}

// ProxyHost
JNIEXPORT jstring JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetProxyHost(JNIEnv *env, jobject, jlong options) {
    return env->NewStringUTF(tox_options_get_proxy_host((const struct Tox_Options *)options));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetProxyHost(JNIEnv *env, jobject, jlong options, jstring proxyHost) {
    // TODO(robinlinden): Release this at some point.
    const char* asChars = env->GetStringUTFChars(proxyHost, nullptr);
    tox_options_set_proxy_host((struct Tox_Options *)options, asChars);
//    env->ReleaseStringUTFChars(proxyHost, asChars);
}

// ProxyPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetProxyPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_proxy_port((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetProxyPort(JNIEnv *, jobject, jlong options, jint port) {
    tox_options_set_proxy_port((struct Tox_Options *)options, port);
}

// StartPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetStartPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_start_port((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetStartPort(JNIEnv *, jobject, jlong options, jint port) {
    tox_options_set_start_port((struct Tox_Options *)options, port);
}

// EndPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetEndPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_end_port((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetEndPort(JNIEnv *, jobject, jlong options, jint port) {
    tox_options_set_end_port((struct Tox_Options *)options, port);
}

// TcpPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetTcpPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_tcp_port((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetTcpPort(JNIEnv *, jobject, jlong options, jint port) {
    tox_options_set_tcp_port((struct Tox_Options *)options, port);
}

// HolePunching
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetHolePunchingEnabled(JNIEnv *, jobject, jlong options) {
    return tox_options_get_hole_punching_enabled((const struct Tox_Options *)options);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetHolePunchingEnabled(JNIEnv *, jobject, jlong options, jboolean enabled) {
    tox_options_set_hole_punching_enabled((struct Tox_Options *)options, enabled);
}

// Default
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsDefault(JNIEnv *, jobject, jlong options) {
    tox_options_default((struct Tox_Options *)options);
}

// Lifecycle
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsNew(JNIEnv *, jobject) {
    return (jlong)tox_options_new(nullptr);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsFree(JNIEnv *, jobject, jlong options) {
    tox_options_free((struct Tox_Options *)options);
}

}
