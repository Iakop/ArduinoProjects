#ifndef CARMP3_H
#define CARMP3_H

#include <IRremote.h>
#include "remote_map.h"
#include "decoded_keydefs.h"

#define CARMP3_PREFIX 0x00FF

//Define the keys on the remote:
typedef enum   {
               BTN_0          = 0xFF6897,
               BTN_1          = 0xFF30CF,
               BTN_2          = 0xFF18E7,
               BTN_3          = 0xFF7A85,
               BTN_4          = 0xFF10EF,
               BTN_5          = 0xFF38C7,
               BTN_6          = 0xFF5AA5,
               BTN_7          = 0xFF42BD,
               BTN_8          = 0xFF4AB5,
               BTN_9          = 0xFF52AD,
               CH_DOWN        = 0xFFA25D,
               CH             = 0xFF629D,
               CH_UP          = 0xFFE21D,
               BTN_100        = 0xFF9867,
               BTN_200        = 0xFFB04F,
               PREV           = 0xFF22DD,
               NEXT           = 0xFF02FD,
               PLAY_PAUSE     = 0xFFC23D,
               VOL_DOWN       = 0xFFE01F,
               VOL_UP         = 0xFFA857,
               EQ             = 0xFF906F
               }
carmp3_code_t;

//Decoding callback, returns the keydefs specified:
uint8_t carmp3_callback(uint32_t code){
  switch((carmp3_code_t)code){
    case CH_UP:
      return DEF_POWER_ON;
      break;
    case CH_DOWN:
      return DEF_POWER_OFF;
      break;
    case BTN_2:
      return DEF_ARROW_UP;
      break;
    case BTN_8:
      return DEF_ARROW_DOWN;
      break;
    case BTN_4:
      return DEF_ARROW_LEFT;
      break;
    case BTN_6:
      return DEF_ARROW_RIGHT;
      break;
    case BTN_5:
      return DEF_ENTER;
      break;
    case BTN_1:
      return DEF_ESCAPE;
      break;
    case BTN_3:
      return DEF_BACK;
      break;
    case PLAY_PAUSE:
      return DEF_SPACE;
      break;
    case PREV:
      return DEF_PREV;
      break;
    case NEXT:
      return DEF_NEXT;
      break;
    case VOL_DOWN:
      return DEF_VOL_DOWN;
      break;
    case VOL_UP:
      return DEF_VOL_UP;
      break;
    case EQ:
      return DEF_MUTE;
      break;
    //Always default to DEF_INVALID
    default:
      return DEF_INVALID;
      break;
  }
  //Always default to DEF_INVALID
  return DEF_INVALID;
}

#endif /*CARMP3_H*/
