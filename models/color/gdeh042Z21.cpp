#include "gdeh042Z21.h"
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/task.h"


//Place data into DRAM. Constant data gets placed into DROM by default, which is not accessible by DMA.
//full screen update LUT
DRAM_ATTR const epd_init_44 Gdeh042Z21::lut_vcom0_full={
0x20, {
0x00, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
},44};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_ww_full={
0x21, {
    0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_bw_full={
0x22,{
    0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_wb_full={
0x23,{
    0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_bb_full={
0x24,{
    0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
},42};

// new waveform created by Jean-Marc Zingg for the actual panel
#define T1 25 // color change charge balance pre-phase
#define T2  1 // color change or sustain charge balance pre-phase
#define T3  2 // color change or sustain phase
#define T4 25 // color change phase

DRAM_ATTR const epd_init_44 Gdeh042Z21::lut_20_vcom0_partial = {
0x20,{
  0x00, T1, T2, T3, T4, 1, // 00 00 00 00
  0x00,  1,  0,  0,  0, 1, // gnd phase
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00
},44};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_21_ww_partial={
0x21,{
  0x18, T1, T2, T3, T4, 1, // 00 01 10 00
  0x00,  1,  0,  0,  0, 1, // gnd phase - 12 till here
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_22_bw_partial={
0x22,{ // 10 w
  0x5A, T1, T2, T3, T4, 1, // 01 01 10 10
  0x00,  1,  0,  0,  0, 1, // gnd phase
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_23_wb_partial={
0x23,{
  0xA5, T1, T2, T3, T4, 1, // 10 10 01 01
  0x00,  1,  0,  0,  0, 1, // gnd phase
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
},42};

DRAM_ATTR const epd_init_42 Gdeh042Z21::lut_24_bb_partial={
0x24,{
  0x24, T1, T2, T3, T4, 1, // 00 10 01 00
  0x00,  1,  0,  0,  0, 1, // gnd phase
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
},42};


// Constructor
Gdeh042Z21::Gdeh042Z21(EpdSpi& dio): 
  Adafruit_GFX(GDEH042Z21_WIDTH, GDEH042Z21_HEIGHT),
  Epd(GDEH042Z21_WIDTH, GDEH042Z21_HEIGHT), IO(dio)
{
  printf("Gdeh042Z21() constructor injects IO and extends Adafruit_GFX(%d,%d)\n",
  GDEH042Z21_WIDTH, GDEH042Z21_HEIGHT);  
}

//Initialize the display
void Gdeh042Z21::init(bool debug)
{
    debug_enabled = debug;
    if (debug_enabled) printf("Gdeh042Z21::init(%d) and reset EPD\n", debug);
    //Initialize the Epaper and reset it
    IO.init(4, debug); // 4MHz frequency, debug

    //Reset the display
    IO.reset(20);
    //setModel("GDEW042C37"); // Can be commented and set from your app_main()
    fillScreen(EPD_WHITE);

    IO.cmd(0x00);  // panel setting
    IO.data(0x2f); // LUT from OTP 400x300: No large initialization commands with this IC driver

    /*
    IO.cmd(lut_vcom0_full.cmd);
    IO.data(lut_vcom0_full.data,lut_vcom0_full.databytes);
   
    IO.cmd(lut_ww_full.cmd);
    IO.data(lut_ww_full.data,lut_ww_full.databytes);

    IO.cmd(lut_bw_full.cmd);
    IO.data(lut_bw_full.data,lut_bw_full.databytes);

    IO.cmd(lut_wb_full.cmd);
    IO.data(lut_wb_full.data,lut_wb_full.databytes);

    IO.cmd(lut_bb_full.cmd);
    IO.data(lut_bb_full.data,lut_bb_full.databytes);
 
    IO.cmd(0x25);
    IO.data(lut_bw_full.data,lut_bw_full.databytes);

    IO.cmd(0x26);
    IO.data(lut_bb_full.data,lut_bb_full.databytes);
    */

    // LUT Tables for partial update. Send them directly in 42 bytes chunks. In total 210 bytes
    IO.cmd(lut_20_vcom0_partial.cmd);
    IO.data(lut_20_vcom0_partial.data,lut_20_vcom0_partial.databytes);

    IO.cmd(lut_21_ww_partial.cmd);
    IO.data(lut_21_ww_partial.data,lut_21_ww_partial.databytes);

    IO.cmd(lut_22_bw_partial.cmd);
    IO.data(lut_22_bw_partial.data,lut_22_bw_partial.databytes);

    IO.cmd(lut_23_wb_partial.cmd);
    IO.data(lut_23_wb_partial.data,lut_23_wb_partial.databytes);

    IO.cmd(lut_24_bb_partial.cmd);
    IO.data(lut_24_bb_partial.data,lut_24_bb_partial.databytes);

    IO.cmd(0x25);
    IO.data(lut_22_bw_partial.data,lut_22_bw_partial.databytes);

    IO.cmd(0x26);
    IO.data(lut_22_bw_partial.data,lut_22_bw_partial.databytes);

    printf("Setting PLL...");

    IO.cmd(0x30);   // set PLL
    IO.data(0x39);
}

// Model setter. GDEH042Z15 is default but this class supports also GDEH042Z21  and  GDEW042C37
void Gdeh042Z21::setModel(std::string set_model) {
  model = set_model;
  printf("EPAPER model set to %s\n", set_model.c_str());
}

void Gdeh042Z21::_wakeUp() {
  IO.reset(10);
    
  IO.cmd(0x04);  
  _waitBusy("epd_wakeup"); // waiting for the electronic paper IC to release the idle signal
    
  // Without this Black appeared washed out near RED. If colors appear washed out try to "use boost soft start"
  if (model=="Gdeh042Z21") {
    printf("Sending additional boost soft start settings for %s\n", model.c_str());
    IO.cmd(0x06);   // panel setting
    IO.data(0x17);    // Boost soft start
    IO.data(0x18);
    IO.data(0x18);
  }
}

void Gdeh042Z21::_waitBusy(const char* message) {
  if (debug_enabled) {
    ESP_LOGI(TAG, "_waitBusy for %s", message);
  }
  int64_t time_since_boot = esp_timer_get_time();

  while (1) {
    if (gpio_get_level((gpio_num_t)CONFIG_EINK_BUSY) == 1) break;
    vTaskDelay(1);
    if (esp_timer_get_time()-time_since_boot>2000000) {
      if (debug_enabled) ESP_LOGI(TAG, "Busy Timeout");
      break;
    }
  }
}

void Gdeh042Z21::_sleep() {
    IO.cmd(0X50);  //VCOM AND DATA INTERVAL SETTING  
    IO.data(0xf7);
       
    IO.cmd(0X02);   //power off
    _waitBusy("power off");
    IO.cmd(0X07);   //deep sleep
    IO.data(0xA5);
}

void Gdeh042Z21::_rotate(uint16_t& x, uint16_t& y, uint16_t& w, uint16_t& h) {
  switch (getRotation()) {
    case 1:
      swap(x, y);
      swap(w, h);
      x = GDEH042Z21_WIDTH - x - w - 1;
      break;
    case 2:
      x = GDEH042Z21_WIDTH - x - w - 1;
      y = GDEH042Z21_HEIGHT - y - h - 1;
      break;
    case 3:
      swap(x, y);
      swap(w, h);
      y = GDEH042Z21_HEIGHT - y - h - 1;
      break;
  }
}

void Gdeh042Z21::update() {
  uint64_t startTime = esp_timer_get_time();
  _using_partial_mode = false;
  _wakeUp();


  // BLACK: Write RAM for black(0)/white (1)
  // v2 SPI optimizing. Check: https://github.com/martinberlin/cale-idf/wiki/About-SPI-optimization
  uint16_t i = 0;
  uint8_t xLineBytes = GDEH042Z21_WIDTH/8;
  uint8_t x1buf[xLineBytes];

// Note that in IC specs is 0x10 BLACK and 0x13 RED
// BLACK: Write RAM
  IO.cmd(0x10);
  for(uint16_t y =  1; y <= GDEH042Z21_HEIGHT; y++) {
        for(uint16_t x = 1; x <= xLineBytes; x++) {
          uint8_t data = i < sizeof(_black_buffer) ? _black_buffer[i] : GDEH042Z21_8PIX_WHITE;
          x1buf[x-1] = data;
          if (x==xLineBytes) { // Flush the X line buffer to SPI
            IO.data(x1buf,sizeof(x1buf));
          }
          ++i;
        }
    }
   
   i = 0;

  // RED: Write RAM
  IO.cmd(0x13);
    for(uint16_t y =  1; y <= GDEH042Z21_HEIGHT; y++) {
        for(uint16_t x = 1; x <= xLineBytes; x++) {
          uint8_t data = i < sizeof(_red_buffer) ? _red_buffer[i] : GDEH042Z21_8PIX_RED_WHITE;
          //printf("%x ",data);
          x1buf[x-1] = data;
          if (x==xLineBytes) {
            IO.data(x1buf,sizeof(x1buf));
          }
          ++i;
        }
    }

  uint64_t endTime = esp_timer_get_time();
  IO.cmd(0x12);     //DISPLAY REFRESH 

  _waitBusy("epaper refresh");
  uint64_t powerOnTime = esp_timer_get_time();

  // GxEPD comment: Avoid double full refresh after deep sleep wakeup
  // if (_initial) {  // --> Original deprecated 
  
  printf("\n\nSTATS (ms)\n%llu _wakeUp settings+send Buffer\n%llu _powerOn\n%llu total time in millis\n",
  (endTime-startTime)/1000, (powerOnTime-endTime)/1000, (powerOnTime-startTime)/1000);

  _sleep();
}

void Gdeh042Z21::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
  switch (getRotation())
  {
    case 1:
      swap(x, y);
      x = GDEH042Z21_WIDTH - x - 1;
      break;
    case 2:
      x = GDEH042Z21_WIDTH - x - 1;
      y = GDEH042Z21_HEIGHT - y - 1;
      break;
    case 3:
      swap(x, y);
      y = GDEH042Z21_HEIGHT - y - 1;
      break;
  }
  uint16_t i = x / 8 + y * GDEH042Z21_WIDTH / 8;
  
  // This formulas are from gxEPD that apparently got the color right:
  _black_buffer[i] = (_black_buffer[i] | (1 << (7 - x % 8))); // white pixel
  _red_buffer[i] = (_red_buffer[i] | (1 << (7 - x % 8)));     // white pixel

  if (color == EPD_WHITE) {
    //printf("w:%x ",_black_buffer[i]);
    return;
  }
  else if (color == EPD_BLACK) {
    _black_buffer[i] = (_black_buffer[i] & (0xFF ^ (1 << (7 - x % 8))));
    //printf("B ");
  }
  else if (color == EPD_RED) {
    _red_buffer[i] = (_red_buffer[i] & (0xFF ^ (1 << (7 - x % 8))));
    //printf("R %x ",_red_buffer[i]);
  }
}

void Gdeh042Z21::fillScreen(uint16_t color) {
  // Fill screen will be inverted with the way is done NOW
  uint8_t black = GDEH042Z21_8PIX_WHITE;
  uint8_t red = GDEH042Z21_8PIX_RED_WHITE;
  if (color == EPD_WHITE) {
    if (debug_enabled) printf("fillScreen WHITE\n");
  } else if (color == EPD_BLACK) {
    black = GDEH042Z21_8PIX_BLACK;
    if (debug_enabled) printf("fillScreen BLACK SELECTED\n");
  } else if (color == EPD_RED) {
    red = GDEH042Z21_8PIX_RED;
    if (debug_enabled) printf("fillScreen RED SELECTED\n");
  } else if ((color & 0xF100) > (0xF100 / 2)) {
    red = 0xFF;
  } else if ((((color & 0xF100) >> 11) + ((color & 0x07E0) >> 5) + (color & 0x001F)) < 3 * 255 / 2) {
    black = 0xFF;
  }
  
  for (uint16_t x = 0; x < sizeof(_black_buffer); x++)
  {
    _black_buffer[x] = black;
    _red_buffer[x] = red;
  }

  if (debug_enabled) printf("fillScreen(%x) black/red _buffer len:%d\n",color,sizeof(_black_buffer));
}

/*
const unsigned char lut_vcom0_quick[] = {
    0x00, 0x0E, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_ww_quick[] = {
    0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bw_quick[] = {
    0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bb_quick[] = {
    0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_wb_quick[] = {
    0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
*/
