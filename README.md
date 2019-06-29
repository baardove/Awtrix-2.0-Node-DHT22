**AWTRIX - Node with DHT22 sensor**

Based on general code from AWTRIX

Change configuration and it should be good to go


**HARDWARE**

- ESP8266
- DHT-22 Temperature and Humidity sensor


*WIREING*

- DHT VCC and GROUND wired to 3.3v and Ground on ESP8266 (VCC 5v should also work)
- DHT Datapin wired to D4 (any digital pin could be used)


**CONFIG**

Change Wifi info
Change server IP
Update DHT22 datapin if necessary



**Introducing AWTRIX-Nodes**

AWTRIX Nodes are smart devices (based on ESP8266) that send their data directly to AWTRIX 2.0 and display it in the form of an app. For example, an AWTRIX node can measure temperature  with a DHT22 and send it to AWTRIX.

This is especially intended for users who do not have their own smarthome server like IOBroker, FHEM etc.

Download the template firmware for an AWTRIX Node, edit the node-conf.h and modify it in doJob to send a custom text and IconID. 

AWTRIX displays each node at the end of the apploop. After that, AWTRIX deletes the data. So if the node is offline or doesnt sends any data, the node is not longer displayed.
