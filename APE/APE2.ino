
// Variables globales
int LED_PINS[] = {2, 3, 4, 5, 6, 7};
int BOTON_PIN = 8;
int patronActual = 0;
// Para detectar cambio de botón (debounce básico)
int estadoBoton = 0;
int ultimoEstadoBoton = 0;

void setup() {
  // CONFIGURAR LEDs como SALIDA
  for (int i = 0; i < 6; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  // CONFIGURAR botón como ENTRADA
  pinMode(BOTON_PIN, INPUT);
  Serial.begin(9600);
  // Inicializar aleatorio
  randomSeed(analogRead(0));
  
}

void loop() {
  // REPETIR
  leerBoton();

  // SEGUN patronActual HACER
  switch (patronActual) {
    case 0:
    Serial.println("Patron: Secuencia");
    patronSecuencia();
    break;

  case 1:
    Serial.println("Patron: Persecucion");
    patronPersecucion();
    break;

  case 2:
    Serial.println("Patron: Parpadeo");
    patronParpadeo();
    break;

  case 3:
    Serial.println("Patron: Aleatorio");
    patronAleatorio();
    break;

  case 4:
    Serial.println("Patron: Onda");
    patronOnda();
    break;
}
}

// FUNCION leerBoton()
void leerBoton() {
  estadoBoton = digitalRead(BOTON_PIN);

  // Detectar flanco (cuando se presiona)
  if (estadoBoton == HIGH && ultimoEstadoBoton == LOW) {
    patronActual = random(0, 5); // aleatorio entre 0 y 4
    delay(200); // debounce básico
  }

  ultimoEstadoBoton = estadoBoton;
}

// CASO 0: Secuencia
void patronSecuencia() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(200);
    digitalWrite(LED_PINS[i], LOW);
  }
}

// CASO 1: Persecución (ida y vuelta)
void patronPersecucion() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
    digitalWrite(LED_PINS[i], LOW);
  }
  for (int i = 4; i > 0; i--) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
    digitalWrite(LED_PINS[i], LOW);
  }
}

// CASO 2: Parpadeo
void patronParpadeo() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);
  }
  delay(300);

  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  delay(300);
}

// CASO 3: Aleatorio
void patronAleatorio() {
  int led = random(0, 6);
  digitalWrite(LED_PINS[led], HIGH);
  delay(150);
  digitalWrite(LED_PINS[led], LOW);
}

// CASO 4: Onda
void patronOnda() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED_PINS[i], LOW);
    delay(100);
  }
}