"""
Configuration for the generate module
"""

#-----------------------------------------------------------------------------#
# Flags for running on CPU
#-----------------------------------------------------------------------------#
FLAG_CPU_MODE = False

#-----------------------------------------------------------------------------#
# Paths to models and biases
#-----------------------------------------------------------------------------#
paths = dict()

# Skip-thoughts
paths['skmodels'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/skip-thoughts'
paths['sktables'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/skip-thoughts'

# Decoder
paths['decmodel'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/romance.npz'
paths['dictionary'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/romance_dictionary.pkl'

# Image-sentence embedding
paths['vsemodel'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/coco_embedding.npz'

# VGG-19 convnet
paths['vgg'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/vgg/vgg19.pkl'
# paths['pycaffe'] = '/u/yukun/Projects/caffe-run/python'
# paths['vgg_proto_caffe'] = '/ais/guppy9/movie2text/neural-storyteller/models/VGG_ILSVRC_19_layers_deploy.prototxt'
# paths['vgg_model_caffe'] = '/ais/guppy9/movie2text/neural-storyteller/models/VGG_ILSVRC_19_layers.caffemodel'


# COCO training captions
paths['captions'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/coco_train_caps.txt'

# Biases
paths['negbias'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/caption_style.npy'
paths['posbias'] = '/Users/sonneundasche/programming/of/apps/ElisaKora/research/peter/StoryTeller/data/neural_storyteller/romance_style.npy'
