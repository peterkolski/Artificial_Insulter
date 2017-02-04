# import insulterFromDatabase

# =========== OSC ===============
# osc INIT
import OSC

oscSender_HostPort = ('127.0.0.1', 22222)  # to OpenFrameworks
oscSenderAddress_Txt = "/answer_text"  # Sending   - python to OF

oscReciever_HostPort = ('127.0.0.1', 33333)  # python
oscRecieverAddress_Txt = "/original_text"  # Recieving - OF to python

# --- Python to openframeworks:
oscSender = OSC.OSCClient( )
oscSender.connect( oscSender_HostPort )

# --- OpenFrameworks to python:
oscReceiver = OSC.ThreadingOSCServer( oscReciever_HostPort )

# --- send ready message to openframeworks
message = OSC.OSCMessage( )
message.setAddress( oscSenderAddress_Txt )
message.append( "READY" )
oscSender.send( message )

def transformMessageCallback( addr, tags, stuff, source ):
    input_sentence = stuff[ 0 ]
    print "received text to transform:", input_sentence
    message = OSC.OSCMessage( )
    message.setAddress( oscSenderAddress_Txt )
    message.append( "message recieved" )
    oscSender.send( message )
    return

# --------
print "listening to:", oscRecieverAddress_Txt
# start osc listener:
oscReceiver.addMsgHandler( oscRecieverAddress_Txt, transformMessageCallback )
oscReceiver.serve_forever( )  # nothing after that works
