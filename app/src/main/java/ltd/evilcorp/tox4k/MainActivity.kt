package ltd.evilcorp.tox4k

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private val tox = ToxJni()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val version = "${tox.versionMajor()}.${tox.versionMinor()}.${tox.versionPatch()}"
        sample_text.text = "Linked against c-toxcore $version"
    }
}
