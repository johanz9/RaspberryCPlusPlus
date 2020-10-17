///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

//#define NO_PI

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;

const int led_Red = 0;
const int led_Green = 1;
const int led_Yellow = 2;
const int timeoutMs = 1000; // 1 second

///
/// Utils
///
void init()
{
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_Red, OUTPUT);
    pinMode(led_Green, OUTPUT);
    pinMode(led_Yellow, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value)
{
#ifndef NO_PI
    digitalWrite(ledNumber, value);

#else
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#endif
}

void blinkingYellow(){
    bool onoff = true;
    int count = 0;
    while(count < 5){
        setLed(led_Yellow,onoff);
        onoff = !onoff;
        delay(100);
        count++;
    }
}

void setOnOff(int time, int led){
    setLed(led, true);

    #ifndef NO_PI
        delay(time*1000);
    #else
        Sleep(time*1000);
    #endif

    setLed(led, false);

}

void normalCycle(){

    int currentState = 0;
    int errorCounter = 0;
    int time1 = 10;
    int time2 = 15;
    int time3 = 5;

    while(1)
    {
        cout << "CurrentState: S"<< currentState << endl;

        //FAKE ERROR
        if(errorCounter == 10){
            cout << "Unexpected Error" << endl;
            blinkingYellow();
            break;
        }

        if(currentState == 0){
            setOnOff(time1,led_Red);
            currentState = 2;
            errorCounter++;
        } else if(currentState == 2){
            setOnOff(time2,led_Green);
            currentState = 1;
        } else{
            setOnOff(time3,led_Yellow);
            currentState = 0;

        }

    }
}


int main()
{
    init();
    normalCycle();

    return 0;


}
