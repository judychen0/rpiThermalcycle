#!/usr/bin/python
# Copyright (c) 2014 Adafruit Industries
# Author: Tony DiCola

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
import sys
import time
import datetime
import Adafruit_DHT
import os.path
import serial

import board
import busio
import digitalio
import adafruit_max31865

#data reading frequency
FrequencySeconds = 9

ser = serial.Serial(
    
    port='/dev/ttyUSB0',
    baudrate = 9600,
    parity=serial.PARITY_EVEN,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.SEVENBITS,
    xonxoff=False,
    rtscts=False,
    writeTimeout=None,
    dsrdtr=False,
    interCharTimeout=None,
    timeout=0.5
)

# Parse command line parameters.
sensor_args = { '11': Adafruit_DHT.DHT11,
                '22': Adafruit_DHT.DHT22,
                '2302': Adafruit_DHT.AM2302 }
if len(sys.argv) == 3 and sys.argv[1] in sensor_args:
    sensor = sensor_args[sys.argv[1]]
    pin = sys.argv[2]
else:
    print('Usage: sudo ./Adafruit_DHT.py [11|22|2302] <GPIO pin number>')
    print('Example: sudo ./Adafruit_DHT.py 2302 4 - Read from an AM2302 connected to GPIO pin #4')
    sys.exit(1)

#open dht22 data file to log data
save_path = "/home/pi/Adafruit_Python_DHT/data"
filename = raw_input("Data filename (without .txt) : ")
full_filename = os.path.join(save_path, filename+".csv")
f = open(full_filename, "w")

# Initialize SPI bus and sensor.
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
cs2 = digitalio.DigitalInOut(board.D13)  #rtd100 # Chip select of the MAX31865 board. D5 = GPIO5 on Rpi3
cs3 = digitalio.DigitalInOut(board.D6) #rtd1000
sensor2 = adafruit_max31865.MAX31865(spi, cs2)
sensor3 = adafruit_max31865.MAX31865(spi, cs3, rtd_nominal=1000, ref_resistor=4300.0, wires=2)

# Try to grab a sensor reading.  Use the read_retry method which will retry up
# to 15 times to get a sensor reading (waiting 2 seconds between each retry).
while 1:
    humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

    temp2 = sensor2.temperature
    resis2 = sensor2.resistance
    
    temp3 = sensor3.temperature
    resis3 = sensor3.resistance

    # Un-comment the line below to convert the temperature to Fahrenheit.
    # temperature = temperature * 9/5.0 + 32
    
    # Note that sometimes you won't get a reading and
    # the results will be null (because Linux can't
    # guarantee the timing of calls to read the sensor).
    # If this happens try again!
    if humidity is not None and temperature is not None:

        command = "C2\r"
        ser.write(command.encode()) #python3
        data = ser.readline()
        decode_data = data.decode("utf-8")
        print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S ") + decode_data)
        print('Temperature_S1: {0:0.1f} C '.format(temp_s1) + 'Humidity_S1: {0:0.1f} %'.format(humidity_s1))
        print("pt100  Temperature: {0:0.2f}*C Resistance: {1:0.3f}*Ohms".format(temp2, resis2))
        print("pt1000 Temperature: {0:0.2f}*C Resistance: {1:0.3f}*Ohms".format(temp3, resis3))
	f.writelines(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S,")+'{0:0.01f},{1:0.01f},{2:0.2f},{3:0.2f},'.format(temperature, humidity, temp2, temp3)+ decode_data)
    else:
        print('Failed to get reading. Try again!')

    print('Wrote a row to {0}'.format(filename))
    time.sleep(FrequencySeconds)
    #sys.exit(1)
