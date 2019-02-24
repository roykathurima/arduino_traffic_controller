#include <IRremote.h>

//#define PIN_DETECT 2

IRsend irsend;

double sensor[4][3];
double a = 0, b = 0, c = 0, d= 0, maxi;
void setup()
{
//   pinMode(PIN_DETECT, INPUT);
    //initialize pins 22 - 33 as input
   for(int i=18; i<29; i++){
    pinMode(i, INPUT);
    }
    //initialize pins 34 - 45 as output
  for(int i=34; i<46; i++){
    pinMode(i, OUTPUT);
  }
    Serial.begin(115200);
    Serial.println("READY");
 
   // attachInterrupt(digitalPinToInterrupt(PIN_DETECT), checkIRBeamBreak, RISING);
   /*
    for(int i=2; i<4; i++){
      attachInterrupt(digitalPinToInterrupt(i), checkIRBeamBreak, RISING);
      }
      */
    for(int i=18; i<22; i++){
      attachInterrupt(digitalPinToInterrupt(i), checkIRBeamBreak, RISING);
      }
    // Note : the IR emitter is on PIN #3 on the Uno and on PIN #9 on the MEGA
    irsend.enableIROut(38);
    IREmitterOn();
}

// Use this function instead of delay() as delay() does not work in interrupt callbacks
void pause(int ms) {
    // We need a loop as the largest value for delayMicroseconds that will produce an accurate delay is 16383
    for (int i = 0; i < ms; i++) {
        delayMicroseconds(1000);
    }
}

void IREmitterOff() {
    irsend.space(0);
    pause(60); // 60 ms is OK for my TSOP but should be tuned
}

void IREmitterOn() {
    irsend.mark(0);
    pause(10);
}

void switchOffOnIREmitter() {
    IREmitterOff();
    IREmitterOn();
}

void checkIRBeamBreak() {
//    int val = digitalRead(PIN_DETECT);
    for (int i=18; i<29; i++){
      for(int k=0; k<4; k++){
        for(int j=0; j<3; j++){
          sensor[k][j]= digitalRead(i);
          if (sensor[k][j] == LOW){
              return;
          }
          detachInterrupt(digitalPinToInterrupt(i));
          switchOffOnIREmitter();
          if(k==0 && sensor[k][j] == HIGH){
            a++;
            } else if (k==1 && sensor[k][j] == HIGH){
              b++;
              } else if (k==2 && sensor[k][j] == HIGH){
                c++;
                } else if (k==3 && sensor[k][j] == HIGH){
                  d++;
                  }
        }
      }
      }
    double maxi2, maxi3, maxi1, maxi4;
    maxi2 = fmax(a,b);
    maxi3 = fmax(maxi2,c);
    maxi = fmax(maxi3,d);
      if(maxi == a){
        maxi4 = fmax(b, c);
        maxi1 = fmax(maxi4, d);
        if(maxi1 == b){
          Serial.println("Arm 1 has highest traffic density followed by Arm 2");
          digitalWrite(36, HIGH);
          digitalWrite(38, HIGH);
          digitalWrite(40, HIGH);
          digitalWrite(43, HIGH);
        } else if(maxi1 == c){
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        digitalWrite(41, HIGH);
        digitalWrite(43, HIGH);
      } else if (maxi1 == d){
          digitalWrite(36, HIGH);
          digitalWrite(37, HIGH);
          digitalWrite(40, HIGH);
          digitalWrite(44, HIGH);
          }
          } else if (maxi == b){
            maxi4 = fmax(a, c);
            maxi1 = fmax(maxi4, d);
            if(maxi1 == a){
            digitalWrite(35, HIGH);
            digitalWrite(39, HIGH);
            digitalWrite(40, HIGH);
            digitalWrite(43, HIGH);
            } else if (maxi1 == c){
                  digitalWrite(34, HIGH);
                  digitalWrite(39, HIGH);
                  digitalWrite(41, HIGH);
                  digitalWrite(43, HIGH);
                  } else if (maxi1 == d){
                    digitalWrite(34, HIGH);
                    digitalWrite(39, HIGH);
                    digitalWrite(40, HIGH);
                    digitalWrite(44, HIGH);
                    }  
              }         else if (maxi == c){
                        maxi4 = fmax(b, a);
                        maxi1 = fmax(maxi4, d);
                        if (maxi1 == a){
                        digitalWrite(35, HIGH);
                        digitalWrite(37, HIGH);
                        digitalWrite(42, HIGH);
                        digitalWrite(43, HIGH);
                        } else  if (maxi1 == b){
                          digitalWrite(34, HIGH);
                          digitalWrite(38, HIGH);
                          digitalWrite(42, HIGH);
                          digitalWrite(43, HIGH);
                          } else if (maxi == d){
                            digitalWrite(34, HIGH);
                            digitalWrite(37, HIGH);
                            digitalWrite(42, HIGH);
                            digitalWrite(44, HIGH);
                            }
                      } else if (maxi == d){
                              maxi4 = fmax(b, c);
                              maxi1 = fmax(maxi4, a);
                              if(maxi1 == a){
                              digitalWrite(35, HIGH);
                              digitalWrite(37, HIGH);
                              digitalWrite(40, HIGH);
                              digitalWrite(45, HIGH);
                              } else if (maxi1 == b){
                                digitalWrite(34, HIGH);
                                digitalWrite(38, HIGH);
                                digitalWrite(40, HIGH);
                                digitalWrite(45, HIGH);
                                } else  if (maxi1 == c){
                                  digitalWrite(34, HIGH);
                                  digitalWrite(37, HIGH);
                                  digitalWrite(41, HIGH);
                                  digitalWrite(45, HIGH);
                                  }
                            }
    // LOW : no beam break
    // HIGH : beam break
    /*
    if (val == LOW)
        return;

    detachInterrupt(digitalPinToInterrupt(PIN_DETECT));
    switchOffOnIREmitter();
    if (digitalRead(PIN_DETECT) == HIGH) {
        Serial.println("IR BEAM BREAK !!!!");
    }
    */
    for(int i =18; i<29; i++){
    attachInterrupt(digitalPinToInterrupt(i), checkIRBeamBreak, RISING);
    }
    
}


void loop() {
  checkIRBeamBreak();
  delay(10000);
}
