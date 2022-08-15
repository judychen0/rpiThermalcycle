#!/usr/bin/env python
          
      
import time
import datetime
import serial
import os.path
      
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
#ser.close()
#ser.open()

def writeCode(command):
    Command = command.upper()
    ser.write(Command+"\r")
    print(ser.readline())
    
def offset():
    #program setting mode
    writeCode("C3=P")
    #program No.
    writeCode("C4=1")

#steptime format 0:00 or 00:00
def oneStep(stepnum, temp, steptime):
    writeCode("C5="+str(stepnum))
    writeCode("C6="+str(temp))
    writeCode("C8="+steptime)

# go : return from step No.go
# to : return to step No.to
def returnStep(go, to, repetition):
    writeCode("C5="+str(go))
    writeCode("C9="+str(to))
    writeCode("CA="+str(repetition))

### Start of command script ###
if ser.isOpen():
    
    # put in setting mode
    offset()

    # define steps
    oneStep(1, 40, "0:17")
    oneStep(2, 40, "0:20")
    oneStep(3, -10, "0:50")
    oneStep(4, -10, "0:20")
    oneStep(5, 22, "0:11")
    oneStep(6, 22, "99:00")
    writeCode("CE=7")
    returnStep(4, 1, 2)
    
### End of command script ###

save_path = "/home/pi/Adafruit_Python_DHT/data"
filename = raw_input("Data filename(without .txt) : ")
full_serial_filename = os.path.join(save_path, filename+"_serial.txt")


def saveRead():
    print(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S "))
    writeCode("C2")
    f_S = open(full_serial_filename, "a")
    data = ser.readline()
    decode_data = str(data[0:len(data)-2].decode("utf-7"))
    print(type(decode_data))
    f_S.writelines(decode_data)
    f_S.close()
    
    #f_S.writelines(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S ")+ser.readline()+"\n")
    #f_S.writelines(line)

while 1:
    saveRead()
    time.sleep(0.5)
