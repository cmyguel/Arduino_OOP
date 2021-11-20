class Button{
  public:
    // General class variables
    unsigned long t;
    unsigned long update_time;
    //-----------------------
    byte pin;
    byte current_state=1;
    bool pressed=false;

    // Constructor
    Button(byte PIN){
      pin = PIN;
      pinMode(pin, INPUT_PULLUP);
      current_state = 1;
      update_time = 0;
      }

    // General class function
    void update(){
      t = millis();
      if(t >= update_time){
        switch (current_state) {
          case 1:
            state1_released();
            break;
          case 2:
            state2_pressed();
            break;
          default:
            break;
        }
        }
      }

    bool was_pressed(){
      if(pressed){
        pressed=false;
        return true;
        }
      else {return false;}
      }

//  STATES
    void state1_released(){
      if(digitalRead(pin)==LOW){
        pressed = true;
        current_state = 2;
        update_time = t + 20;
        }
      else {
        update_time = t + 1;
        }
      }

    void state2_pressed(){
      if(digitalRead(pin)==HIGH){
        current_state = 1;
        update_time = t + 20;
        }
      else{
        update_time = t + 1;
        }
      }
  };

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
    // YOUR CODE HERE 
    // IMPLEMENT FUNCTIONS: UPDATE(), STATE1_STOPPED(), STATE2_SPINNING(), SET_STEP_DELAY(ms), START(), STOP()
    // NEW VARIABLES: unsigned long t, unsigned long update_time, byte current_state,
    //                bool spinning, int number_steps, int step_count, int spin_count, int spin_delay

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
//  for(int i=1; i<=10; i++){
//    motor1.do_step();
//    motor2.do_step();
//    delay(100);
//    }
//  motor1.change_direction();
//  motor2.change_direction();

  // Connect buttons to Stop/Start and Change direction of motors. 
  //
  // YOUR CODE HERE

  // UPDATES



  // LOGIC

  

  delay(1); // TO AVOID SLOW SIMULATION. CAN BE REMOVED IN REAL IMPLEMENTATION.

}
