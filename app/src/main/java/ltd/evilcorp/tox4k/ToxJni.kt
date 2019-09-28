package ltd.evilcorp.tox4k

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

    companion object {
        init {
            System.loadLibrary("tox4k")
        }
    }
}
