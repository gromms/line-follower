from math import *
#target rpm?

# fixed targets
v = 5 # m/s
d_l = [25,30,35,40,45] # mm 
# sumoroboti arvestus: ca 12mm lisab kumm läbimõõdule


c_v=4 # cell voltage
voldid = [1*c_v,2*c_v,3*c_v]


for d in d_l:
    #calc
    #yhe poordega läbib:
    d = d/1000.0 # mm to m
    s = pi * d

    #rpm = 60*pööret sekundis
    rpm = 60*v/s
    print ("D = "+str(d*1000) + " mm, rmp=",int(rpm))
    for volt in voldid:
        print ("\tvoldid: "+str(volt)+"  ",int(rpm/volt),"kv")
