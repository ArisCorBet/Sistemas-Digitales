
// Canal 1 - Señal 555 (Pin D2) [cite: 58, 65]
const int pinSenal555 = 2;
int estadoActual555 = LOW;
int estadoAnterior555 = LOW;
unsigned long tiempoAnterior555 = 0;
unsigned long tiempoCambio555 = 0;
unsigned long periodo555 = 0;
unsigned long tHigh555 = 0;
unsigned long tLow555 = 0;
float frecuencia555 = 0;
float duty555 = 0;

// Canal 2 - Señal Flip-Flop (Pin D3) [cite: 59, 65]
const int pinSenalFF = 3;
int estadoActualFF = LOW;
int estadoAnteriorFF = LOW;
unsigned long tiempoAnteriorFF = 0;
unsigned long tiempoCambioFF = 0;
unsigned long periodoFF = 0;
unsigned long tHighFF = 0;
unsigned long tLowFF = 0;
float frecuenciaFF = 0;
float dutyFF = 0;

void setup() {
  Serial.begin(9600); // Para visualización en Serial Monitor/Plotter [cite: 38, 80]
  pinMode(pinSenal555, INPUT);
  pinMode(pinSenalFF, INPUT);
}

void loop() {
  unsigned long tiempoActual = millis();

  // CANAL 1: 555
  estadoActual555 = digitalRead(pinSenal555);
  if (estadoActual555 == HIGH && estadoAnterior555 == LOW) {
    unsigned long duracionCiclo = tiempoActual - tiempoAnterior555;
    if (duracionCiclo > 0) {
      periodo555 = duracionCiclo;
      frecuencia555 = 1000.0 / periodo555;
      tiempoAnterior555 = tiempoActual;
    }
  }
  if (estadoActual555 != estadoAnterior555) {
    if (estadoActual555 == HIGH) tLow555 = tiempoActual - tiempoCambio555;
    else tHigh555 = tiempoActual - tiempoCambio555;
    tiempoCambio555 = tiempoActual;
    if (tHigh555 > 0 && tLow555 > 0) {
      duty555 = (float)tHigh555 / (tHigh555 + tLow555) * 100;
    }
  }
  estadoAnterior555 = estadoActual555;

  // CANAL 2: FLIP-FLOP
  estadoActualFF = digitalRead(pinSenalFF);
  if (estadoActualFF == HIGH && estadoAnteriorFF == LOW) {
    unsigned long duracionCicloFF = tiempoActual - tiempoAnteriorFF;
    if (duracionCicloFF > 0) {
      periodoFF = duracionCicloFF;
      frecuenciaFF = 1000.0 / periodoFF;
      tiempoAnteriorFF = tiempoActual;
    }
  }
  if (estadoActualFF != estadoAnteriorFF) {
    if (estadoActualFF == HIGH) tLowFF = tiempoActual - tiempoCambioFF;
    else tHighFF = tiempoActual - tiempoCambioFF;
    tiempoCambioFF = tiempoActual;
    if (tHighFF > 0 && tLowFF > 0) {
      dutyFF = (float)tHighFF / (tHighFF + tLowFF) * 100;
    }
  }
  estadoAnteriorFF = estadoActualFF;
  
  // 1. FORMATO PARA EL GRÁFICO (PLOTTER)
  // Imprimimos los estados actuales para ver las ondas cuadradas
  Serial.print(estadoActual555);    // Señal 1 (0 o 1)
  Serial.print(",");               // Separador requerido por Tinkercad
  Serial.print(estadoActualFF + 2); // Señal 2 (2 o 3) para que no se traslapen
  
  // 2. FORMATO PARA DATOS (MONITOR SERIE)
  Serial.print("\tHz_555:"); 
  Serial.print(frecuencia555, 2);  // [cite: 98, 99]
  Serial.print("\tD%_555:");
  Serial.print(duty555, 1);        // [cite: 109]
  Serial.print("\tHz_FF:");
  Serial.print(frecuenciaFF, 2);   // [cite: 111, 113]
  Serial.print("\tD%_FF:");
  Serial.println(dutyFF, 1);       // [cite: 113]
}