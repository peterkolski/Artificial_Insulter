import pandas as pd
from chatterbot import ChatBot
from Chatter import ChatterSystem

# =================================
# ====== SETUP
# =================================

dataTableShitTalk = pd.read_csv('../../data/ShitTalkTable.csv')

host = '127.0.0.1'
portSender = 22222
portReciever = 33333

chatterbotInstance = ChatBot('Kora',
                            storage_adapter="chatterbot.storage.JsonFileStorageAdapter",
                            read_only=True,
                            filters=["chatterbot.filters.RepetitiveResponseFilter"],    #Do not repeat yourself too often
                            database = "./databasePeter.json"
                             )
# chatbot.train("chatterbot.corpus.english") # Train based on the english corpus

chatterElisa = ChatterSystem( host, portSender, portReciever, dataTableShitTalk, chatterbotInstance )

# =================================
# ===== APP
# =================================

# --- send ready message to openframeworks
chatterElisa.send( "READY" )

# --------
print "listening to:", chatterElisa.oscRecieverAddress_Txt
# start osc listener:
chatterElisa.oscReceiver.addMsgHandler( chatterElisa.oscRecieverAddress_Txt, chatterElisa.replyOscHandler )
chatterElisa.oscReceiver.serve_forever( )  # nothing after that works
