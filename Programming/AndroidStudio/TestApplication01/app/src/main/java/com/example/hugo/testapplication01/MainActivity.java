package com.example.hugo.testapplication01;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.location.GpsSatellite;
import android.location.GpsStatus;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.io.IOException;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

@SuppressLint("MissingPermission")
public class MainActivity extends Activity {
    Button mButton1;
    Button mButton2;
    Button mButton3;
    Button mButton4;
    Button mButton5;
    Button mButton6;
    Button mButton7;
    Button mButton8;
    Button mButton9;
    Button mButton10;
    Button mButton11;
    Button mButton12;
    TextView mTextView1;
    TextView mTextView2;
    TextView mTextView3;
    static TestStringList sInfo = new TestStringList(16);

    WifiManager mWifiManager;
    TelephonyManager mTelephonyManager;
    LocationManager mLocationManager;
    PowerManager.WakeLock mWakeLock;

    LineGraphSeries<DataPoint> mSeries = new LineGraphSeries<>();
    GraphView mGraph;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mGraph = findViewById(R.id.graph);
        mButton1 = findViewById(R.id.button_1);
        mButton2 = findViewById(R.id.button_2);
        mButton3 = findViewById(R.id.button_3);
        mButton4 = findViewById(R.id.button_4);
        mButton5 = findViewById(R.id.button_5);
        mButton6 = findViewById(R.id.button_6);
        mButton7 = findViewById(R.id.button_7);
        mButton8 = findViewById(R.id.button_8);
        mButton9 = findViewById(R.id.button_9);
        mButton10 = findViewById(R.id.button_10);
        mButton11 = findViewById(R.id.button_11);
        mButton12 = findViewById(R.id.button_12);
        mTextView1 = findViewById(R.id.textview_1);
        mTextView2 = findViewById(R.id.textview_2);
        mTextView3 = findViewById(R.id.textview_3);
        sInfo.updateUiThread();
        sInfo.clear();
        sInfo.setTextView(mTextView3);
        mTextView3.setTextSize(12);

        log("onCreate() ver=1");

        mButton1.setText("Start");
        mButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startServices();
            }
        });
        mButton2.setText("Stop");
        mButton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                stopServices();
            }
        });
        mButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("3");
            }
        });
        mButton4.setText("Clear");
        mButton4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sInfo.clear();
            }
        });
        mButton5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("5");
            }
        });
        mButton6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("6");
            }
        });
        mButton7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("7");
            }
        });
        mButton8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("8");
            }
        });
        mButton9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("9");
            }
        });
        mButton10.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("10");
            }
        });
        mButton11.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("11");
            }
        });
        mButton12.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                log("12");
            }
        });

        mWifiManager = (WifiManager) getApplicationContext().getSystemService(WIFI_SERVICE);
        if(mWifiManager == null) {
            toast("WifiManager is null");
            finish();
        }

        mLocationManager = (LocationManager) getApplicationContext().getSystemService(LOCATION_SERVICE);
        if(mLocationManager == null) {
            toast("LocationManager is null");
            finish();
        }

        mTelephonyManager = (TelephonyManager) getApplicationContext().getSystemService(TELEPHONY_SERVICE);
        if(mTelephonyManager == null) {
            toast("mTelephonyManager is null");
            finish();
        }

        PowerManager pm = (PowerManager)getApplicationContext().getSystemService(POWER_SERVICE);
        if(pm == null) {
            toast("PowerManager is null");
            finish();
        }
        mWakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, "TestApplication01:myapp");
        if(mWakeLock == null) {
            toast("WakeLock is null");
            finish();
        }
        mWakeLock.acquire();

        IntentFilter filter = new IntentFilter();
        filter.addAction(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
        registerReceiver(mBroadcastReceiver, filter);

        Message m = new Message();
        m.what = 0;
        mHandler.sendMessageDelayed(m, 1000);

        mGraph.setTitle("Title 1");
        mGraph.setTitleColor(0xffff0000);
        mGraph.getViewport().setXAxisBoundsManual(true);
        mGraph.getViewport().setMinX(0);
        mGraph.getViewport().setMaxX(10);
        mGraph.getViewport().setYAxisBoundsManual(true);
        mGraph.getViewport().setMinY(0);
        mGraph.getViewport().setMaxY(5);
        mGraph.getGridLabelRenderer().setNumHorizontalLabels(6);
        mGraph.getGridLabelRenderer().setNumVerticalLabels(3);
        mGraph.addSeries(mSeries);
    }

    private void startServices() {
        mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, mLocationListener);
        mLocationManager.addGpsStatusListener(mGpsStatusListener);
        mTelephonyManager.listen(mPhoneStateListener, PhoneStateListener.LISTEN_DATA_CONNECTION_STATE);
    }

    private void stopServices() {
        mLocationManager.removeUpdates(mLocationListener);
        mLocationManager.removeGpsStatusListener(mGpsStatusListener);
        mTelephonyManager.listen(mPhoneStateListener, PhoneStateListener.LISTEN_NONE);
    }

    int x = 0;
    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            if(msg.what == 0) {
                x++;
                mSeries.appendData(new DataPoint(x, new Random().nextInt(5)), false, 100);
                mGraph.getViewport().scrollToEnd();

                Message m = new Message();
                m.what = 0;
                mHandler.sendMessageDelayed(m, 1000);
            }
        }

    };

    BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if(action.equals(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION)) {
                List<ScanResult> list = mWifiManager.getScanResults();
                //sort according to level
                Collections.sort(list, new Comparator<ScanResult>() {
                    @Override
                    public int compare(ScanResult o1, ScanResult o2) {
                        return o2.level - o1.level;
                    }
                });
                log("WiFi ScanResult size=" + list.size());
            }
        }
    };

    LocationListener mLocationListener = new LocationListener() {
        @Override
        public void onLocationChanged(Location location) {
            log("onLocationChanged() " + location);
        }
        @Override
        public void onStatusChanged(String provider, int status, Bundle extras) {
        }
        @Override
        public void onProviderEnabled(String provider) {
        }
        @Override
        public void onProviderDisabled(String provider) {
        }
    };

    GpsStatus.Listener mGpsStatusListener = new GpsStatus.Listener() {
        @Override
        public void onGpsStatusChanged(int event) {
            if(event == GpsStatus.GPS_EVENT_SATELLITE_STATUS) {
                GpsStatus status = mLocationManager.getGpsStatus(null);
                Iterable<GpsSatellite> it = status.getSatellites();
                List<GpsSatellite> list = new ArrayList<>();
                for(GpsSatellite s : it) {
                    list.add(s);
                }
                log("onGpsStatusChanged size=" + list.size());
            }
        }
    };

    PhoneStateListener mPhoneStateListener = new PhoneStateListener() {
        @Override
        public void onDataConnectionStateChanged(int state) {
            switch(state) {
                case TelephonyManager.DATA_CONNECTED:
                    break;
                case TelephonyManager.DATA_CONNECTING:
                    break;
                case TelephonyManager.DATA_DISCONNECTED:
                    break;
                case TelephonyManager.DATA_SUSPENDED:
                    break;
            }
        }
    };

    @Override
    protected void onStart() {
        super.onStart();
        log("onStart()");
    }

    @Override
    protected void onResume() {
        super.onResume();
        log("onResume()");
        if(isPermissionOk() == false) {
            requestPermissions(new String[] {Manifest.permission.ACCESS_FINE_LOCATION,
            Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.READ_PHONE_STATE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE},
                    1);
        } else {
            //success, start showing UI

        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        log("onPause()");
    }

    @Override
    protected void onStop() {
        super.onStop();
        log("onStop()");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        log("onDestroy()");
        if(mWakeLock.isHeld()) {
            mWakeLock.release();
        }
        unregisterReceiver(mBroadcastReceiver);
        mHandler.removeMessages(0);
        stopServices();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        if(hasFocus) {
            //update the UI
        }
        super.onWindowFocusChanged(hasFocus);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int grantResults[]) {
        if(isPermissionOk() == false) {
            toast("You must grant all permissions before using this app");
            finish();
        }
    }

    private boolean isPermissionOk() {
        if(checkSelfPermission(Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_DENIED ||
                checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_DENIED ||
                checkSelfPermission(Manifest.permission.READ_PHONE_STATE) == PackageManager.PERMISSION_DENIED ||
                checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED ||
                checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED ) {
            return false;
        } else {
            return true;
        }
    }

    public static void msleep(long milliseconds) {
        try {
            Thread.sleep(milliseconds);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static long getTick() {
        return System.nanoTime() / 1000000;
    }

    public static int ping(String host, int timeout) {
        long time = getTick();
        try {
            InetAddress addr = InetAddress.getByName(host);
            boolean reachable = addr.isReachable(timeout);
            if(reachable) {
                time = getTick() - time;
                return (int)time;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return timeout;
    }

    public void toast(Object msg) {
        Toast.makeText(this.getApplicationContext(), "" + msg, Toast.LENGTH_SHORT).show();
        log("toast() msg=[" + msg + "]");
    }

    public static void log(Object msg) {
        Log.d("my_app", "" + msg);
        sInfo.print("" + msg);
    }
}
