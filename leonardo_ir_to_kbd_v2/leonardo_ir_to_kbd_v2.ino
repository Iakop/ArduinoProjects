#include <IRremote.h>
#include <Keyboard.h>

#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
char print_buf[255];
#endif

//Backbone lib that registers and run remote- keypresses
#include "remote_map.h"

//Remote mapping libs - define which keydef remote presses map to
#include "optoma.h"
#include "carmp3.h"

//Keypress libs - for putting the keypresses wanted from keydef
#include "kodi_keys.h"

#define RECV_PIN 11

IRrecv myRecv(RECV_PIN);
decode_results results;
keydef_t keydef_val;

void setup(){
  //Setup IR receiver:
  myRecv.enableIRIn();
  //Register Optoma remote:
  register_remote(NEC, OPTOMA_PREFIX, &optoma_callback);
  //Register CarMP3 remote:
  register_remote(NEC, CARMP3_PREFIX, &optoma_callback);
  //Register Kodi keys:
  register_put_keys_callback(&put_kodi_keys);
  //Begin keyboard stream:
  Keyboard.begin();

  //Begin serial, if serial print debugging is enabled:
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  #endif
}

void loop() {
  //Check if IR receiver has gotten any results:
  if (myRecv.decode(&results)) {

    #ifdef SERIAL_DEBUG
    sprintf(print_buf, "Received remote press!\n\r");
    Serial.print(print_buf);
    #endif
    
    //Evaluate the remote signal to a keydef value:
    keydef_val = decode_remote(results.decode_type, results.value);
    //Put the keydef val as the corresponding keypress(es):
    put_keys(keydef_val);
    
    myRecv.resume(); // myRecv resumes recording
  }
}
