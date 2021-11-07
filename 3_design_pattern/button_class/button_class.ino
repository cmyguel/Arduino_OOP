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

Button button1 = Button(8);
Button button2 = Button(9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  button1.update();
  button2.update();

  if (button1.was_pressed()) do_something();
  if (button2.was_pressed()) do_something_else();

}

void do_something(){
  Serial.println("Doing something");
  }

void do_something_else(){
  Serial.println("Doing something else");
  }
