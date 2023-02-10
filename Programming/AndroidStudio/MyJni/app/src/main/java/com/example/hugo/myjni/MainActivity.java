package com.example.hugo.myjni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
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
        c.c = new MyClass2();
        c.c.i2 = 987654321;
        nativeInputClass(c);

        nativeInputClassArray(null);
        nativeInputClassArray(new MyClass[0]);
        nativeInputClassArray(new MyClass[1]);
        nativeInputClassArray(new MyClass[]{null, new MyClass(), c});

        log("before " + c);
        nativeModifyClass(c);
        log("after " + c);

        c = nativeReturnClass();
        log(c);

        nativeCallbacks();

        nativeThread();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        for (int i = 0; i < 1; i++) {
            log(" ------------ " + i + " ------------ ");
            nativeTester();
        }

        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText("hello world");

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
        MyClass2 c;

        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("MyClass ");
            sb.append("boo=" + boo + " ");
            sb.append("b=" + b + " ");
            sb.append("s=" + s + " ");
            sb.append("i=" + i + " ");
            sb.append("l=" + l + " ");
            sb.append("f=" + f + " ");
            sb.append("d=" + d + " ");
            sb.append("str=" + str + " ");
            if (ba == null) {
                sb.append("ba=" + ba + " ");
            } else {
                sb.append("ba=[len=" + ba.length + " " + Arrays.toString(ba) + "] ");
            }
            sb.append("c=" + c + " ");
            return sb.toString();
        }
    }

    static class MyClass2 {
        int i2;

        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("MyClass2 ");
            sb.append("i2=" + i2 + " ");
            return sb.toString();
        }
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------

    private void callback() {
        log("callback");
    }

    private boolean callbackReturnBool() {
        return true;
    }

    private byte callbackReturnByte() {
        return 1;
    }

    private short callbackReturnShort() {
        return 2;
    }

    private int callbackReturnInt() {
        return 3;
    }

    private long callbackReturnLong() {
        return 4;
    }

    private float callbackReturnFloat() {
        return 1.1f;
    }

    private double callbackReturnDouble() {
        return 2.2;
    }

    private String callbackReturnString() {
        return "hello world";
    }

    private byte[] callbackReturnByteArray() {
        return new byte[]{1, 2, 3, 0};
    }

    private void callbackInputs(boolean boo, byte b, short s, int i, long l, float f, double d) {
        log("callbackInputs boo=" + boo + " b=" + b + " s=" + s + " i=" + i + " l=" + l + " f=" + f + " d=" + d);
    }

    private void callbackInputString(String str) {
        log("callbackInputString str=" + str);
    }

    private void callbackInputByteArray(byte[] data) {
        log("callbackInputByteArray " + Arrays.toString(data));
    }

    private void callbackInputClass(MyClass c) {
        log("callbackInputClass c=" + c);
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------
    public native void nativeVoid();

    public native String nativeReturnString();

    public native int nativeReturnInt();

    public native MyClass nativeReturnClass();

    public native void nativeInputPrimitive(boolean boo, byte b, short s, int i, long l, float f, double d);

    public native void nativeInputByteArray(byte[] in);

    public native void nativeInputString(String in);

    public native void nativeInputClass(MyClass c);

    public native void nativeInputClassArray(MyClass c[]);

    public native void nativeModifyClass(MyClass c);

    public native void nativeCallbacks();

    public native void nativeThread();

    public static void log(Object msg) {
        Log.i("hugo_app", "" + msg);
    }

}
