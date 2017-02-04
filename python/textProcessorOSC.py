import insulterFromDatabase

# =========== OSC ===============
# osc INIT
import OSC

oscSender_HostPort = ('127.0.0.1', 22222)  # to OpenFrameworks
oscSenderAddress = "/answer"  # Sending   - python to OF

oscReciever_HostPort = ('127.0.0.1', 33333)  # python
oscRecieverAddress = "/original"  # Recieving - OF to python

# --- Python to openframeworks:
oscSender = OSC.OSCClient( )
oscSender.connect( oscSender_HostPort )

# --- OpenFrameworks to python:
oscReceiver = OSC.ThreadingOSCServer( oscReciever_HostPort )

# ---
# send ready message to openframeworks
oscmsg = OSC.OSCMessage( )
oscmsg.setAddress( oscSenderAddress )
oscmsg.append( "READY" )
oscSender.send( oscmsg )

# --------
print "listening to:", oscRecieverAddress
# start osc listener:
oscReceiver.addMsgHandler( oscRecieverAddress, transformMessageCallback )
oscReceiver.serve_forever( )  # nothing after that works
