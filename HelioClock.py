import time
#------------------
import FormPeticion

ESP8266_Bracelet_Mac='"fc-f5-c4-ac-e8-f2"'
FormPeticion.fInit(ESP8266_Bracelet_Mac)

def clock():
    actualTime=time.strftime("%H:%M")
    while True:
        time.sleep(5) #refresh rate
        timeRequest=time.strftime("%H:%M") # "%H:%M" 24h format  "%I:%M" 12h format
        if(timeRequest != actualTime):
            actualTime=timeRequest
            FormPeticion.fPeticion(actualTime)
