#include "esphome.h"
#include "Adafruit_VEML7700.h"

class VEML7700Sensor : public PollingComponent, public Sensor {
    public:
    Adafruit_VEML7700 veml = Adafruit_VEML7700(4096, 32768);

    Sensor *lux_sensor = new Sensor();
    Sensor *als_sensor = new Sensor();

    VEML7700Sensor() : PollingComponent(15000) {}

    void setup() override {
        Wire.begin();
        veml.begin();
        veml.enable(false);
        veml.setGain(VEML7700_GAIN_1);
        veml.setIntegrationTime(VEML7700_IT_100MS);
        ESP_LOGD("VEML7700", "Initial setup complete, Gain=1, IntegtationTime=100ms");
        veml.enable(true);
    }

    void update() override {
        uint16_t raw = veml.readALS();
        ESP_LOGD("VEML7700", "Initial ALS reading: %u", raw);
        ESP_LOGD("VEML7700", "Initial gain value = %.3f", veml.getGainValue());
        ESP_LOGD("VEML7700", "Initial integration time factor = %.3f", veml.getIntegrationTimeFactor());

        // Determine whether gain/integtation time can be optimized to improve measurement
        bool optimalParams = !veml.optimizeParams(raw);

        // if optimization is indicated, wait for refresh time, take a new measurement,
        // then check if further optimization is possible.
        while (!optimalParams) {
            ESP_LOGD("VEML7700", "VEML parameters RE-optimized.");
            ESP_LOGD("VEML7700", "Now using gain = %.3f", veml.getGainValue());
            ESP_LOGD("VEML7700", "Now using integration time factor = %.3f", veml.getIntegrationTimeFactor());
            delay(veml.getRefreshTime());
            raw = veml.readALS();
            ESP_LOGD("VEML7700", "Updated ALS reading: %d", raw);
            optimalParams = !veml.optimizeParams(raw);
        }

        float lux = veml.convertToLux(raw);

        ESP_LOGD("VEML7700", "The value of sensor ALS is: %u", raw);
        ESP_LOGD("VEML7700", "The value of sensor lux is: %.2f", lux);

        lux_sensor->publish_state(lux);
        als_sensor->publish_state(raw);
    }
};
