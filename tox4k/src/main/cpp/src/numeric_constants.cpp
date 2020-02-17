#include "util.h"

#include <jni.h>
#include <tox/tox.h>

extern "C" {

T4K(jlong, publicKeySize)(JNIEnv *, jobject) {
    return tox_public_key_size();
}
T4K(jlong, secretKeySize)(JNIEnv *, jobject) {
    return tox_secret_key_size();
}
T4K(jlong, conferenceUidSize)(JNIEnv *, jobject) {
    return tox_conference_uid_size();
}
T4K(jlong, conferenceIdSize)(JNIEnv *, jobject) {
    return tox_conference_id_size();
}
T4K(jlong, nospamSize)(JNIEnv *, jobject) {
    return tox_nospam_size();
}
T4K(jlong, addressSize)(JNIEnv *, jobject) {
    return tox_address_size();
}
T4K(jlong, maxNameLength)(JNIEnv *, jobject) {
    return tox_max_name_length();
}
T4K(jlong, maxStatusMessageLength)(JNIEnv *, jobject) {
    return tox_max_status_message_length();
}
T4K(jlong, maxFriendRequestLength)(JNIEnv *, jobject) {
    return tox_max_friend_request_length();
}
T4K(jlong, maxMessageLength)(JNIEnv *, jobject) {
    return tox_max_message_length();
}
T4K(jlong, maxCustomPacketSize)(JNIEnv *, jobject) {
    return tox_max_custom_packet_size();
}
T4K(jlong, hashLength)(JNIEnv *, jobject) {
    return tox_hash_length();
}
T4K(jlong, fileIdLength)(JNIEnv *, jobject) {
    return tox_file_id_length();
}
T4K(jlong, maxFilenameLength)(JNIEnv *, jobject) {
    return tox_max_filename_length();
}
T4K(jlong, maxHostnameLength)(JNIEnv *, jobject) {
    return tox_max_hostname_length();
}

}
