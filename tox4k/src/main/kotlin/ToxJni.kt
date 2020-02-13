package ltd.evilcorp.tox4k

typealias ToxJniOptions = Long
typealias ToxHandle = Long

// Global enumerations
enum class UserStatus {
    NONE,
    AWAY,
    BUSY,
}
enum class MessageType {
    NORMAL,
    ACTION,
}

// Startup options
enum class ProxyType {
    NONE,
    HTTP,
    SOCKS5,
}
enum class SavedataType {
    NONE,
    TOX_SAVE,
    SECRET_KEY,
}
enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
}

class ToxJni {
    // Startup options
    interface ILogCallbackListener {
        fun onLog(tox: ToxHandle, level: LogLevel, file: String, line: Long, func: String, message: String)
    }

    companion object {
        // API version
        @JvmStatic external fun versionMajor(): Long
        @JvmStatic external fun versionMinor(): Long
        @JvmStatic external fun versionPatch(): Long
        @JvmStatic external fun versionIsCompatible(major: Long, minor: Long, patch: Long): Boolean

        // Numeric constants
        @JvmStatic external fun publicKeySize(): Long
        @JvmStatic external fun secretKeySize(): Long
        @JvmStatic external fun conferenceUidSize(): Long
        @JvmStatic external fun conferenceIdSize(): Long
        @JvmStatic external fun nospamSize(): Long
        @JvmStatic external fun addressSize(): Long
        @JvmStatic external fun maxNameLength(): Long
        @JvmStatic external fun maxStatusMessageLength(): Long
        @JvmStatic external fun maxFriendRequestLength(): Long
        @JvmStatic external fun maxMessageLength(): Long
        @JvmStatic external fun maxCustomPacketSize(): Long
        @JvmStatic external fun hashLength(): Long
        @JvmStatic external fun fileIdLength(): Long
        @JvmStatic external fun maxFilenameLength(): Long
        @JvmStatic external fun maxHostnameLength(): Long

        // Startup options
        @JvmStatic external fun optionsGetIpv6Enabled(options: ToxJniOptions): Boolean
        @JvmStatic external fun optionsSetIpv6Enabled(options: ToxJniOptions, enabled: Boolean)
        @JvmStatic external fun optionsGetUdpEnabled(options: ToxJniOptions): Boolean
        @JvmStatic external fun optionsSetUdpEnabled(options: ToxJniOptions, enabled: Boolean)
        @JvmStatic external fun optionsGetLocalDiscoveryEnabled(options: ToxJniOptions): Boolean
        @JvmStatic external fun optionsSetLocalDiscoveryEnabled(options: ToxJniOptions, enabled: Boolean)
        @JvmStatic external fun optionsGetProxyType(options: ToxJniOptions): ProxyType
        @JvmStatic external fun optionsSetProxyType(options: ToxJniOptions, proxyType: ProxyType)
        @JvmStatic external fun optionsGetProxyHost(options: ToxJniOptions): String
        @JvmStatic external fun optionsSetProxyHost(options: ToxJniOptions, proxyHost: String)
        @JvmStatic external fun optionsGetProxyPort(options: ToxJniOptions): Int
        @JvmStatic external fun optionsSetProxyPort(options: ToxJniOptions, port: Int)
        @JvmStatic external fun optionsGetStartPort(options: ToxJniOptions): Int
        @JvmStatic external fun optionsSetStartPort(options: ToxJniOptions, port: Int)
        @JvmStatic external fun optionsGetEndPort(options: ToxJniOptions): Int
        @JvmStatic external fun optionsSetEndPort(options: ToxJniOptions, port: Int)
        @JvmStatic external fun optionsGetTcpPort(options: ToxJniOptions): Int
        @JvmStatic external fun optionsSetTcpPort(options: ToxJniOptions, port: Int)
        @JvmStatic external fun optionsGetHolePunchingEnabled(options: ToxJniOptions): Boolean
        @JvmStatic external fun optionsSetHolePunchingEnabled(options: ToxJniOptions, enabled: Boolean)
        @JvmStatic external fun optionsGetSavedataType(options: ToxJniOptions): SavedataType
        @JvmStatic external fun optionsSetSavedataType(options: ToxJniOptions, type: SavedataType)
        @JvmStatic external fun optionsGetSavedataData(options: ToxJniOptions): ByteArray
        @JvmStatic external fun optionsSetSavedataData(options: ToxJniOptions, data: ByteArray)
        @JvmStatic external fun optionsGetSavedataLength(options: ToxJniOptions): Long
        @JvmStatic external fun optionsSetSavedataLength(options: ToxJniOptions, length: Long)
        @JvmStatic external fun optionsGetLogCallback(options: ToxJniOptions): ILogCallbackListener
        @JvmStatic external fun optionsSetLogCallback(options: ToxJniOptions, callbackListener: ILogCallbackListener)
        @JvmStatic external fun optionsDefault(options: ToxJniOptions)

        @JvmStatic external fun optionsNew(): ToxJniOptions
        @JvmStatic external fun optionsFree(options: ToxJniOptions)

        // Creation and destruction
        //typedef enum TOX_ERR_NEW {
        //    TOX_ERR_NEW_OK,
        //    TOX_ERR_NEW_NULL,
        //    TOX_ERR_NEW_MALLOC,
        //    TOX_ERR_NEW_PORT_ALLOC,
        //    TOX_ERR_NEW_PROXY_BAD_TYPE,
        //    TOX_ERR_NEW_PROXY_BAD_HOST,
        //    TOX_ERR_NEW_PROXY_BAD_PORT,
        //    TOX_ERR_NEW_PROXY_NOT_FOUND,
        //    TOX_ERR_NEW_LOAD_ENCRYPTED,
        //    TOX_ERR_NEW_LOAD_BAD_FORMAT,
        //} TOX_ERR_NEW;

        // TODO(robinlinden): ToxJniOptions?, toxNew supports null.
        @JvmStatic external fun toxNew(options: ToxJniOptions): ToxHandle
        @JvmStatic external fun toxKill(tox: ToxHandle)

        //size_t tox_get_savedata_size(const Tox *tox);
        //void tox_get_savedata(const Tox *tox, uint8_t *savedata);

        // Connection lifecycle and event loop
        //typedef enum TOX_ERR_BOOTSTRAP {
        //    TOX_ERR_BOOTSTRAP_OK,
        //    TOX_ERR_BOOTSTRAP_NULL,
        //    TOX_ERR_BOOTSTRAP_BAD_HOST,
        //    TOX_ERR_BOOTSTRAP_BAD_PORT,
        //} TOX_ERR_BOOTSTRAP;
        //bool tox_bootstrap(Tox *tox, const char *host, uint16_t port, const uint8_t *public_key, TOX_ERR_BOOTSTRAP *error);
        //bool tox_add_tcp_relay(Tox *tox, const char *host, uint16_t port, const uint8_t *public_key, TOX_ERR_BOOTSTRAP *error);
        //typedef enum TOX_CONNECTION {
        //    TOX_CONNECTION_NONE,
        //    TOX_CONNECTION_TCP,
        //    TOX_CONNECTION_UDP,
        //} TOX_CONNECTION;
        //TOX_CONNECTION tox_self_get_connection_status(const Tox *tox);
        //typedef void tox_self_connection_status_cb(Tox *tox, TOX_CONNECTION connection_status, void *user_data);
        //void tox_callback_self_connection_status(Tox *tox, tox_self_connection_status_cb *callback);
        //uint32_t tox_iteration_interval(const Tox *tox);
        //void tox_iterate(Tox *tox, void *user_data);


        // Internal client information (Tox address/id)
        //void tox_self_get_address(const Tox *tox, uint8_t *address);
        //void tox_self_set_nospam(Tox *tox, uint32_t nospam);
        //uint32_t tox_self_get_nospam(const Tox *tox);
        //void tox_self_get_public_key(const Tox *tox, uint8_t *public_key);
        //void tox_self_get_secret_key(const Tox *tox, uint8_t *secret_key);

        // User-visible client information (nickname/status)
        //typedef enum TOX_ERR_SET_INFO {
        //    TOX_ERR_SET_INFO_OK,
        //    TOX_ERR_SET_INFO_NULL,
        //    TOX_ERR_SET_INFO_TOO_LONG,
        //} TOX_ERR_SET_INFO;
        //bool tox_self_set_name(Tox *tox, const uint8_t *name, size_t length, TOX_ERR_SET_INFO *error);
        //size_t tox_self_get_name_size(const Tox *tox);
        //void tox_self_get_name(const Tox *tox, uint8_t *name);
        //bool tox_self_set_status_message(Tox *tox, const uint8_t *status_message, size_t length, TOX_ERR_SET_INFO *error);
        //size_t tox_self_get_status_message_size(const Tox *tox);
        //void tox_self_get_status_message(const Tox *tox, uint8_t *status_message);
        //void tox_self_set_status(Tox *tox, TOX_USER_STATUS status);
        //TOX_USER_STATUS tox_self_get_status(const Tox *tox);

        //Friend list management
        //typedef enum TOX_ERR_FRIEND_ADD {
        //    TOX_ERR_FRIEND_ADD_OK,
        //    TOX_ERR_FRIEND_ADD_NULL,
        //    TOX_ERR_FRIEND_ADD_TOO_LONG,
        //    TOX_ERR_FRIEND_ADD_NO_MESSAGE,
        //    TOX_ERR_FRIEND_ADD_OWN_KEY,
        //    TOX_ERR_FRIEND_ADD_ALREADY_SENT,
        //    TOX_ERR_FRIEND_ADD_BAD_CHECKSUM,
        //    TOX_ERR_FRIEND_ADD_SET_NEW_NOSPAM,
        //    TOX_ERR_FRIEND_ADD_MALLOC,
        //} TOX_ERR_FRIEND_ADD;
        //uint32_t tox_friend_add(Tox *tox, const uint8_t *address, const uint8_t *message, size_t length, TOX_ERR_FRIEND_ADD *error);
        //uint32_t tox_friend_add_norequest(Tox *tox, const uint8_t *public_key, TOX_ERR_FRIEND_ADD *error);
        //typedef enum TOX_ERR_FRIEND_DELETE {
        //    TOX_ERR_FRIEND_DELETE_OK,
        //    TOX_ERR_FRIEND_DELETE_FRIEND_NOT_FOUND,
        //} TOX_ERR_FRIEND_DELETE;
        //bool tox_friend_delete(Tox *tox, uint32_t friend_number, TOX_ERR_FRIEND_DELETE *error);


        init {
            System.loadLibrary("tox4k")
        }
    }
}
