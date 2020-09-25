package java.android.net;

import android.net.LocalSocketAddress;

import java.io.InputStream;
import java.io.OutputStream;

@SimpleCClassName
public class LocalSocket {

    public LocalSocket(int sockType);

    public void bind(LocalSocketAddress bindpoint);

    public LocalSocketAddress getLocalSocketAddress();

    public InputStream getInputStream();

    public OutputStream getOutputStream();

    public void close();

    public void shutdownInput();

    public void shutdownOutput();

    public void setReceiveBufferSize(int size);

    public int getReceiveBufferSize();

    public void setSoTimeout(int n);

    public int getSoTimeout();

    public void setSendBufferSize(int n);

    public int getSendBufferSize();

    public LocalSocketAddress getRemoteSocketAddress();

    public boolean isConnected();

    public boolean isClosed();

    public boolean isBound();

    public boolean isOutputShutdown();

    public boolean isInputShutdown();

    public void connect(LocalSocketAddress endpoint, int timeout);
}
