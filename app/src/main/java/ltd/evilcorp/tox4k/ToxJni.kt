package ltd.evilcorp.tox4k

class ToxJni {
    // API version
    external fun versionMajor(): Long
    external fun versionMinor(): Long
    external fun versionPatch(): Long
    external fun versionIsCompatible(major: Long, minor: Long, patch: Long): Boolean

    companion object {
        init {
            System.loadLibrary("tox4k")
        }
    }
}
