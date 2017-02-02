import nltk
from nltk.tokenize import RegexpTokenizer   #For getting rid of punctuation
tokenizer = RegexpTokenizer(r'\w+') #Special tokenizer



def getKeywords( textIn ):
    tokens_ = tokenizer.tokenize( textIn )
    tagged_ = nltk.pos_tag( tokens_ )
    result = [ word for word,pos in tagged_ if pos == 'NN']
    return result


def putRowKeywordsToDict( row_, dict_ ):
    rowNum_ = row_[ 0 ]
    text_ = row_[ 1 ]
    keywords_ = getKeywords( text_ )
    for key in keywords_:
        dict_[ key ].append( rowNum_ )

