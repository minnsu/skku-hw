import numpy as np
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.feature_extraction.text import TfidfTransformer

from utils import load_features, save_descriptors, load_object, save_object

np.random.seed(0)

# Common
def kmeans_clustering(features, n_clusters):
    """
    features.shape = list(2000) of (n, feature dim), can be is different for each image
    """
    features = np.concatenate(features, axis=0)
    kmeans = KMeans(n_clusters=n_clusters, random_state=0).fit(features)
    return kmeans

def BagOfVisualWords(features, kmeans):
    """
    features = list(2000) of (n, feature dim), n can be different for each image
    return shape: (2000, # of clusters)
    """
    histogram = np.zeros((len(features), kmeans.n_clusters))
    for i, feat in enumerate(features):
        labels = kmeans.predict(feat)
        for label in labels:
            histogram[i, label] += 1
    return histogram

def VLAD(features, kmeans):
    """
    features = list(2000) of (n, feature dim), n can be different for each image
    return shape: (2000, # of clusters * feature dim)
    """
    vlad = np.zeros((len(features), kmeans.n_clusters * features[0].shape[1]))
    for i, feat in enumerate(features):
        labels = kmeans.predict(feat)
        for label in np.unique(labels):
            idx = np.where(labels == label)[0]
            cluster_center = kmeans.cluster_centers_[label]
            diff = feat[idx] - cluster_center
            vlad[i, label*features[0].shape[1]:(label+1)*features[0].shape[1]] = np.sum(diff, axis=0)
    return vlad

# CNN Features
def CNN_SumPooling(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, 512)
    """
    descriptor = np.sum(cnn_features, axis=(1, 2))
    descriptor = descriptor / np.linalg.norm(descriptor, axis=1, keepdims=True, ord=1)
    return descriptor

def CNN_SumPooling_centering_prior(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, 512)
    """
    gaussian = np.zeros((14, 14))
    sigma = 4.1225
    for i in range(14):
        for j in range(14):
            gaussian[i, j] = np.exp(-((i-7)**2 + (j-7)**2) / (2*sigma**2))
    gaussian = gaussian / np.sum(gaussian)
    gaussian = np.expand_dims(gaussian, axis=2)

    descriptor = np.sum(cnn_features * gaussian, axis=(1, 2))
    descriptor = descriptor / np.linalg.norm(descriptor, axis=1, keepdims=True, ord=1)

    return descriptor

def CNN_MaxPooling(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, 512)
    """
    descriptor = np.max(cnn_features, axis=(1, 2))
    descriptor = descriptor / np.linalg.norm(descriptor, axis=1, keepdims=True, ord=1)

    pca = PCA(n_components=512)
    descriptor = pca.fit_transform(descriptor)
    descriptor = descriptor / np.linalg.norm(descriptor, axis=1, keepdims=True, ord=1)

    return descriptor

def CNN_MaxPosition(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, 1024)
    """
    descriptor = np.zeros((len(cnn_features), 1024))
    for i in range(len(cnn_features)):
        for j in range(512):
            descriptor[i, 2*j:2*j+2] = np.unravel_index(np.argmax(cnn_features[i, :, :, j]), (14, 14))
    descriptor = descriptor / np.linalg.norm(descriptor, axis=1, keepdims=True, ord=1)
    return descriptor

def CNN_SumAndMax_concat(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, 1024)
    """
    sum_descriptor = CNN_SumPooling_centering_prior(sift_features, cnn_features)
    max_descriptor = CNN_MaxPooling(sift_features, cnn_features)

    w_sum, w_max = 1, 0.9
    descriptor = np.concatenate((w_sum * sum_descriptor, w_max * max_descriptor), axis=1)

    return descriptor

def CNN_BoVW(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, # of clusters)
    """
    n_clusters = 512

    bovw_path = f'./A4_<student_id>_cnn_bovw_{n_clusters}.pkl'
    bovw = load_object(bovw_path)
    if bovw is None:
        kmeans_path = f'./A4_<student_id>_cnn_kmeans_{n_clusters}.pkl'
        kmeans = load_object(kmeans_path)
        if kmeans is None:
            kmeans = kmeans_clustering(cnn_features.reshape(-1, 14*14, 512), n_clusters)
            save_object(kmeans_path, kmeans)

        histogram = BagOfVisualWords(cnn_features.reshape(-1, 14*14, 512), kmeans)

        tfidf_transformer = TfidfTransformer(norm='l1')
        bovw = tfidf_transformer.fit_transform(histogram).astype(np.float32).toarray()
        save_object(bovw_path, bovw)

    return bovw

def CNN_VLAD(sift_features, cnn_features):
    """
    features.shape = (2000, 14, 14, 512)
    return shape: (2000, # of clusters * 512)
    """
    n_clusters = 2
    kmeans_path = f'./A4_<student_id>_cnn_kmeans_{n_clusters}_for_vlad.pkl'
    kmeans = load_object(kmeans_path)
    if kmeans is None:
        kmeans = kmeans_clustering(cnn_features.reshape(-1, 14*14, 512), n_clusters)
        save_object(kmeans_path, kmeans)

    vlad = VLAD(cnn_features.reshape(-1, 14*14, 512), kmeans)
    vlad = vlad / np.linalg.norm(vlad, axis=1, keepdims=True, ord=1)

    pca = PCA(n_components=512)
    vlad = pca.fit_transform(vlad)
    vlad = vlad / np.linalg.norm(vlad, axis=1, keepdims=True, ord=1)

    return vlad.astype(np.float32)

# SIFT Features
def SIFT_BoVW(sift_features, cnn_features):
    """
    sift_features.shape = list(2000) of (n, 128), n is different for each image
    cnn_features.shape = (2000, 14, 14, 512)
    return shape: (2000, # of clusters)
    """
    n_clusters = 2048

    bovw_path = f'./A4_<student_id>_sift_bovw_{n_clusters}.pkl'
    bovw = load_object(bovw_path)
    if bovw is None:
        kmeans_path = f'./A4_<student_id>_sift_kmeans_{n_clusters}.pkl'
        kmeans = load_object(kmeans_path)
        if kmeans is None:
            kmeans = kmeans_clustering(sift_features, n_clusters)
            save_object(kmeans_path, kmeans)

        histogram = BagOfVisualWords(sift_features, kmeans)

        tfidf_transformer = TfidfTransformer(norm='l1')
        bovw = tfidf_transformer.fit_transform(histogram).astype(np.float32).toarray()
        save_object(bovw_path, bovw)

    use_pca = True
    if use_pca:
        target_components = 512
        pca_path = f'./A4_<student_id>_sift_pca_{n_clusters}_to_{target_components}.pkl'
        pca_bovw = load_object(pca_path)
        if pca_bovw is None:
            pca = PCA(n_components=target_components)
            pca_bovw = pca.fit_transform(bovw)
            pca_bovw = pca_bovw / np.linalg.norm(pca_bovw, axis=1, keepdims=True, ord=1)
            save_object(pca_path, pca_bovw)
        return pca_bovw

    return bovw

def SIFT_VLAD(sift_features, cnn_features):
    """
    sift_features.shape = list(2000) of (n, 128), n is different for each image
    cnn_features.shape = (2000, 14, 14, 512)
    return shape: (2000, # of clusters * 128)
    """
    n_clusters = 32
    kmeans_path = f'./A4_<student_id>_sift_kmeans_{n_clusters}_for_vlad.pkl'
    kmeans = load_object(kmeans_path)
    if kmeans is None:
        kmeans = kmeans_clustering(sift_features, n_clusters)
        save_object(kmeans_path, kmeans)

    vlad = VLAD(sift_features, kmeans)
    vlad = vlad / np.linalg.norm(vlad, axis=1, keepdims=True, ord=1)

    pca = PCA(n_components=512)
    vlad = pca.fit_transform(vlad)
    vlad = vlad / np.linalg.norm(vlad, axis=1, keepdims=True, ord=1)

    return vlad.astype(np.float32)

# Use both SIFT and CNN features

def SC_all(sift_features, cnn_features):
    """
    sift_features.shape = list(2000) of (n, 128), n is different for each image
    cnn_features.shape = (2000, 14, 14, 512)
    """
    desc_path = f'./A4_<student_id>_SC_all.pkl'
    descriptor = load_object(desc_path)
    if descriptor is None:
        sift_vlad = SIFT_VLAD(sift_features, cnn_features)
        cnn_vlad = CNN_VLAD(sift_features, cnn_features)
        sift_bovw = SIFT_BoVW(sift_features, cnn_features)
        cnn_bovw = CNN_BoVW(sift_features, cnn_features)
        cnn_maxpool = CNN_MaxPooling(sift_features, cnn_features)
        cnn_sumpool = CNN_SumPooling_centering_prior(sift_features, cnn_features)

        weights = [1.60852, -0.07743, 0.94614, -0.00585, 1.79413, 1.15811]
        descriptor = np.concatenate((weights[0] * sift_vlad, weights[1] * cnn_vlad, weights[2] * sift_bovw, weights[3] * cnn_bovw, weights[4] * cnn_maxpool, weights[5] * cnn_sumpool), axis=1)
        save_object(desc_path, descriptor)

    return descriptor


if __name__ == '__main__':
    # 이미지 feature 로드하기
    sift_features = load_features('./features/', mode='sift')
    cnn_features = load_features('./features/', mode='cnn')
    cnn_features = np.array(cnn_features)

    # descriptor 생성 함수 선택하기
    make_descriptor = SC_all

    # descriptor 계산하기
    descriptor = make_descriptor(sift_features, cnn_features)
    print(descriptor.shape)

    # descriptor 저장하기
    save_descriptors('./A4_<student_id>.des', descriptor)