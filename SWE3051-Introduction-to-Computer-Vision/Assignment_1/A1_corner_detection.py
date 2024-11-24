import cv2
import numpy as np
import time

from A1_image_filtering import *
from utils import sobel_x, sobel_y, blur_filter, derivative_filter

gaussian_filter = get_gaussian_filter_2d(7, 1.5)
gaussian_filter_1d = get_gaussian_filter_1d(7, 1.5)

def response_function(l1, l2, kappa=0.04):
    return l1*l2 - kappa*((l1+l2)**2)

def compute_corner_response(img):
    img_shape = img.shape

    # 1d version
    I_x = cross_correlation_1d(img.astype(np.float64), blur_filter.T)
    I_x = cross_correlation_1d(I_x, derivative_filter)
    I_y = cross_correlation_1d(img.astype(np.float64), np.flip(derivative_filter.T))
    I_y = cross_correlation_1d(I_y, blur_filter)

    # 2d version
    # I_x = cross_correlation_2d(img.astype(np.float64), sobel_x)
    # I_y = cross_correlation_2d(img.astype(np.float64), sobel_y)

    I_xx = I_x**2
    I_xy = I_x*I_y
    I_yy = I_y**2

    window_size = 5
    offset = window_size // 2

    response_img = np.zeros_like(img, dtype=np.float64)

    for i in range(offset, img_shape[0]-offset):
        for j in range(offset, img_shape[1]-offset):
            Mxx = np.sum(I_xx[i-offset:i+offset+1, j-offset:j+offset+1])
            Mxy = np.sum(I_xy[i-offset:i+offset+1, j-offset:j+offset+1])
            Myy = np.sum(I_yy[i-offset:i+offset+1, j-offset:j+offset+1])

            M = np.array([[Mxx, Mxy],
                          [Mxy, Myy]])
            
            # eigenvalues = np.linalg.eigvals(M)
            # response_img[i, j] = response_function(eigenvalues[0], eigenvalues[1], kappa=0.04)
            response_img[i, j] = np.linalg.det(M) - 0.04 * (np.trace(M)**2)

    response_img = np.where(response_img < 0, 0, response_img)
    response_img = response_img / np.max(response_img)

    return response_img


def non_maximum_suppression_win(R, winSize):
    offset = winSize // 2
    R_nms = np.zeros_like(R, dtype=np.float64)

    threshold = 0.1
    for i in range(offset, R.shape[0]-offset):
        for j in range(offset, R.shape[1]-offset):
            window = R[i-offset:i+offset+1, j-offset:j+offset+1].flatten()
            
            prevs = window[:len(window)//2]
            nexts = window[len(window)//2+1:]
            if (R[i, j] > threshold) and all(R[i, j] >= prevs) and all(R[i, j] >= nexts):
                R_nms[i, j] = R[i, j]

    return R_nms


if __name__ == '__main__':
    lenna = cv2.imread('./A1_Images/lenna.png', cv2.IMREAD_GRAYSCALE)
    shapes = cv2.imread('./A1_Images/shapes.png', cv2.IMREAD_GRAYSCALE)

    # 3-1.
    # filtered_lenna = cross_correlation_1d(lenna, gaussian_filter_1d.T)
    # filtered_lenna = cross_correlation_1d(filtered_lenna, gaussian_filter_1d)
    # filtered_shapes = cross_correlation_1d(shapes, gaussian_filter_1d.T)
    # filtered_shapes = cross_correlation_1d(filtered_shapes, gaussian_filter_1d)

    filtered_lenna = cross_correlation_2d(lenna, gaussian_filter)
    filtered_shapes = cross_correlation_2d(shapes, gaussian_filter)

    # 3-2.
    def part3_2(img, img_name):
        start = time.time()
        response_img = compute_corner_response(img)
        end = time.time()

        print(f'compute_corner_response [{img_name}] time: {end - start}')

        scaled_img = np.clip(255 * response_img, 0, 255).astype(np.uint8)
        cv2.imshow(f'part_3_corner_raw_{img_name}.png', scaled_img)
        cv2.imwrite(f'./result/part_3_corner_raw_{img_name}.png', scaled_img)
        
        return response_img

    lenna_response = part3_2(filtered_lenna, 'lenna')
    shapes_response = part3_2(filtered_shapes, 'shapes')

    # 3-3.
    def part3_3(original_img, R, img_name):
        green_point_img = original_img.copy()

        # a)
        threshold = 0.1
        green_point_img[:][R > threshold] = np.array([0, 255, 0]) # set green channel to 255

        # b)
        cv2.imshow(f'part_3_corner_bin_{img_name}.png', green_point_img)
        cv2.imwrite(f'./result/part_3_corner_bin_{img_name}.png', green_point_img)

        # d)
        start = time.time()
        suppressed_R = non_maximum_suppression_win(R, winSize=11)
        end = time.time()

        print(f'non_maximum_suppression_win [{img_name}] time: {end - start}')
        green_circle_img = original_img.copy()

        threshold = 0.1
        i_s, j_s = np.where(suppressed_R > threshold)
        for i, j in zip(i_s, j_s):
            cv2.circle(green_circle_img, (j, i), 5, (0, 255, 0), 2)
        cv2.imshow(f'part_3_corner_sup_{img_name}.png', green_circle_img)
        cv2.imwrite(f'./result/part_3_corner_sup_{img_name}.png', green_circle_img)
        
    lenna_3ch = cv2.cvtColor(lenna, cv2.COLOR_GRAY2BGR)
    shapes_3ch = cv2.cvtColor(shapes, cv2.COLOR_GRAY2BGR)
    
    part3_3(lenna_3ch, lenna_response, 'lenna')
    part3_3(shapes_3ch, shapes_response, 'shapes')



    cv2.waitKey(20000)
    cv2.destroyAllWindows()    