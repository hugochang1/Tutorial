package com.example.hugo.testapplication01;

import android.os.Handler;
import android.os.Message;
import android.text.Html;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class TestStringList {
    private TextView mTextView;
    private ArrayList<String> mList;
    private int mMaxStringNumber;
    private MyHandler mHandler;
    private int mDelayInterval;

    public TestStringList() {
        this(null, 16);
    }

    public TestStringList(int maxStringNumber) {
        this(null, maxStringNumber);
    }

    public TestStringList(TextView textView) {
        this(textView, 16);
    }

    public TestStringList(TextView textView, int maxStringNumber) {
        mTextView = textView;
        mList = new ArrayList<String>();
        mMaxStringNumber = maxStringNumber;
        mDelayInterval = 100;
        updateUiThread();
    }

    public void setmDelayInterval(int delay) {
        mDelayInterval = delay;
    }

    public void setMaxStringNumber(int num) {
        mMaxStringNumber = num;
    }

    public void updateUiThread() {
        mHandler = new MyHandler();
    }

    public void setTextView(TextView textView) {
        mTextView = textView;
    }

    public void print(String string) {
        print(0x00888888, string);
    }

    public synchronized void print(int color, String string) {
        if (mList.size() > mMaxStringNumber) {
            mList.remove(0);
        }
        mList.add("<font color='#" + Integer.toHexString(color & 0x00ffffff)
                + "'>" + getTimeString() + " " + string + "</font><br>");
        updateTextView();
    }

    public synchronized String get() {
        String o = "";
        for (String s : mList) {
            o += s;
        }
        return o;
    }

    public synchronized void clear() {
        mList.clear();
        ;
        updateTextView();
    }

    private void updateTextView() {
        if (mTextView == null) {
            return;
        }
        Message m = Message.obtain();
        m.what = 0;
        mHandler.removeMessages(0);
        mHandler.sendMessageDelayed(m, mDelayInterval);
    }

    private class MyHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            mTextView.setText(Html.fromHtml(get()), TextView.BufferType.SPANNABLE);
        }
    }

    private String getTimeString() {
        Calendar c = new GregorianCalendar();
        c.setTimeInMillis(System.currentTimeMillis());
        String date = String.format("%02d:%02d.%03d", c.get(Calendar.MINUTE),
                c.get(Calendar.SECOND), c.get(Calendar.MILLISECOND));
        return date;
    }

    public String toString() {
        return get();
    }
}
