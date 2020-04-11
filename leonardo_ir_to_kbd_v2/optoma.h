#ifndef OPTOMA_H
#define OPTOMA_H

#include <IRremote.h>
#include "remote_map.h"
#include "decoded_keydefs.h"

#define OPTOMA_PREFIX 0x4CB3

//Define the keys on the remote:
typedef enum   {
               ON             = 0x4CB340BF,
               OFF            = 0x4CB3748B,
               USER1          = 0x4CB36C93,
               USER2          = 0x4CB3A659,
               USER3          = 0x4CB36699,
               BRIGHTNESS     = 0x4CB3827D,
               CONTRAST       = 0x4CB342BD,
               MODE           = 0x4CB3A05F,
               KEYSTONE       = 0x4CB3E01F,
               ASPECT_RATIO   = 0x4CB326D9,
               ENABLE_3D      = 0x4CB3916E,
               MUTE           = 0x4CB34AB5,
               DB             = 0x4CB322DD,
               SLEEP_TIMER    = 0x4CB3C639,
               UP             = 0x4CB38877,
               LEFT           = 0x4CB308F7,
               RIGHT          = 0x4CB348B7,
               DOWN           = 0x4CB328D7,
               ENTER          = 0x4CB3F00F,
               MENU           = 0x4CB3708F,
               HDMI1          = 0x4CB36897,
               HDMI2          = 0x4CB30CF3,
               VGA1           = 0x4CB3D827,
               VGA2           = 0x4CB37887,
               VIDEO          = 0x4CB338C7,
               YPBPR          = 0x4CB3E817,
               EXTEND         = 0xFFFFFFFF
               }
optoma_code_t;

//Decoding callback, returns the keydefs specified:
uint8_t optoma_callback(uint32_t code){
  switch((optoma_code_t)code){
    case ON:
      return DEF_POWER_ON;
      break;
    case OFF:
      return DEF_POWER_OFF;
      break;
    case UP:
      return DEF_ARROW_UP;
      break;
    case DOWN:
      return DEF_ARROW_DOWN;
      break;
    case LEFT:
      return DEF_ARROW_LEFT;
      break;
    case RIGHT:
      return DEF_ARROW_RIGHT;
      break;
    //Always default to DEF_INVALID
    default:
      return DEF_INVALID;
      break;
  }
  //Always default to DEF_INVALID
  return DEF_INVALID;
}

#endif /*OPTOMA_H*/
