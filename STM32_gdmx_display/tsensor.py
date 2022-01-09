from subprocess import Popen, PIPE
from time import sleep
#import json
while True:
    out= Popen('sensors', shell=True, stdout=PIPE) #.communicate()
    rawOut=str(out.stdout.read())
    #print (rawOut)
    #sensors=json.loads(rawOut)
    index=rawOut.find("Core ")
    output=rawOut[index:index+7]
    rawOut=rawOut[index:]
    index=rawOut.find("+")
    output=output+" "*8+rawOut[index:index+5]
    #t0=int(rawOut[index+1:index+3])
    t0=int((int(rawOut[index+1:index+3])-30)*20/70)
    rawOut=rawOut[index:]
    index=rawOut.find("Core ")
    output=output+rawOut[index:index+7]
    rawOut=rawOut[index:]
    index=rawOut.find("+")
    output=output+" "*8+rawOut[index:index+5]
    #t1=int(rawOut[index+1:index+3])
    t1=int((int(rawOut[index+1:index+3])-30)*20/70)
    output=output+"="*t0+" "*(20-t0)+"="*t1+" "*(20-t1)
    print(output)
    sleep(0.1)
    