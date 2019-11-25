package ltd.evilcorp.tox4k

typealias ToxJniOptions = Long
typealias ToxInstance = Long

class ToxJni {
    // API version
    external fun versionMajor(): Long
    external fun versionMinor(): Long
    external fun versionPatch(): Long
    external fun versionIsCompatible(major: Long, minor: Long, patch: Long): Boolean

    // Numeric constants
    external fun publicKeySize(): Long
    external fun secretKeySize(): Long
    external fun conferenceUidSize(): Long
    external fun conferenceIdSize(): Long
    external fun nospamSize(): Long
    external fun addressSize(): Long
    external fun maxNameLength(): Long
    external fun maxStatusMessageLength(): Long
    external fun maxFriendRequestLength(): Long
    external fun maxMessageLength(): Long
    external fun maxCustomPacketSize(): Long
    external fun hashLength(): Long
    external fun fileIdLength(): Long
    external fun maxFilenameLength(): Long
    external fun maxHostnameLength(): Long

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

    interface ILogCallbackListener {
        fun onLog(tox: ToxInstance, level: LogLevel, file: String, line: Long, func: String, message: String)
    }

    external fun optionsGetIpv6Enabled(options: ToxJniOptions): Boolean
    external fun optionsSetIpv6Enabled(options: ToxJniOptions, enabled: Boolean)
    external fun optionsGetUdpEnabled(options: ToxJniOptions): Boolean
    external fun optionsSetUdpEnabled(options: ToxJniOptions, enabled: Boolean)
    external fun optionsGetLocalDiscoveryEnabled(options: ToxJniOptions): Boolean
    external fun optionsSetLocalDiscoveryEnabled(options: ToxJniOptions, enabled: Boolean)
    external fun optionsGetProxyType(options: ToxJniOptions): ProxyType
    external fun optionsSetProxyType(options: ToxJniOptions, proxyType: ProxyType)
    external fun optionsGetProxyHost(options: ToxJniOptions): String
    external fun optionsSetProxyHost(options: ToxJniOptions, proxyHost: String)
    external fun optionsGetProxyPort(options: ToxJniOptions): Int
    external fun optionsSetProxyPort(options: ToxJniOptions, port: Int)
    external fun optionsGetStartPort(options: ToxJniOptions): Int
    external fun optionsSetStartPort(options: ToxJniOptions, port: Int)
    external fun optionsGetEndPort(options: ToxJniOptions): Int
    external fun optionsSetEndPort(options: ToxJniOptions, port: Int)
    external fun optionsGetTcpPort(options: ToxJniOptions): Int
    external fun optionsSetTcpPort(options: ToxJniOptions, port: Int)
    external fun optionsGetHolePunchingEnabled(options: ToxJniOptions): Boolean
    external fun optionsSetHolePunchingEnabled(options: ToxJniOptions, enabled: Boolean)
    external fun optionsGetSavedataType(options: ToxJniOptions): SavedataType
    external fun optionsSetSavedataType(options: ToxJniOptions, type: SavedataType)
    external fun optionsGetSavedataData(options: ToxJniOptions): ByteArray
    external fun optionsSetSavedataData(options: ToxJniOptions, data: ByteArray)
    external fun optionsGetSavedataLength(options: ToxJniOptions): Long
    external fun optionsSetSavedataLength(options: ToxJniOptions, length: Long)
    external fun optionsGetLogCallback(options: ToxJniOptions): ILogCallbackListener
    external fun optionsSetLogCallback(options: ToxJniOptions, callbackListener: ILogCallbackListener)
    external fun optionsDefault(options: ToxJniOptions)

    external fun optionsNew(): ToxJniOptions
    external fun optionsFree(options: ToxJniOptions)

    companion object {
        init {
            System.loadLibrary("tox4k")
        }
    }
}
