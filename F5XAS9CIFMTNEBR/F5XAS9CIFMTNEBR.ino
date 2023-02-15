#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire); //how it works here? //remember, it's "Arduino time"

#define DS18B20_COUNT  9

 union sensor_address{
        uint8_t sensor_address_byte_table[8];
        uint64_t sensor_address_u64;
      };  


 struct used_temperature_sensor{

        union sensor_address ID;
        uint8_t sensor_physical_order_no;  
        uint8_t assigned_discovery_number;
        int32_t offset_calibration;
        };

int sensors_count;
used_temperature_sensor DS18B20_table[DS18B20_COUNT];
 
 
void setup(void)
{
  sensor_address tempDS18B20_address;
  
//used sensor adressess
  DS18B20_table[0] = {{0x28, 0x96, 0x00, 0x00, 0x9A, 0x5C, 0x00, 0x65}, 0, 0xFF, 184}; //why extended init did not work? maybe only during init and def?//C allows nesting, c++ not, that's why
  DS18B20_table[1] = {{0x28, 0xC8, 0x00, 0x00, 0x11, 0x63, 0x00, 0xCE}, 1, 0xFF, 144};
  DS18B20_table[2] = {{0x28, 0x96, 0x00, 0x00, 0x99, 0x46, 0x00, 0x8A}, 2, 0xFF}, 16;
  DS18B20_table[3] = {{0x28, 0x96, 0x00, 0x00, 0xB2, 0x4A, 0x00, 0x92}, 3, 0xFF, 88};
  DS18B20_table[4] = {{0x28, 0xAF, 0x00, 0x00, 0xD8, 0x10, 0x01, 0xE8}, 4, 0xFF, -16};
  DS18B20_table[5] = {{0x28, 0xC8, 0x00, 0x00, 0xC6, 0x0C, 0x00, 0xEF}, 5, 0xFF, 312};
  DS18B20_table[6] = {{0x28, 0xC8, 0x00, 0x00, 0x6A, 0x20, 0x00, 0x2E}, 6, 0xFF, 216};
  DS18B20_table[7] = {{0x28, 0xC8, 0x00, 0x00, 0x31, 0x61, 0x00, 0xCB}, 7, 0xFF, 144};
  DS18B20_table[8] = {{0x28, 0x96, 0x00, 0x00, 0xBD, 0x64, 0x00, 0xD0}, 8, 0xFF, 8};
  
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  
  // Start up the library
  sensors.begin();
  //get sensors info (number etc)
  sensors_count = sensors.getDS18Count();
Serial.println("init sensor count");
Serial.print(sensors_count);
   for (int i = 0; i < sensors_count; i++){

        sensors.getAddress(tempDS18B20_address.sensor_address_byte_table, i); //table / sensor number

        for (int j=0; j<DS18B20_COUNT; j++) {
          if(DS18B20_table[j].ID.sensor_address_u64 == tempDS18B20_address.sensor_address_u64) DS18B20_table[j].assigned_discovery_number = i;
          //some cheking in later
      
        }
  }

}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
//  uint8_t DS18B20_address[8]; //adress is 8-byte long for each sensor

  //read available sensors

 // for (int i =0; i < sensors_count; i++){

 //sensors.getAddress(DS18B20_address, i); //table / sensor number


 // }
  
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("");

for (int i =0; i <DS18B20_COUNT ; i++){
  
  //Serial.print(sensors.getTempCByIndex(DS18B20_table[i].assigned_discovery_number)); // Why "byIndex"? 
  //Serial.print("\t");
Serial.print(sensors.getTemp(DS18B20_table[i].ID.sensor_address_byte_table));
Serial.print(" ");

  Serial.print((float) (sensors.getTemp(DS18B20_table[i].ID.sensor_address_byte_table)+DS18B20_table[i].offset_calibration)/128.f); //9bit res, 1/128 temp value
  //Serial.print(".");
  //Serial.print((sensors.getTemp(DS18B20_table[i].ID.sensor_address_byte_table)%128)/128);//get some value after colon, make this binary shift later
  Serial.print(";");

  }
  Serial.println("");
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
    delay(30000);
    //test for raw values 
    

}

