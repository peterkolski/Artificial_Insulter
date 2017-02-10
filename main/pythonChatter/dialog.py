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
import threading

osc_to_of_addressLeft= ('127.0.0.1' , 20001) #OpenFrameworks
osc_to_of_addressRight= ('127.0.0.1' , 20003) #OpenFrameworks

osc_generate_address = "/generate"    #Recieving - OF to python
osc_original_address = "/original_text"    #Recieving - OF to python

osc_send_address = "/answer_text"

osc_from_of_addressLeft = ('127.0.0.1' , 20002) #python
osc_from_of_addressRight = ('127.0.0.1' , 20004) #python

# Python to openframeworks:
oscSenderLeft = OSC.OSCClient()
oscSenderLeft.connect(osc_to_of_addressLeft)
oscSenderRight = OSC.OSCClient()
oscSenderRight.connect(osc_to_of_addressRight)

# OpenFrameworks to python:
oscReceiver = OSC.ThreadingOSCServer(osc_from_of_addressLeft)
oscReceiverRight = OSC.ThreadingOSCServer(osc_from_of_addressRight)

#globals

input_pipe_name = os.path.expanduser("~/transformer_in")
output_pipe_name = os.path.expanduser("~/transformer_out")

score=0.
oscData=[]
current_oscData_id=0

question_type_isthere=0

qtype=0
qword=1
qquestion=2
qtemplate_index=3

templatesQ=['Do you see a {}?','I see a {}. Can you see it as well?','Is there a {}?','Looks like a {}?']
templatesAp=['Yes, I see a {}.','Yes, Looks like there is a {}.',"There is a {}.",'Yes, looks like a {}!']
templatesAn=["No, I see no {}.","Nope, I can't see it",'No, there is no {}.',"Not sure, it doesnt look like a {}..."]
templatesRant=["Hmm, this one might be a bit difficult.","I'm afraid of abstractions. This might be one. I'll try anyway.","I always get confused by abstraction."]

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


def q_is_there_an(tkin,t_index):
    aword=tkin[0]
    aword=wn.morphy(aword).encode('latin1')
    #draw_hypernyms(wn.synset(aword+'.n.01'))
    return [question_type_isthere,aword, templatesQ[t_index].format(aword),t_index]

def make_questions(postoksin):
    questions=[]
    for tok in postoksin:
        if tok[1].startswith('NN'):
            template_index=random.randint(0,len(templatesQ)-1)
            if not wn.synset('abstraction.n.06') in wn.synsets(tok[0])[0].lowest_common_hypernyms(wn.synset('abstraction.n.01')):
                questions.append(q_is_there_an(tok,template_index))
            #print "hypos:",wn.synsets(tok[0])[0].hypernyms()
            #if wn.synset('abstraction.n.06') in wn.synsets(tok[0])[0].hypernyms():
            else:
                #print "abstraction6",tok,"but asking anyway"
                abstract_q = q_is_there_an(tok,template_index)
                rant_template_index=random.randint(0,len(templatesRant)-1)
                abstract_q[qquestion]=templatesRant[rant_template_index]+abstract_q[qquestion]
                questions.append(abstract_q)
    return questions

def a_is_there_an(q,postoksin):
    for tok in postoksin:
        if tok[1].startswith('NN'):
            aword=tok[0]
            aword=wn.morphy(aword).encode('latin1')
            if (q[qword]==aword):
                return [templatesAp[q[qtemplate_index]].format(q[qword]),1]
    return [templatesAn[q[qtemplate_index]].format(q[qword]),0]

def get_answers(qs,postoksin):
    answers=[]
    for q in qs:
        if (q[qtype]==0):
            a = a_is_there_an(q,postoksin)
            answers.append(a)
    #print "question:",q[qquestion],"\nanswer:",a
    return answers

# tuple question:
# (type,tok)
#idx=random.randint(0,len(allcaptions)-1)
#sentence_str =' '.join(allcaptions[idx])
#print "sentence[",idx,"]=",sentence_str
#tree,postoks=get_tree_and_postoks(sentence_str)

#sentence_strA = "a flock of birds sitting on top of a power line"
#sentence_strB = "a group of birds sitting on top of a sign"
#print "a:",sentence_strA
#print "b:",sentence_strB
#treeA,postoksA=get_tree_and_postoks(sentence_strA)
#treeB,postoksB=get_tree_and_postoks(sentence_strB)

#print "we share our eyes but have different minds"
#print "we live in multiple bodies"
#print postoks

#for n in xrange(0,5):
#    print "cycle:",n
#    q=make_questions(postoksA)
#    a=get_answers(q,postoksB)
#    positive_a_sum=0.
#    for i in xrange(0,len(q)):
#        print "Q:",q[i][qquestion]
#        print "A:",a[i][0]
#        positive_a_sum=positive_a_sum+a[i][1]
#    print "Agrement score:",positive_a_sum/len(q)," or ",positive_a_sum,"/",len(q)

def generateQA(sA,sB):
    treeA,postoksA=get_tree_and_postoks(sA)
    treeB,postoksB=get_tree_and_postoks(sB)
    q=make_questions(postoksA)
    a=get_answers(q,postoksB)
    return q,a

def formatQAtoOSC(q,a):
    positive_a_sum=0.
    qa = []
    total=len(q)
    positive_a_sum=0.
    for i in xrange(0,total):
        positive_a_sum=positive_a_sum+a[i][1]
        qstr = q[i][qquestion]
        qa.append(q[i][qquestion])
        qa.append(a[i][0])
    score=positive_a_sum/len(q)
    print "Agrement score:",score," or ",positive_a_sum,"/",len(q)
    return score,qa

def generateMessageCallback(addr, tags, stuff, source):
    input_sentenceA=stuff[0]
    input_sentenceB=stuff[1]
    global score,oscData,current_oscData_id
    print "received text to transform:",input_sentenceA,input_sentenceB
    q,a=generateQA(input_sentenceA,input_sentenceB)
    score,oscData=formatQAtoOSC(q,a)
    current_oscData_id=0
        #for i in xrange(0,len(oscData)):
        #newMessage = OSC.OSCMessage()
        #newMessage.setAddress(osc_send_address)
        #newMessage.append(oscData[i]);
        #oscSender.send(newMessage)
    return

def getNextMessage():
    global current_oscData_id
    global oscData
    current_oscData_id += 1
    last_flag=0
    newMessage = OSC.OSCMessage()
    newMessage.setAddress(osc_send_address)
    if current_oscData_id>=len(oscData):
        data="DATA UNDERFLOW, FELLOW HUMAN"
        last_flag=1
    else:
        data=oscData[current_oscData_id]

    if current_oscData_id==(len(oscData)-1):
        last_flag=1
    newMessage.append([data,last_flag]);
    return newMessage

def getLeftMessageCallback(addr, tags, stuff, source):
    oscSenderLeft.send(getNextMessage())
    return

def getRightMessageCallback(addr, tags, stuff, source):
    oscSenderRight.send(getNextMessage())
    return

def startServer2():
    print "2 listening to:",osc_from_of_addressRight
    # start osc listener:
    oscReceiverRight.addMsgHandler( osc_original_address, getLeftMessageCallback)
    oscReceiverRight.addMsgHandler( osc_generate_address, generateMessageCallback )
    oscReceiverRight.serve_forever()

generateMessageCallback(0, 0, ["a flock of birds sitting on top of a power line" ,"a group of birds sitting on top of a sign"], 0)

t = threading.Thread(target=startServer2)#, args = (q,u))
t.daemon = True
t.start()


# send ready message to openframeworks
#oscmsg = OSC.OSCMessage()
#oscmsg.setAddress(osc_send_address)
#oscmsg.append("READY");
#oscSender.send(oscmsg)


print "listening to:",osc_generate_address
# start osc listener:
oscReceiver.addMsgHandler(osc_generate_address, generateMessageCallback)
oscReceiver.addMsgHandler(osc_original_address, getRightMessageCallback)
oscReceiver.serve_forever()


