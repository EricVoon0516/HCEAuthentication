# HCEAuthentication
This repository contains development of security system with the implementation of HCE, HCE Android application development and Arduino codes.
Using Arduino to enabling HCE features of Android phone. Get yourself familiar to Java <sup> (Java or Kotlin, it depends on yourself; I prefer Java because there are many resources that I found is in Java) </sup> and C (C & C++) programming languages.

## Things You Need to Know before Downloading the Code File:
   1. The `Android HCE.zip` is same as `AndroidHCE`, the difference is just one is compressed and another one is original file.
      > You can directly import `AndroidHCE` as a project in Android Studio. Documentation: https://developer.android.com/studio/intro/migrate
   2. Study the `README.md` of this repository and supported documention regarding implementain of HCE before developing HCE application.
   3. `AndroidHCE` and `Android HCE.zip` require minimum API (application programming interface, [What is API](https://developer.android.com/guide/topics/manifest/uses-sdk-element#ApiLevels)) is **26 (Android 8.0)** for emulating and implementing to Android phone. 
      
> **Disclaimer:**
>
> **As the author of the code provided, I want to make it clear that this code is intended for educational and illustrative purposes only. While I have made efforts to ensure the accuracy and functionality of the code, it may still contain errors, bugs, or unintended behaviors. Therefore, I cannot guarantee its suitability for any specific purpose or its fitness for any particular application.**
> 
> **You are free to use, modify, and distribute this code as per the terms of the applicable licenses and laws. However, I assume no responsibility or liability for any direct or indirect damages, loss of data, or any other negative consequences that may arise from the use or misuse of this code.**
> 
> **Before using this code in any critical or production environments, it is strongly recommended to thoroughly review and test it to ensure its reliability and security. Additionally, I advise seeking professional assistance or guidance for complex or sensitive projects.**
> 
> **By using this code, you acknowledge and accept that I am not responsible for any consequences resulting from its use and agree to hold me harmless from any claims, damages, or liabilities that may arise.**
> 
> **Please use this code responsibly and at your own risk. Always exercise caution and use your best judgment when working with code or software.**
>
> Happy coding and have fun with NFC :smile:


## List of Materials:
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
Path: [AndroidHCE](https://github.com/EricVoon0516/HCEAuthentication/tree/main/AndroidHCE)
> Requires minSDK is **26 (Android 8.0)**
> 
After reading the documentation provided by Android Developer, you will notice:
> Before you develop an Android application with HCE features, please study the declaration of manifest and AID registration: https://developer.android.com/guide/topics/connectivity/nfc/hce#manifest-declaration
> 
> Without the registration of AID and delcaration of HCE service, you cannot enable HCE features in your application. Appication ID (AID) is important to help the Android phones for recognising the application protocol data unit (APDU) command from the NFC reader. You can have multiple AIDs within a category.
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
Path: [Arduino Coding](https://github.com/EricVoon0516/HCEAuthentication/tree/bbd375988e1c878463f3124cf35a9e5a6d1b3a98/APDU_Command)

> You can refer to the documentation[^1].
> 
> In this section, I will briefly guide you through the Arduino coding. Firstly, you need to prepare yourself an Arduino, regardless which board that you are going to use <sup> (just make sure it is Arduino compatible) </sup>, and install Arduino IDE to your computer. You are welcome to use any board other than Arduino <sup> (eg. Raspberry) </sup>, but I am going to use Arduino to demonstrate the implementation of HCE authentication.

   1. Download the library: https://github.com/elechouse/PN532/tree/PN532_HSU
Be aware that zipfile contains mutliple libraries, you might need to extract and sort out all libraries, to prevent "libray not found" issue.
   2. You will see there is similar example for Android HCE. https://github.com/elechouse/PN532/blob/PN532_HSU/PN532/examples/android_hce/android_hce.ino.
You may use it or ammend the code according to the condition that you want.
```
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>

PN532_I2C pn532_i2c(Wire);
PN532 nfc(pn532_i2c);
```
> Remember to include the libraries that are required and its general setup.
> 
```
uint8_t selectApdu[] = {
  0x00, /* CLA */
  0xA4, /* INS */
  0x04, /* P1  */
  0x00, /* P2  */
  0x07, /* Length of AID  */
  0xF0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* AID  */
  0x00  /* Le  */
};
```
> This is an important array to define the APDU command for enabling Android HCE. As you can see, the `selectApdu[]` has the same value as we register for our AID {0xF0, 0x01, 0x02, 0x03, 0x04, 0x05 0x06}. You may change the AID but make sure you are following the rules that are stated in the documentation.
> 
```
uint8_t AvailableResponse[32];
uint8_t responseLength = 32;
```
> This `AvaliableResponse[32]` is the response sent from the Android phones. Do you still remember Android application we have the `String response = "Hello";` and converting this string response to bytes with `return response.getBytes();`. This return will response to the `AvailableResponse[32]` <sup> (only 32 bytes of responese is allowed in this case) </sup>.
> ![image](https://github.com/EricVoon0516/HCEAuthentication/assets/96558437/c4111963-1aec-41b9-81e2-93967f59770a)

```
bool success = nfc.inDataExchange(selectApdu, sizeof(selectApdu), AvailableResponse, &responseLength);  
if (success) {...}
```
> The `nfc.inDataExchange` will send the `selectApdu` and the size of the `selectApdu` to the HCE enabling Android phone for enbaling the application's HCE features.
> After the phone recognises the APDU <sup> (selectApdu) </sup>, the phone will response with the "result of the return" in bytes to the NFC reader
> > In this case, the phone received and recognised <sup> (this means the selectApdu has the same registered AID in the application) </sup> the APDU command and it will send 'Hello' in bytes which are `{0x48, 0x65, 0x6C, 0x6C, 0x6F}` to the reader as the response. Now, we can use the response for different condition, such as authentication.
> > The byte of data exchange between devices is the value of "string of characters" <sup> (referring hexadecimal value of each character in ASCII table, including special characters, special commands and spacing) </sup>; the devices will recognise those hex bytes for data transmission.
> > For example:
> > ```
> > /*
> > for (int n = 0; n < 5; n++)
> > /*
> >    The value 5 can be changed to the responseLength, meaning it will follow the size of response sent from Android phone.
> >    You may change the variable 'n' to other variable.
> >    This for loop is the iteration of comparing different bytes in same position of different arrays, this is a common method for UID's NFC authentication.
> > */ 
> > {
> >    //if (AvailableResponse[n] == ...) //Make sure it is comparing with other variables; this is the 
> >    {/* write your condition here*/}    
> > }
> > */
> > ```
> >
> > > This is example code for comapring bytes.
> > > ```
> > > ///////////////////////////////////////// Check Bytes   ///////////////////////////////////
> > >      bool checkTwo ( byte a[], byte b[] ) {   
> > >        for ( uint8_t k = 0; k < 4; k++ ) {   // Loop 4 times
> > >          if ( a[k] != b[k] ) {     // IF a != b then false, because: one fails, all fail
> > >             return false;
> > >          }
> > >        }
> > >        return true;  
> > >      }
> > > ```
> > > 
> > There are many ways to compare two variable for authentication, and this is the simpliest measure for authentication; this way of authentication has the limitation of authentication efficiency.
> 

   4. You may use the example code `android_hce` in `PN532` library, or you can try to modify the code <sup> (Just make sure those elements that I have mentioned are included in your code) </sup>. Yet, you may also need to study the documentation before starting this Android HCE application and Arduino coding. Have fun in coding 😄 🧑‍💻.




[^1]: The connection of PN532:   https://how2electronics.com/interfacing-pn532-nfc-rfid-module-with-arduino/
