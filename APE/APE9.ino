/*
--------------------------------------------------------
SISTEMA DE MONITOREO DE TEMPERATURA
LM35 + Pulsador + LEDs + Buzzer
Sin delay() usando millis()
--------------------------------------------------------
*/

const int LM35 = A0;

const int BOTON = 2;

const int LED_ROJO = 7;
const int LED_VERDE = 8;

const int BUZZER = 6;


//================ TIEMPOS ===================
const unsigned long TIEMPO_HEARTBEAT = 500;
const unsigned long TIEMPO_TELEMETRIA = 2000;
const unsigned long TIEMPO_ALARMA = 300;

//================ VARIABLES ==================
unsigned long tiempoHeartbeat = 0;
unsigned long tiempoTelemetria = 0;
unsigned long tiempoAlarma = 0;

bool estadoHeartbeat = false;
bool estadoAlarma = false;

bool alarmaActiva = false;
bool alarmaSilenciada = false;

float temperatura = 0;


//=============================================
void setup()
{
    Serial.begin(9600);

    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_ROJO, OUTPUT);

    pinMode(BUZZER, OUTPUT);

    pinMode(BOTON, INPUT);

    Serial.println("--------------------------------");
    Serial.println(" SISTEMA INICIADO ");
    Serial.println("--------------------------------");
}


//=============================================
void loop()
{
    heartbeat();

    leerTemperatura();

    controlarAlarma();

    revisarBoton();
}


//=============================================
// HEARTBEAT
//=============================================
void heartbeat()
{
    if (millis() - tiempoHeartbeat >= TIEMPO_HEARTBEAT)
    {
        tiempoHeartbeat = millis();

        estadoHeartbeat = !estadoHeartbeat;

        digitalWrite(LED_VERDE, estadoHeartbeat);
    }
}


//=============================================
// LECTURA DEL LM35 Y ENVIO SERIAL
//=============================================
void leerTemperatura()
{
    if (millis() - tiempoTelemetria >= TIEMPO_TELEMETRIA)
    {
        tiempoTelemetria = millis();

        int lectura = analogRead(LM35);

        float voltaje = lectura * (5.0 / 1023.0);

        temperatura = voltaje * 100.0;

        Serial.print("Temperatura: ");
        Serial.print(temperatura);
        Serial.println(" °C");
    }
}


//=============================================
// CONTROL DE ALARMA
//=============================================
void controlarAlarma()
{
    if (temperatura > 30)
    {
        alarmaActiva = true;
    }
    else
    {
        alarmaActiva = false;
        alarmaSilenciada = false;

        digitalWrite(LED_ROJO, LOW);
        digitalWrite(BUZZER, LOW);
    }


    if (alarmaActiva && !alarmaSilenciada)
    {
        if (millis() - tiempoAlarma >= TIEMPO_ALARMA)
        {
            tiempoAlarma = millis();

            estadoAlarma = !estadoAlarma;

            digitalWrite(LED_ROJO, estadoAlarma);

            if (estadoAlarma)
                tone(BUZZER, 1000);
            else
                noTone(BUZZER);
        }
    }
}


//=============================================
// BOTON ACKNOWLEDGE
//=============================================
void revisarBoton()
{
    static bool ultimoEstado = LOW;

    bool estadoActual = digitalRead(BOTON);

    if (estadoActual == HIGH && ultimoEstado == LOW)
    {
        if (alarmaActiva)
        {
            alarmaSilenciada = true;

            digitalWrite(LED_ROJO, LOW);

            noTone(BUZZER);

            Serial.println(">>> ALARMA SILENCIADA POR EL OPERADOR <<<");
        }
    }

    ultimoEstado = estadoActual;
}