#pragma once

#include <Mesh.h>

#if defined(ESP32) || defined(RP2040_PLATFORM)
  #include <FS.h>
  #define FILESYSTEM  fs::FS
#elif defined(NRF52_PLATFORM) || defined(STM32_PLATFORM)
  #include <Adafruit_LittleFS.h>
  #define FILESYSTEM  Adafruit_LittleFS

  using namespace Adafruit_LittleFS_Namespace;
#endif

struct NodePrefs {  // persisted to file
    float airtime_factor;
    char node_name[32];
    double node_lat, node_lon;
    float freq;
    uint8_t tx_power_dbm;
    float rx_delay_base;
    float tx_delay_factor;
    uint32_t guard;
    uint8_t sf;
    uint8_t cr;
    float bw;
    uint8_t interference_threshold;
    uint8_t agc_reset_interval;   // secs / 4
    uint8_t sync_word;
    bool log_rx;
};

class CommonCLICallbacks {
public:
  virtual void savePrefs() = 0;
  virtual const char* getFirmwareVer() = 0;
  virtual const char* getBuildDate() = 0;
  virtual bool formatFileSystem() = 0;
  virtual void setLoggingOn(bool enable) = 0;
  virtual void eraseLogFile() = 0;
  virtual void dumpLogFile() = 0;
  virtual void setTxPower(uint8_t power_dbm) = 0;
  virtual void clearStats() = 0;
  virtual void applyTempRadioParams(float freq, float bw, uint8_t sf, uint8_t cr, uint8_t sync_word, int timeout_mins) = 0;
  virtual void applyRadioParams(float freq, float bw, uint8_t sf, uint8_t cr, uint8_t sync_word) = 0;
};

class CommonCLI {
  mesh::RTCClock* _rtc;
  NodePrefs* _prefs;
  mesh::Mesh* _mesh;
  CommonCLICallbacks* _callbacks;
  mesh::MainBoard* _board;
  char tmp[80];

  mesh::RTCClock* getRTCClock() { return _rtc; }
  void savePrefs();
  void loadPrefsInt(FILESYSTEM* _fs, const char* filename);

public:
  CommonCLI(mesh::MainBoard& board, mesh::RTCClock& rtc, NodePrefs* prefs, CommonCLICallbacks* callbacks, mesh::Mesh* mesh)
      : _board(&board), _rtc(&rtc), _prefs(prefs), _callbacks(callbacks), _mesh(mesh) { }

  void loadPrefs(FILESYSTEM* _fs);
  void savePrefs(FILESYSTEM* _fs);
  void handleCommand(uint32_t sender_timestamp, const char* command, char* reply);
};
