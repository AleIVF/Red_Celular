/*
 * ======================================================================================
 * INSTITUCIÓN: Universidad de Colima - Facultad de Telemática
 * MATERIA: Entornos Inteligentes y Tecnologías Disruptivas
 * PRÁCTICA: Actividad VII - Fundamentos y aplicación del módulo SIM800L
 * EQUIPO: Equipo 1
 * INTEGRANTES:
 * 1. Vega Flores Alejandra Ixchel
 * 2. Diaz Ramirez Dulce Maria
 * 3. Rodriguez Jimenez Jazmin
 * 4. Mancilla Radillo Jocelyn Yareli
 * ======================================================================================
 */

#define TINY_GSM_MODEM_SIM800

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGsmClient.h>
#include <PubSubClient.h>

// --- Definición de pines y Hardware ---
const int RXD2 = 16;     // Pin RX2 del ESP32 -> Conectar a TXD del SIM800L
const int TXD2 = 17;     // Pin TX2 del ESP32 -> Conectar a RXD del SIM800L
const int PIN_LED = 4;   // Pin para control de LED (Ánodo)

// Instancia de la interfaz serie por Hardware
HardwareSerial sim800Serial(2);

// --- Configuración de Integrantes del Equipo y Mensajes ---
const String NUMEROS_EQUIPO[] = {
  "+523122717286", 
  "+523123391408", 
  "+523121077679", 
  "+523121448362"  
};
const int TOTAL_INTEGRANTES = sizeof(NUMEROS_EQUIPO) / sizeof(NUMEROS_EQUIPO[0]);
const String MENSAJE_SMS = "Prueba ESP32 - Actividad VII: Mensaje autonomo Equipo 1";

// --- Credenciales APN Telcel México ---
const char apn[]  = "internet.itelcel.com";
const char user[] = "webgprs";
const char pass[] = "webgprs2002";

// --- Configuración del Broker MQTT ---
const char broker[]     = "broker.hivemq.com";
const int puertoMQTT    = 1883;
const char topicLED[]   = "equipo1/led"; // Tópico asignado al Equipo 1

// --- Instancias de TinyGSM y PubSubClient ---
TinyGsm modem(sim800Serial);
TinyGsmClient gsmClient(modem);
PubSubClient mqtt(gsmClient);

// Prototipos de funciones
void enviarComandoAT(String comando, int tiempoEspera);
void callbackMQTT(char* topic, byte* payload, unsigned int length);
void conectarMQTT();

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // Inicializar comunicación serie con el SIM800L
  sim800Serial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(3000); 

  Serial.println("\n==================================================");
  Serial.println("--- Iniciando Secuencia Autónoma GSM - Equipo 1 ---");
  Serial.println("==================================================");

  // Verificación básica de comunicación AT y ajustes
  enviarComandoAT("AT", 1000);
  enviarComandoAT("ATE0", 1000);                      // Desactivar eco
  enviarComandoAT("AT&F", 1000);                      // Restaurar configuración de fábrica
  enviarComandoAT("AT+CFUN=1", 2000);                 // Forzar funcionalidad completa del radio
  enviarComandoAT("AT+COPS=0", 3000);                 // Selección de operador automática
  enviarComandoAT("AT+CBAND=\"ALL_BAND\"", 1000);     // Habilitar todas las bandas 2G
  enviarComandoAT("AT+CHFA=0", 1000);                 // Seleccionar canal de audio principal
  enviarComandoAT("AT+CLVL=100", 1000);               // Volumen de llamada al 100%
  enviarComandoAT("AT+CSTA=145", 1000);               // Formato de marcación internacional (+)

  // 1. Configurar SMS en modo texto
  enviarComandoAT("AT+CMGF=1", 1000);

  // 2. Enviar SMS a los integrantes
Serial.println("\n[INFO] Iniciando envio de SMS a integrantes...");

for (int i = 0; i < TOTAL_INTEGRANTES; i++) {

    Serial.print("Enviando SMS a: ");
    Serial.println(NUMEROS_EQUIPO[i]);

    while (sim800Serial.available())
        sim800Serial.read();

    // Modo texto
    sim800Serial.println("AT+CMGF=1");
    delay(1000);

    while (sim800Serial.available())
        Serial.write(sim800Serial.read());

    // Solicitar envío
    sim800Serial.print("AT+CMGS=\"");
    sim800Serial.print(NUMEROS_EQUIPO[i]);
    sim800Serial.println("\"");

    // Esperar respuesta del SIM800L
    unsigned long inicio = millis();
    bool prompt = false;

    while (millis() - inicio < 5000) {

        while (sim800Serial.available()) {

            char c = sim800Serial.read();
            Serial.write(c);

            if (c == '>') {
                prompt = true;
            }
        }

        if (prompt)
            break;
    }

    // Si no apareció >
    if (!prompt) {
        Serial.println("\n[ERROR] El SIM800L no dio el prompt '>'.");
        Serial.println("[ERROR] No se enviara el SMS.");
        continue;
    }

    // Ahora sí enviar el mensaje
    sim800Serial.print(MENSAJE_SMS);

    // Ctrl + Z
    sim800Serial.write(26);

    Serial.println("\n[INFO] Esperando confirmacion del SMS...");

    inicio = millis();
    String respuesta = "";

    while (millis() - inicio < 20000) {

        while (sim800Serial.available()) {

            char c = sim800Serial.read();
            Serial.write(c);
            respuesta += c;
        }

        if (respuesta.indexOf("OK") >= 0) {
            Serial.println("\n[OK] SMS enviado correctamente.");
            break;
        }

        if (respuesta.indexOf("ERROR") >= 0) {
            Serial.println("\n[ERROR] El SIM800L rechazo el SMS.");
            break;
        }
    }

    delay(2000);
}
  // 3. DIAGNÓSTICO DE RED PREVIO A LAS LLAMADAS
  Serial.println("\n==================================================");
  Serial.println("--- DIAGNÓSTICO DE RED PREVIO A REALIZAR LLAMADA ---");
  Serial.println("==================================================");
  
  Serial.println("\n[DIAGNÓSTICO] Registro en la red (AT+CREG?):");
  enviarComandoAT("AT+CREG?", 1000);

  Serial.println("\n[DIAGNÓSTICO] Calidad de Señal (AT+CSQ):");
  enviarComandoAT("AT+CSQ", 1000);

  delay(2000);

  // 4. Realizar Llamada y Corte programado
  Serial.println("\n[INFO] Iniciando secuencia de llamadas de voz...");
  for (int i = 0; i < TOTAL_INTEGRANTES; i++) {
    Serial.print("\nLlamando a: ");
    Serial.println(NUMEROS_EQUIPO[i]);

    while(sim800Serial.available()) sim800Serial.read();

    sim800Serial.print("ATD");
    sim800Serial.print(NUMEROS_EQUIPO[i]);
    sim800Serial.println(";");

    delay(2000);
    
    while (sim800Serial.available()) {
      Serial.write(sim800Serial.read());
    }

    Serial.println("\nEsperando 15 segundos antes de colgar...");
    delay(15000); 

    Serial.println("Colgando llamada...");
    enviarComandoAT("ATH", 1000);
    delay(2000);
  }

  // --- FASE MQTT / GPRS ---
  Serial.println("\n--- Iniciando Conexión GPRS y Broker MQTT ---");

  // Reinicio suave del módem para entregar el control de la red a TinyGSM
  modem.restart();

  Serial.println("[GPRS] Esperando red celular...");
  if (!modem.waitForNetwork(60000L)) {
    Serial.println("[ERROR] No se pudo registrar en la red celular.");
    return;
  }
  Serial.println("[GPRS] ¡Red celular lista!");

  Serial.print("[GPRS] Conectando a APN: ");
  Serial.println(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println("[ERROR] Fallo en la conexión GPRS.");
    return;
  }
  Serial.println("[GPRS] ¡Conectado con éxito a la red de datos!");

  IPAddress localIP = modem.localIP();
  Serial.print("[GPRS] IP Local asignada por Telcel: ");
  Serial.println(localIP);

  Serial.println("[GPRS] Estabilizando canal de red (5 segundos)...");
  delay(5000);

  // Configurar cliente y servidor MQTT
  mqtt.setServer(broker, puertoMQTT);
  mqtt.setCallback(callbackMQTT);
}

void loop() {
  if (!mqtt.connected()) {
    conectarMQTT();
  }
  mqtt.loop();
}

// --- FUNCIONES AUXILIARES ---

void enviarComandoAT(String comando, int tiempoEspera) {
  while(sim800Serial.available()) sim800Serial.read();
  sim800Serial.println(comando);
  long tiempoInicio = millis();
  while (millis() - tiempoInicio < tiempoEspera) {
    while (sim800Serial.available()) {
      Serial.write(sim800Serial.read());
    }
  }
}

void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";
  for (unsigned int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  Serial.print("[MQTT] Mensaje recibido en [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(mensaje);

  if (mensaje.equalsIgnoreCase("ON")) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("[ACTUADOR] LED ENCENDIDO");
  } else if (mensaje.equalsIgnoreCase("OFF")) {
    digitalWrite(PIN_LED, LOW);
    Serial.println("[ACTUADOR] LED APAGADO");
  }
}

void conectarMQTT() {
  while (!mqtt.connected()) {
    Serial.print("[MQTT] Intentando conexión al broker...");
    String clientId = "ESP32-Equipo1-Client-";
    clientId += String(random(0xffff), HEX);

    if (mqtt.connect(clientId.c_str())) {
      Serial.println(" ¡Conectado!");
      mqtt.subscribe(topicLED);
      Serial.print("[MQTT] Suscrito al tópico: ");
      Serial.println(topicLED);
    } else {
      Serial.print(" Fallo, rc=");
      Serial.print(mqtt.state());
      Serial.println(" Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}
