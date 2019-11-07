#include <IRremote.h>
#include <Keyboard.h>

#define RECV_PIN 11

IRrecv myRecv(RECV_PIN);
decode_results results;

// Enum for the remote codes
typedef enum remote_code_t { BTN_0,
                             BTN_1,
                             BTN_2,
                             BTN_3,
                             BTN_4,
                             BTN_5,
                             BTN_6,
                             BTN_7,
                             BTN_8,
                             BTN_9,
                             BTN_100,
                             BTN_200,
                             CH_DOWN,
                             CH,
                             CH_UP,
                             PREV,
                             NEXT,
                             PLAY_PAUSE,
                             VOL_DOWN,
                             VOL_UP,
                             EQ,
                             UNDEFINED = 0xFFFF};

remote_code_t evaluate(uint32_t data);
uint8_t remote_to_key(remote_code_t remote_code);

remote_code_t remote_code;
uint8_t keycode;


#ifdef SERIAL_DEBUG
char print_buf[255];
#endif

void setup(){
  myRecv.enableIRIn();
  Keyboard.begin();
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  #endif
}

void loop() {
  // Check if IR receiver has gotten any results:
  if (myRecv.decode(&results)) {
    // Evaluate the remote signal to a code
    remote_code = evaluate(results.value);
    #ifdef SERIAL_DEBUG
    sprintf(print_buf, "Remote = 0x%02x\n", remote_code);
    Serial.print(print_buf);
    #endif
    
    // In the code is defined, send it as a keycode to through usb:
    if (remote_code != UNDEFINED){
      keycode = remote_to_key(remote_code);
      Keyboard.write(keycode);
      #ifdef SERIAL_DEBUG
      sprintf(print_buf, "Keycode = 0x%02x\n", keycode);
      Serial.print(print_buf);
      #endif
    }
    
    myRecv.resume(); // myRecv gør sig klar til næste værdi.
  }
}

remote_code_t evaluate(uint32_t data){
  switch (data)
  {
    case 0xFF6897:  
      return BTN_0; 
      break;
    
    case 0xFF30CF:  
      return BTN_1; 
      break;

    case 0xFF18E7:  
      return BTN_2; 
      break;

    case 0xFF7A85:  
      return BTN_3; 
      break;

    case 0xFF10EF:  
      return BTN_4; 
      break;

    case 0xFF38C7:  
      return BTN_5; 
      break;

    case 0xFF5AA5:  
      return BTN_6; 
      break;

    case 0xFF42BD:  
      return BTN_7; 
      break;

    case 0xFF4AB5:  
      return BTN_8; 
      break;

    case 0xFF52AD:  
      return BTN_9; 
      break;

    case 0xFFA25D:  
      return CH_DOWN; 
      break;

    case 0xFF629D:  
      return CH; 
      break;

    case 0xFFE21D:  
      return CH_UP;
      break;

    case 0xFF9867:  
      return BTN_100; 
      break;

    case 0xFFB04F:  
      return BTN_200; 
      break;

    case 0xFF22DD:  
      return PREV; 
      break;

    case 0xFF02FD:  
      return NEXT; 
      break;

    case 0xFFC23D:  
      return PLAY_PAUSE; 
      break;

    case 0xFFE01F:  
      return VOL_DOWN; 
      break;

    case 0xFFA857:  
      return VOL_UP; 
      break;

    case 0xFF906F:  
      return EQ; 
      break;

    default:
      return UNDEFINED;
      break;
  }
  return UNDEFINED;
}

uint8_t remote_to_key(remote_code_t remote_code){
  switch (remote_code)
  {
    case BTN_4:  
      return KEY_LEFT_ARROW; 
      break;

    case BTN_6:  
      return KEY_RIGHT_ARROW; 
      break;

    case BTN_2:  
      return KEY_UP_ARROW; 
      break;

    case BTN_8:  
      return KEY_DOWN_ARROW; 
      break;

    case BTN_5:  
      return KEY_RETURN; 
      break;

    case BTN_1:  
      return KEY_ESC; 
      break;

    case BTN_3:  
      return KEY_BACKSPACE; 
      break;

    case PLAY_PAUSE:  
      return 0x20;
      break;

    case PREV:  
      return KEY_LEFT_ARROW; 
      break;

    case NEXT:
      return KEY_RIGHT_ARROW;
      break;

    default:
      return 0;
      break;
  }
  return 0;
}
