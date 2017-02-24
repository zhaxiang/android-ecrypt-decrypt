package com.android.suning.jnimode;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.TextView;

import com.android.suning.jnimode.jnibase.JniUtils;

public class DesBlowfishMd5Activity extends Activity implements View.OnClickListener {

    private RadioButton radioDes;
    private RadioButton radioBlow;
    private RadioButton radioMd5;
    private EditText editKey;
    private EditText editStr;
    private Button btnEn;
    private Button btnDe;
    private TextView textFormat;
    private LinearLayout activityDesBlowfishMd5;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        {
            System.loadLibrary("jnimode");
        }

        setContentView(R.layout.activity_des_blowfish_md5);
        initView();
    }

    private void initView() {
        radioDes = (RadioButton) findViewById(R.id.radio_des);
        radioBlow = (RadioButton) findViewById(R.id.radio_blow);
        radioMd5 = (RadioButton) findViewById(R.id.radio_md5);
        editKey = (EditText) findViewById(R.id.edit_key);
        editStr = (EditText) findViewById(R.id.edit_str);
        btnEn = (Button) findViewById(R.id.btn_en);
        btnDe = (Button) findViewById(R.id.btn_de);
        textFormat = (TextView) findViewById(R.id.text_format);
        activityDesBlowfishMd5 = (LinearLayout) findViewById(R.id.activity_des_blowfish_md5);

        btnEn.setOnClickListener(this);
        btnDe.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_en:
                enOper();
                break;
            case R.id.btn_de:
                deOper();
                break;
        }
    }

    private void enOper()
    {
        String key = editKey.getText().toString().trim();
//        if (TextUtils.isEmpty(key)) {
//            Toast.makeText(this, "input key", Toast.LENGTH_SHORT).show();
//            return;
//        }

        String str = editStr.getText().toString().trim();
//        if (TextUtils.isEmpty(str)) {
//            Toast.makeText(this, "input string", Toast.LENGTH_SHORT).show();
//            return;
//        }

        String keyMode;
        if(radioDes.isChecked())
        {
            keyMode = JniUtils.DES_MODULE;
        }
        else if(radioBlow.isChecked())
        {
            keyMode = JniUtils.BF_MODULE;
        }
        else
        {
            keyMode = JniUtils.MS_MODULE;
        }
        textFormat.setText(JniUtils.encryptionString(str, keyMode, key));
    }

    private void deOper()
    {
        String key = editKey.getText().toString().trim();
//        if (TextUtils.isEmpty(key)) {
//            Toast.makeText(this, "input key", Toast.LENGTH_SHORT).show();
//            return;
//        }

        String str = editStr.getText().toString().trim();
//        if (TextUtils.isEmpty(str)) {
//            Toast.makeText(this, "input string", Toast.LENGTH_SHORT).show();
//            return;
//        }

        String keyMode;
        if(radioDes.isChecked())
        {
            keyMode = JniUtils.DES_MODULE;
        }
        else if(radioBlow.isChecked())
        {
            keyMode = JniUtils.BF_MODULE;
        }
        else
        {
            keyMode = JniUtils.MS_MODULE;
        }

        String s = JniUtils.decryptionString(textFormat.getText().toString(), keyMode, key);
        Log.e("zhaxaing", "s =" + s);

        textFormat.setText(s);
    }


}
