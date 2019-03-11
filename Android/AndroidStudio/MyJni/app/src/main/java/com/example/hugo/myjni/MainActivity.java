package com.example.hugo.myjni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public static void log(Object msg) {
        Log.d("hugo_app", "" + msg);
    }

    void nativeTester() {
        log(nativeReturnString());
        log(nativeReturnInt());

        nativeVoid();
        nativeInputPrimitive(false, (byte) 0, (short) 0, 0, 0, 0, 0);
        nativeInputPrimitive(true, (byte) Byte.MAX_VALUE, (short) Short.MAX_VALUE,
                Integer.MAX_VALUE, Long.MAX_VALUE, Float.MAX_VALUE, Double.MAX_VALUE);
        nativeInputPrimitive(true, (byte) Byte.MIN_VALUE, (short) Short.MIN_VALUE,
                Integer.MIN_VALUE, Long.MIN_VALUE, Float.MIN_VALUE, Double.MIN_VALUE);

        nativeInputByteArray(null);
        nativeInputByteArray(new byte[0]);
        nativeInputByteArray(new byte[]{0, 1, 127, -1, -128});

        nativeInputString(null);
        nativeInputString("");
        nativeInputString("hello");
        nativeInputString("中文字");

        nativeInputClass(null);
        nativeInputClass(new MyClass());
        MyClass c = new MyClass();
        c.boo = true;
        c.b = 123;
        c.s = 12345;
        c.i = 123456789;
        c.l = 1234567890123456L;
        c.f = 1.1f;
        c.d = 123.456;
        c.str = "hello";
        c.ba = new byte[]{0, 1, 2, 3};
        nativeInputClass(c);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("hello world");

        for(int i = 0; i < 1; i++) {
            log(" ------------ " + i + " ------------ ");
            nativeTester();
        }
    }

    static class MyClass {
        boolean boo;
        byte b;
        short s;
        int i;
        long l;
        float f;
        double d;
        String str;
        byte[] ba;
    }

    public native void nativeVoid();

    public native String nativeReturnString();

    public native int nativeReturnInt();

    public native void nativeInputPrimitive(boolean boo, byte b, short s, int i, long l, float f, double d);

    public native void nativeInputByteArray(byte[] in);

    public native void nativeInputString(String in);

    public native void nativeInputClass(MyClass c);
}
