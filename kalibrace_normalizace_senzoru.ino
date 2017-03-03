
int _foto = A0;

int maxVal = 860;
int minVal = 524;

const int width = 30;
int hodnoty[width];
int index = 0;

int sum = 0;

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
  digitalWrite(_led, HIGH);
  for(int i = 0; i< caliTime * 1000; i++)
  {
    int val = analogRead(_foto);
    if(val>maxVal)
      maxVal = val;
    if(val<minVal)
      minVal = val;

      delay(1);
  }
  digitalWrite(_led, LOW);
}

float getNormalizedValue(int val)
{
  if(val>maxVal) val = maxVal;
  if(val<minVal) val = minVal;

  int citatel = val - minVal;
  int jmenovatel = maxVal - minVal;

  float out = (float)citatel / (float)jmenovatel;
  return out * 255;
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
