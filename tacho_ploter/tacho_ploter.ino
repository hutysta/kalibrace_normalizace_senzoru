#define TACHO1 A1
#define TACHO2 A4
#define MOTOR1 9
#define MOTOR2 6
const int diff_l = 5;
const int raw_l = 5;

bool stojime = false;
unsigned int lastTimeStamp = 0;
unsigned int timeStamp = 0;

int diff_values[5];
int diff_w = 0;
int diff_sum = 0;
int diff_last = 0;

int raw_values[5];
int raw_w = 0;
int raw_sum = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for(int i = 0; i < diff_l; i++){
    diff_values[i] = 0;
  }

  for(int i = 0; i < raw_l; i++){
    raw_values[i] = 0;
  }
}

int GetFloatAverage(int pin)
{
  int val = analogRead(pin);
  
  raw_sum += val;
  
  raw_sum -= raw_values[raw_w];
  
  raw_values[raw_w] = val;
  
  raw_w++;
  
  if(raw_w>raw_l-1) {
    raw_w = 0;
  }
  
  return raw_sum/raw_l;
}

int GetFloatAverageDiff(int pin)
{
  int currVal = GetFloatAverage(pin);

  int diff =  currVal - diff_last;
  
  diff_sum += diff;

  //získání frekvence


  if(diff_last == 0 && currVal == 0)
  stojime = true;
  
  if(diff_last > 0 && currVal < 0)
  {
    stojime = false;
    
  timeStamp = millis();
    lastTimeStamp = timeStamp;
  }

  diff_last = currVal;
  
  diff_sum -= diff_values[diff_w];
  
  diff_values[diff_w] = diff;
  
  diff_w ++;
  
  if(diff_w > diff_l -1) {diff_w = 0;}

  
  
  return diff_sum/diff_l;  
}




void loop() {
  // put your main code here, to run repeatedly:
  GetFloatAverageDiff(TACHO2);
  if(!stojime)
    Serial.println(lastTimeStamp-timeStamp);
  else
    Serial.println("stojime");
  
}
