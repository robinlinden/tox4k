#pragma once

#include <jni.h>
#include <tox/tox.h>

#include <cstdint>
#include <cstdlib>

#define T4K(rettype, name) extern "C" rettype JNIEXPORT JNICALL \
    Java_ltd_evilcorp_tox4k_ToxJni_##name

namespace tox4k {
    struct options_container {
        options_container() = default;

        ~options_container() {
            tox_options_free(options);
            free(save_data);
            free(proxy_host);
        }

        JavaVM *jvm{nullptr};

        Tox_Options *const options{tox_options_new(nullptr)};
        uint8_t *save_data{nullptr};
        char *proxy_host{nullptr};
        jobject log_callback{nullptr}; // TODO(robinlinden): Move callbacks into dedicated class.
    };

    inline auto as_tox(jlong tox) -> Tox * {
        return reinterpret_cast<Tox *>(tox);
    }

    inline auto as_options(jlong c) -> Tox_Options * {
        return reinterpret_cast<options_container *>(c)->options;
    }

    inline auto as_container(jlong c) -> options_container * {
        return reinterpret_cast<options_container *>(c);
    }

    inline auto as_jlong(const options_container *c) -> jlong {
        static_assert(sizeof(intptr_t) <= sizeof(jlong));
        return reinterpret_cast<intptr_t>(c);
    }

    inline auto as_jlong(const Tox *t) -> jlong {
        static_assert(sizeof(intptr_t) <= sizeof(jlong));
        return reinterpret_cast<intptr_t>(t);
    }
}
