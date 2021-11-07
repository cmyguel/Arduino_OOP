//class Motor{
//  public:
//    Motor(WIRE_1, WIRE_2, WIRE_3, WIRE_4, ENABLE_PIN)
//
//    void enable()
//    void change_direction()
//    void do_step()
//}

  // YOUR CODE HERE

class Motor{
  byte wire_1;
  byte wire_2;
  byte wire_3;
  byte wire_4;
  byte enable_pin;
  short spin_direction=1; // 1 or -1
  short state=1; 

  public:
    Motor(byte WIRE_1, byte WIRE_2, byte WIRE_3, byte WIRE_4, byte ENABLE_PIN){
      wire_1 = WIRE_1;
      wire_2 = WIRE_2;
      wire_3 = WIRE_3;
      wire_4 = WIRE_4;
      enable_pin = ENABLE_PIN;
      
      pinMode(enable_pin, OUTPUT);
      pinMode(wire_1, OUTPUT);
      pinMode(wire_2, OUTPUT);
      pinMode(wire_3, OUTPUT);
      pinMode(wire_4, OUTPUT);
      enable(HIGH);
      }

    void enable(bool en){
      digitalWrite(enable_pin, en);
      }

    void change_direction(){
      if(spin_direction==1)
        {spin_direction=-1;}
      else 
        {spin_direction=1;}
      }

    void do_step(){
      state = state + spin_direction;
      if(state>4){state=1;}
      if(state<1){state=4;}

      switch (state) {
        case 1:
          digitalWrite(wire_1, LOW);
          digitalWrite(wire_2, HIGH);
          digitalWrite(wire_3, HIGH);
          digitalWrite(wire_4, LOW);
          break;
        case 2:
          digitalWrite(wire_1, LOW);
          digitalWrite(wire_2, HIGH);
          digitalWrite(wire_3, LOW);
          digitalWrite(wire_4, HIGH);
          break;
        case 3:
          digitalWrite(wire_1, HIGH);
          digitalWrite(wire_2, LOW);
          digitalWrite(wire_3, LOW);
          digitalWrite(wire_4, HIGH);
          break;
        case 4:
          digitalWrite(wire_1, HIGH);
          digitalWrite(wire_2, LOW);
          digitalWrite(wire_3, HIGH);
          digitalWrite(wire_4, LOW);
          break;
        default:
          // statements
          break;
      }
      }
  };


Motor motor1 = Motor(1, 2, 3, 4, 5);
Motor motor2 = Motor(8, 9, 10, 11, 12);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  // Have the stepper motors move one turn to one side, one turn to the other, repeatedly.
  //
  // YOUR CODE HERE
  
  for(int i=1; i<=10; i++){
    motor1.do_step();
    motor2.do_step();
    delay(100);
    }
  motor1.change_direction();
  motor2.change_direction();
}
