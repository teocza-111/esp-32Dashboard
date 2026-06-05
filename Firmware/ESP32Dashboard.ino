#define DISABLE_LIBRARY
#define DISABLE_PLAYLISTS
#define DISABLE_METADATA
#define DISABLE_USER
#define DISABLE_SIMPLIFIED

#include <SpotifyEsp32.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include "secrets.h"

#define EPD_MOSI  9
#define EPD_SCK   7
#define EPD_CS    2
#define EPD_DC    3
#define EPD_RST   4
#define EPD_BUSY  8
#define BAT_ADC   1

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(
  GxEPD2_420(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY)
);

const char* WEATHER_URL =
  "https://api.open-meteo.com/v1/forecast"
  "?latitude=53.01&longitude=18.60"
  "&current=temperature_2m";


const unsigned long SPOTIFY_REFRESH_MS = 40000;
const unsigned long WEATHER_REFRESH_MS = 600000;

Spotify sp(SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET);

unsigned long lastSpotifyRefresh = 0;
unsigned long lastWeatherRefresh = 0;

struct DashboardData {
  String track     = "—";
  String artist    = "—";
  bool   isPlaying = false;
  float  tempC     = NAN;
  int    hour      = -1;
  int    lastDrawnHour = -2;
  float  batteryV  = 0.0f;
} data;

void fetchSpotify();
void fetchWeather();
void fetchTime();
void fetchBattery();
void drawDashboard();
void drawCentered(const char* text, int y);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("[boot] Starting...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[wifi] connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.printf("\n[wifi] Connected. IP: %s\n", WiFi.localIP().toString().c_str());

  configTime(7200, 0, "pool.ntp.org");
  Serial.print("[ntp] syncing");
  struct tm t;
  while (!getLocalTime(&t)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[ntp] Synced.");

  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  display.init(115200, true, 2, false);
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeSansBold18pt7b);
    drawCentered("Dashboard", 120);
    display.setFont(&FreeSans9pt7b);
    drawCentered("connect to sptify:", 165);
    String url = "http://" + WiFi.localIP().toString() + "/login";
    drawCentered(url.c_str(), 190);
  } while (display.nextPage());

  sp.begin();
  Serial.printf("[spotify] Auth URL: http://%s/login\n", WiFi.localIP().toString().c_str());
  while (!sp.is_auth()) {
    sp.handle_client();
  }
  Serial.println("[spotify] authenticated.");

  fetchTime();
  fetchWeather();
  fetchSpotify();
  fetchBattery();
  drawDashboard();

  lastSpotifyRefresh = millis();
  lastWeatherRefresh = millis();
}

void loop() {
  sp.handle_client();

  unsigned long now = millis();

  bool redraw = false;

  if (now - lastSpotifyRefresh >= SPOTIFY_REFRESH_MS) {
    lastSpotifyRefresh = now;
    fetchTime();
    fetchBattery();
    fetchSpotify();
    redraw = true;
  }

  if (now - lastWeatherRefresh >= WEATHER_REFRESH_MS) {
    lastWeatherRefresh = now;
    fetchWeather();
    redraw = true;
  }

  if (redraw) {
    drawDashboard();
  }
}


void fetchSpotify() {
  player_currently_playing_t result;
  if (!sp.currently_playing(result)) {
    Serial.println("[spotify] Nothing playing or fetch failed.");
    data.track     = "Nothing playing rn";
    data.artist    = "";
    data.isPlaying = false;
    return;
  }
  data.isPlaying = result.is_playing;
  data.track     = String(result.item.name);
  data.artist    = String(result.item.artists[0].name);
  Serial.printf("[spotify] %s – %s\n", data.artist.c_str(), data.track.c_str());
}

void fetchWeather() {
  HTTPClient http;
  http.begin(WEATHER_URL);
  int code = http.GET();
  if (code != 200) {
    Serial.printf("[weather] HTTP error %d\n", code);
    http.end();
    return;
  }
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, http.getStream());
  http.end();
  data.tempC = doc["current"]["temperature_2m"].as<float>();
  Serial.printf("[weather] %.1f°C\n", data.tempC);
}

void fetchTime() {
  struct tm t;
  if (!getLocalTime(&t)) {
    Serial.println("[time] Failed.");
    return;
  }
  data.hour = t.tm_hour;
}

void fetchBattery() {
  int raw = analogRead(BAT_ADC);
  data.batteryV = raw * (3.3f / 4095.0f) * 2.0f;
}

void drawDashboard() {
  Serial.println("[epd] Drawing...");

  int16_t x1, y1;
  uint16_t tw, th;

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.fillRect(0, 0, 400, 50, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);

    char hourStr[8];
    snprintf(hourStr, sizeof(hourStr), "%02d:00", data.hour >= 0 ? data.hour : 0);
    display.setFont(&FreeSansBold18pt7b);
    display.setCursor(12, 38);
    display.print(hourStr);

    char tempStr[12];
    if (isnan(data.tempC)) {
      snprintf(tempStr, sizeof(tempStr), "--°C");
    } else {
      snprintf(tempStr, sizeof(tempStr), "%.1f°C", data.tempC);
    }
    display.setFont(&FreeSansBold18pt7b);
    display.getTextBounds(tempStr, 0, 0, &x1, &y1, &tw, &th);
    display.setCursor(400 - tw - 12 - x1, 38);
    display.print(tempStr);

    display.setTextColor(GxEPD_BLACK);

    String playIcon = data.isPlaying ? "> " : "|| ";
    String track = data.track.length() > 22
                 ? data.track.substring(0, 21) + "~"
                 : data.track;
    String trackLine = playIcon + track;

    display.setFont(&FreeSansBold12pt7b);
    display.getTextBounds(trackLine.c_str(), 0, 0, &x1, &y1, &tw, &th);
    display.setCursor((400 - tw) / 2 - x1, 135);
    display.print(trackLine);

    display.setFont(&FreeSans12pt7b);
    String artist = data.artist.length() > 30
                  ? data.artist.substring(0, 29) + "~"
                  : data.artist;
    display.getTextBounds(artist.c_str(), 0, 0, &x1, &y1, &tw, &th);
    display.setCursor((400 - tw) / 2 - x1, 165);
    display.print(artist);

    display.drawLine(0, 200, 400, 200, GxEPD_BLACK);

    float pct = constrain((data.batteryV - 3.0f) / 1.2f, 0.0f, 1.0f);
    int barFill = (int)(120 * pct);
    display.drawRect(10, 212, 122, 20, GxEPD_BLACK);
    display.fillRect(132, 217, 4, 10, GxEPD_BLACK);
    display.fillRect(11, 213, barFill, 18, GxEPD_BLACK);

    display.setFont(&FreeSans9pt7b);
    char batStr[12];
    snprintf(batStr, sizeof(batStr), "%.2fV", data.batteryV);
    display.setCursor(142, 228);
    display.print(batStr);

    display.setCursor(300, 228);
    display.print("WiFi: ");
    display.print(WiFi.status() == WL_CONNECTED ? "OK" : "--");

  } while (display.nextPage());

  Serial.println("[epd] Done.");
}

void drawCentered(const char* text, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((400 - w) / 2 - x1, y);
  display.print(text);
}