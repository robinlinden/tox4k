package ltd.evilcorp.tox4k

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.assertFalse
import org.junit.Assert.assertTrue
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
class ToxJniTest {
    @Test
    fun api_version_functions_can_be_called(): Unit = with(ToxJni()) {
        versionMajor()
        versionMinor()
        versionPatch()
    }

    @Test
    fun version_compatibility_seems_to_work(): Unit = with(ToxJni()) {
        assertTrue(versionIsCompatible(versionMajor(), versionMinor(), versionPatch()))
        assertFalse(versionIsCompatible(versionMajor() + 1, versionMinor(), versionPatch()))
    }

    @Test
    fun numeric_constant_functions_can_be_called(): Unit = with(ToxJni()) {
        publicKeySize()
        secretKeySize()
        conferenceUidSize()
        conferenceIdSize()
        nospamSize()
        addressSize()
        maxNameLength()
        maxStatusMessageLength()
        maxFriendRequestLength()
        maxMessageLength()
        maxCustomPacketSize()
        hashLength()
        fileIdLength()
        maxFilenameLength()
        maxHostnameLength()
    }
}
