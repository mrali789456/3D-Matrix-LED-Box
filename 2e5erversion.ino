#include <FastLED.h>
#include <WiFi.h>
#include <WebServer.h>

#define NUM_LEDS 343
#define DATA_PIN 33

CRGB leds[NUM_LEDS];

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

WebServer server(8080);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print ESP32 IP address to Serial Monitor
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());

  // Set up LED strip
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Routes for animations
  server.on("/", HTTP_GET, handleRoot);
  server.on("/color_cycle", HTTP_POST, colorCycle);
  server.on("/rainbow", HTTP_POST, rainbow);
  server.on("/theater_chase", HTTP_POST, theaterChase);
  server.on("/fade", HTTP_POST, fade);
  server.on("/sparkle", HTTP_POST, sparkle);
  server.on("/toggle_led", HTTP_POST, toggleLED);
  server.on("/turn_off_all_leds", HTTP_POST, turnOffAllLEDs);
  server.on("/turn_on_plane", HTTP_POST, [](){
    turnOnPlane();
  });

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
}

void handleRoot() {

  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>3D Matrix LED Box Experient</title>";
  html += "</head>";
  html += "<body style='background-color: yellow;'>"; // Set background color to green
  html += "<h1>3D Matrix LED Box Experient</h1>";
  html += "<form action='/turn_off_all_leds' method='post'><button type='submit'>Turn Off All LEDs</button></form>";
      html += "<h3>                        </h3>";
  html += "<img src=\"https://f8171bde27de.ngrok.app \" width=\"300\" height=\"200\">";
    html += "<h2>                        </h2>";
    html += "<h2>Animations application (after each animation you need to turn Off all leds):</h2>";
  html += "<form action='/color_cycle' method='post'><button type='submit'>Color Cycle</button></form>";
  html += "<form action='/rainbow' method='post'><button type='submit'>Rainbow</button></form>";
  html += "<form action='/theater_chase' method='post'><button type='submit'>Theater Chase</button></form>";
  html += "<form action='/fade' method='post'><button type='submit'>Fade</button></form>";
  html += "<form action='/sparkle' method='post'><button type='submit'>Sparkle</button></form>";
      html += "<h4>                        </h4>";
      html += "<h2>set led and turn it on with specific color:</h2>";
      html += "<h4>Here you need to fill all informations</h4>"; 
            html += "<h4>for example led (0,0,0) RGB(255,0,0) the led it will be turn On with the Red color</h4>";     
  html += "<form action='/toggle_led' method='post'><button type='submit'>Turn On/Off Single LED</button>";
  html += "<label for='x'>X:</label><input type='number' name='x' min='0' max='6'>";
  html += "<label for='y'>Y:</label><input type='number' name='y' min='0' max='6'>";
  html += "<label for='z'>Z:</label><input type='number' name='z' min='0' max='6'>";
  html += "<label for='r'>Red:</label><input type='number' name='r' min='0' max='255'>";
  html += "<label for='g'>Green:</label><input type='number' name='g' min='0' max='255'>";
  html += "<label for='b'>Blue:</label><input type='number' name='b' min='0' max='255'>";
  
  html += "</form>";
  
  
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
  
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
void turnOnAllLEDs() {
  fill_solid(leds, NUM_LEDS, CRGB::White); // or any other color you prefer
  FastLED.show();
  server.send(200, "text/plain", "All LEDs turned on");
}
