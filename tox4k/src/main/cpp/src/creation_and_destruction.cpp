#include "util.h"

#include <jni.h>
#include <tox/tox.h>

#include <stdexcept>

extern "C" {

JNIEXPORT jlong JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_toxNew(JNIEnv *, jobject, jlong options) {
    auto *const c = tox4k::as_container(options);

    TOX_ERR_NEW err{TOX_ERR_NEW_OK};
    Tox *tox = tox_new(c ? c->options : nullptr, &err);
    switch (err) {
        case TOX_ERR_NEW_NULL:
            throw std::runtime_error("null");
        case TOX_ERR_NEW_MALLOC:
            throw std::runtime_error("malloc");
        case TOX_ERR_NEW_PORT_ALLOC:
            throw std::runtime_error("port alloc");
        case TOX_ERR_NEW_PROXY_BAD_TYPE:
            throw std::runtime_error("proxy bad type");
        case TOX_ERR_NEW_PROXY_BAD_HOST:
            throw std::runtime_error("proxy bad host");
        case TOX_ERR_NEW_PROXY_BAD_PORT:
            throw std::runtime_error("proxy bad port");
        case TOX_ERR_NEW_PROXY_NOT_FOUND:
            throw std::runtime_error("proxy not found");
        case TOX_ERR_NEW_LOAD_ENCRYPTED:
            throw std::runtime_error("load encrypted");
        case TOX_ERR_NEW_LOAD_BAD_FORMAT:
            throw std::runtime_error("load bad format");
        case TOX_ERR_NEW_OK:
            break;
    }

    return tox4k::as_jlong(tox);
}

JNIEXPORT void JNICALL
Java_ltd_evilcorp_tox4k_ToxJni_toxKill(JNIEnv *, jobject, jlong tox) {
    tox_kill(tox4k::as_tox(tox));
}

}
