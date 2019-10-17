package ltd.evilcorp.tox4k

import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Assert.*
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

    @Test
    fun the_options_probably_work(): Unit = with(ToxJni()) {
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
}
