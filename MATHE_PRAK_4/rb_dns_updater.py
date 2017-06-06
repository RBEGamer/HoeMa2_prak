#!/bin/bash
import urllib2
import time

gen_uuid = "2b96b335-0216-40fa-ae20-c717a6d2469f"
device_name = "MainServer"
password = "1590"
port = "80"
device_type = "server"

print("UUID : " + gen_uuid)
print("PW : " + password)

update_url = "http://109.230.230.209/rb_dns_server/update.php?uuid=" +gen_uuid + "&pass=" + password + "&port=" + port+ "&type=" + device_type + "&device_name=" + device_name
while true:
    #print(update_url)
    content = urllib2.urlopen(update_url).read()
    #print content
    time.sleep(60)
