/*
Discovery Message

{
"device": "ESP32",
"sensorType" : "Temperature",
"pattern" : [rainbowBars, outrunPeak, purpleBars, centerBars, changingBars, Waterfall]
}

*/

#include <ArduinoJson.h>
#include <mqtt_client.h>

#define DISCOVERY_TOPIC "homeassistant/light/sound-reactive-matrix/config"

#define COMMAND_TOPIC "sound-reactive-matrix/light/switch/cmd"
#define STATE_TOPIC "sound-reactive-matrix/light/switch/state"
#define BRIGHTNESS_COMMAND_TOPIC "sound-reactive-matrix/light/brightness/cmd"
#define BRIGHTNESS_STATE_TOPIC "sound-reactive-matrix/light/brightness/state"

#define EFFECTS_LIST_TOPIC "sound-reactive-matrix/light/effects/list"
#define EFFECTS_COMMAND_TOPIC "sound-reactive-matrix/light/effects/cmd"
#define EFFECTS_STATE_TOPIC "sound-reactive-matrix/light/effects/state"


void sendDiscoveryMessage()
{
    setupMQTT();


    StaticJsonDocument<256> jsonMessage;
    char rawMessage[256];

    // name

    //  command_topic
    //  payload_on: "ON"
    //  payload_off: "OFF"

    //  brightness
    //  brightness_command_topic
    //  brightness_scale
    //  brightness_state_topic

    //  effect_command_topic
    //  effect_list
    //  effect_state_topic


    jsonMessage["name"] = "sound-reactive-matrix";
    jsonMessage["cmd_t"] = COMMAND_TOPIC;
    jsonMessage["stat_t"] = STATE_TOPIC;
    jsonMessage["bri_scl"] = "255";
    jsonMessage["bri_cmd_t"] = BRIGHTNESS_COMMAND_TOPIC;
    jsonMessage["bri_stat_t"] = BRIGHTNESS_STATE_TOPIC;

    jsonMessage['fx_cmd_t'] = EFFECTS_COMMAND_TOPIC;
    jsonMessage['fx_stat_t'] = EFFECTS_STATE_TOPIC;
    jsonMessage["fx_stat_t"] = EFFECTS_LIST_TOPIC;

    JsonArray effects = jsonMessage.createNestedArray("fx_list");
    effects.add("rainbowBars");
    effects.add("outrunPeak");
    effects.add("purpleBars");
    effects.add("centerBars");
    effects.add("changingBars");
    effects.add("Waterfall");

    serializeJson(jsonMessage, rawMessage);
    
    mqttClient.publish(DISCOVERY_TOPIC, 1, true, rawMessage);
}