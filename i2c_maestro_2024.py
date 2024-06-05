"""
Lectura de I2C en ESP32 con MicroPython
---------------------------------------
El tamaño de los datos a leer debe especificarse y ser consistente con lo que envia el dispositivo esclavo o sensor, de lo contrario
se producira un error tipo ENODEV en la lectura.... se puede implementar un try except y leer byte a byte hasta que se reciba un error
para leer n bytes.
---------------------------------------

"""

# importar desde machine i2C y Pin
from machine import I2C, Pin
from time import sleep

# Crear un objeto I2C en el bus 0
bus = I2C(0, scl=Pin(22), sda=Pin(21), freq=400000)

# Dirección del dispositivo esclavo
mbed = 40
# Dirección del microcontroaldor MBED corrida una a la derecha

print(bus.scan())

while True:
    
    print(bus.readfrom(mbed, 6))
    sleep(2)

