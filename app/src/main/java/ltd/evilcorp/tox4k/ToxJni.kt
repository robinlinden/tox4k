package ltd.evilcorp.tox4k

class ToxJni {
    external fun versionMajor(): Long
    external fun versionMinor(): Long
    external fun versionPatch(): Long

    companion object {
        init {
            System.loadLibrary("tox4k")
        }
    }
}
