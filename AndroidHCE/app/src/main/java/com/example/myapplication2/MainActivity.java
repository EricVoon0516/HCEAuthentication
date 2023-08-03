package com.example.myapplication2;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.nfc.NfcAdapter;
import android.nfc.cardemulation.CardEmulation;
import android.os.Bundle;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.example.myapplication2.MyHostApduService;
import com.example.myapplication2.R;

public class MainActivity extends Activity {

    private boolean isHceActivated;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        isHceActivated = false;

        // Button click listener
        Button hceButton = findViewById(R.id.hce_button);
        hceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (isHceActivated) {
                    // Deactivate HCE service (User must manually disable from settings)
                    Intent intent = new Intent(Settings.ACTION_NFC_SETTINGS);
                    startActivity(intent);
                    isHceActivated = false;
                } else {
                    // Activate HCE service (User must manually enable from settings)
                    Intent intent = new Intent(Settings.ACTION_NFC_SETTINGS);
                    startActivity(intent);
                    isHceActivated = true;
                }
            }
        });


    }
}
