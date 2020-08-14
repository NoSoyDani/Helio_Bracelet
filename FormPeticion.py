
import MacToIp as mp
from selenium import webdriver

def fPeticion(mac,msg):
    ip=mp.MacIp(mac)
    url="http://"+ip+"/"
    driver = webdriver.Chrome(r"E:\Development\ATOM WSP\chromedriver.exe")  #CHROMEDRIVER PATH
    driver.get(url)
    form = driver.find_element_by_name("txt")
    form.send_keys(msg)
    form.submit()
