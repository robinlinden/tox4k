package ltd.evilcorp.tox4k

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
class ToxJniTest {
    @Test
    fun version_functions_can_be_called() {
        with(ToxJni()) {
            versionMajor()
            versionMinor()
            versionPatch()
        }
    }
}
