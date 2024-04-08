// Library for working with IMU modules 
#include <TroykaIMU.h> 
 
// Create an object for working with the accelerometer 
Barometer barometer ; 
 
void setup ( )  { 
    // Open the Serial port 
    Serial. begin ( 115200 ) ; 
    // Display a message about the start of 
    Serial. println ( "Barometer begin" ) ; 
    // Initialize the barometer 
    barometer. begin ( ) ; 
    // Display a message about successful initialization 
    Serial. println ( "Initialization completed" ) ; 
}
 
void loop ( )  { 
    // Create a variable for the atmospheric pressure value in Pascals 
    float pressurePascals = barometer. readPressurePascals ( ) ; 
    // Create a variable for the atmospheric pressure value in mmHg. 
    float pressureMillimetersHg = barometer. readPressureMillimetersHg ( ) ; 
    // Create a variable for the altitude above sea level 
    float altitude = barometer. readAltitude ( ) ; 
    // Create a variable for the ambient temperature value 
    float temperature = barometer. readTemperatureC ( ) ; 
 
    // Output data to the Serial port 
    Serial. print ( "Pressure: " ) ; 
    Serial. print ( pressurePascals ) ; 
    Serial. print ( "Pa \t " ) ; 
    Serial. print ( pressureMillimetersHg ) ; 
    Serial. print ( "mmHg \t " ) ; 
    Serial. print ( "Height: " ) ; 
    Serial. print ( altitude ) ; 
    Serial. print ( "m \t " ) ; 
    Serial. print ("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    delay(100);
}