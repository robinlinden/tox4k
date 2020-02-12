#include "util.h"

#include <jni.h>
#include <tox/tox.h>

#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace tox4k;

namespace {
    const char *PROXY_TYPE_CLASS = "ltd/evilcorp/tox4k/ProxyType";
    const char *PROXY_TYPE_ARG = "Lltd/evilcorp/tox4k/ProxyType;";
    const char *LOG_LEVEL_ARG = "Lltd/evilcorp/tox4k/LogLevel;";
    const char *SAVEDATA_TYPE_CLASS = "ltd/evilcorp/tox4k/SavedataType";
    const char *SAVEDATA_TYPE_ARG= "Lltd/evilcorp/tox4k/SavedataType;";

    jobject make_java_log_level(JNIEnv *env, TOX_LOG_LEVEL log_level) {
        jclass enum_class = env->FindClass(PROXY_TYPE_CLASS);
        jfieldID enum_field;

        switch (log_level) {
            case TOX_LOG_LEVEL_TRACE:
                enum_field = env->GetStaticFieldID(enum_class, "TRACE", LOG_LEVEL_ARG);
                break;
            case TOX_LOG_LEVEL_DEBUG:
                enum_field = env->GetStaticFieldID(enum_class, "DEBUG", LOG_LEVEL_ARG);
                break;
            case TOX_LOG_LEVEL_INFO:
                enum_field = env->GetStaticFieldID(enum_class, "INFO", LOG_LEVEL_ARG);
                break;
            case TOX_LOG_LEVEL_WARNING:
                enum_field = env->GetStaticFieldID(enum_class, "WARNING", LOG_LEVEL_ARG);
                break;
            case TOX_LOG_LEVEL_ERROR:
                enum_field = env->GetStaticFieldID(enum_class, "ERROR", LOG_LEVEL_ARG);
                break;
            default:
                assert(false);
        }

        return env->GetStaticObjectField(enum_class, enum_field);
    }

    TOX_PROXY_TYPE make_c_proxy_type(JNIEnv *env, jobject proxy_type) {
        jclass enum_class = env->FindClass(PROXY_TYPE_CLASS);
        jmethodID get_name = env->GetMethodID(enum_class, "name", "()Ljava/lang/String;");
        const auto java_name = static_cast<jstring>(env->CallObjectMethod(proxy_type, get_name));
        const char *name = env->GetStringUTFChars(java_name, nullptr);

        TOX_PROXY_TYPE c_type;
        if (strcmp(name, "NONE") == 0) {
            c_type = TOX_PROXY_TYPE_NONE;
        } else if (strcmp(name, "HTTP") == 0) {
            c_type = TOX_PROXY_TYPE_HTTP;
        } else if (strcmp(name, "SOCKS5") == 0) {
            c_type = TOX_PROXY_TYPE_SOCKS5;
        } else {
            assert(false);
        }

        env->ReleaseStringUTFChars(java_name, name);
        return c_type;
    }

    jobject make_java_proxy_type(JNIEnv *env, TOX_PROXY_TYPE proxy_type) {
        jclass enum_class = env->FindClass(PROXY_TYPE_CLASS);
        jfieldID enum_field;

        switch (proxy_type) {
            case TOX_PROXY_TYPE_NONE:
                enum_field = env->GetStaticFieldID(enum_class, "NONE", PROXY_TYPE_ARG);
                break;
            case TOX_PROXY_TYPE_HTTP:
                enum_field = env->GetStaticFieldID(enum_class, "HTTP", PROXY_TYPE_ARG);
                break;
            case TOX_PROXY_TYPE_SOCKS5:
                enum_field = env->GetStaticFieldID(enum_class, "SOCKS5", PROXY_TYPE_ARG);
                break;
            default:
                assert(false);
        }

        return env->GetStaticObjectField(enum_class, enum_field);
    }

    TOX_SAVEDATA_TYPE make_c_savedata_type(JNIEnv *env, jobject savedata_type) {
        jclass enum_class = env->FindClass(SAVEDATA_TYPE_CLASS);
        jmethodID get_name = env->GetMethodID(enum_class, "name", "()Ljava/lang/String;");
        const auto java_name = static_cast<jstring>(env->CallObjectMethod(savedata_type, get_name));
        const char *name = env->GetStringUTFChars(java_name, nullptr);

        TOX_SAVEDATA_TYPE c_type;
        if (strcmp(name, "NONE") == 0) {
            c_type = TOX_SAVEDATA_TYPE_NONE;
        } else if (strcmp(name, "TOX_SAVE") == 0) {
            c_type = TOX_SAVEDATA_TYPE_TOX_SAVE;
        } else if (strcmp(name, "SECRET_KEY") == 0) {
            c_type = TOX_SAVEDATA_TYPE_SECRET_KEY;
        } else {
            assert(false);
        }

        env->ReleaseStringUTFChars(java_name, name);
        return c_type;
    }

    jobject make_java_savedata_type(JNIEnv *env, TOX_SAVEDATA_TYPE savedata_type) {
        jclass enum_class = env->FindClass(SAVEDATA_TYPE_CLASS);
        jfieldID enum_field;

        switch (savedata_type) {
            case TOX_SAVEDATA_TYPE_NONE:
                enum_field = env->GetStaticFieldID(enum_class, "NONE", SAVEDATA_TYPE_ARG);
                break;
            case TOX_SAVEDATA_TYPE_TOX_SAVE:
                enum_field = env->GetStaticFieldID(enum_class, "TOX_SAVE", SAVEDATA_TYPE_ARG);
                break;
            case TOX_SAVEDATA_TYPE_SECRET_KEY:
                enum_field = env->GetStaticFieldID(enum_class, "SECRET_KEY", SAVEDATA_TYPE_ARG);
                break;
            default:
                assert(false);
        }

        return env->GetStaticObjectField(enum_class, enum_field);
    }

    void tox_log_callback(Tox *tox, TOX_LOG_LEVEL level, const char *file, uint32_t line,
                          const char *func, const char *message, void *user_data) {
        const auto *container = reinterpret_cast<options_container *>(user_data);
        if (container->log_callback == nullptr) return;

        JNIEnv *env;
        container->jvm->AttachCurrentThread(&env, nullptr);

        jclass callback_class = env->GetObjectClass(container->log_callback);
        jmethodID callback_method = env->GetMethodID(
                callback_class,
                "onLog",
                "(JLltd/evilcorp/tox4k/LogLevel;Ljava/lang/String;Jjava/lang/String;java/lang/String;)V");

        jobject jlevel = make_java_log_level(env, level);

        jstring jfile = env->NewStringUTF(file);
        jstring jfunc = env->NewStringUTF(func);
        jstring jmessage = env->NewStringUTF(message);

        env->CallVoidMethod(container->log_callback, callback_method, reinterpret_cast<jlong>(tox),
                            jlevel, jfile, static_cast<jlong>(line), jfunc, jmessage);

        env->DeleteLocalRef(jmessage);
        env->DeleteLocalRef(jfunc);
        env->DeleteLocalRef(jfile);

        container->jvm->DetachCurrentThread();
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

// ProxyType
JNIEXPORT jobject JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetProxyType(JNIEnv *env, jobject, jlong options) {
    return make_java_proxy_type(env, tox_options_get_proxy_type(as_options(options)));
}

JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetProxyType(JNIEnv *env, jobject, jlong options,
                                                   jobject proxy_type) {
    tox_options_set_proxy_type(as_options(options), make_c_proxy_type(env, proxy_type));
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

// SavedataType
JNIEXPORT jobject JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetSavedataType(JNIEnv *env, jobject, jlong options) {
    return make_java_savedata_type(env, tox_options_get_savedata_type(as_options(options)));
}

JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetSavedataType(JNIEnv *env, jobject, jlong options,
                                                   jobject savedata_type) {
    tox_options_set_savedata_type(as_options(options), make_c_savedata_type(env, savedata_type));
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

// LogCallback
JNIEXPORT jobject JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsGetLogCallback(JNIEnv *, jobject, jlong options) {
    return as_container(options)->log_callback;
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsSetLogCallback(JNIEnv *env, jobject, jlong options,
                                                     jobject callback) {
    if (as_container(options)->log_callback != nullptr) env->DeleteGlobalRef(callback);
    as_container(options)->log_callback = env->NewGlobalRef(callback);
}

// Default
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsDefault(JNIEnv *, jobject, jlong options) {
    tox_options_default(as_options(options));
}

// Lifecycle
JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsNew(JNIEnv *env, jobject) {
    auto *c = new options_container;
    env->GetJavaVM(&c->jvm);
    tox_options_set_log_callback(c->options, tox_log_callback);
    return as_jlong(c);
}
JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_optionsFree(JNIEnv *, jobject, jlong options) {
    delete as_container(options);
}

}
