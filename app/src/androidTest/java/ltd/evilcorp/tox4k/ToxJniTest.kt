package ltd.evilcorp.tox4k

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.assertFalse
import org.junit.Assert.assertTrue
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

    @Test
    fun version_compatibility_seems_to_work() {
        with(ToxJni()) {
            assertTrue(versionIsCompatible(versionMajor(), versionMinor(), versionPatch()))
            assertFalse(versionIsCompatible(versionMajor() + 1, versionMinor(), versionPatch()))
        }
    }
}
