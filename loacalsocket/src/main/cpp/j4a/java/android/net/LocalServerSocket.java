package java.android.net;


import android.net.LocalSocket;
import android.net.LocalSocketAddress;

@SimpleCClassName
public class LocalServerSocket {

    public LocalServerSocket(String name);

    public LocalSocketAddress getLocalSocketAddress();

    public LocalSocket accept();

    public void close();
}
