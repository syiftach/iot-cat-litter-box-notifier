#define trigPin 10
#define echoPin 11
#define PULSE "pulse"
#define VELOCITY 0.034 // cm/microseconds

long duration = 0;
int distance = 0;
static String command;
char buf[32];


int get_distance()
{
  // clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // read returned pulse duration
  duration = pulseIn(echoPin, HIGH);
  // compute distance (d=v*t).
  // divide by 2 because the sound travel forwards and backwards
  return duration * VELOCITY / 2;

}

void setup()
{
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  memset(buf, 0, 32);
  //  Serial.println("starting ultrasonic example program with arduino");
  //  delay(1000);
}


void loop()
{
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0)
  {
    //wait
  }
  command = Serial.readStringUntil("\r\n");
  /* for debugging */
  //  Serial.print("received: ");
  //  Serial.println(command);
  command.trim();
  
  /* measure distance */
  if (command.equals(PULSE))
  {
    distance = get_distance();
    sprintf(buf, "%d", distance);
    Serial.write(buf);
  }
  //  delay(5000);

} // loop
