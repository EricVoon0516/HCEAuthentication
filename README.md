# HCEAuthentication
This repository contains development of security system with the implementation of HCE, HCE Android application development and Arduino codes.
Using Arduino to enabling HCE features of Android phone. Get yourself familiar to Java <sup> (Java or Kotlin, it depends on yourself; I prefer Java because there are many resources that I found is in Java) </sup> and C (C & C++) programming languages.

## List of materials:
   1. Arduino UNO
   2. PN532
   3. Android phones

## Software:
  1. Android Studio:   https://developer.android.com/studio?gclid=CjwKCAjw_aemBhBLEiwAT98FMq-8NRAZYn0AiymZutJLZKTLktTCV2I9DBgDXp8_HawybEUhCpFFCBoCIvsQAvD_BwE&gclsrc=aw.ds
  2. Arduino IDE:      https://www.arduino.cc/en/software

## Documentation
HCE Android development:   https://developer.android.com/guide/topics/connectivity/nfc/hce

The connection of PN532:   https://how2electronics.com/interfacing-pn532-nfc-rfid-module-with-arduino/

## Connection of PN532 to Arduino UNO
![PN532 Connection drawio](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/84884d53-21da-4b60-9d17-251f494be62f)

## Implementation
### Android Application Development
After reading the documentation provided by Android Developer, you will notice:
> Before you develop an Android application with HCE features, please study the declaration of manifest and AID registration: https://developer.android.com/guide/topics/connectivity/nfc/hce#manifest-declaration
> 
> Without the registration of AID and delcaration of HCE service, you cannot enable HCE features in your application. Appication ID (AID) is important to help the Android phones for recognising the application protocol data unit (APDU) command from the NFC reader. You can have multiple AIDs (the AID shall be can within an application.
   1. Before registering the AID, you will need to declare `<service>` in **manifest**'s `<application>`, as shown:
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

   2. Then, you will need to register for the AID. There are two different categories of AID you can register; payment or other.
   3. You need to create xml resource file (name it as `apduservice`) at the file path `.main\res\xml`.
> The name of the resource file can be ammended according to your preferences, but it should be same as the name you have declared in the manifest:`<meta-data android:name="android.nfc.cardemulation.host_apdu_service" android:resource=` **`"@xml/apduservice"`** `/>`.

This is the registration of AID:
```
<host-apdu-service xmlns:android="http://schemas.android.com/apk/res/android"
           android:description="@string/servicedesc"
           android:requireDeviceUnlock="false">
    <aid-group android:description="@string/aiddescription"
               android:category="other">
        <aid-filter android:name="F0010203040506"/>
        <aid-filter android:name="F0394148148100"/>
    </aid-group>
</host-apdu-service>
```
> The `<aid-filter>` is defining the AID in hexadecimal value. In this case, `<aid-filter android:name="F0010203040506"/>` means one of AIDs of this application <sup> (there are 2 AIDs have been registered in this scenario) </sup> is {0xF0, 0x01, 0x02, 0x03, 0x04, 0x05 0x06}.
> 
> It is important for the Android phones to recognise the APDU <sup> (APDU consists of AID) </sup> of this application for enabling HCE features of this particular application.
>
![HCE drawio](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/e90692c9-8b89-40b9-8508-fceb74d4ab70)
> Without the APDU command sent from the NFC reader, the phone will not be enabling the HCE for that application <sup> (your application) </sup>.
   4. Now, you can create `MyHostApduService` class <sup> (you might notice the name of the class is same as name of service in the manifest's `<service>`) </sup> and with the extend of `HostApduService`.
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
> The `public byte[] processCommandApdu(byte[] apdu, Bundle extras) {...}` is performing the data exchange between Anroid phones and NFC reader.

![image](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/c4111963-1aec-41b9-81e2-93967f59770a)
> > In this case, when the phone receives the APDU command from the NFC reader, the application will start `MainActivity.class` of the application and response with `Hello` in bytes, which are {0x48, 0x65, 0x6C, 0x6C, 0x6F} to the NFC reader.
> > 
> > The value of APDU command from NFC reader shall be same as the registered AID; the AID of this application is {0xF0, 0x01, 0x02, 0x03, 0x04, 0x05 0x06} and APDU command of NFC reader shall be the same.
>
> You can have different conditions when the phones recognise the APDU command. Just code it, and have fun. :smile:
> 
### Arduino Coding
> You can refer to the documentation[^1].
> In this section, I will briefly guide you through the Arduino coding.

[^1]: The connection of PN532:   https://how2electronics.com/interfacing-pn532-nfc-rfid-module-with-arduino/
