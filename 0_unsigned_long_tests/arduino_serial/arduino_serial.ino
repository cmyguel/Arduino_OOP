
void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Millis: ");
  Serial.println(millis());

  // Unsigned long max value is 4,294,967,295. Here are some tests. 
  
  Serial.println("UL valid sum (4,294,000,000 UL + 900,000 UL): ");
  Serial.println(4294000000UL + 900000UL );

  Serial.println("is sum overflow possible? ( 4294967295UL + 100UL ) : ");
  Serial.println( 4294967295UL + 100UL );

  Serial.println("is large positive substraction using long possible? ( long n = 4294967295UL - 4294967000UL ) : ");
  long n = 4294967295UL - 4294967000UL;
  Serial.println( n );

  Serial.println("is large negative substraction using long possible? ( long n = 4294967000UL - 4294967295UL ) : ");
  n = 4294967000UL - 4294967295UL;
  Serial.println( n );

  Serial.println("is Overflown - Large, possitive? ( long n = 100UL - 4294967295UL ) : ");
  n = 100UL - 4294967295UL;
  Serial.println( n );

  Serial.println("is Large - Overflown, negative? ( long n = 4294967295UL - 100UL ) : ");
  n = 4294967295UL - 100UL;
  Serial.println( n );






}

void loop() {

}
