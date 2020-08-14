import subprocess
def MacIp(mac):
    shell_output = subprocess.check_output('arp -a | find '+ mac, shell=True)   #arp -n | grep <direccion_MAC>     LINUX
    ip=shell_output.split()[0].decode("utf-8")
    return ip

#'"e0-dc-ff-08-12-0e"'   #MODEL
