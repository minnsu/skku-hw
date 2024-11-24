import cv2
import numpy as np
import time

from A1_image_filtering import *
from utils import quantize_degree
from utils import sobel_x, sobel_y, blur_filter, derivative_filter

gaussian_filter = get_gaussian_filter_2d(7, 1.5)
gaussian_filter_1d = get_gaussian_filter_1d(7, 1.5)

def compute_image_gradient(img):
    # a) Apply sobel filter

    # 1d version (faster)
    I_x = cross_correlation_1d(img.astype(np.float64), blur_filter.T)
    I_x = cross_correlation_1d(I_x, derivative_filter)
    I_y = cross_correlation_1d(img.astype(np.float64), np.flip(derivative_filter).T)
    I_y = cross_correlation_1d(I_y, blur_filter)

    # 2d version
    # I_x = cross_correlation_2d(img.astype(np.float64), sobel_x)
    # I_y = cross_correlation_2d(img.astype(np.float64), sobel_y)

    # b) Compute magnitude and direction
    mag = np.sqrt(I_x**2 + I_y**2)
    
    # 원래 magintude의 차이를 유지하기 위해 255를 곱하고 max로 나누는 방법?
    # mag = np.clip(255 * mag / np.max(mag), 0, 255).astype(np.uint8)
    # mag = np.clip(mag, 0, 255).astype(np.uint8)

    dir = np.arctan2(I_y, I_x)

    # degree 단위로 반환
    dir = np.rad2deg(dir).astype(np.int32)
    dir = np.where(dir < 0, dir + 360, dir) # - degree to + degree

    return mag, dir


def non_maximum_suppression_dir(mag, dir):
    # a) Quantize the direction
    dir = quantize_degree(dir)

    # b) Non-maximum suppression
    sup_mag = np.zeros_like(mag)
    for i in range(1, mag.shape[0]-1):
        for j in range(1, mag.shape[1]-1):
            neighbor = mag[i-1:i+2, j-1:j+2].flatten()
                       
            dir_encode = (dir[i, j] // 45) % 4
            target = neighbor[[3 - dir_encode, 5 + dir_encode]]

            if target[0] <= mag[i, j] >= target[1]:
                # example이랑 최대한 비슷하려면...
                if dir[i, j] in [0, 135, 180, 315]:
                    sup_mag[i, j] = mag[i, j] if mag[i, j] > target[0] else 0
                elif dir[i, j] in [90, 270]:
                    sup_mag[i, j] = mag[i, j] if mag[i, j] > target[1] else 0
                elif dir[i, j] in [45, 225]:
                    sup_mag[i, j] = mag[i, j]

    return sup_mag


if __name__ == '__main__':
    lenna = cv2.imread('./A1_Images/lenna.png', cv2.IMREAD_GRAYSCALE)
    shapes = cv2.imread('./A1_Images/shapes.png', cv2.IMREAD_GRAYSCALE)

    # 2-1.
    filtered_lenna = cross_correlation_1d(lenna, gaussian_filter_1d.T)
    filtered_lenna = cross_correlation_1d(filtered_lenna, gaussian_filter_1d)
    filtered_shapes = cross_correlation_1d(shapes, gaussian_filter_1d.T)
    filtered_shapes = cross_correlation_1d(filtered_shapes, gaussian_filter_1d)

    # filtered_lenna = cross_correlation_2d(lenna, gaussian_filter)
    # filtered_shapes = cross_correlation_2d(shapes, gaussian_filter)

    # 2-2.
    def part2_2(img, img_name):
        # d) Compute image gradient with time check
        start = time.time()
        mag, dir = compute_image_gradient(img)
        end = time.time()

        clipped_mag = np.clip(mag, 0, 255).astype(np.uint8)
        # Display and store
        print(f'compute_image_gradient [{img_name}] time: {end - start}')
        cv2.imshow(f'part_2_edge_raw_{img_name}.png', clipped_mag)
        cv2.imwrite(f'./result/part_2_edge_raw_{img_name}.png', clipped_mag)
        
        return mag, dir

    lenna_mag, lenna_dir = part2_2(filtered_lenna, 'lenna')
    shapes_mag, shapes_dir = part2_2(filtered_shapes, 'shapes')

    # 2-3.
    def part2_3(mag, dir, img_name):
        # d) Non-maximum suppression with time check
        start = time.time()
        suppressed_mag = non_maximum_suppression_dir(mag, dir)
        end = time.time()

        # Display and store
        clipped_suppressed_mag = np.clip(suppressed_mag, 0, 255).astype(np.uint8)
        print(f'non_maximum_suppression_dir [{img_name}] time: {end - start}')
        cv2.imshow(f'part_2_edge_sup_{img_name}.png', clipped_suppressed_mag)
        cv2.imwrite(f'./result/part_2_edge_sup_{img_name}.png', clipped_suppressed_mag)

        return suppressed_mag

    lenna_suppressed_mag = part2_3(lenna_mag, lenna_dir, 'lenna')
    shapes_suppressed_mag = part2_3(shapes_mag, shapes_dir, 'shapes')

    cv2.waitKey(20000)
    cv2.destroyAllWindows()