#include "esphome.h"
#include "Adafruit_VEML7700.h"

class VEML7700Sensor : public PollingComponent, public Sensor {
    public:
    Adafruit_VEML7700 veml = Adafruit_VEML7700();

    Sensor *lux_sensor = new Sensor();
    Sensor *white_sensor = new Sensor();
    Sensor *als_sensor = new Sensor();

    VEML7700Sensor() : PollingComponent(5000) {}

    void setup() override {
        Wire.begin();
        veml.begin();
        ESP_LOGD("VEML7700", "Setting Up VEML7700 Sensor");
        veml.setGain(VEML7700_GAIN_1);
        veml.setIntegrationTime(VEML7700_IT_800MS);
        // veml.powerSaveEnable(true);
        // veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);
        // veml.setLowThreshold(10000);
        // veml.setHighThreshold(20000);
        // veml.interruptEnable(true);
    }

    void update() override {
        float lux = veml.readLux();
        float white = veml.readWhite();
        float als = veml.readALS();
        ESP_LOGD("VEML7700", "The value of sensor lux is: %.0f", lux);
        ESP_LOGD("VEML7700", "The value of sensor white is: %.0f", white);
        ESP_LOGD("VEML7700", "The value of sensor ALS is: %.0f", als);
        lux_sensor->publish_state(lux);
        white_sensor->publish_state(white);
        als_sensor->publish_state(als);
    }
};
