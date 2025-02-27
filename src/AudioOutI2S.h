/*
  Copyright (c) 2016 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef _AUDIO_OUT_I2S_INCLUDED
#define _AUDIO_OUT_I2S_INCLUDED

#ifdef ESP_PLATFORM
  #include "driver/i2s.h"
#else
  #include <I2S.h>
#endif

#include <cstring>
#include "AudioOut.h"

class AudioOutI2SClass : public AudioOut
{
public:
  AudioOutI2SClass();
  virtual ~AudioOutI2SClass();

  #if defined ESP_PLATFORM
    #if defined ESP32
      //int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=35, const bool use_dac=true, const int esp32_i2s_port_number=0);
  int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=26, const int esp32_i2s_port_number=0);
    #elif defined ESP32S2
      //int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=35, const bool use_dac=true);
  int outBegin(long sampleRate=44100, int bitsPerSample=16, const int bit_clock_pin=5, const int word_select_pin=25, const int data_out_pin=26);
    #endif
  #endif

  virtual int canPlay(AudioIn& input);
  virtual int play(AudioIn& input);
  virtual int loop(AudioIn& input);

  virtual int pause();
  virtual int resume();
  virtual int stop();

  virtual int isPlaying();
  virtual int isPaused();

#ifdef I2S_HAS_SET_BUFFER_SIZE
  void setBufferSize(int bufferSize);
#endif

  // Manual data transmit
  virtual void transmit();

private:
  int startPlayback(AudioIn& input, bool loop);

  void onTransmit();

  static void onI2STransmit();

public:
  AudioIn* _input; // this belongs to private
private:
  //AudioIn* _input; // this belongs here
  bool _loop;
  bool _paused;
};

extern AudioOutI2SClass AudioOutI2S;

#endif
