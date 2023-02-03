/*
   Copyright 2019 Leon Kiefer

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <CorsairLightingProtocol.h>
#include <FastLED.h>

// Hint: The Arduino Uno does not have as much memory as the Arduino Mega, it may be that problems occur when a higher
// value is set here.

#define NUMBER_OF_LEDS_PER_FAN 9

#define DATA_PIN_FAN_1 7
#define DATA_PIN_FAN_2 2
#define DATA_PIN_FAN_3 4
#define DATA_PIN_FAN_4 3


#define DATA_PIN_CHANNEL_2 5
#define DATA_PIN_CHANNEL_3 6


CRGB ledsChannel1[36];
CRGB ledsChannel2[27];
CRGB ledsChannel3[27];



CorsairLightingFirmwareStorageEEPROM firmwareStorage;
CorsairLightingFirmware firmware(CORSAIR_LIGHTING_NODE_PRO, &firmwareStorage);
FastLEDControllerStorageEEPROM storage;
FastLEDController ledController(&storage);
CorsairLightingProtocolController cLP(&ledController, &firmware);
CorsairLightingProtocolSerial cLPS(&cLP);


void setup() {
	/*
	YOU MUST NOT USE Serial!
	Serial is used by CorsairLightingProtocolSerial!
	*/
	cLPS.setup();
  FastLED.addLeds<WS2812B, DATA_PIN_FAN_1, GRB>(ledsChannel1, NUMBER_OF_LEDS_PER_FAN * 0, NUMBER_OF_LEDS_PER_FAN);
  FastLED.addLeds<WS2812B, DATA_PIN_FAN_2, GRB>(ledsChannel1, NUMBER_OF_LEDS_PER_FAN * 1, NUMBER_OF_LEDS_PER_FAN);
  FastLED.addLeds<WS2812B, DATA_PIN_FAN_3, GRB>(ledsChannel1, NUMBER_OF_LEDS_PER_FAN * 2, NUMBER_OF_LEDS_PER_FAN);
  FastLED.addLeds<WS2812B, DATA_PIN_FAN_4, GRB>(ledsChannel1, NUMBER_OF_LEDS_PER_FAN * 3, NUMBER_OF_LEDS_PER_FAN);


  // normal strip on channel 2
  FastLED.addLeds<WS2812B, DATA_PIN_CHANNEL_2, GRB>(ledsChannel2, 27);
  FastLED.addLeds<WS2812B, DATA_PIN_CHANNEL_3, GRB>(ledsChannel3, 27);
  ledController.addLEDs(0, ledsChannel1, 36);
  ledController.addLEDs(1, ledsChannel2, 27);
  ledController.addLEDs(3, ledsChannel3, 27);

}
void loop() {
	cLPS.update();

	if (ledController.updateLEDs()) {
		FastLED.show();
	}
}
