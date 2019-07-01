
#define encoder0PinA 3
#define encoder0PinB 2
volatile int encoder0Count = 0;
volatile float angle0 = 0;
volatile float velocity0 = 0;
volatile float angle0_previous = 0;
volatile float angle0_post = 0;
#define encoder1PinA 20
#define encoder1PinB 21
volatile int encoder1Count = 0;
volatile float angle1 = 0;
volatile float velocity1 = 0;
volatile float angle1_previous = 0;
volatile float angle1_post = 0;
#define rxPin 18
volatile float error_proportional = 0;
volatile float error_derivative = 0;
volatile float error_integral = 0;
float kp = 50;
float kd = 8;
float ki = 40;
float u = 0;
float motor_input = 0;
int INPUT_MAX = 500;

void setup()
{
 
  Serial1.begin(9600);
  delay(5);
 
  Serial1.write(0xAA);

  exitSafeStart();

  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT); 
  attachInterrupt(0, doEncoder0A, CHANGE);  
  attachInterrupt(1, doEncoder0B, CHANGE);  
  
  pinMode(encoder1PinA, INPUT); 
  pinMode(encoder1PinB, INPUT); 
  attachInterrupt(2, doEncoder1A, CHANGE);  
  attachInterrupt(3, doEncoder1B, CHANGE);    
// TIMER
  TIMSK2 &= ~(1<<TOIE2);
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  ASSR &= ~(1<<AS2);
  TIMSK2 &= ~(1<<OCIE2A);
  TCCR2B |= (1<<CS22)  | (1<<CS20);
  TCCR2B &= ~(1<<CS21);
  TCNT2 = tcnt2;
  TIMSK2 |= (1<<TOIE2);

}

void loop()
{
  u = - (kp*error_proportional + kd*error_derivative + ki*error_integral);
  motor_input = 500 / 9 * u; // because a 9V battery is used to power the motor
  // 3200 : 9V = motor_input : u, thus motor_input = 3200*u/9
  motor_input = (int)motor_input;
  
  if (motor_input >= INPUT_MAX){
    motor_input = INPUT_MAX;
  }
  else if (motor_input <= -INPUT_MAX){
    motor_input = -INPUT_MAX;
  }
  
  /*
  Serial.print(error_proportional);
  Serial.print(" ");
  Serial.print(error_derivative);
  Serial.print(" ");
  Serial.print(error_integral);
  Serial.print(" ");
  Serial.println(motor_input);
  */
  
  setMotorSpeed(motor_input); // maxima velocidad 3200
}
