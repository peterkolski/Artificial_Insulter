import insulterFromDatabase as ai
import pandas as pd
import OSC

dataTable = pd.read_csv('../data/ShitTalkTable.csv')
resultDict = ai.putKeywordsToDict( dataTable )

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

def replyToMessage( addr, tags, stuff, source ):
    input_sentence = stuff[ 0 ]
    print "Original:", input_sentence
    answer = ai.answerFromText( input_sentence, resultDict, dataTable )
    answer = ai.changeToMale( answer  )
    messageAnswer = OSC.OSCMessage()
    messageAnswer.setAddress( oscSenderAddress_Txt )
    messageAnswer.append( answer )
    oscSender.send( messageAnswer )
    return

# --------
print "listening to:", oscRecieverAddress_Txt
# start osc listener:
oscReceiver.addMsgHandler( oscRecieverAddress_Txt, replyToMessage )
oscReceiver.serve_forever( )  # nothing after that works
