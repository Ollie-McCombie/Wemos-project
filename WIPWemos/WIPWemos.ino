#include <Streaming.h>
// -- OLED --
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define OLED_SCREEN_I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width
#define SCREEN_HEIGHT 64 // OLED display height
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

// -- Expansion Board --
#include <TM1638plus.h> 
#define STROBE_TM D5 // strobe 
#define CLOCK_TM D6 // clock 
#define DIO_TM D7 // data 
bool high_freq = false; 
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);
byte buttons;
// -- OLED and Expansion Board settings copied from WEMOS worksheets on MLS

bool phase_one{true};

void setup()
{
  phase_one = true;
  Serial.begin(115200);
  //Serial << endl << "Hello World" << endl;
  // ------------------------ OLED -----------------------------
  display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1); 
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display << "~~~~~SIMON SAYS~~~~~" << endl;
  display << "" << endl;
  display << "Lights will flash" << endl;
  display << "Once lights finished flashing" << endl;
  display << "input matching order" << endl;
  display << "Press 8 to Start" << endl;
  display.display();
  // ---------------------- Expansion Board --------------------------
  tm.displayBegin();
  tm.reset();
  byte buttons;
}

// --------------- LED Functions ---------------------
void LED_One()
{
  tm.setLEDs(0x0100);
  delay(1000);
  tm.setLEDs(0x0000);
  delay(500);
}

void LED_Two()
{
  tm.setLEDs(0x0200);
  delay(1000);
  tm.setLEDs(0x0000);
  delay(500);
}

void LED_Three()
{
  tm.setLEDs(0x0400);
  delay(1000);
  tm.setLEDs(0x0000);
  delay(500);
}

void LED_Four()
{
  tm.setLEDs(0x0800);
  delay(1000);
  tm.setLEDs(0x0000);
  delay(500);
}



// ------------ Program Main Body -------------
void loop()
{
// ------------- OUTPUT -----------------
  //Serial.print(phase_one);
  //Serial.print(endl);
  Serial <<phase_one << endl;
  if (phase_one == true){
    int counterOut{0};
    buttons = tm.readButtons();
    // if statement for "on button"
    if (buttons == 128){
        // looping 5 times to make random 5 digit sequence
      while (counterOut < 5){
        int randLED = random(0,4);
        // using randRead for ease of writing code
        int randRead = randLED + 1;
        int randArray[5];
        randArray[counterOut] = randRead;
        /* for testing
        int arrayOut = 0;
        arrayOut = randArray[counterOut];
        Serial.print(arrayOut);
        */
        switch(randLED){
          case 0:
            LED_One();
            break;

          case 1:
            LED_Two();
            break;

          case 2:
            LED_Three();
            break;

          case 3:
            LED_Four();
            break;

          default:
            break;
        } 
        counterOut++;
      }
      phase_one = false;
    }
  }
    // -------- INPUT -------
  else if(phase_one==false){
    int counterIN;
    counterIN=0;
    byte buttonIN;
    buttonIN=0;
    buttonIN = tm.readButtons();
    int arrayIN[5];
    if(buttonIN>0){
        //Serial.print("something");
      
      if (counterIN < 5){
        Serial.print("If working????");
        Serial << counterIN;
        switch(buttonIN){
          case 1:
            LED_One();
            counterIN++;
            break;

          case 2:
            LED_Two();
            counterIN++; 
            break;

          case 4:
            LED_Three();
            counterIN++; 
            break;

          case 8:
            LED_Four();
            counterIN++; 
            break;

          default:
          //Serial.print("is doing something ffs");
          delay(10);
        }
       counterIN++; 
      }
      delay(10000); 
      Serial.print("after loop"); 
    }
  }
}