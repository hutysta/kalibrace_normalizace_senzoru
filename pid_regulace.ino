int _foto = A0;
#define MOTOR1 2
#define MOTOR1_SPEED 3
#define MOTOR2 4
#define MOTOR2_SPEED 5
#define MAX_SPEED 1024

int maxVal = 860;
int minVal = 524;

const int width = 30;
int hodnoty[width];
int index = 0;

int sum = 0;

float PIDRegulator = 0;
float PIDLastTimestamp = 0;
float KI = 0.1;

int getFloatAverage(int input)
{
  sum -= hodnoty[index];
  hodnoty[index] = input;
  sum += input;
  index++;
  if(index == width)
  {
    index = 0;
  }

  return sum/width;
}

void setMinMax(int caliTime)
{
  for(int i = 0; i< caliTime * 1000; i++)
  {
    int val = analogRead(_foto);
    if(val>maxVal)
      maxVal = val;
    if(val<minVal)
      minVal = val;

      delay(1);
  }
}

float getNormalizedValue(int val)
{
  if(val>maxVal) val = maxVal;
  if(val<minVal) val = minVal;

  int citatel = val - minVal;
  int jmenovatel = maxVal - minVal;

  float out = (float)citatel / (float)jmenovatel;
  return out * MAX_SPEED;
}

void setMotorSpeed(int value, float lastTimeStamp)
{
  float deltaTime = millis() - lastTimeStamp;
  
  int val1 = (MAX_SPEED - value);
  int val2 = (value);

  PIDRegulator += (val1 - val2) * KI;

  val1 += PIDRegulator * deltaTime;
  val2 -= PIDRegulator * deltaTime;

  val1 = getValInRange(val1);
  val2 = getValInRange(val2);
  
  analogWrite(MOTOR1_SPEED, val1);
  analogWrite(MOTOR2_SPEED, val2);
}

int getValInRange(int val) {
  val = min(val, MAX_SPEED);
  val = max(val, 0);

  return val;
}


void setup() {
  // put your setup code here, to run once:
  //pinMode(_led,OUTPUT);
  Serial.begin(9600);
  setMinMax(5);  
  Serial.println(minVal);
  Serial.println(maxVal);
  for(int i = 0; i < width; i++)
  {
    getFloatAverage(analogRead(_foto)); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
 Serial.println(getNormalizedValue(getFloatAverage(analogRead(_foto))));
}
