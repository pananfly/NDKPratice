package java.java.io;

@SimpleCClassName
public abstract class OutputStream {

    public void write(byte[] b, int off, int len);

    public void flush();

    public void close();
}
