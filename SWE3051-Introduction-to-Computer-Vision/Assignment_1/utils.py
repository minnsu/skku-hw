import numpy as np

def padding(img, pad_size, mode):
    tmp = None
    if mode == 0: # 'horizontal':
        tmp = np.zeros((img.shape[0], img.shape[1] + 2 * pad_size), dtype=img.dtype)
        tmp[:, pad_size:-pad_size] = img
        
        tmp[:, :pad_size] = img[:, 0].reshape(-1, 1) # left
        tmp[:, -pad_size:] = img[:, -1].reshape(-1, 1) # right
    elif mode == 1: # 'vertical':
        tmp = np.zeros((img.shape[0] + 2 * pad_size, img.shape[1]), dtype=img.dtype)
        tmp[pad_size:-pad_size, :] = img
        
        tmp[:pad_size, :] = img[0, :] # top
        tmp[-pad_size:, :] = img[-1, :] # bottom
    else:
        tmp = np.zeros((img.shape[0] + 2 * pad_size, img.shape[1] + 2 * pad_size), dtype=img.dtype)
        tmp[pad_size:-pad_size, pad_size:-pad_size] = img
        
        tmp[:pad_size, :pad_size] = img[0, 0] # left-top
        tmp[:pad_size, -pad_size:] = img[0, -1] # right-top
        tmp[-pad_size:, :pad_size] = img[-1, 0] # left-bottom
        tmp[-pad_size:, -pad_size:] = img[-1, -1] # right-bottom

        tmp[:pad_size, pad_size:-pad_size] = img[0, :] # top
        tmp[-pad_size:, pad_size:-pad_size] = img[-1, :] # bottom
        tmp[pad_size:-pad_size, :pad_size] = img[:, 0].reshape(-1, 1) # left
        tmp[pad_size:-pad_size, -pad_size:] = img[:, -1].reshape(-1, 1) # right

    return tmp


def quantize_degree(dir):
    # divide 360 degree into 8 directions
    dir = np.where(
        (315 + 22.5 <= dir) | (dir < 0 + 22.5), 0, dir
    )
    dir = np.where(
        (45 - 22.5 <= dir) & (dir < 45 + 22.5), 45, dir
    )
    dir = np.where(
        (90 - 22.5 <= dir) & (dir < 90 + 22.5), 90, dir
    )
    dir = np.where(
        (135 - 22.5 <= dir) & (dir < 135 + 22.5), 135, dir
    )
    dir = np.where(
        (180 - 22.5 <= dir) & (dir < 180 + 22.5), 180, dir
    )
    dir = np.where(
        (225 - 22.5 <= dir) & (dir < 225 + 22.5), 225, dir
    )
    dir = np.where(
        (270 - 22.5 <= dir) & (dir < 270 + 22.5), 270, dir
    )
    dir = np.where(
        (315 - 22.5 <= dir) & (dir < 315 + 22.5), 315, dir
    )

    return dir.astype(np.int32)


sobel_x = np.array([[-1, 0, 1],
                    [-2, 0, 2],
                    [-1, 0, 1]], dtype=np.float64)
sobel_y = np.array([[1, 2, 1],
                    [0, 0, 0],
                    [-1, -2, -1]], dtype=np.float64)

blur_filter = np.array([[1, 2, 1]], dtype=np.float64)
derivative_filter = np.array([[-1, 0, 1]], dtype=np.float64)