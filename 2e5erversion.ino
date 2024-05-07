#include <FastLED.h> // Include the FastLED library
#include <WiFi.h>    // Include the WiFi library
#include <WebServer.h>

#define NUM_LEDS 343 // Total number of LEDs in the box (7x7x7)
#define DATA_PIN 33  // GPIO pin connected to the LED box

CRGB leds[NUM_LEDS]; // Declare an array of CRGB LEDs

// LED coordinates
int ledCoords[343][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6},
  {0, 1, 6}, {0, 1, 5}, {0, 1, 4}, {0, 1, 3}, {0, 1, 2}, {0, 1, 1}, {0, 1, 0},
  {0, 2, 0}, {0, 2, 1}, {0, 2, 2}, {0, 2, 3}, {0, 2, 4}, {0, 2, 5}, {0, 2, 6},
  {0, 3, 6}, {0, 3, 5}, {0, 3, 4}, {0, 3, 3}, {0, 3, 2}, {0, 3, 1}, {0, 3, 0},
  {0, 4, 0}, {0, 4, 1}, {0, 4, 2}, {0, 4, 3}, {0, 4, 4}, {0, 4, 5}, {0, 4, 6},
  {0, 5, 6}, {0, 5, 5}, {0, 5, 4}, {0, 5, 3}, {0, 5, 2}, {0, 5, 1}, {0, 5, 0},
  {0, 6, 0}, {0, 6, 1}, {0, 6, 2}, {0, 6, 3}, {0, 6, 4}, {0, 6, 5}, {0, 6, 6},

  {1, 6, 6}, {1, 6, 5}, {1, 6, 4}, {1, 6, 3}, {1, 6, 2}, {1, 6, 1}, {1, 6, 0},
  {1, 5, 0}, {1, 5, 1}, {1, 5, 2}, {1, 5, 3}, {1, 5, 4}, {1, 5, 5}, {1, 5, 6},
  {1, 4, 6}, {1, 4, 5}, {1, 4, 4}, {1, 4, 3}, {1, 4, 2}, {1, 4, 1}, {1, 4, 0},
  {1, 3, 0}, {1, 3, 1}, {1, 3, 2}, {1, 3, 3}, {1, 3, 4}, {1, 3, 5}, {1, 3, 6},
  {1, 2, 6}, {1, 2, 5}, {1, 2, 4}, {1, 2, 3}, {1, 2, 2}, {1, 2, 1}, {1, 2, 0},
  {1, 1, 0}, {1, 1, 1}, {1, 1, 2}, {1, 1, 3}, {1, 1, 4}, {1, 1, 5}, {1, 1, 6},
  {1, 0, 6}, {1, 0, 5}, {1, 0, 4}, {1, 0, 3}, {1, 0, 2}, {1, 0, 1}, {1, 0, 0},

  {2, 0, 0}, {2, 0, 1}, {2, 0, 2}, {2, 0, 3}, {2, 0, 4}, {2, 0, 5}, {2, 0, 6},
  {2, 1, 6}, {2, 1, 5}, {2, 1, 4}, {2, 1, 3}, {2, 1, 2}, {2, 1, 1}, {2, 1, 0},
  {2, 2, 0}, {2, 2, 1}, {2, 2, 2}, {2, 2, 3}, {2, 2, 4}, {2, 2, 5}, {2, 2, 6},
  {2, 3, 6}, {2, 3, 5}, {2, 3, 4}, {2, 3, 3}, {2, 3, 2}, {2, 3, 1}, {2, 3, 0},
  {2, 4, 0}, {2, 4, 1}, {2, 4, 2}, {2, 4, 3}, {2, 4, 4}, {2, 4, 5}, {2, 4, 6},
  {2, 5, 6}, {2, 5, 5}, {2, 5, 4}, {2, 5, 3}, {2, 5, 2}, {2, 5, 1}, {2, 5, 0},
  {2, 6, 0}, {2, 6, 1}, {2, 6, 2}, {2, 6, 3}, {2, 6, 4}, {2, 6, 5}, {2, 6, 6},

  {3, 6, 6}, {3, 6, 5}, {3, 6, 4}, {3, 6, 3}, {3, 6, 2}, {3, 6, 1}, {3, 6, 0},
  {3, 5, 0}, {3, 5, 1}, {3, 5, 2}, {3, 5, 3}, {3, 5, 4}, {3, 5, 5}, {3, 5, 6},
  {3, 4, 6}, {3, 4, 5}, {3, 4, 4}, {3, 4, 3}, {3, 4, 2}, {3, 4, 1}, {3, 4, 0},
  {3, 3, 0}, {3, 3, 1}, {3, 3, 2}, {3, 3, 3}, {3, 3, 4}, {3, 3, 5}, {3, 3, 6},
  {3, 2, 6}, {3, 2, 5}, {3, 2, 4}, {3, 2, 3}, {3, 2, 2}, {3, 2, 1}, {3, 2, 0},
  {3, 1, 0}, {3, 1, 1}, {3, 1, 2}, {3, 1, 3}, {3, 1, 4}, {3, 1, 5}, {3, 1, 6},
  {3, 0, 6}, {3, 0, 5}, {3, 0, 4}, {3, 0, 3}, {3, 0, 2}, {3, 0, 1}, {3, 0, 0},

  {4, 0, 0}, {4, 0, 1}, {4, 0, 2}, {4, 0, 3}, {4, 0, 4}, {4, 0, 5}, {4, 0, 6},
  {4, 1, 6}, {4, 1, 5}, {4, 1, 4}, {4, 1, 3}, {4, 1, 2}, {4, 1, 1}, {4, 1, 0},
  {4, 2, 0}, {4, 2, 1}, {4, 2, 2}, {4, 2, 3}, {4, 2, 4}, {4, 2, 5}, {4, 2, 6},
  {4, 3, 6}, {4, 3, 5}, {4, 3, 4}, {4, 3, 3}, {4, 3, 2}, {4, 3, 1}, {4, 3, 0},
  {4, 4, 0}, {4, 4, 1}, {4, 4, 2}, {4, 4, 3}, {4, 4, 4}, {4, 4, 5}, {4, 4, 6},
  {4, 5, 6}, {4, 5, 5}, {4, 5, 4}, {4, 5, 3}, {4, 5, 2}, {4, 5, 1}, {4, 5, 0},
  {4, 6, 0}, {4, 6, 1}, {4, 6, 2}, {4, 6, 3}, {4, 6, 4}, {4, 6, 5}, {4, 6, 6},

  {5, 6, 6}, {5, 6, 5}, {5, 6, 4}, {5, 6, 3}, {5, 6, 2}, {5, 6, 1}, {5, 6, 0},
  {5, 5, 0}, {5, 5, 1}, {5, 5, 2}, {5, 5, 3}, {5, 5, 4}, {5, 5, 5}, {5, 5, 6},
  {5, 4, 6}, {5, 4, 5}, {5, 4, 4}, {5, 4, 3}, {5, 4, 2}, {5, 4, 1}, {5, 4, 0},
  {5, 3, 0}, {5, 3, 1}, {5, 3, 2}, {5, 3, 3}, {5, 3, 4}, {5, 3, 5}, {5, 3, 6},
  {5, 2, 6}, {5, 2, 5}, {5, 2, 4}, {5, 2, 3}, {5, 2, 2}, {5, 2, 1}, {5, 2, 0},
  {5, 1, 0}, {5, 1, 1}, {5, 1, 2}, {5, 1, 3}, {5, 1, 4}, {5, 1, 5}, {5, 1, 6},
  {5, 0, 6}, {5, 0, 5}, {5, 0, 4}, {5, 0, 3}, {5, 0, 2}, {5, 0, 1}, {5, 0, 0},

  {6, 0, 0}, {6, 0, 1}, {6, 0, 2}, {6, 0, 3}, {6, 0, 4}, {6, 0, 5}, {6, 0, 6},
  {6, 1, 6}, {6, 1, 5}, {6, 1, 4}, {6, 1, 3}, {6, 1, 2}, {6, 1, 1}, {6, 1, 0},
  {6, 2, 0}, {6, 2, 1}, {6, 2, 2}, {6, 2, 3}, {6, 2, 4}, {6, 2, 5}, {6, 2, 6},
  {6, 3, 6}, {6, 3, 5}, {6, 3, 4}, {6, 3, 3}, {6, 3, 2}, {6, 3, 1}, {6, 3, 0},
  {6, 4, 0}, {6, 4, 1}, {6, 4, 2}, {6, 4, 3}, {6, 4, 4}, {6, 4, 5}, {6, 4, 6},
  {6, 5, 6}, {6, 5, 5}, {6, 6, 4}, {6, 5, 3}, {6, 5, 2}, {6, 5, 1}, {6, 5, 0},
  {6, 6, 0}, {6, 6, 1}, {6, 6, 2}, {6, 6, 3}, {6, 6, 4}, {6, 6, 5}, {6, 6, 6}
};

const char* ssid = "Tenda_277850";
const char* password = "naJGnH2j";

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up LED strip
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Route for animations
  server.on("/color_cycle", HTTP_POST, colorCycle);
  server.on("/rainbow", HTTP_POST, rainbow);
  server.on("/theater_chase", HTTP_POST, theaterChase);
  server.on("/fade", HTTP_POST, fade);
  server.on("/sparkle", HTTP_POST, sparkle);

  // Routes for LED control
  server.on("/toggle_led", HTTP_POST, toggleLED);
  server.on("/turn_off_all_leds", HTTP_POST, turnOffAllLEDs);
  
  // Use lambda function as the handler for turn_on_plane
  server.on("/turn_on_plane", HTTP_POST, [](){
    turnOnPlane();
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void colorCycle() {
  for (int i = 0; i < 256; i++) {
    fill_solid(leds, NUM_LEDS, CHSV(i, 255, 255));
    FastLED.show();
    delay(20);
  }
  server.send(200, "text/plain", "Color cycle animation finished");
}

void rainbow() {
  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  FastLED.show();
  delay(30);
  server.send(200, "text/plain", "Rainbow animation finished");
}

void theaterChase() {
  for (int j = 0; j < 3; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        leds[i + q] = CRGB::Red;
      }
      FastLED.show();
      delay(50);
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
  }
  server.send(200, "text/plain", "Theater chase animation finished");
}

void fade() {
  for (int i = 0; i < 256; i++) {
    fill_solid(leds, NUM_LEDS, CRGB(i, 255 - i, 0));
    FastLED.show();
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    fill_solid(leds, NUM_LEDS, CRGB(i, 255 - i, 0));
    FastLED.show();
    delay(10);
  }
  server.send(200, "text/plain", "Fade animation finished");
}

void sparkle() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  for (int i = 0; i < 50; i++) {
    int randomLed = random(NUM_LEDS);
    leds[randomLed] = CRGB::White;
    FastLED.show();
    delay(50);
    leds[randomLed] = CRGB::Black;
    FastLED.show();
    delay(50);
  }
  server.send(200, "text/plain", "Sparkle animation finished");
}

void toggleLED() {
  int x = server.arg("x").toInt();
  int y = server.arg("y").toInt();
  int z = server.arg("z").toInt();
  int g = server.arg("r").toInt();
  int r = server.arg("g").toInt();
  int b = server.arg("b").toInt();

  int ledIndex = getLedIndex(x, y, z);
  if (ledIndex != -1) {
    if (leds[ledIndex] == CRGB::Black) {
      leds[ledIndex] = CRGB(r, g, b);
    } else {
      leds[ledIndex] = CRGB::Black;
    }
    FastLED.show();
    server.send(200, "text/plain", "LED toggled");
  } else {
    server.send(404, "text/plain", "LED not found");
  }
}

void turnOffAllLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  server.send(200, "text/plain", "All LEDs turned off");
}

void turnOnPlane() {
  char axis = server.arg("axis").charAt(0);
  int plane = server.arg("plane").toInt();
  int r = server.arg("r").toInt();
  int g = server.arg("g").toInt();
  int b = server.arg("b").toInt();

  turnOnPlane(axis, plane, r, g, b);
  server.send(200, "text/plain", "Plane turned on");
}

int getLedIndex(int x, int y, int z) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (ledCoords[i][0] == x && ledCoords[i][1] == y && ledCoords[i][2] == z) {
      return i;
    }
  }
  return -1;
}

void turnOnPlane(char axis, int plane, int g, int r, int b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (axis == 'x' && ledCoords[i][0] == plane) {
      leds[i] = CRGB(r, g, b);
    } else if (axis == 'y' && ledCoords[i][1] == plane) {
      leds[i] = CRGB(r, g, b);
    } else if (axis == 'z' && ledCoords[i][2] == plane) {
      leds[i] = CRGB(r, g, b);
    }
  }
  FastLED.show();
}
