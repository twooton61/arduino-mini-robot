#ifndef ROBO_TEMP_SENSOR_H
#define ROBO_TEMP_SENSOR_H

#include <AbstractRoboPart.h>
#include <DHT.h>

DHT m_weather_sensor(13, DHT11);

class RoboWeatherSensor : AbstractRoboPart {
  public:
  RoboWeatherSensor(RoboBrain& robo_brain, const int temp_input_pin)
  {
      robo_brain.add_part(this);
  }

  inline void setup() override {
    m_weather_sensor.begin();
  }

  inline float get_temperature_fahrenheit() {
    return m_weather_sensor.readTemperature(true);
  }

  inline float get_humidity() {
    return m_weather_sensor.readHumidity();
  }
};

#endif