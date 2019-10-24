#include <jni.h>
#include <tox/tox.h>

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace {
    struct options_container {
        options_container() = default;

        ~options_container() {
            tox_options_free(options);
            free(save_data);
            free(proxy_host);
        }

        Tox_Options *const options{tox_options_new(nullptr)};
        uint8_t *save_data{nullptr};
        char *proxy_host{nullptr};
    };

    inline auto as_options(jlong options) -> Tox_Options * {
        return reinterpret_cast<options_container *>(options)->options;
    }

    inline auto as_container(jlong options) -> options_container * {
        return reinterpret_cast<options_container *>(options);
    }
}

extern "C" {

// Ipv6
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetIpv6Enabled(JNIEnv *, jobject, jlong options) {
    return static_cast<jboolean>(tox_options_get_ipv6_enabled(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetIpv6Enabled(JNIEnv *, jobject, jlong options,
                                                     jboolean enabled) {
    tox_options_set_ipv6_enabled(as_options(options), enabled);
}

// Udp
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetUdpEnabled(JNIEnv *, jobject, jlong options) {
    return static_cast<jboolean>(tox_options_get_udp_enabled(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetUdpEnabled(JNIEnv *, jobject, jlong options,
                                                    jboolean enabled) {
    tox_options_set_udp_enabled(as_options(options), enabled);
}

// LocalDiscovery
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetLocalDiscoveryEnabled(JNIEnv *, jobject, jlong options) {
    return static_cast<jboolean>(tox_options_get_local_discovery_enabled(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetLocalDiscoveryEnabled(JNIEnv *, jobject, jlong options,
                                                               jboolean enabled) {
    tox_options_set_local_discovery_enabled(as_options(options), enabled);
}

// ProxyHost
JNIEXPORT jstring JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetProxyHost(JNIEnv *env, jobject, jlong options) {
    return env->NewStringUTF(tox_options_get_proxy_host(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetProxyHost(JNIEnv *env, jobject, jlong options,
                                                   jstring proxyHost) {
    const char *asChars = env->GetStringUTFChars(proxyHost, nullptr);

    as_container(options)->proxy_host = strdup(asChars);
    tox_options_set_proxy_host(as_options(options), as_container(options)->proxy_host);

    env->ReleaseStringUTFChars(proxyHost, asChars);
}

// ProxyPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetProxyPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_proxy_port(as_options(options));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetProxyPort(JNIEnv *, jobject, jlong options, jint port) {
    if (port < 0) return;
    tox_options_set_proxy_port(as_options(options), static_cast<uint16_t>(port));
}

// StartPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetStartPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_start_port(as_options(options));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetStartPort(JNIEnv *, jobject, jlong options, jint port) {
    if (port < 0) return;
    tox_options_set_start_port(as_options(options), static_cast<uint16_t>(port));
}

// EndPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetEndPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_end_port(as_options(options));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetEndPort(JNIEnv *, jobject, jlong options, jint port) {
    if (port < 0) return;
    tox_options_set_end_port(as_options(options), static_cast<uint16_t>(port));
}

// TcpPort
JNIEXPORT jint JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetTcpPort(JNIEnv *, jobject, jlong options) {
    return tox_options_get_tcp_port(as_options(options));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetTcpPort(JNIEnv *, jobject, jlong options, jint port) {
    if (port < 0) return;
    tox_options_set_tcp_port(as_options(options), static_cast<uint16_t>(port));
}

// HolePunching
JNIEXPORT jboolean JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetHolePunchingEnabled(JNIEnv *, jobject, jlong options) {
    return static_cast<jboolean>(tox_options_get_hole_punching_enabled(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetHolePunchingEnabled(JNIEnv *, jobject, jlong options,
                                                             jboolean enabled) {
    tox_options_set_hole_punching_enabled(as_options(options), enabled);
}

// SavedataData
JNIEXPORT jbyteArray JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetSavedataData(JNIEnv *env, jobject, jlong options) {
    const auto *real_options = as_options(options);

    const auto *data = reinterpret_cast<const jbyte *>(tox_options_get_savedata_data(real_options));
    const jint size = static_cast<jint>(tox_options_get_savedata_length(real_options));

    jbyteArray savedata = env->NewByteArray(size);
    env->SetByteArrayRegion(savedata, 0, size, data);

    return savedata;
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetSavedataData(JNIEnv *env, jobject, jlong options,
                                                      jbyteArray save_data) {
    jsize length = env->GetArrayLength(save_data);
    assert(length >= 0);

    options_container *c = as_container(options);
    c->save_data = static_cast<uint8_t *>(malloc(static_cast<size_t>(length)));
    env->GetByteArrayRegion(save_data, 0, length, reinterpret_cast<jbyte *>(c->save_data));

    tox_options_set_savedata_data(as_options(options), c->save_data, static_cast<uint32_t>(length));
}

// SavedataLength
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetSavedataLength(JNIEnv *, jobject, jlong options) {
    return static_cast<jlong>(tox_options_get_savedata_length(as_options(options)));
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetSavedataLength(JNIEnv *, jobject, jlong options,
                                                        jlong length) {
    assert(length >= 0);
    tox_options_set_savedata_length(as_options(options), static_cast<uint32_t>(length));
}

// Default
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsDefault(JNIEnv *, jobject, jlong options) {
    tox_options_default(as_options(options));
}

// Lifecycle
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsNew(JNIEnv *, jobject) {
    return reinterpret_cast<jlong>(new options_container);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsFree(JNIEnv *, jobject, jlong options) {
    delete as_container(options);
}

}
