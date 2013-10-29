#include <OneWire.h>
#include <DallasTemperature.h>
#define SERIAL_BAUDRATE 19200
#define DS18B20_PIN 12
OneWire oneWire(DS18B20_PIN);
DallasTemperature tSensors(&oneWire);

void pf(const char *fmt, ... ){
    char tmp[256];
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 256, fmt, args);
    va_end (args);
    Serial.print(tmp);
}

void setup(void)
{
  Serial.begin(SERIAL_BAUDRATE);
  while(!Serial){
  }
  tSensors.begin();
  int deviceCount = tSensors.getDeviceCount();
  pf("There are %d device(s).\n", deviceCount);
  
  for(int i = 0; i < deviceCount; i++){
    uint8_t a[8];
    tSensors.getAddress(a, i);
    pf("Device index %d, address 0x %02x %02x %02x %02x %02x %02x %02x %02x\n", 
      i, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
  }
}

void loop(void)
{
  tSensors.requestTemperatures();
  float c = tSensors.getTempCByIndex(0);
  float f = tSensors.toFahrenheit(c);
  Serial.print("Temperature is ");
  Serial.print(c);
  Serial.print(" degree(Celsius), ");
  Serial.print(f);
  Serial.println(" degree(Fahrenheit).");
  delay(1000);
}

