package java.java.io;

@SimpleCClassName
public abstract class InputStream {

    public int read(byte[] b, int off, int len);

    public long skip(long n);

    public int available();

    public void close();

    public void mark(int readlimit);

    public void reset();

    public boolean markSupported();
}
