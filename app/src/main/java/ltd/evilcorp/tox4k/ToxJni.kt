package ltd.evilcorp.tox4k

class ToxJni {
    external fun stringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("tox4k")
        }
    }
}
