#ifndef KODI_KEYS_H
#define KODI_KEYS_H

#include <Keyboard.h>

void put_kodi_keys(keydef_t keydef_val){

  #ifdef SERIAL_DEBUG
  sprintf(print_buf, "Keydef value = 0x%02X\n\r", keydef_val);
  Serial.print(print_buf);
  #endif
  
  switch (keydef_val){
    case DEF_POWER_ON:
      //Pull the RPi power-on pin HIGH:
      break;
    case DEF_POWER_OFF:
      //Pull the RPi power-on pin LOW:
      break;
    case DEF_ARROW_UP:
      break;
    case DEF_ARROW_DOWN:
      break;
    case DEF_ARROW_LEFT:
      break;
    case DEF_ARROW_RIGHT:
      break;
    case DEF_ENTER:
      break;
    case DEF_ESCAPE:
      break;
    case DEF_BACK:
      break;
    case DEF_SPACE:
      break;
    case DEF_PREV:
      break;
    case DEF_NEXT:
      break;
    case DEF_VOL_DOWN:
      break;
    case DEF_VOL_UP:
      break;
    case DEF_MUTE:
      break;
    case DEF_INVALID:
      break;
    default:
      #ifdef SERIAL_DEBUG
      sprintf(print_buf, "Error in putting keys!\n\r");
      Serial.print(print_buf);
      #endif
      break;
  }
}

#endif /*KODI_KEYS_H*/
