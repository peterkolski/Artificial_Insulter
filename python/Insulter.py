
#known issues: words like 'remote control' are detected separately
#control gets detected as verb?
#animals should be detected as persons?
# I, YOU also not detected

print "initializing..."

import nltk
import random
from nltk.corpus import stopwords as stopw
from nltk.corpus import wordnet as wn

#pipe stuff
import os, time,sys

#osc stuff
import OSC

osc_to_of_address= ('127.0.0.1' , 22222) #OpenFrameworks
osc_send_address = "/python_here"       #Sending   - python to OF
osc_transform_address = "/transform"    #Recieving - OF to python
osc_from_of_address = ('127.0.0.1' , 33333) #python

# Python to openframeworks:
oscSender = OSC.OSCClient()
oscSender.connect(osc_to_of_address)

# OpenFrameworks to python:
oscReceiver = OSC.ThreadingOSCServer(osc_from_of_address)

#globals

input_pipe_name = os.path.expanduser("~/transformer_in")
output_pipe_name = os.path.expanduser("~/transformer_out")

lemmatizer = nltk.WordNetLemmatizer()
stemmer = nltk.stem.SnowballStemmer("english")
stopwords = stopw.words('english')

################################################
#
# gist code to extract the term-words only
# source: https://gist.github.com/alexbowe/879414
#


# Used when tokenizing words

sentence_re = r'(?:(?:[A-Z])(?:\.[A-Z])+\.?)|(?:\w+(?:-\w+)*)|(?:\$?\d+(?:\.\d+)?%?)|(?:\.\.\.|)(?:[][\.,;"\'?():-_`])'
    
#Taken from Su Nam Kim Paper...
grammar = r"""
    NBAR:
        {<NN.*|JJ>*<NN.*>}  # Nouns and Adjectives, terminated with Nouns
        
    NP:
        {<NBAR>}
        {<NBAR><IN><NBAR>}  # Above, connected with in/of/etc...
"""
chunker = nltk.RegexpParser(grammar)

def leaves(tree):
    #"""Finds NP (nounphrase) leaf nodes of a chunk tree."""
    for subtree in tree.subtrees(filter = lambda t: t.label()=='NP'):
        yield subtree.leaves()

def normalise(word):
    #"""Normalises words to lowercase and stems and lemmatizes it."""
    word = word.lower()
    #print "lower:",word
    #word = stemmer.stem(word) #we don't need stemming for now
    #print "stemmed:",word
    word = lemmatizer.lemmatize(word)
    #print "lematized:",word
    return word

def acceptable_word(word):
    #"""Checks conditions for acceptable word: length, stopword."""
    #print "acceptable:", word
    accepted = bool(2 <= len(word) <= 40
        and word.lower() not in stopwords)
    return accepted

def get_terms(tree):
    for leaf in leaves(tree):
        term = [ normalise(w) for w,t in leaf if acceptable_word(w) ]
        yield term

def get_tree_and_postoks(str_in):
    tokens = nltk.regexp_tokenize(str_in.lower(), sentence_re) # problem with latest nltk
    #tokens = nltk.word_tokenize(sentence)
    #tokens = nltk.wordpunct_tokenize(sentence)
    postoks = nltk.tag.pos_tag(tokens)
    tree = chunker.parse(postoks)
    return tree,postoks

#for term in get_terms(tree):
#    for word in term:
#        print "result:",word
#    print


################################################
#
# analyse every term in a sentence and extract persons and objects:
#


wn_entity = wn.synset('entity.n.01')
wn_physical_entity = wn.synset('physical_entity.n.01')
wn_causal_agent = wn.synset('causal_agent.n.01')
wn_person = wn.synset('person.n.01')
wn_object = wn.synset('object.n.01')

# person hierarchy: entity->ph_entity->cas_agent->person
# object hierarchy: entity->ph_entity->object
maxdepth = 4 #don't search thourgh the tree deeper then maxdepth nodes

def make_object_person_list_using_terms(terms):
    persons = []
    objects = []
    for term in terms:
        for word in term:
            l=wn.synsets(word)
            #print word,":"
            if (l):
                #print word,
                paths = l[0].hypernym_paths()
                if (paths):
                    synset = paths[0]
                    synset = wn.synsets(word)[0].hypernym_paths()[0]
                    #print word, ":"
                    #print synset,
                    if (wn_object in synset[:maxdepth]): objects.append(word)
                    if (wn_person in synset[:maxdepth]): persons.append(word)
    return objects,persons

def make_object_person_list_using_tokens(tokens_in):
    persons = []
    objects = []
    for word in tokens_in:
        l=wn.synsets(word)
        #print word,":"
        if (l):
            paths = l[0].hypernym_paths()
            if (paths):
                synset = paths[0]
                #print synset,
                if (wn_object in synset[:maxdepth]): objects.append(word)
                if (wn_person in synset[:maxdepth]): persons.append(word)
    return objects,persons

# In[354]:

################################################
#
# insult generator: insert nasty words only before words that belong to persons:
#

def insert_words(toks_in, object_list_in,person_list_in):
    insults = ["ugly", "fat", "smelly","greasy","dirty","stupid as fuck","lame"]
    #enlargers = ["glorious", "great","supperior"]
    transformed = []
    for currentpair in toks_in:
        if ((currentpair[1]=='NN')&(currentpair[0] in person_list_in)): transformed.append(random.choice(insults))
        #if ((currentpair[1]=='NN')&(currentpair[0] in object_list_in)): transformed.append(random.choice(enlargers))
        transformed.append(currentpair[0])
    return transformed

def transform_sentence(str_in):
    outputstr=""
    tree, postoks = get_tree_and_postoks(str_in)
    objects,persons = make_object_person_list_using_terms(get_terms(tree))
    transformed = insert_words(postoks,objects,persons)
    for s in transformed: outputstr+=" "+s
    return outputstr

def pipe_in_loop(pname):
    pipein = open(pname, 'r')
    while True:
        line = pipein.readline()[:-1]
        if (line):
            print "got a line:",line
            insult=transform_sentence(line)
            print "transformed:",insult
            os.write(pipeout,insult+"\n")
        time.sleep(10./1000.); # sleep for 10 milisseconds, cheap way to relax cpu usage
    return

def transformMessageCallback(addr, tags, stuff, source):
    input_sentence=stuff[0]
    print "received text to transform:",input_sentence
    insult=transform_sentence(input_sentence)
    print "transformed:",insult
    newMessage = OSC.OSCMessage()
    newMessage.setAddress(osc_send_address)
    # newMessage.append("transformed")
    newMessage.append(insult);
    oscSender.send(newMessage)
    return


# send ready message to openframeworks
oscmsg = OSC.OSCMessage()
oscmsg.setAddress(osc_send_address)
oscmsg.append("READY");
oscSender.send(oscmsg)

print "listening to:",osc_transform_address
# start osc listener:
oscReceiver.addMsgHandler(osc_transform_address, transformMessageCallback)
oscReceiver.serve_forever()

#print "checking input pipe:", input_pipe_name
#if not os.path.exists(input_pipe_name):
#    print "creating input pipe..."
#    os.mkfifo(input_pipe_name)
#
#print "checking output pipe:", output_pipe_name
#if not os.path.exists(output_pipe_name):
#    print "creating output pipe..."
#    os.mkfifo(output_pipe_name)
#
#print "opening output pipe..."
#pipeout = os.open(output_pipe_name, os.O_RDWR,os.O_NONBLOCK)
#
#print "waiting for input on:",input_pipe_name
#pipe_in_loop(input_pipe_name)

###### say it:

#outputstr=transform_sentence(sentence)
#print "original:",sentence
#print "detected objects:", objects
#print "detected persons:", persons
#print "transformed:",outputstr
#print
#time.sleep(1)
#call(["say","--rate=150","--voice=Victoria",sentence])
#time.sleep(1)
#call(["say","--rate=80","--voice=Alex",outputstr])

