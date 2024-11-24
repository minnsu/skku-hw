import cv2
import numpy as np
import time

from utils import padding

def cross_correlation_1d(img, kernel):
    new_img = np.zeros_like(img, dtype=np.float64)

    if kernel.shape[0] == 1:
        # Horizontal kernel
        offset = kernel.shape[1] // 2
        padded_img = padding(img, offset, 0)

        for j in range(offset, img.shape[1] + offset):
            new_img[:, j-offset] = np.sum(padded_img[:, j-offset:j+offset+1] * kernel, axis=1)
    else:
        # Vertical kernel
        offset = kernel.shape[0] // 2
        padded_img = padding(img, offset, 1)

        for i in range(offset, img.shape[0] + offset):
            new_img[i-offset, :] = np.sum(padded_img[i-offset:i+offset+1, :] * kernel, axis=0)
    
    return new_img.astype(img.dtype)

def cross_correlation_2d(img, kernel):
    offset = kernel.shape[0] // 2
    padded_img = padding(img, offset, 2)

    new_img = np.zeros_like(img, dtype=np.float64)
    for i in range(offset, img.shape[0] + offset):
        for j in range(offset, img.shape[1] + offset):
            new_img[i-offset, j-offset] = np.sum(padded_img[i-offset:i+offset+1, j-offset:j+offset+1] * kernel)
    
    return new_img.astype(img.dtype)


def get_gaussian_filter_1d(size, sigma):
    kernel = np.zeros((1, size), dtype=np.float64)

    mid = size // 2
    for i in range(size):
        kernel[0, i] = np.exp(-(((mid-i)**2) / (2 * sigma**2)))
    kernel /= np.sum(kernel)

    return kernel

def get_gaussian_filter_2d(size, sigma):
    kernel = np.zeros((size, size), dtype=np.float64)

    mid = size // 2
    for i in range(size):
        for j in range(size):
            kernel[i, j] = np.exp(-(((mid-i)**2 + (mid-j)**2) / (2 * sigma**2)))
    kernel /= np.sum(kernel)

    return kernel


if __name__ == '__main__':
    lenna = cv2.imread('./A1_Images/lenna.png', cv2.IMREAD_GRAYSCALE)
    shapes = cv2.imread('./A1_Images/shapes.png', cv2.IMREAD_GRAYSCALE)

    # 1-2. c)
    print('get_gaussian_filter_1d(5,1)')
    print(get_gaussian_filter_1d(5,1), '\n')
    print('get_gaussian_filter_2d(5,1)')
    print(get_gaussian_filter_2d(5,1), '\n')

    # 1-2. d)
    def part1_2_D(img, gaussian_parameters, img_name):
        filtered_images = []
        for size, sigma in gaussian_parameters:
            kernel = get_gaussian_filter_2d(size, sigma)
            
            filtered_image = cross_correlation_2d(img, kernel)
            filtered_image = cv2.putText(filtered_image, f'{size}x{size} s={sigma}', (15, 40), cv2.FONT_HERSHEY_DUPLEX, 1, 0, 2, bottomLeftOrigin=False)

            filtered_images.append(filtered_image)

        rows = []
        for idx, img in enumerate(filtered_images):
            if idx % 3 == 0:
                rows.append(np.hstack(filtered_images[idx:idx+3]))
        compounded_img = np.vstack(rows)

        cv2.imshow(f'part_1_gaussian_filtered_{img_name}.png', compounded_img)
        cv2.imwrite(f'./result/part_1_gaussian_filtered_{img_name}.png', compounded_img)

    gaussian_parameters = [
        (5, 1), (5, 6), (5, 11),
        (11, 1), (11, 6), (11, 11),
        (17, 1), (17, 6), (17, 11)
    ]

    part1_2_D(lenna, gaussian_parameters, 'lenna')
    part1_2_D(shapes, gaussian_parameters, 'shapes')

    # 1-2. e)
    def part1_2_E(img, gaussian_parameter, img_name):
        # 1D Gaussian Filter
        kernel_1d = get_gaussian_filter_1d(*gaussian_parameter)
        start_1d = time.time()
        filtered_image_vertical = cross_correlation_1d(img, kernel_1d.T)
        filtered_image_1d = cross_correlation_1d(filtered_image_vertical, kernel_1d)
        end_1d = time.time()

        # 2D Gaussian Filter
        kernel_2d = get_gaussian_filter_2d(*gaussian_parameter)
        start_2d = time.time()
        filtered_image_2d = cross_correlation_2d(img, kernel_2d)
        end_2d = time.time()

        difference_map = np.maximum(filtered_image_1d, filtered_image_2d) - np.minimum(filtered_image_1d, filtered_image_2d)

        cv2.imshow(f'Difference Map {img_name}', difference_map)
        print(f'Total Difference [{img_name}]:', np.sum(np.abs(difference_map)))
        print(f'cross_correlation_1d [{img_name}] time: {end_1d - start_1d}')
        print(f'cross_correlation_2d [{img_name}] time: {end_2d - start_2d}')
        print()

    part1_2_E(lenna, (17, 6), 'lenna')
    part1_2_E(shapes, (17, 6), 'shapes')

    cv2.waitKey(20000)
    cv2.destroyAllWindows()