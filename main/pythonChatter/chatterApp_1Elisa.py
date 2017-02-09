import insulterFromDatabase as ai
import pandas as pd
import OSC
from chatterbot import ChatBot

dataTableShitTalk = pd.read_csv('../../data/ShitTalkTable.csv')

host = '127.0.0.1'
portSender = 22222
portReciever = 33333


# chatbot = ChatBot( 'Elisa Test', trainer='chatterbot.trainers.ChatterBotCorpusTrainer' )
chatterbotInstance = ChatBot('Kora',
                     trainer='chatterbot.trainers.ChatterBotCorpusTrainer',
                     storage_adapter="chatterbot.storage.JsonFileStorageAdapter",
                     read_only=True,
                     database = "./databasePeter.json")
# chatbot.train("chatterbot.corpus.english") # Train based on the english corpus
# chatbot.get_response("Hello, how are you today?")

# =================================
# === CHATTER CLASS
# =================================

class Chatter:
    oscSender               = OSC.OSCClient( )
    oscSenderAddress_Txt    = "/answer_text"     # Python to OF
    oscRecieverAddress_Txt  = "/original_text"   # OF to python

    def __init__(self, host, portSender, portReciever, dataTable, chatterbot):
        self.host_ = host
        self.portSender_ = portSender
        self.portReciever_ = portReciever
        self.dataTable_      = dataTable
        self.chatterbot_     = chatterbot
        self.oscSender_HostPort = (self.host_, self.portSender_)  # to OpenFrameworks
        self.oscReciever_HostPort = (self.host_, self.portReciever_)  # python
        self.counter = 0
        print self.oscSender_HostPort
        print self.oscReciever_HostPort
        self.oscSender.connect( self.oscSender_HostPort )
        self.oscReceiver = OSC.ThreadingOSCServer( self.oscReciever_HostPort )
        self.resultDict = ai.putKeywordsToDict( dataTable )

    def send(self, text ):
        messageOSC = OSC.OSCMessage( )
        messageOSC.setAddress( self.oscSenderAddress_Txt )
        messageOSC.append( text )
        self.oscSender.send( messageOSC )

    def replyOscHandler( self, addr, tags, stuff, source ):
        input_sentence = str( stuff[ 0 ] )
        print "Original:", input_sentence
        self.counter += 1
        # answer = str( self.counter ) + " "
        answer = ""
        if ( self.counter % 2 == 0 ):        # TODO switching between the chatters
            # answer += "ChatterBot | "
            if (input_sentence != ""):
                answer += str(self.chatterbot_.get_response(input_sentence))
        else:
            # answer += "DataInsulter | "
            answerTMP = ai.answerFromText(input_sentence, self.resultDict, self.dataTable_)
            answer += ai.changeToMale( answerTMP )
        print "Answer: ", answer
        self.send( answer )
        return

# =================================
# =================================

chatterElisa = Chatter( host, portSender, portReciever, dataTableShitTalk, chatterbotInstance )

# --- send ready message to openframeworks
chatterElisa.send( "READY" )
chatterElisa.send( "Second start message")

# --------
print "listening to:", chatterElisa.oscRecieverAddress_Txt
# start osc listener:
chatterElisa.oscReceiver.addMsgHandler( chatterElisa.oscRecieverAddress_Txt, chatterElisa.replyOscHandler )
chatterElisa.oscReceiver.serve_forever( )  # nothing after that works
