
# ======== Dependencies ===============
import pandas as pd
import nltk
from nltk.tokenize import RegexpTokenizer   #For getting rid of punctuation
from collections import defaultdict         # to get a dictionary of lists
from random import randint

# ======== Special tokenizer ==========
tokenizer = RegexpTokenizer(r'\w+')


_dictChangeUni  ={  "'re"     : "'s",
                    "were": "was",
                    "Were": "Was",
                    "are": "is",
                    "Are": "Is",
                    }

_changerMale ={"yours"   : "his",
                "Yours"   : "His",
                "your "    : "his ",
                "Your "    : "His ",
                "you "     : "he ",
                "You "     : "He ",
                "You' "     : "He' ",
                "you' "     : "he' ",
               }
_changerFemale ={"yours"   : "hers",
                "Yours"   : "Hers",
                "your "    : "her ",
                "Your "    : "Her ",
                "you "     : "she ",
                "you've"     : "she's",
                "You "     : "she ",
                "You've"     : "she's",
                 "You' ": "She' ",
                 "you' ": "she' ",
                 }


def changeToMale( text_ ):
    tmpText = reduce(lambda x, y: x.replace(y, _dictChangeUni[y]), _dictChangeUni, text_ )
    return reduce(lambda x, y: x.replace(y, _changerMale[y]), _changerMale, tmpText)

def changeToFemale( text_ ):
    tmpText = reduce(lambda x, y: x.replace(y, _dictChangeUni[y]), _dictChangeUni, text_ )
    return reduce(lambda x, y: x.replace(y, _changerFemale[y]), _changerFemale, tmpText)


# =========== Functions ===============

# -----------------------------------
def getKeywords( textIn ):
    tokens_ = tokenizer.tokenize( textIn )
    tagged_ = nltk.pos_tag( tokens_ )
    result = [ word for word,pos in tagged_ if pos == 'NN']
    return result

# -----------------------------------
"""Get Pandas dataFrame, extract keywords and put it into a dictionary [Key->List]"""

def putKeywordsToDict( dataFrame ):
    dict_ = defaultdict( list )
    for index, row_ in dataFrame.iterrows():
        text_ = row_[ 1 ]
        keywords_ = getKeywords( text_ )
        for _key in keywords_:
            dict_[ _key ].append( index )
    return dict_

# -----------------------------------

def answerFromText( textIn_, dict_, dataFrame_ ):
    entriesNumDF = len( dataFrame_.index )
    keysIn_ = getKeywords(textIn_)
    idKey = 0   #
    textAnswer = "ERROR"

    if ((len(keysIn_) != 0) and (keysIn_[idKey] in dict_)):
        list = dict_[keysIn_[idKey]]
        idList = randint(0, len(list) - 1)  # Random list entry
        rowNum = list[idList]
        textAnswer = dataFrame_.iloc[rowNum ][ 'Text' ]
    else:
        textAnswer = dataFrame_.iloc[randint( 0, entriesNumDF ) ][ 'Text' ]
    textAnswer += " "
    return textAnswer

