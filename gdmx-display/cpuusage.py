import psutil

from time import sleep
while True:
    usagelist=psutil.cpu_percent(interval=1, percpu=True)
    i=0
    output=""
    for x in usagelist:
        output=output+"Core "+str(i)+":"+" "*(20-7-len(str(x)))+str(x)
        i=i+1
    print (output)
    #print (usagelist)
    sleep (0.1)
    