#
# Kradziony i przerobionyskrypt.Znaleźć oryginał i dodać odnośnik
#

import matplotlib.pyplot as plt
from drawnow import *
import atexit
import serial


plot_data = []
row = []
samples_count = 256

plt.ion()
cnt=0
ports = ['/dev/ttyUSB0', '/dev/ttyUSB1', '/dev/ttyACM0', '/dev/ttyACM1']
port = ""
serialArduino = None
err = None
for port in ports:
    try:
        serialArduino = serial.Serial(port, 115200)
    except IOError as e:
        err = e

if serialArduino is None:
    raise err

colors = ('b','g','r','c','m','y','k','w',)
styles = ('o', 'v', '^', '<', '>', '8', 's', 'p', '*', 'h', 'H', 'D', 'd')
line_styles = map(lambda offset: colors[offset] + styles[offset], range(min(len(colors), range(len(styles)))))


def plotValues():
    plt.title('Serial value from Arduino')
    #plt.axis([0.0, samples_count, 0.0,5.0])
    #plt.gca().set_autoscale_on(False)
    plt.grid(True)
    plt.ylabel('Values')
    processed_data = []
    for column in range(len(plot_data)):
        processed_data.append(list(range(samples_count)))
        processed_data.append(plot_data[column])
        processed_data.append(line_styles[column])
        #processed_data.append('values ' + str(column))

    plt.plot(*processed_data)
    plt.legend(loc='upper right')

def doAtExit():
    serialArduino.close()
    print("Close serial")
    print("serialArduino.isOpen() = " + str(serialArduino.isOpen()))

atexit.register(doAtExit)

print("serialArduino.isOpen() = " + str(serialArduino.isOpen()))

while True:
    while (serialArduino.inWaiting()==0):
        pass
    valueRead = serialArduino.readline(500)

    try:
        row = map(float, valueRead.strip().split(','))
    except ValueError:
        print("Invalid! cannot cast")
    #row = map(lambda val: float(val) / 1024.0 * 5.0, row)
    print(valueRead.strip() + " -> " + str(row))
    for column in range(len(row)):
        if len(plot_data) <= column:
            plot_data.append([0] * samples_count)
        plot_data[column].append(row[column])
        plot_data[column].pop(0)
    drawnow(plotValues)

