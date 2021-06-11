//Conor Brereton

//computer version sitting relatively close to screen

//gestures
// pause/play, volume up/down, mute, rewind/fastforward, big/small video view(youtube), tab right tab left

const int trigger1 = 11; //Trigger pin of 1st Sesnor
const int echo1 = 12; //Echo pin of 1st Sesnor
const int trigger2 = 6; //Trigger pin of 2nd Sesnor
const int echo2 = 7;//Echo pin of 2nd Sesnor
const int trigger3 = 2; //Trigger pin of 3rd Sesnor
const int echo3 = 3;//Echo pin of 3rd Sesnor
const int trigger4 = 8; //Trigger pin of 4th Sesnor
const int echo4 = 9;//Echo pin of 4th Sesnor

int lastdist; // used just to fault find to find distance

long time_taken;
int dist,distR1,distL1,distR2,distL2; // distance variable for each sensor
long duration; 
float r1;
float l1;
float r2;
float l2;

unsigned long temp=0;
int temp1=0;
int l=0;
void find_distance (void);   // this function returns the value in cm.

void find_distance (void)
                   
{ 
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  duration = pulseIn(echo1, HIGH, 5000);  // here this pulsein function wont wait more then 5000us for the ultrasonic sound to came back. (due to this it wont measure more than 60cm)
                                           // it helps this project to use the gesture control in the defined space. 
                                           // so that, it will return zero if distance greater then 60m. ( it helps usually if we remove our hands infront of the sensors ).
 
  r1 = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function   
  distL1 = r1 / 100.00;
  
   digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  duration = pulseIn(echo2, HIGH, 5000);
  r1 = 3.4 * duration / 2;     
  distR1 = r1 / 100.00;
  delay(100);

   digitalWrite(trigger3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger3, LOW);
  duration = pulseIn(echo3, HIGH, 5000);
  r2 = 3.4 * duration / 2;                      
  distL2 = r2 / 100.00;

  digitalWrite(trigger4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger4, LOW);
  duration = pulseIn(echo4, HIGH, 5000);
  r2 = 3.4 * duration / 2;                      
  distR2 = r2 / 100.00;
  delay(100);

}

void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT);   // initialize the trigger and echo pins of both the sensor as input and output:
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
pinMode(trigger3, OUTPUT);
pinMode(echo3, INPUT); 
pinMode(trigger4, OUTPUT); 
pinMode(echo4, INPUT); 
}

void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distL1 =dist; //get distance of L1 sensor

calculate_distance(trigger2,echo2);
distR1 =dist; //get distance of R1 sensor


calculate_distance(trigger3,echo3);
distL2 =dist; //get distance of L2 sensor

calculate_distance(trigger4,echo4);
distR2 =dist; //get distance of R2 sensor


// pause mode
if ((distL1 >25 && distR1>25) && (distL1 <50 && distR1<50)) // if hand is greater than 25 and less than 50 Detect both hands
{Serial.println("Play/Pause"); delay (500);} //play/pause video with a delay of half a second
//}

calculate_distance(trigger1,echo1);
distL1 =dist;



// volume
if (distL1>=10 && distL1<=20)                 // if volume is greater than 10 and less than 20 
{
  delay(100);                                 //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL1 =dist;
  if (distL1>=10 && distL1<=20)
  {
    
    Serial.println("Left Locked");
    while(distL1<=40)
    {
      calculate_distance(trigger1,echo1);
      distL1 =dist;
       if (distL1<10 && distL1<=lastdist)        //Hand pushed in 
       //break;
      {Serial.println ("Volume Increased"); delay (300);}  //prints volume increased delay of 300 m/s
       if (distL1>20 && distL1 >= lastdist)     //Hand pulled out
        //break;
      {Serial.println ("Volume Decreased"); delay (300);} //prints volume decreased delay of 300 m/s
      lastdist=dist;
      Serial.println (lastdist);
      
    }
  }
}

//Swipe to next tab and previous tab
  else if(distR2<=11 && distR2>=0) // once if we placed our hands in front of the R2 sensor in the range between 9 to 0 cm this condition becomes true.
  { 
    temp=millis();                  //store the current time in the variable temp. (" millis " Returns the number of milliseconds since the Arduino board began running the current program)      
    while(millis()<=(temp+300))     // this loop measures the distance for another 300 milliseconds. 
    find_distance();
                                    
    {
      Serial.println("next");               // goes to next tab
      
      
    }
    
  }


   else if(distL2<=9 && distL2>=0) //if we place are hand on L2 sensor between 9 and 0 cm condition comes true
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();
                                    
    {
     
      Serial.println("previous");            //goes to previous tab   
      
      
    }
     }

       //Lock Right - rewind, fastforward
if (distR1>=8 && distR1<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR1 =dist;
  if (distR1>=8 && distR1<=17)
  {
    Serial.println("Right Locked");
    while(distR1<=40)
    {
      calculate_distance(trigger2,echo2);
      distR1 =dist;
      if (distR1<10)                                      //Right hand pushed in towards r1 sensor
      {Serial.println ("Rewind"); delay (300);}           // rewinds with a delay of 300 m/s
      if (distR1>20)                                      //Right hand pulled out away from R1 sensor
      {Serial.println ("Forward"); delay (300);}          //Forwards a video with delay with a delay of 300 m/s
   }
  }
}

// mute mode
if ((distL2 >25 && distL2<40 ))                           // if L2 hand is between 25 and 40 cm condition comes true
{Serial.println("mute"); delay (500);}                    // mute with a delay of half a second




  //fullscreen
else if ((distL1 >25 && distR2<50)&& (distL1 <50 && distR2 < 50))  //if L1 and R2 hand is between 20 and 50cm
{Serial.println("fullscreen"); delay (500);}  // fullscreen with a delay of half a sec

     
delay(200);                                  // overall delay of 200 m/s

}

     
