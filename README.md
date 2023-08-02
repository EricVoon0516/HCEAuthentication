# HCEAuthentication
This repository contains development of security system with the implementation of HCE, HCE Android application development and Arduino codes.
Using Arduino to enabling HCE features of Android phone.

## List of materials:
   1. Arduino UNO
   2. PN532
   3. Android phones

## Software:
  1. Android Studio:   https://developer.android.com/studio?gclid=CjwKCAjw_aemBhBLEiwAT98FMq-8NRAZYn0AiymZutJLZKTLktTCV2I9DBgDXp8_HawybEUhCpFFCBoCIvsQAvD_BwE&gclsrc=aw.ds
  2. Arduino IDE:      https://www.arduino.cc/en/software

## Documentation
HCE Android development:  https://developer.android.com/guide/topics/connectivity/nfc/hce

The connection of PN532:  https://how2electronics.com/interfacing-pn532-nfc-rfid-module-with-arduino/

## Connection of PN532 to Arduino UNO
![PN532 Connection drawio](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/84884d53-21da-4b60-9d17-251f494be62f)

## Implementation
After reading the documentation provided by Android Developer, you will notice:
   1. Before you develop an Android application with HCE features, please study the declaration of manifest and AID registration: https://developer.android.com/guide/topics/connectivity/nfc/hce#manifest-declaration
   2. Appication ID (AID) is important to help the Android phones for recognising the application protocol data unit (APDU) command from the NFC reader. You can have multiple AIDs (the AID shall be ca within an application.
   3. Before registering the AID, you will need to declare `<service>` in manifest's `<application>`, as shown:
```
<application>
   ...
   <service android:name=".MyHostApduService" android:exported="true"
            android:permission="android.permission.BIND_NFC_SERVICE">
       <intent-filter>
           <action android:name="android.nfc.cardemulation.action.HOST_APDU_SERVICE"/>
       </intent-filter>
       <meta-data android:name="android.nfc.cardemulation.host_apdu_service"
                  android:resource="@xml/apduservice"/>
   </service>
   ...
</application>
```   
   4. 
```
public class MyHostApduService extends HostApduService {
    @Override
    public byte[] processCommandApdu(byte[] apdu, Bundle extras) {
       ...
    }
    @Override
    public void onDeactivated(int reason) {
       ...
    }
}
```
The `public byte[] processCommandApdu(byte[] apdu, Bundle extras) {...}` is performing the data exchange between Anroid phones and NFC reader.
![image](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/c4111963-1aec-41b9-81e2-93967f59770a)

