/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2018 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __ES8388_H__
#define __ES8388_H__

#include "Arduino.h"
#include "AudioInI2S.h"
#include "AudioOutI2S.h"
#include "esxxx_common.h"
#include "audio_hal.h"
#include <Wire.h> // I2C config connection

//#ifdef __cplusplus
extern "C" {
//#endif

/* ES8388 address */
#define ES8388_ADDR 0x20  /*!< 0x22:CE=1;0x20:CE=0*/

/* ES8388 register */
#define ES8388_CONTROL1         0x00
#define ES8388_CONTROL2         0x01

#define ES8388_CHIPPOWER        0x02

#define ES8388_ADCPOWER         0x03
#define ES8388_DACPOWER         0x04

#define ES8388_CHIPLOPOW1       0x05
#define ES8388_CHIPLOPOW2       0x06

#define ES8388_ANAVOLMANAG      0x07

#define ES8388_MASTERMODE       0x08
/* ADC */
#define ES8388_ADCCONTROL1      0x09
#define ES8388_ADCCONTROL2      0x0a
#define ES8388_ADCCONTROL3      0x0b
#define ES8388_ADCCONTROL4      0x0c
#define ES8388_ADCCONTROL5      0x0d
#define ES8388_ADCCONTROL6      0x0e
#define ES8388_ADCCONTROL7      0x0f
#define ES8388_ADCCONTROL8      0x10
#define ES8388_ADCCONTROL9      0x11
#define ES8388_ADCCONTROL10     0x12
#define ES8388_ADCCONTROL11     0x13
#define ES8388_ADCCONTROL12     0x14
#define ES8388_ADCCONTROL13     0x15
#define ES8388_ADCCONTROL14     0x16
/* DAC */
#define ES8388_DACCONTROL1      0x17
#define ES8388_DACCONTROL2      0x18
#define ES8388_DACCONTROL3      0x19
#define ES8388_DACCONTROL4      0x1a
#define ES8388_DACCONTROL5      0x1b
#define ES8388_DACCONTROL6      0x1c
#define ES8388_DACCONTROL7      0x1d
#define ES8388_DACCONTROL8      0x1e
#define ES8388_DACCONTROL9      0x1f
#define ES8388_DACCONTROL10     0x20
#define ES8388_DACCONTROL11     0x21
#define ES8388_DACCONTROL12     0x22
#define ES8388_DACCONTROL13     0x23
#define ES8388_DACCONTROL14     0x24
#define ES8388_DACCONTROL15     0x25
#define ES8388_DACCONTROL16     0x26
#define ES8388_DACCONTROL17     0x27
#define ES8388_DACCONTROL18     0x28
#define ES8388_DACCONTROL19     0x29
#define ES8388_DACCONTROL20     0x2a
#define ES8388_DACCONTROL21     0x2b
#define ES8388_DACCONTROL22     0x2c
#define ES8388_DACCONTROL23     0x2d
#define ES8388_DACCONTROL24     0x2e
#define ES8388_DACCONTROL25     0x2f
#define ES8388_DACCONTROL26     0x30
#define ES8388_DACCONTROL27     0x31
#define ES8388_DACCONTROL28     0x32
#define ES8388_DACCONTROL29     0x33
#define ES8388_DACCONTROL30     0x34

typedef void *i2c_bus_handle_t;

// ES8388 adc(GPIO_NUM_21,GPIO_NUM_23,GPIO_NUM_18);
class ES8388 : public AudioInI2SClass, public AudioOutI2SClass
{
private:
  int _PA_ENABLE_GPIO = -1;
  int _i2c_scl_pin = -1;
  int _i2c_sda_pin = -1;
  audio_hal_codec_config_t _cfg;
  bool _i2c_initialized = false;
  int _bit_clock_pin;
  int _word_select_pin;
  int _codec_data_in_pin;
  int _codec_data_out_pin;
  TwoWire _wire;
public:
  //ES8388(int PA_ENABLE_GPIO, int i2c_scl_pin, int i2c_sda_pin, int bit_clock_pin, int word_select_pin, int data_in_pin);
  ES8388(int PA_ENABLE_GPIO, TwoWire wire=Wire, int bit_clock_pin=5, int word_select_pin=25, int codec_data_in_pin=26, int codec_data_out_pin=35);
  virtual ~ES8388();

  /* Audio In */
  #ifdef CONFIG_IDF_TARGET_ESP32
    //int begin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_in_pin=35, const int esp32_i2s_port_number=0);
  int begin(long sampleRate=44100, int bitsPerSample=16, bool use_external_mic=false, int esp32_i2s_port_number=0);
  #elif CONFIG_IDF_TARGET_ESP32S2
    //int begin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_in_pin=35);
  int begin(long sampleRate=44100, int bitsPerSample=16, bool use_external_mic=false);
  #endif // ifdef ESP
  virtual void end();

  /* Audio Out */
  #ifdef CONFIG_IDF_TARGET_ESP32
    //int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=26, const int esp32_i2s_port_number=0);
  int outBegin(long sampleRate=44100, int bitsPerSample=16, const int esp32_i2s_port_number=0);
  #elif CONFIG_IDF_TARGET_ESP32S2
    //int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=26);
  int outBegin(long sampleRate=44100, int bitsPerSample=16);
  #endif

  /* Original functions from ESP-ADF */

/**
 * @brief Initialize ES8388 codec chip
 *
 * @param cfg configuration of ES8388
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_init(audio_hal_codec_config_t *cfg);

/**
 * @brief Deinitialize ES8388 codec chip
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_deinit(void);

/**
 * @brief Configure ES8388 I2S format
 *
 * @param mode:  set ADC or DAC or both
 * @param fmt:   ES8388 I2S format
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_config_fmt(es_module_t mode, audio_hal_iface_format_t fmt);

/**
 * @brief Configure I2s clock in MSATER mode
 *
 * @param cfg:  set bits clock and WS clock
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_i2s_config_clock(es_i2s_clock_t cfg);

/**
 * @brief Configure ES8388 data sample bits
 *
 * @param mode:  set ADC or DAC or both
 * @param bit_per_sample:  bit number of per sample
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_set_bits_per_sample(es_module_t mode, es_bits_length_t bit_per_sample);

/**
 * @brief  Start ES8388 codec chip
 *
 * @param mode:  set ADC or DAC or both
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_start(es_module_t mode);

/**
 * @brief  Stop ES8388 codec chip
 *
 * @param mode:  set ADC or DAC or both
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_stop(es_module_t mode);

/**
 * @brief  Set voice volume
 *
 * @param volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_set_voice_volume(int volume);

/**
 * @brief Get voice volume
 *
 * @param[out] *volume:  voice volume (0~100)
 *
 * @return
 *     - ESP_OK
 *     - ESP_FAIL
 */
esp_err_t es8388_get_voice_volume(int *volume);

/**
 * @brief Configure ES8388 DAC mute or not. Basically you can use this function to mute the output or unmute
 *
 * @param enable enable(1) or disable(0)
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_set_voice_mute(bool enable);

/**
 * @brief Get ES8388 DAC mute status
 *
 *  @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_get_voice_mute(void);

/**
 * @brief Set ES8388 mic gain
 *
 * @param gain db of mic gain
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_set_mic_gain(es_mic_gain_t gain);

/**
 * @brief Set ES8388 adc input mode
 *
 * @param input adc input mode
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_config_adc_input(es_adc_input_t input);

/**
 * @brief Set ES8388 dac output mode
 *
 * @param output dac output mode
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_config_dac_output(es_dac_output_t output);

/**
 * @brief Write ES8388 register
 *
 * @param reg_add address of register
 * @param data data of register
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_write_reg(uint8_t reg_add, uint8_t data);

/**
 * @brief Print all ES8388 registers
 *
 * @return
 *     - void
 */
void es8388_read_all();

/**
 * @brief Configure ES8388 codec mode and I2S interface
 *
 * @param mode codec mode
 * @param iface I2S config
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface);

/**
 * @brief Control ES8388 codec chip
 *
 * @param mode codec mode
 * @param ctrl_state start or stop decode or encode progress
 *
 * @return
 *     - ESP_FAIL Parameter error
 *     - ESP_OK   Success
 */
esp_err_t es8388_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state);

/**
 * @brief Set ES8388 PA power
 *
 * @param enable true for enable PA power, false for disable PA power
 *
 * @return
 *      - void
 */
void es8388_pa_power(bool enable);

/**
 * @brief Set volume in range 0.0 ~ 100.0 %
 *
 * @param float number of volume in % (range 0.0 to 100.0)
 *
 * @return
 *      - void
 *
 * Sets volume for both input and output channels of ES8388 in its native db format
 * and sets volume of parent object
 */
void volume(float level);

int es8388_set_adc_dac_volume(int mode, int volume, int dot);

virtual int read(void* buffer, size_t size);

private:
esp_err_t es_write_reg(uint8_t slave_addr, uint8_t reg_add, uint8_t data);
esp_err_t es_read_reg(uint8_t reg_add, uint8_t *p_data);
int i2c_init();
int i2c_init(int i2c_scl_pin, int i2c_sda_pin);
}; // class ES8388

//#ifdef __cplusplus
}
//#endif

#endif //__ES8388_H__
