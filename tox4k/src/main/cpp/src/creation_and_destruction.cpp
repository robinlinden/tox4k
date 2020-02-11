#include "util.h"

#include <jni.h>
#include <tox/tox.h>

#include <stdexcept>

namespace {
    void throw_exception(JNIEnv *const env, const char *const message) {
        env->ThrowNew(env->FindClass("java/lang/Exception"), message);
    }
}

extern "C" {

JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_toxNew(JNIEnv *const env, jobject, jlong c_handle) {
    auto *const c = tox4k::as_container(c_handle);

    TOX_ERR_NEW err{TOX_ERR_NEW_OK};
    Tox *tox = tox_new(c ? c->options : nullptr, &err);
    switch (err) {
        case TOX_ERR_NEW_NULL:
            throw_exception(env, "null");
            return 0;
        case TOX_ERR_NEW_MALLOC:
            throw_exception(env, "malloc");
            return 0;
        case TOX_ERR_NEW_PORT_ALLOC:
            throw_exception(env, "port alloc");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_TYPE:
            throw_exception(env, "proxy bad type");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_HOST:
            throw_exception(env, "proxy bad host");
            return 0;
        case TOX_ERR_NEW_PROXY_BAD_PORT:
            throw_exception(env, "proxy bad port");
            return 0;
        case TOX_ERR_NEW_PROXY_NOT_FOUND:
            throw_exception(env, "proxy not found");
            return 0;
        case TOX_ERR_NEW_LOAD_ENCRYPTED:
            throw_exception(env, "load encrypted");
            return 0;
        case TOX_ERR_NEW_LOAD_BAD_FORMAT:
            throw_exception(env, "load bad format");
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
