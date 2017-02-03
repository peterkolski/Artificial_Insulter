
# ======== Dependencies ===============
import pandas as pd
import nltk
from nltk.tokenize import RegexpTokenizer   #For getting rid of punctuation
from collections import defaultdict         # to get a dictionary of lists

# ======== Special tokenizer ==========
tokenizer = RegexpTokenizer(r'\w+')


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
