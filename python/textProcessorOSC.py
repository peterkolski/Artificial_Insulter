import insulterFromDatabase

# =========== OSC ===============
#osc INIT
import OSC

osc_sender_HostPort= ('127.0.0.1' , 22222) #OpenFrameworks
osc_send_address = "/python_here"       #Sending   - python to OF
osc_transform_address = "/transform"    #Recieving - OF to python
oscReciever_HostPort = ('127.0.0.1' , 33333) #python

# Python to openframeworks:
oscSender = OSC.OSCClient()
oscSender.connect(osc_sender_HostPort)

# OpenFrameworks to python:
oscReceiver = OSC.ThreadingOSCServer(oscReciever_HostPort)

#---
# send ready message to openframeworks
oscmsg = OSC.OSCMessage()
oscmsg.setAddress(osc_send_address)
oscmsg.append("READY");
oscSender.send(oscmsg)

#--------
print "listening to:",osc_transform_address
# start osc listener:
oscReceiver.addMsgHandler(osc_transform_address, transformMessageCallback)
oscReceiver.serve_forever() # nothing after that works
