#include "pico/stdlib.h"
#include <arduino.h>
#include <SimRelay.h>

unsigned long previusDebug = 0; //Stores last time data sent
unsigned long intervalDebug = 200; //Stores interval time data sends
bool debug = 0 ;
bool debug_text = 0 ;

//Buttons / Brakers
bool Br1; //Closed (braken to mute bells)
bool Br2; //Closed (braken to activate the Signalling)

//Relays
bool Iv;	//trackdetection from Iv  (activate)
bool Sv;	//trackdetection at crossing (normally just 50m in real world)
bool IIv;	//trackdetection from IIv (activate)
bool Akv;	//Stop signalling
bool Vv;	//Signalling

//Help relay
bool xVS;	//VS Lamp

const int OccIv  =  2; // Iv
const int OccSv  =  3; // Sv
const int OccIIv =  4; // IIv
const int BtnBr1 =  6; // Br1 Turn off Sound
const int BtnBr2 =  5; // Br2 Start signalling

int WarnRi = 21; //Warning Car Right
int WarnLe = 20; //Warning Car Left
int Bells   = 19; //Sound / Bells

int VSiWh  = 17; //Train Signal white (proceed)
int VSiRe  = 16; //Train Signal red   (Stop)

unsigned long millisLast;

static void SRelayhandler(uint8_t Id, uint8_t RState) {
 bool status=1;
  if (RState == 0) {status=0;}
  switch (Id){

	case 0: Iv  = RState; break;
	case 1:	Sv  = RState; break;
	case 2: IIv = RState; break;
	case 3: Br1 = RState; break;
    case 4: Br2 = RState; break;
	case 5: Vv  = RState; break;

} // End switch
} // End SRelayhandler

//SRelay::SRelay(         uint8_t id,
  //                           bool ref,
  //                             int turnon,
  //                                       int turnoff,
  //                                               SRelayHandler_t handlerFn):
  static SRelay SrIv       (0 ,0,500      ,10    , SRelayhandler);
  static SRelay SrSv       (1 ,0,500      ,10    , SRelayhandler);
  static SRelay SrIIv      (2 ,0,500      ,10    , SRelayhandler);
  static SRelay SrBr1      (3 ,0,10       ,10    , SRelayhandler);
  static SRelay SrBr2      (4 ,0,10       ,10    , SRelayhandler);
  static SRelay Vv_R       (5 ,0,0        ,100   , SRelayhandler);

// index to previousMillis[x] storage
int bl40 =  0; //blink 40/min, previous timer index nr
int bl60 =  1; //blink 60/min, previous time
int bl80 =  2; //blink 80/min, previous time
int bl120 = 3; //blink 80/min, previous time
unsigned long previousMillis[4];  // Variable for blink timing
unsigned long currentMillis;   // Variable for current loopstart time
bool State[4] = {false,false,false,false};

void setup() {
Serial.begin(9600); //USB

  pinMode(OccIv,  INPUT_PULLDOWN);
  pinMode(OccSv,  INPUT_PULLDOWN);
  pinMode(OccIIv, INPUT_PULLDOWN);
  pinMode(BtnBr1, INPUT_PULLDOWN);
  pinMode(BtnBr2, INPUT_PULLDOWN);
  
  pinMode(WarnRi, OUTPUT);
  pinMode(WarnLe, OUTPUT);
  pinMode(Bells,   OUTPUT);
  pinMode(VSiRe,  OUTPUT);
  pinMode(VSiWh,  OUTPUT);
  }

  static void pollSRelays() {
  SrIv.update	(digitalRead(OccIv));
  SrSv.update	(digitalRead(OccSv));
  SrIIv.update	(digitalRead(OccIIv));
  SrBr1.update	(digitalRead(BtnBr1));
  SrBr2.update	(digitalRead(BtnBr2));
  //		Vv = Br2 *  (Iv *  IIv +  Akv *  Sv) *  (Vv +  Sv)
  Vv_R.update	(Br2 && (Iv && IIv || Akv && Sv) && (Vv || Sv));
  }

  bool blink (int timer,int rate) {
  unsigned long interval = 60000/rate/2;   // 1 min / rate / 2

	if (currentMillis >= (previousMillis[timer] + interval)) {
	  previousMillis[timer] = currentMillis;
	  State[timer] = !State[timer];
	  //digitalWrite(ledPin,State) ;
	}
	return State[timer];
  }

  void loop() {
  pollSRelays();
  currentMillis = millis();  // Loop Starttime
 
  //Automatik (se även static void pollSRelays()
  //Akv = (/Iv *  IIv +  Iv *  /IIv) *  (/Sv +  Akv)
  Akv =   (!Iv && IIv || Iv && !IIv) && (!Sv || Akv);
  xVS =   ((!Akv || !Sv) && !Vv);
  
  digitalWrite(WarnRi,(!Vv && blink(bl80,80)));
  digitalWrite(WarnLe,(!Vv && !blink(bl80,80)));
  
  digitalWrite(Bells,(!Vv && Br1));

  digitalWrite(VSiRe,(!xVS));
  //			VS =  (/Akv +  /Sv) *  /Vv
  digitalWrite(VSiWh,(xVS));

if (debug_text){
  //Hanterar Seriell backfeed text
  //time hadle interval Serial send data
  unsigned long Millis_Debug = millis(); //Get current time

  //Check if it's time to send
  if (Millis_Debug - previusDebug >= intervalDebug)
	{previusDebug = Millis_Debug; //save current time

	//Serilal monitor
	//Has to be first, clear screen first, then write new information
	//#### Serial terminal
	Serial.write(12);//FF Form Feed, New Page
	//#### End Serial terminal

	Serial.print("Iv");Serial.print("\t");Serial.print(Iv);Serial.print("\t");Serial.print("Sv");Serial.print("\t");Serial.print(Sv);Serial.print("\t");Serial.print("IIv");Serial.print("\t");Serial.print(IIv);
	Serial.print("\n\r");
	Serial.print("Akv");Serial.print("\t");Serial.print(Akv);
	Serial.print("\n\r");
	Serial.print("Vv");Serial.print("\t");Serial.print(Vv);
	Serial.print("\n\r");
	Serial.print("VSiWh");Serial.print("\t");Serial.print(xVS);
	Serial.print("\n\r");
	Serial.print("Br1");Serial.print("\t");Serial.print(Br1);Serial.print("\t");Serial.print("Br2");Serial.print("\t");Serial.print(Br2);

	//Last row
	Serial.print("\n\r");
	}
}
  }
