import serial
import os
f = os.popen('ls /dev/ttyACM*')
now = f.read()
now=now[:-1]
print now
#os.system('sudo minicom')
ser = serial.Serial(now,9600)
while True:
 ser.write("ok")