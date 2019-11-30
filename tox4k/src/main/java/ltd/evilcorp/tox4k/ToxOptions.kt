package ltd.evilcorp.tox4k

import java.util.*

class ToxOptions {
    private val options = ToxJni.optionsNew().also { ToxJni.optionsDefault(it) }
    protected fun finalize() = ToxJni.optionsFree(options)

    var ipv6Enabled: Boolean
        get() = ToxJni.optionsGetIpv6Enabled(options)
        set(value) = ToxJni.optionsSetIpv6Enabled(options, value)

    var udpEnabled: Boolean
        get() = ToxJni.optionsGetUdpEnabled(options)
        set(value) = ToxJni.optionsSetUdpEnabled(options, value)

    var localDiscoveryEnabled: Boolean
        get() = ToxJni.optionsGetLocalDiscoveryEnabled(options)
        set(value) = ToxJni.optionsSetLocalDiscoveryEnabled(options, value)

    var proxyType: ProxyType
        get() = ToxJni.optionsGetProxyType(options)
        set(value) = ToxJni.optionsSetProxyType(options, value)

    var proxyHost: String
        get() = ToxJni.optionsGetProxyHost(options)
        set(value) = ToxJni.optionsSetProxyHost(options, value)

    var proxyPort: Int
        get() = ToxJni.optionsGetProxyPort(options)
        set(value) = ToxJni.optionsSetProxyPort(options, value)

    var startPort: Int
        get() = ToxJni.optionsGetStartPort(options)
        set(value) = ToxJni.optionsSetStartPort(options, value)

    var endPort: Int
        get() = ToxJni.optionsGetEndPort(options)
        set(value) = ToxJni.optionsSetEndPort(options, value)

    var tcpPort: Int
        get() = ToxJni.optionsGetTcpPort(options)
        set(value) = ToxJni.optionsSetTcpPort(options, value)

    var holePunchingEnabled: Boolean
        get() = ToxJni.optionsGetHolePunchingEnabled(options)
        set(value) = ToxJni.optionsSetHolePunchingEnabled(options, value)

    var savedataType: SavedataType
        get() = ToxJni.optionsGetSavedataType(options)
        set(value) = ToxJni.optionsSetSavedataType(options, value)

    var savedataData: ByteArray
        get() = ToxJni.optionsGetSavedataData(options)
        set(value) = ToxJni.optionsSetSavedataData(options, value)

    var savedataLength: Long
        get() = ToxJni.optionsGetSavedataLength(options)
        set(value) = ToxJni.optionsSetSavedataLength(options, value)

    var logCallback: ToxJni.ILogCallbackListener
        get() = ToxJni.optionsGetLogCallback(options)
        set(value) = ToxJni.optionsSetLogCallback(options, value)

    override fun hashCode(): Int = Objects.hash(
        ipv6Enabled,
        udpEnabled,
        localDiscoveryEnabled,
        proxyType,
        proxyHost,
        proxyPort,
        startPort,
        endPort,
        tcpPort,
        holePunchingEnabled,
        savedataType,
        savedataData.contentHashCode(),
        savedataLength,
        logCallback
    )

    override fun equals(other: Any?): Boolean = (other is ToxOptions)
            && other.ipv6Enabled == ipv6Enabled
            && other.udpEnabled == udpEnabled
            && other.localDiscoveryEnabled == localDiscoveryEnabled
            && other.proxyType == proxyType
            && other.proxyHost == proxyHost
            && other.proxyPort == proxyPort
            && other.startPort == startPort
            && other.endPort == endPort
            && other.tcpPort == tcpPort
            && other.holePunchingEnabled == holePunchingEnabled
            && other.savedataType == savedataType
            && other.savedataData.contentEquals(savedataData)
            && other.savedataLength == savedataLength
            && other.logCallback == logCallback
}
