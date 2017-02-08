import insulterFromDatabase as ai
import pandas as pd
import OSC
from chatterbot import ChatBot

dataTable = pd.read_csv('../../data/ShitTalkTable.csv')
resultDict = ai.putKeywordsToDict( dataTable )

host = '127.0.0.1'
portSender = 22222
portReciever = 33333

chatbot = ChatBot( 'Elisa Test', trainer='chatterbot.trainers.ChatterBotCorpusTrainer' )
# chatbot.train("chatterbot.corpus.english") # Train based on the english corpus
# chatbot.get_response("Hello, how are you today?")

class Chatter:
    oscSender = OSC.OSCClient( )
    oscSenderAddress_Txt = "/answer_text"       # Python to OF
    oscRecieverAddress_Txt = "/original_text"   # OF to python

    def __init__(self, host, portSender, portReciever):
        self.host_ = host
        self.portSender_ = portSender
        self.portReciever_ = portReciever
        self.oscSender_HostPort = (self.host_, self.portSender_)  # to OpenFrameworks
        self.oscReciever_HostPort = (self.host_, self.portReciever_)  # python
        print self.oscSender_HostPort
        print self.oscReciever_HostPort
        self.oscSender.connect( self.oscSender_HostPort )
        self.oscReceiver = OSC.ThreadingOSCServer( self.oscReciever_HostPort )

    def send(self, text ):
        messageOSC = OSC.OSCMessage( )
        messageOSC.setAddress( self.oscSenderAddress_Txt )
        messageOSC.append( text )
        self.oscSender.send( messageOSC )

    def replyOscHandler( self, addr, tags, stuff, source ):
        input_sentence = stuff[ 0 ]
        print "Original:", input_sentence
        answer = chatbot.get_response( input_sentence )
        # answer = ai.answerFromText( input_sentence, resultDict, dataTable )
        # answer = ai.changeToMale( answer )
        print "Answer: ", answer
        self.send( answer )
        return

# =================================
# =================================

chatterElisa = Chatter( host, portSender, portReciever )

# --- send ready message to openframeworks
textInit = "READY"
chatterElisa.send( textInit )

# --------
print "listening to:", chatterElisa.oscRecieverAddress_Txt
# start osc listener:
chatterElisa.oscReceiver.addMsgHandler( chatterElisa.oscRecieverAddress_Txt, chatterElisa.replyOscHandler )
chatterElisa.oscReceiver.serve_forever( )  # nothing after that works
