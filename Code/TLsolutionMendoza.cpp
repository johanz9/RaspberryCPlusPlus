///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

#define NO_PI

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
        Sleep(1);
        count++;
    }
}

void counter(int time, int led){
    int count = 0;

    if(led == led_Yellow){
        while(count < time){
            //*cout << " N " << time <<endl;
            setLed(led, true);
            setLed(led_Green,true);
            count++;

#ifndef NO_PI
            delay(timeoutMs);
#else
            Sleep(timeoutMs / 1000);
#endif
        }
        setLed(led,false);
        setLed(led_Green,false);

    } else {

        while (count < time) {
            //*cout << " N " << time <<endl;
            setLed(led, true);
            count++;
#ifndef NO_PI
            delay(timeoutMs);
#else
            Sleep(timeoutMs);
#endif
        }
        setLed(led, false);

    }
}

void normalCycle(){

    int errorCounter = 0;
    int time1 = 10;
    int time2 = 10;
    int time3 = 5;
    int count = 0;

    int currentState = 0;

    while(1)
    {
        cout << "CurrentState: S"<< currentState << endl;

        //FAKE ERROR
        if(errorCounter == 10){
            cout << "Unexpected Error" << endl;
            blinkingYellow();
            break;
        }

        if(count < time1 && currentState == 0){
            counter(time1,led_Red);
            currentState = 2;
            errorCounter++;
            count = 0;
        } else if(count < time2 && currentState == 2){
            counter(time2,led_Green);
            currentState = 1;
            count = 0;
        } else if(count < time3 && currentState == 1){
            counter(time3,led_Yellow);
            currentState = 0;
            count = 0;
        }
        count++;

    }
}


int main()
{
    init();
    normalCycle();

    return 0;


}
