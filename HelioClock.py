import time
#------------------
import FormPeticion

ESP8266_Bracelet_Mac='"fc-f5-c4-ac-e8-f2"'
FormPeticion.fInit(ESP8266_Bracelet_Mac)

def clock():
    actualTime=time.strftime("%I:%M")
    while True:
        time.sleep(5) #refresh rate
        timeRequest=time.strftime("%I:%M") # 12h format
        if(timeRequest != actualTime):
            FormPeticion.fPeticion(timeRequest)
