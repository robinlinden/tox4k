package ltd.evilcorp.tox4k

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.*
import org.junit.Test
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
class ToxOptionsTest {
    @Test
    fun new_options_are_the_same() {
        val options = ToxOptions()
        assertEquals(options, ToxOptions())
    }

    @Test
    fun the_hashcode_stays_the_same() {
        val options = ToxOptions()
        assertEquals(options.hashCode(), options.hashCode())
    }

    @Test
    fun it_is_possible_to_change_the_options() {
        val logCallbackListener = object : ToxJni.ILogCallbackListener {
            override fun onLog(
                tox: ToxHandle,
                level: LogLevel,
                file: String,
                line: Long,
                func: String,
                message: String
            ) {
            }
        }

        val options = ToxOptions().apply {
            ipv6Enabled = false
            udpEnabled = false
            localDiscoveryEnabled = false
            proxyType = ProxyType.SOCKS5
            proxyHost = "127.0.0.1"
            proxyPort = 1984
            startPort = 1
            endPort = 10
            tcpPort = 11
            holePunchingEnabled = false
            savedataType = SavedataType.TOX_SAVE
            savedataData = byteArrayOf(0, 1, 2, 3)
            savedataLength = 4
            logCallback = logCallbackListener
        }

        assertEquals(options, options)
        assertNotEquals(options, ToxOptions())

        assertEquals(false, options.ipv6Enabled)
        assertEquals(false, options.udpEnabled)
        assertEquals(false, options.localDiscoveryEnabled)
        assertEquals(ProxyType.SOCKS5, options.proxyType)
        assertEquals("127.0.0.1", options.proxyHost)
        assertEquals(1984, options.proxyPort)
        assertEquals(1, options.startPort)
        assertEquals(10, options.endPort)
        assertEquals(11, options.tcpPort)
        assertEquals(false, options.holePunchingEnabled)
        assertEquals(SavedataType.TOX_SAVE, options.savedataType)
        assertArrayEquals(byteArrayOf(0, 1, 2, 3), options.savedataData)
        assertEquals(4, options.savedataLength)
        assertEquals(logCallbackListener, options.logCallback)
    }
}
