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

// KISS Definitions
#define KISS_FEND  0xC0
#define KISS_FESC  0xDB
#define KISS_TFEND 0xDC
#define KISS_TFESC 0xDD

#define KISS_MASK_PORT   0xF0
#define KISS_MASK_CMD    0x0F

#define KISS_CMD_DATA    0x00
#define KISS_CMD_TXDELAY 0x01
#define KISS_CMD_PERSIST 0x02
#define KISS_CMD_SLTTIME 0x03
#define KISS_CMD_TXTAIL  0x04
#define KISS_CMD_FULLDUP 0x05
#define KISS_CMD_VENDOR  0x06
#define KISS_CMD_RETURN  0xFF

#define CMD_BUF_LEN_MAX 500

enum CLIMode { CLI, KISS };

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
    // KISS Config
    uint8_t kiss_port;
    uint8_t cli_mode;
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
  CLIMode _cli_mode = CLIMode::CLI;
  char _tmp[80];
  char _cmd[CMD_BUF_LEN_MAX];
  uint16_t _kiss_len;
  bool _kiss_esc;
  uint32_t _kiss_txdelay;

  mesh::RTCClock* getRTCClock() { return _rtc; }
  void savePrefs();
  void loadPrefsInt(FILESYSTEM* _fs, const char* filename);
  void parseSerialCLI();
  void parseSerialKISS();
  void handleCLICommand(uint32_t sender_timestamp, const char* command, char* resp);
  void handleKISSCommand(uint32_t sender_timestamp, const char* kiss_data, uint16_t len);

public:
  CommonCLI(mesh::MainBoard& board, mesh::RTCClock& rtc, NodePrefs* prefs, CommonCLICallbacks* callbacks, mesh::Mesh* mesh)
      : _board(&board), _rtc(&rtc), _prefs(prefs), _callbacks(callbacks), _mesh(mesh) {
        _cmd[0] = 0;
        _kiss_len = 0;
        _kiss_esc = false;
        _kiss_txdelay = 0;
        _cli_mode = (CLIMode)_prefs->cli_mode;
      }

  void loadPrefs(FILESYSTEM* _fs);
  void savePrefs(FILESYSTEM* _fs);
  void handleSerialData();
  CLIMode getCLIMode();
};
