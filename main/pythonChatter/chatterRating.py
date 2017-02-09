import pandas as pd

dataTable = pd.read_csv('../../data/ShitTalk_Filtered.csv')
inputValue = ''

if inputValue == 'N':
    dataTable.set_value( 0, 'Rating', 'shit')


# --- deleting parts completely
# dataTable = dataTable.drop( dataTable.index[ keyDict[ filterWord ] ] )
# dataTable[ dataTable.Rating != 'shit' ]