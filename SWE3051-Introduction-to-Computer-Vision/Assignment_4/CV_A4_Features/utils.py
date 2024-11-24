import os
import glob
import pickle

import numpy as np

def load_features(path : str, mode : str='sift'):
    path += mode
    file_list = sorted(glob.glob(os.path.join(path, '*')))

    features = []
    if mode == 'sift':
        for file in file_list:
            with open(file, 'rb') as f:
                features.append(np.fromfile(f, dtype=np.uint8).reshape(-1, 128))
    elif mode == 'cnn':
        for file in file_list:
            with open(file, 'rb') as f:
                features.append(np.fromfile(f, dtype=np.float32).reshape(14, 14, 512))
    
    return features

def save_descriptors(path : str, descriptors : np.ndarray):
    with open(path, 'wb') as f:
        N, D = descriptors.shape
        f.write(np.array([N, D], dtype=np.int32).tobytes())
        f.write(descriptors.astype(np.float32).tobytes())

def load_object(path : str):
    # path 있는지 확인
    if not os.path.exists(path):
        return None
    
    with open(path, 'rb') as f:
        obj = pickle.load(f)
    return obj

def save_object(path : str, obj):
    with open(path, 'wb') as f:
        pickle.dump(obj, f)