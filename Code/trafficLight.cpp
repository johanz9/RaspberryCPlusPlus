///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//


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
                Sleep(timeoutMs / 1000);
        #endif
        }
        setLed(led, false);
   
    }
}

void normalCycle(){

    //int count = 0;
    int time1 = 10;
    int time2 = 10;
    int time3 = 5;
    while(1)
    {
        counter(time1,led_Red);
        counter(time2,led_Green);
        counter(time3,led_Yellow);

    }
}


int main()
{
    init();
    normalCycle();

    return 0;


}
