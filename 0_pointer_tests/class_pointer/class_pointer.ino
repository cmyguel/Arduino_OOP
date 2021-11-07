class Printer{
  public:

  void print_something(){
    Serial.println("Something");
    }
  
  };

Printer g = Printer();
Printer *c;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  c = &g;

}

void loop() {
  // put your main code here, to run repeatedly:
  c->print_something();
  g.print_something();
  delay(1000);

}
