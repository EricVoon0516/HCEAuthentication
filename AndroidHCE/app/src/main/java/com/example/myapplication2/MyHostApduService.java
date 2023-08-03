package com.example.myapplication2;

import android.content.Intent;
import android.nfc.cardemulation.HostApduService;
import android.os.Bundle;
import android.util.Log;

import java.util.Arrays;

public class MyHostApduService extends HostApduService {

    @Override
    public byte[] processCommandApdu(byte[] commandApdu, Bundle extras) {
        Log.d("HCE", "processCommandApdu");
        Log.d("HCE", Arrays.toString(commandApdu));

       // Open your application here
       Intent intent = new Intent(getApplicationContext(), MainActivity.class);
       intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
       startActivity(intent);

        String response = "Hello";
        return response.getBytes();
    }

    @Override
    public void onDeactivated(int reason) {
        Log.d("HCE", "Deactivated: " + reason);
    }
}