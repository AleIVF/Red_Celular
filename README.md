# Actividad VII - Fundamentos y aplicación del módulo SIM800L

**Facultad de Telemática**  
**Ingeniería en Tecnologías de Internet**  
**Entornos inteligentes y tecnologías disruptivas**

---

## Integrantes del equipo

1. Vega Flores Alejandra Ixchel
2. Diaz Ramirez Dulce Maria
3. Jazmin Rodriguez Jimenez
4. Jocelyn Yareli Mancilla Radillo

**Profesor:** Esli Castellanos Berjan

**Nombre del equipo:**  
Equipo 1

**Fecha:** 10/09/2026

---

## 1. Objetivo General

Diseñar e implementar una solución que integre el microcontrolador ESP32 y el módulo SIM800L para gestionar comunicaciones GSM (envío de mensajes SMS y llamadas telefónicas) y control remoto de un LED mediante el protocolo MQTT sobre GPRS, permitiéndonos comprender y resolver los retos de interoperabilidad, alimentación y cobertura entre redes celulares e IoT.

## 2. Objetivos Específicos

1. Investigar y probar los comandos AT del módulo SIM800L para validar el envío de mensajes SMS, hacer llamadas y la configuración de datos GPRS.
2. Armar el circuito conectando el ESP32 con el módulo SIM800L, asegurando una fuente de energía suficiente para que no se apague al buscar señal.
3. Programar el envío de SMS y llamadas de forma automática hacia los celulares de cada uno de los integrantes del equipo para comprobar que el módulo sí se conecta a la red móvil.
4. Conectar el módulo a Internet móvil (GPRS) configurando el APN de la compañía telefónica para poder comunicarnos con el servidor MQTT.
5. Encender y apagar un LED a distancia recibiendo las instrucciones (ON/OFF) que enviemos a través de un canal de mensajes MQTT.

## 3. Competencias

- **Comunicación mediante comandos AT:** Habilidad para enviar comandos por puerto serie al SIM800L y gestionar SMS, llamadas de voz y conexiones GPRS.
- **Configuración de redes celulares e IoT:** Dominio en la configuración de APN y MQTT sobre GPRS para interconectar nodos remotos a la nube.
- **Desarrollo de lógica en microcontroladores:** Programación en el ESP32 para interpretar datos entrantes y controlar periféricos como un LED de forma autónoma.
- **Diagnóstico y análisis de conectividad:** Habilidad para identificar y solucionar fallas de señal, latencia y errores de transmisión en el entorno celular.

## 4. Tabla de Contenidos

1. [Objetivo General](#1-objetivo-general)
2. [Objetivos Específicos](#2-objetivos-específicos)
3. [Competencias](#3-competencias)
4. [Tabla de Contenidos](#4-tabla-de-contenidos)
5. [Descripción](#5-descripción)
6. [Requisitos](#6-requisitos)
7. [Instalación y Configuración](#7-instalación-y-configuración)
8. [Conexiones de Hardware](#8-conexiones-de-hardware)
9. [Parámetros Técnicos del SIM800L](#9-parámetros-técnicos-del-sim800l)
10. [Uso y ejemplos de Código](#10-uso-y-ejemplos-de-código)
11. [Resultados de Prueba](#11-resultados-de-prueba)
12. [Consideraciones Éticas y de Seguridad](#12-consideraciones-éticas-y-de-seguridad)
13. [Solución de Problemas](#13-solución-de-problemas)
14. [Contribuciones](#14-contribuciones)
15. [Referencias](#15-referencias)

---

## 5. Descripción

En los entornos inteligentes, contar con una conectividad celular confiable es fundamental cuando no existe acceso a Wi-Fi o redes cableadas. El módulo SIM800L ofrece una solución compacta que integra el envío de SMS, llamadas de voz y conexión de datos GPRS en un solo dispositivo, permitiendo que nodos remotos se comuniquen con servidores o la nube.

En esta práctica, integramos este módulo con el microcontrolador ESP32 para desarrollar un prototipo capaz de gestionar alertas celulares y controlar un LED de manera remota mediante el protocolo MQTT.

Este ejercicio nos permite comprender la interacción entre redes móviles e IoT, abordando retos clave de alimentación eléctrica, cobertura y configuración de red en sistemas distribuidos.

## 6. Requisitos

### Hardware necesario

- Microcontrolador ESP32.
- Módulo SIM800L con antena GSM.
- Fuente de alimentación externa (4 V - 5 V / 2 A).
- Tarjeta SIM con saldo o datos activos.
- Protoboard.
- LED.
- Resistencia.
- Cables puente Dupont.
- Equipo de cómputo con Arduino IDE.

### Software y bibliotecas requeridas

- Arduino IDE.
- Cliente MQTT.
- Broker MQTT.
- Librerías: `HardwareSerial`, `PubSubClient`, `*****`

### Conocimientos previos imprescindibles

- Comunicación por puerto serie (UART) y comandos AT.
- Conceptos básicos de electrónica y manejo de alimentación en hardware.
- Funcionamiento del protocolo MQTT (Broker, Tópicos, Publicación y Suscripción).
- Configuración de APN y redes celulares GPRS.

## 7. Instalación y Configuración

El primer paso fue armar el circuito conectando los pines UART entre el ESP32 y el SIM800L, el LED indicador en el GPIO 4 y la fuente de alimentación externa de 4.0 V con masa común compartida.

Después, se configuró el código. Para ello, abrimos el programa en Arduino IDE y actualizamos los parámetros de la práctica:

- Número telefónico asignado.
- APN del proveedor.
- Broker MQTT.
- Tópico de suscripción.

Posteriormente, conectamos el ESP32 a la computadora mediante USB, seleccionamos el puerto COM correspondiente y transferimos el firmware a la placa.

Por último, durante la ejecución de las pruebas, se abrió el Monitor Serie a 115200 baudios para verificar en secuencia:

1. La respuesta a los comandos AT.
2. El envío del SMS.
3. La llamada automatizada.
4. El control del LED vía MQTT.

## 8. Conexiones de Hardware

| Señal del módulo | Pin de la placa | Función |
|---|---|---|
| **VCC (SIM800L)** | Fuente Externa (+) | Entrada de alimentación dedicada (4.0 V – 4.2 V / 2 A pico). |
| **GND (SIM800L)** | GND (ESP32) y Fuente (-) | Referencia eléctrica común (masa compartida). |
| **TXD (SIM800L)** | GPIO 16 (RX2) | Transmisión serie del módem hacia recepción del ESP32. |
| **RXD (SIM800L)** | GPIO 17 (TX2) | Recepción serie del módem desde transmisión del ESP32. |
| **Ánodo LED** | GPIO 4 *(vía resistencia)* | Salida digital para control ON/OFF mediante MQTT. |
| **Cátodo LED** | GND | Retorno de corriente a tierra para el LED. |

## 9. Parámetros Técnicos del SIM800L

| Parámetro Clave | Valor Típico | Unidad de Medida |
|---|---|---|
| Voltaje de Operación | 3.4 – 4.4 (Recomendado: 4.0) | V (Voltios) |
| Pico de Corriente (Transmisión RF) | 2.0 | A (Amperios) |
| Consumo en reposo (*Sleep mode*) | ~ 1.0 – 1.5 | mA (Miliamperios) |
| Frecuencias de Operación (Cuatribanda) | 850 / 900 / 1800 / 1900 | MHz (Megahercios) |
| Interfaz de Comunicación | UART (Niveles lógicos 2.8 V – 3.3 V) | Baudios (9600 – 115200 bps) |
| Conector de Antena RF | IPX / U.FL o Pad para antena helicoidal | 50 Ω de impedancia |
| Clase de Datos GPRS | Clase 12 (hasta 85.6 kbps) | kbps (Kilobits por segundo) |

## 10. Uso y ejemplos de Código

El código fuente del proyecto debe descargarse de GitHub y abrirse en Arduino IDE.

Cada bloque del programa debe ser comentado de manera descriptiva, explicando la finalidad del proyecto y manteniendo una redacción profesional.

Esto incluye documentar detalladamente cada una de las declaraciones de variables utilizadas, tales como:

- Los pines de comunicación serie con el SIM800L.
- Los parámetros de red y APN.
- La dirección del broker y tópicos MQTT.
- Los números telefónicos asignados a cada integrante del equipo.

## 11. Resultados de Prueba

<!-- Agregar aquí los resultados obtenidos durante las pruebas del proyecto. -->

## 12. Consideraciones Éticas y de Seguridad

- **Privacidad de datos en tránsito:** El protocolo MQTT estándar opera en texto plano sobre el puerto 1883. Los paquetes pueden ser interceptados mediante ataques de intermediario (MitM) si no se implementa cifrado de capa de transporte (MQTTS/TLS sobre el puerto 8883).

- **Filtros de control y autenticación:** Dejar brokers públicos sin usuario ni contraseña expone los actuadores a manipulaciones no autorizadas por terceros en la misma red. Se debe mitigar configurando tokens o listas de control de acceso (ACLs).

- **Protección de identificadores y números celulares:** La exposición de credenciales del APN, claves de brokers o agendas telefónicas de los integrantes en repositorios públicos vulnera la privacidad y expone a campañas de spam o cobros indebidos. Deben gestionarse mediante variables de entorno o un archivo `.gitignore`.

- **Uso responsable del espectro celular:** El envío masivo no controlado de SMS o la generación de llamadas cíclicas continuas satura canales y puede acarrear penalizaciones o la suspensión del servicio por parte del operador de telecomunicaciones.

## 13. Solución de Problemas

### No hay conexión a Internet

**Causa:** APN mal escrito o la SIM no tiene datos.

**Solución:** Revisar que el APN coincida con la compañía y confirmar que la SIM tenga saldo o paquete activo.

### El cliente MQTT no conecta o no recibe mensajes

**Causa:** IP/puerto del Broker incorrectos o error al escribir el tópico.

**Solución:** Confirmar la dirección del Broker y el puerto 1883. Usar el cliente MQTT para verificar que estés publicando en el mismo tópico.

### Error al escribir el número telefónico

**Causa:** Transcripción incorrecta de dígitos al capturar el teléfono en el código.

**Solución:** Revisar número por número antes de subir el programa y asegurarse de incluir la lada del país.

### Voltaje incorrecto

**Causa:** Alimentar el SIM800L desde el ESP32 o meterle más de 4.4 V.

**Solución:** Conectar una fuente externa a 4 V (mínimo 2 A) para evitar que el módulo se reinicie o se queme.

## 14. Contribuciones

Para sumar mejoras al proyecto, la idea es empezar haciendo un **fork** del repositorio a tu cuenta personal.

A partir de ahí, desarrollas los cambios en ramas (*branches*) separadas, nombrándolas de forma clara según la función o corrección que vayas a implementar.

Ya que pruebes los cambios localmente y veas que todo funciona bien, mandas un **pull request** detallando qué fue lo que ajustaste.

Este flujo nos ayuda a mantener el repositorio ordenado y hace que la revisión entre el equipo sea mucho más rápida y directa.

## 15. Referencias

- Espressif Systems. (2021). *ESP32 Technical Reference Manual* (Revision 3) [Technical Manual]. Espressif Systems.

- OASIS. (2015). *MQTT Version 3.1.1*. OASIS Standard.  
  https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html

- Pérez, L., & Gómez, F. (2023). *Latency and Power Consumption in GPRS-based IoT Communication: A Case Study with SIM800L*. En *Proceedings of the 2023 IEEE Latin American Conference on Communications*.

- SIMCom Wireless Solutions. (2016). *SIM800L Hardware Design V1.00* [Datasheet]. Recuperado de:  
  https://www.simcom.com/product/SIM800L

- SIMCom Wireless Solutions. (2016). *SIM800 Series AT Commands Manual V2.11* [Application Note]. Recuperado de:  
  https://www.simcom.com/documents/SIM800-Series/AT%20Commands%20Manual_V2.11.pdf
