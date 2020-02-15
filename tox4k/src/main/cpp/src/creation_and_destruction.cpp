#include "util.h"

#include <jni.h>
#include <tox/tox.h>

#include <stdexcept>

extern "C" {

JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_toxNew(JNIEnv *const env, jobject, jlong c_handle) {
    auto *const c = tox4k::as_container(c_handle);

    TOX_ERR_NEW err{TOX_ERR_NEW_OK};
    Tox *tox = tox_new(c ? c->options : nullptr, &err);
    switch (err) {
        case TOX_ERR_NEW_NULL:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewNullException"), "");
            return 0;
        case TOX_ERR_NEW_MALLOC:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewMallocException"), "");
            return 0;
        case TOX_ERR_NEW_PORT_ALLOC:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewPortAllocException"), "");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_TYPE:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewProxyBadTypeException"), "");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_HOST:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewProxyBadHostException"), "");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_PORT:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewProxyBadPortException"), "");
            return 0;
        case TOX_ERR_NEW_PROXY_NOT_FOUND:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewProxyNotFoundException"), "");
            return 0;
        case TOX_ERR_NEW_LOAD_ENCRYPTED:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewLoadEncryptedException"), "");
            return 0;
        case TOX_ERR_NEW_LOAD_BAD_FORMAT:
            env->ThrowNew(env->FindClass("ltd/evilcorp/tox4k/ToxNewLoadBadFormatException"), "");
            return 0;
        case TOX_ERR_NEW_OK:
            return tox4k::as_jlong(tox);
    }
}

JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_toxKill(JNIEnv *, jobject, jlong tox) {
    tox_kill(tox4k::as_tox(tox));
}

}
