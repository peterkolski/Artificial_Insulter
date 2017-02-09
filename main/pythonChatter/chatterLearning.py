# -*- coding: utf-8 -*-
from chatterbot import ChatBot
import logging

# Uncomment the following line to enable verbose logging
# logging.basicConfig(level=logging.INFO)

databaseName = "./databaseTest.json"

bot = ChatBot(
    'Feedback Learning Bot',
    storage_adapter='chatterbot.storage.JsonFileStorageAdapter',
    logic_adapters=[ 'chatterbot.logic.BestMatch'],
    database = databaseName,
    input_adapter='chatterbot.input.TerminalAdapter',
    output_adapter='chatterbot.output.TerminalAdapter'
)

print("====================================================")
print("LEARNING for database " + databaseName )
print("====================================================")

# The following loop will execute each time the user enters input
while True:
    try:
        print "Type a statement (KEYWORD): "
        input_statement = bot.input.process_input_statement()
        print "Type a response (sentence): "
        response        = bot.input.process_input_statement()
        bot.learn_response(response,input_statement)

        print "Learned!\n"
        # It is important that this happens last, after the learning step
        bot.conversation_sessions.update(
            bot.default_session.id_string,
            (input_statement, response, )
        )

    # Press ctrl-c or ctrl-d on the keyboard to exit
    except (KeyboardInterrupt, EOFError, SystemExit):
        break