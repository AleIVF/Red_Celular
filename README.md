# Actividad VII - Fundamentos y aplicación del módulo SIM800L

**Facultad de Telemática**  
**Ingeniería en Tecnologías de Internet**  
**Materia:** Entornos inteligentes y tecnologías disruptivas

## Integrantes

1. Vega Flores Alejandra Ixchel
2. Diaz Ramirez Dulce Maria
3. Jazmin Rodriguez Jimenez
4. Jocelyn Yareli Mancilla Radillo

**Profesor:** Esli Castellanos Berjan  
**Equipo:** Equipo 1  
**Fecha:** 10/09/2026

---

## 1. Objetivo General

Diseñar e implementar una solución que integre el microcontrolador **ESP32** y el módulo **SIM800L** para gestionar comunicaciones GSM, como el envío de mensajes SMS y llamadas telefónicas, además del control remoto de un LED mediante el protocolo **MQTT sobre GPRS**.

Con esta práctica se busca comprender y resolver los principales retos relacionados con la interoperabilidad, alimentación eléctrica y cobertura en sistemas de comunicación celular e IoT.

## 2. Objetivos Específicos

1. Investigar y probar los comandos **AT** del módulo SIM800L para validar el envío de mensajes SMS, realizar llamadas y configurar la conexión de datos GPRS.
2. Armar el circuito conectando el ESP32 con el SIM800L, utilizando una fuente de alimentación suficiente para evitar que el módulo se apague durante la búsqueda de señal.
3. Programar el envío automático de SMS y llamadas a los celulares de los integrantes del equipo para comprobar la conexión del módulo a la red móvil.
4. Conectar el módulo a Internet mediante **GPRS**, configurando el APN del proveedor telefónico para establecer comunicación con un servidor MQTT.
5. Controlar un LED de forma remota mediante mensajes **MQTT**, utilizando las instrucciones `ON` y `OFF`.

## 3. Competencias

Durante la realización de esta práctica se desarrollaron las siguientes competencias:

- **Comunicación mediante comandos AT:** envío de comandos por puerto serie al SIM800L para gestionar SMS, llamadas y conexiones GPRS.
- **Configuración de redes celulares e IoT:** configuración del APN y MQTT sobre GPRS para conectar dispositivos remotos.
- **Programación de microcontroladores:** desarrollo de la lógica en el ESP32 para interpretar mensajes recibidos y controlar un LED.
- **Diagnóstico de conectividad:** identificación y solución de problemas relacionados con señal, latencia y transmisión de datos.

## 4. Descripción del Proyecto

En los entornos inteligentes, la conectividad celular es importante cuando no se dispone de una red Wi-Fi o una conexión cableada. El módulo **SIM800L** permite realizar comunicaciones mediante SMS, llamadas de voz y conexión de datos GPRS.

En esta práctica se integró el SIM800L con un **ESP32** para desarrollar un prototipo capaz de gestionar comunicaciones celulares y controlar un LED de manera remota mediante el protocolo MQTT.

El proyecto permite comprender la interacción entre las redes móviles y los sistemas IoT, considerando aspectos como la alimentación eléctrica, la cobertura de la red y la configuración de la comunicación.

## 5. Requisitos

### Hardware

- ESP32
- Módulo SIM800L con antena GSM
- Fuente de alimentación externa de 4 V - 5 V / 2 A
- Tarjeta SIM con saldo o datos activos
- Protoboard
- LED
- Resistencia
- Cables puente Dupont
- Computadora con Arduino IDE

### Software y Bibliotecas

- Arduino IDE
- Cliente MQTT
- Broker MQTT
- Biblioteca `HardwareSerial`
- Biblioteca `PubSubClient`

### Conocimientos Previos

- Comunicación mediante puerto serie (UART) y comandos AT.
- Conceptos básicos de electrónica y alimentación eléctrica.
- Funcionamiento del protocolo MQTT: broker, tópicos, publicación y suscripción.
- Configuración de APN y redes celulares GPRS.

## 6. Instalación y Configuración

Para comenzar, se debe armar el circuito conectando los pines UART entre el **ESP32** y el **SIM800L**, además del LED indicador en el **GPIO 4**. El SIM800L debe utilizar una fuente de alimentación externa de aproximadamente **4.0 V**, compartiendo la conexión GND con el ESP32.

Posteriormente, se debe abrir el proyecto en **Arduino IDE** y configurar los parámetros correspondientes, como el número telefónico, el APN del proveedor, el broker MQTT y el tópico de suscripción.

Una vez configurado el código, se conecta el ESP32 a la computadora mediante USB, se selecciona el puerto COM correspondiente y se carga el programa en la placa.

Finalmente, se abre el Monitor Serie a **115200 baudios** para comprobar la respuesta a los comandos AT, el envío del SMS, la llamada automática y el control del LED mediante MQTT.

## 7. Conexiones de Hardware

| Señal del SIM800L | Pin / Conexión | Función |
|---|---|---|
| **VCC** | Fuente externa (+) | Alimentación del módulo, aproximadamente 4.0 - 4.2 V |
| **GND** | GND del ESP32 y fuente (-) | Referencia eléctrica común |
| **TXD** | GPIO 16 (RX2) | Transmisión de datos del SIM800L hacia el ESP32 |
| **RXD** | GPIO 17 (TX2) | Recepción de datos enviados por el ESP32 |
| **Ánodo LED** | GPIO 4 mediante resistencia | Control del LED mediante MQTT |
| **Cátodo LED** | GND | Retorno de corriente |

## 8. Parámetros Técnicos del SIM800L

| Parámetro | Valor Típico |
|---|---|
| Voltaje de operación | 3.4 - 4.4 V |
| Voltaje recomendado | 4.0 V |
| Pico de corriente | 2.0 A |
| Consumo en reposo | ~1.0 - 1.5 mA |
| Frecuencias de operación | 850 / 900 / 1800 / 1900 MHz |
| Interfaz de comunicación | UART |
| Velocidad UART | 9600 - 115200 bps |
| Conector de antena RF | IPX / U.FL o pad para antena helicoidal |
| Clase GPRS | Clase 12 |
| Velocidad GPRS | Hasta 85.6 kbps |

## 9. Uso y Ejemplos de Código

El código fuente del proyecto puede descargarse desde este repositorio y abrirse utilizando **Arduino IDE**.

El programa utiliza la comunicación serial entre el ESP32 y el SIM800L para enviar comandos AT y gestionar las funciones de comunicación celular. También utiliza MQTT sobre GPRS para recibir instrucciones de manera remota.

El código debe contener comentarios que expliquen la función de las principales partes del programa, incluyendo:

- Pines de comunicación con el SIM800L.
- Configuración de la conexión serial.
- APN del proveedor de telefonía.
- Dirección y puerto del broker MQTT.
- Tópicos utilizados.
- Números telefónicos utilizados durante las pruebas.

> **Importante:** No se deben publicar en GitHub números telefónicos, contraseñas, credenciales, tokens o datos privados utilizados durante las pruebas.

## 10. Funcionamiento

El funcionamiento general del proyecto es el siguiente:

```text
ESP32
  │
  │ UART
  ▼
SIM800L
  │
  ├── SMS
  │
  ├── Llamadas
  │
  └── GPRS
        │
        ▼
    Broker MQTT
        │
        ▼
   Mensaje ON/OFF
        │
        ▼
       LED
