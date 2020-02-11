package ltd.evilcorp.tox4k

import android.util.Log
import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.*
import org.junit.Test
import org.junit.runner.RunWith

private fun byteArrayOf(vararg bytes: Int) = ByteArray(bytes.size) { bytes[it].toByte() }

@RunWith(AndroidJUnit4::class)
class ToxJniTest {
    @Test
    fun api_version_functions_can_be_called(): Unit = with(ToxJni) {
        versionMajor()
        versionMinor()
        versionPatch()
    }

    @Test
    fun version_compatibility_seems_to_work(): Unit = with(ToxJni) {
        assertTrue(versionIsCompatible(versionMajor(), versionMinor(), versionPatch()))
        assertFalse(versionIsCompatible(versionMajor() + 1, versionMinor(), versionPatch()))
    }

    @Test
    fun numeric_constant_functions_can_be_called(): Unit = with(ToxJni) {
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

    @Test
    fun the_options_probably_work(): Unit = with(ToxJni) {
        val options = optionsNew()

        optionsSetIpv6Enabled(options, true)
        assertTrue(optionsGetIpv6Enabled(options))
        optionsSetIpv6Enabled(options, false)
        assertFalse(optionsGetIpv6Enabled(options))

        optionsSetUdpEnabled(options, true)
        assertTrue(optionsGetUdpEnabled(options))
        optionsSetUdpEnabled(options, false)
        assertFalse(optionsGetUdpEnabled(options))

        optionsSetLocalDiscoveryEnabled(options, true)
        assertTrue(optionsGetLocalDiscoveryEnabled(options))
        optionsSetLocalDiscoveryEnabled(options, false)
        assertFalse(optionsGetLocalDiscoveryEnabled(options))

        val proxyHost = "amazing proxy host"
        optionsSetProxyHost(options, proxyHost)
        assertEquals(proxyHost, optionsGetProxyHost(options))
        assertNotEquals("bad host", optionsGetProxyHost(options))

        val proxyPort = 404
        optionsSetProxyPort(options, proxyPort)
        assertEquals(proxyPort, optionsGetProxyPort(options))
        assertNotEquals(proxyPort + 1, optionsGetProxyPort(options))

        val startPort = 9_001
        optionsSetStartPort(options, startPort)
        assertEquals(startPort, optionsGetStartPort(options))
        assertNotEquals(startPort - 1, optionsGetStartPort(options))

        val endPort = 1
        optionsSetEndPort(options, endPort)
        assertEquals(endPort, optionsGetEndPort(options))
        assertNotEquals(endPort + 1, optionsGetEndPort(options))

        val tcpPort = 40_000
        optionsSetTcpPort(options, tcpPort)
        assertEquals(tcpPort, optionsGetTcpPort(options))
        assertNotEquals(tcpPort + 1, optionsGetTcpPort(options))

        optionsSetHolePunchingEnabled(options, true)
        assertTrue(optionsGetHolePunchingEnabled(options))
        optionsSetHolePunchingEnabled(options, false)
        assertFalse(optionsGetHolePunchingEnabled(options))

        optionsDefault(options)

        optionsFree(options)
    }

    @Test
    fun the_proxy_types_work(): Unit = with(ToxJni) {
        val options = optionsNew()

        optionsSetProxyType(options, ProxyType.NONE)
        assertEquals(optionsGetProxyType(options), ProxyType.NONE)
        optionsSetProxyType(options, ProxyType.HTTP)
        assertEquals(optionsGetProxyType(options), ProxyType.HTTP)
        optionsSetProxyType(options, ProxyType.SOCKS5)
        assertEquals(optionsGetProxyType(options), ProxyType.SOCKS5)
        optionsSetProxyType(options, ProxyType.NONE)
        assertEquals(optionsGetProxyType(options), ProxyType.NONE)

        optionsFree(options)
    }

    @Test
    fun the_savedata_types_work(): Unit = with(ToxJni) {
        val options = optionsNew()

        optionsSetSavedataType(options, SavedataType.NONE)
        assertEquals(optionsGetSavedataType(options), SavedataType.NONE)
        optionsSetSavedataType(options, SavedataType.SECRET_KEY)
        assertEquals(optionsGetSavedataType(options), SavedataType.SECRET_KEY)
        optionsSetSavedataType(options, SavedataType.TOX_SAVE)
        assertEquals(optionsGetSavedataType(options), SavedataType.TOX_SAVE)
        optionsSetSavedataType(options, SavedataType.NONE)
        assertEquals(optionsGetSavedataType(options), SavedataType.NONE)

        optionsFree(options)
    }

    @Test
    fun savedata_works(): Unit = with(ToxJni) {
        // TODO(robinlinden): Test with known data and read expected values from the loaded save.
        val options = optionsNew()

        val bytes = byteArrayOf(
            0x76, 0x51, 0x84, 0x06, 0xF6, 0xA9, 0xF2, 0x21, 0x7E, 0x8D, 0xC4, 0x87, 0xCC, 0x78,
            0x3C, 0x25, 0xCC, 0x16, 0xA1, 0x5E, 0xB3, 0x6F, 0xF3, 0x2E, 0x33, 0x5A, 0x23, 0x53,
            0x42, 0xC4, 0x8A, 0x39
        )

        optionsSetSavedataData(options, bytes)
        optionsSetSavedataLength(options, bytes.size.toLong())

        assertArrayEquals(bytes, optionsGetSavedataData(options))
        assertEquals(bytes.size.toLong(), optionsGetSavedataLength(options))

        optionsFree(options)
    }

    @Test
    fun log_callbacks_work(): Unit = with(ToxJni) {
        val options = optionsNew()

        var someVariable = 0

        val callback = object : ToxJni.ILogCallbackListener {
            override fun onLog(
                tox: ToxHandle,
                level: LogLevel,
                file: String,
                line: Long,
                func: String,
                message: String
            ) {
                val msg = "$file $line $func $message"
                when (level) {
                    LogLevel.TRACE -> Log.v("LogCallback", msg)
                    LogLevel.DEBUG -> Log.d("LogCallback", msg)
                    LogLevel.INFO -> Log.i("LogCallback", msg)
                    LogLevel.WARNING -> Log.w("LogCallback", msg)
                    LogLevel.ERROR -> Log.e("LogCallback", msg)
                }

                someVariable++
            }
        }

        optionsSetLogCallback(options, callback)
        assertEquals(callback, optionsGetLogCallback(options))

        assertEquals(0, someVariable)
        optionsGetLogCallback(options).onLog(0, LogLevel.TRACE, "file", 1, "func", "message")
        assertEquals(1, someVariable)

        optionsFree(options)
    }

    @Test
    fun tox_creation(): Unit = with(ToxJni) {
        val options = optionsNew()

        val tox = toxNew(options)
        toxKill(tox)

        optionsFree(options)
    }

    @Test
    fun tox_creation_without_options(): Unit = with(ToxJni) {
        val tox = toxNew(null)
        toxKill(tox)
    }

    @Test
    fun failure_to_create_tox_doesnt_exit_the_app(): Unit = with(ToxJni) {
        val options = optionsNew()
        optionsSetSavedataType(options, SavedataType.SECRET_KEY)

        try {
            val tox = toxNew(options)
            toxKill(tox)
            fail()
        } catch (e: Exception) {
            assertEquals(e.message, "load bad format")
        } finally {
            optionsFree(options)
        }
    }
}
