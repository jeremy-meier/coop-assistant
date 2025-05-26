# Coop Assistant
An ESPHome based automatic chicken coop door integrated with Home Assistant

The Coop Assistant project has the following features:
* Integrated DHT22 temperature and humidity sensor
* Integrated VEML7700 ambient light sensor to enable automatic open/close of coop door
* Two inputs for reed relay door sensors - I use these for the nesting box and larger door in our coop
* Motor drive output for controlling a smaller door ('chicken door') via a linear actuator
  * This is integrated with Home Assisstant using a Cover component.  The ADS1115 Analog to Digital converter senses current in each leg of the H-bridge drive to determine when the door is closed.
  * Home Assistant can be used to configure manual operation of the chicken door, or automatic mode can be used to determine the lighting level when the door should be opened or closed.
* Output for connecting a 12V LED strip for coop lighting
* Inputs for connecting switches for manual Open/Close/Stop operations

See https://github.com/jeremy-meier/coop-assistant for additional documentation.
