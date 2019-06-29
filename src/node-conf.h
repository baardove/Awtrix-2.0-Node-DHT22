///////////////////////// AWTRIXNODE CONFIG /////////////////////////

// Wifi Config
const char *ssid = "xxx";
const char *password = "xxx";
char *awtrix_server = "192.168.1.38";


// Node Config

//hardware
const int sensorpin = D4;  // Connect DHT sensor to GPIO D4


// temperature
 const char *nodenameT = "Temp";
 int iconIDT = 233;   // temp C

//Humidity
const char *nodenameH = "Humidity";
int iconIDH = 100;  // shower


const long interval = 30000;
