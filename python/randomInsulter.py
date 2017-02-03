
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
"""Get Pandas row, extract keywords and put it into a dictionary [Key->List]"""

def putRowKeywordsToDict( row_ ):
    dict_ = defaultdict(list)
    rowNum_ = row_[ 0 ]
    text_ = row_[ 1 ]
    keywords_ = getKeywords( text_ )
    for _key in keywords_:
        dict_[ _key ].append( rowNum_ )
    return dict_

