# HCEAuthentication
This repository contains development of security system with the implementation of HCE, HCE Android application development and Arduino codes.
Using Arduino to enabling HCE features of Android phone

## List of materials:
   1. Arduino UNO
   2. PN532
   3. Android phones

## Software:
  1. Android Studio
  2. Arduino IDE

## Documentation
HCE Android development:  https://developer.android.com/guide/topics/connectivity/nfc/hce

The connection of PN532:  https://how2electronics.com/interfacing-pn532-nfc-rfid-module-with-arduino/

## Implementation
After reading the documentation provided by Android Developer, you will notice:
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
