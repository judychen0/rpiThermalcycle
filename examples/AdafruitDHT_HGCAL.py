#!/usr/bin/python

# Google Spreadsheet DHT Sensor Data-logging Example

# Depends on the 'gspread' and 'oauth2client' package being installed.  If you
# have pip installed execute:
#   sudo pip install gspread oauth2client

# Also it's _very important_ on the Raspberry Pi to install the python-openssl
# package because the version of Python is a bit old and can fail with Google's
# new OAuth2 based authentication.  Run the following command to install the
# the package:
#   sudo apt-get update
#   sudo apt-get install python-openssl

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
import json
import sys
import time
import datetime

import serial
import os.path

import Adafruit_DHT
import gspread
from oauth2client.service_account import ServiceAccountCredentials

import board
import busio
import digitalio
import adafruit_max31865


# Type of sensor, can be Adafruit_DHT.DHT11, Adafruit_DHT.DHT22, or Adafruit_DHT.AM2302.
DHT_TYPE = Adafruit_DHT.DHT22

# Example of sensor connected to Raspberry Pi pin 23
DHT_PIN_s1  = 4


# Example of sensor connected to Beaglebone Black pin P8_11
#DHT_PIN  = 'P8_11'

# Google Docs OAuth credential JSON file.  Note that the process for authenticating
# with Google docs has changed as of ~April 2015.  You _must_ use OAuth2 to log
# in and authenticate with the gspread library.  Unfortunately this process is much
# more complicated than the old process.  You _must_ carefully follow the steps on
# this page to create a new OAuth service in your Google developer console:
#   http://gspread.readthedocs.org/en/latest/oauth2.html
#
# Once you've followed the steps above you should have downloaded a .json file with
# your OAuth2 credentials.  This file has a name like SpreadsheetData-<gibberish>.json.
# Place that file in the same directory as this python script.
#
# Now one last _very important_ step before updating the spreadsheet will work.
# Go to your spreadsheet in Google Spreadsheet and share it to the email address
# inside the 'client_email' setting in the SpreadsheetData-*.json file.  For example
# if the client_email setting inside the .json file has an email address like:
#   149345334675-md0qff5f0kib41meu20f7d1habos3qcu@developer.gserviceaccount.com
# Then use the File -> Share... command in the spreadsheet to share it with read
# and write acess to the email address above.  If you don't do this step then the
# updates to the sheet will fail!

# How long to wait (in seconds) between measurements.
FREQUENCY_SECONDS      = 9

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

## Initialize SPI bus and sensor.
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
# Chip select of the MAX31865 board. D5 = GPIO5 on Rpi3
cs2 = digitalio.DigitalInOut(board.D13)  #rtd100  
cs3 = digitalio.DigitalInOut(board.D6) #rtd1000
sensor2 = adafruit_max31865.MAX31865(spi, cs2)
sensor3 = adafruit_max31865.MAX31865(spi, cs3, rtd_nominal=1000, ref_resistor=4300.0, wires=2)

#open dht22 data file to log data
save_path = "/home/pi/Adafruit_Python_DHT/data"
filename = raw_input("Data filename (without .txt) : ")
full_filename = os.path.join(save_path, filename+".csv")
f = open(full_filename, "w")

while True:
    # Login if necessary.
    
    # Attempt to get sensor reading.
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

    # Wait 10 seconds before continuing
    print('Wrote a row to {0}'.format(filename))
    time.sleep(FREQUENCY_SECONDS)
