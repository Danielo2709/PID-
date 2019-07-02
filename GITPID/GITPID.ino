//direcctions
const int direccion = 10;
const int pin_de_paso = 9;
 

int pasosDelay;
int posicion1;
int posicion2;
int posicion;
int setpoint;
int setpoint1;
int setpoint2;
int valor;
int activado;

//for the pid
float integral1;
float derivador1;
float output1;
float integral2;
float derivador2;
float output2;
float RPM_DATO;
float error_previo1=0;
float error_previo2=0;
float Kp2=9.148;
float Ki2=42.93;
float Kd1=0;
float Kp1=8;
float Ki1=42.259;
float Kd2=0;
float error1;
float error2;

//pwm for both sides
float pwmread1;
float pwmread2;


void setup() {
   pinMode(direccion, OUTPUT);
   pinMode(pin_de_paso, OUTPUT);
 
   Serial.begin(9600);
   Serial.println("Posicion actual");
}
 
void loop() {
//maping the pot
 posicion = map(analogRead(A0),3,350,0,150);
 //setpoint to start
 setpoint=97;
  delay(1);
 
 while(setpoint==posicion)
 {
//start the loop
  activado++;
 
if(posicion==setpoint&&activado>=1)
  {
    //maping the pot position left and right 
    posicion1 = map(analogRead(A0),3,180,0,100);
    posicion2 = map(analogRead(A0),355,180,0,90);
   
    setpoint1=123;
     pwmread1=0;
  pwmread2=0;
   error1=0;
   error2=0;
    error_previo1=0;
   error_previo2=0;
   output2=0;
   output1=0;
    integral1 = 0;  
     integral2 = 0;  
   if(posicion1>setpoint1)
   {
    //fist PID
   digitalWrite(direccion, LOW);
         
   error1= setpoint1 - posicion1;
if(error1==0){
  integral1 = 0;  
  
  }
 
  integral1 = integral1 +(error1*0.00001);
  derivador1 = (error1 - error_previo1)/0.00001;
  output1 =-(Kp1*error1+Ki1*integral1+Kd1*derivador1);
  error_previo1=error1;
 
  pwmread1=(pow(setpoint1+output1+4000,0.55));
  analogWrite(pin_de_paso, pwmread1);
    Serial.println(error_previo1);
     Serial.println(pwmread1);
     Serial.println(error1);
   delay(1);
  }
     setpoint2=86;
    if(posicion2>setpoint2)
   {
  //pid 2
   digitalWrite(pin_de_paso, LOW);
   error2= setpoint2 - posicion2;

  if(error2==0){
  integral2 = 0;  
  }
   integral2 = integral2 +(error2*0.00001);
  derivador2 = (error2 - error_previo2)/0.00001;
  output2 =-(Kp2*error2+Ki2*integral2+Kd2*derivador2);
  error_previo2=error2;

  pwmread2=(pow (setpoint2+output2+4000,0.55));
   analogWrite(direccion, pwmread2);
     Serial.println(error_previo2);
    Serial.println(pwmread2);
     Serial.println(error2);
   delay(1);
   }
  if((posicion2<=85 && posicion2>=70) && (posicion1>=80&&posicion1<=122))
   {
    //while setpoint is active
  pwmread1=0;
  pwmread2=0;
   error1=0;
   error2=0;
    error_previo1=0;
   error_previo2=0;
   output2=0;
   output1=0;
   digitalWrite(pin_de_paso, LOW);
   digitalWrite(direccion, LOW);
  
     Serial.println(error1);

     Serial.println(error2);
   delay(1);
   }
 }
  delay(1); 
  }
    Serial.println(posicion1);
     Serial.println(posicion2);
  
}
 
