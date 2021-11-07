typedef void (*GeneralFunction)();

typedef void (*TriggableClass)();

class Triggable {
  public:
    virtual void trigger()=0;
};

class Printer {
  public:
    void trigger(){
      Serial.println("Class Function");
      }
  
  };

class FunctionButton{
  public:
    byte pin;
    GeneralFunction function;
    byte current_state;
    unsigned long t;
    unsigned long update_time;

    FunctionButton(byte PIN, GeneralFunction FUNCTION ){
      pin = PIN;
      pinMode(pin, INPUT_PULLUP);
      function = FUNCTION;
      current_state = 1;
      update_time = 0;
      }

    void check(){
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

    void state1_released(){
      if(digitalRead(pin)==LOW){
        function();
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

class ClassButton {
  public:
    byte pin;
    Printer &printer;
    byte current_state;
    unsigned long t;
    unsigned long update_time;

    ClassButton(byte PIN, Printer &PRINTER ){
      pin = PIN;
      pinMode(pin, INPUT_PULLUP);
      current_state = 1;
      update_time = 0;
      printer(PRINTER);
      }

//    void set_class(TriggableClass OBJECT){
//      object = OBJECT;
//      }

    void check(){
      t = millis();
      if(t >= update_time){
        switch (current_state) {
          case 1:
            state1_released();
            break;
          case 2:
            state2_pressed();
            break;
        }
        }
      }

    void state1_released(){
      if(digitalRead(pin)==LOW){
        object.trigger();
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

void do_something(){
  Serial.println("Function");
  };

Printer printer1 = Printer();

FunctionButton button1 = FunctionButton(8, do_something);
ClassButton button2 = ClassButton(9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  button2.set_class( printer1 );

}

void loop() {
  // put your main code here, to run repeatedly:
  button1.check();
  button2.check();

}
