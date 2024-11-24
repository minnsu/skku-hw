import numpy as np
import cv2

def get_transformed_image(img, M):
    plane = np.zeros((801, 801), dtype=np.uint8)
    plane.fill(255)

    rows, cols = img.shape
    offset_r, offset_c = rows//2, cols//2

    ImgPos = np.where(img < 255)
    Rows, Cols = ImgPos[0]-offset_r, ImgPos[1]-offset_c

    M_inv = np.linalg.inv(M)
    dp = np.array([
        [-0.5, -0.5, 0], [-0.5, 0, 0], [-0.5, 0.5, 0],
        [0, -0.5, 0], [0, 0.5, 0],
        [0.5, -0.5, 0], [0.5, 0, 0], [0.5, 0.5, 0]
    ], dtype=np.float32)

    total_pixels = len(Rows)
    for i in range(total_pixels):
        c, r, _ = M @ [Cols[i], Rows[i], 1] + 400
        cur_val = img[ImgPos[0][i], ImgPos[1][i]]
        plane[int(r), int(c)] = cur_val

        # 현재 픽셀 주변이 매핑될 plane의 범위
        ranges = (M @ (dp + [Cols[i], Rows[i], 1]).T).T + 400
        min_r, max_r = int(np.min(ranges[:, 1])), int(np.max(ranges[:, 1]))
        min_c, max_c = int(np.min(ranges[:, 0])), int(np.max(ranges[:, 0]))

        # 매핑될 plane의 픽셀을 inverse M을 사용해 이미지의 가장 가까운 픽셀 값으로 매핑
        for tr in range(min_r, max_r+1):
            for tc in range(min_c, max_c+1):
                backward_c, backward_r, _ = M_inv @ [tc-400, tr-400, 1]
                backward_r, backward_c = round(backward_r), round(backward_c)

                plane[tr, tc] = img[backward_r+offset_r, backward_c+offset_c]

    cv2.arrowedLine(plane, (400, 800), (400, 0), 0, 3, tipLength=0.03)
    cv2.arrowedLine(plane, (0, 400), (800, 400), 0, 3, tipLength=0.03)
    return plane

def interactive_transform(img):
    
    initial_state = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]], dtype=np.float32)
    M = initial_state.copy()
    while True:
        key = cv2.waitKey(0)

        if key == ord('a'): # move left 5 pixel
            M[0, 2] += -5
        elif key == ord('d'): # move right 5 pixel
            M[0, 2] += 5
        elif key == ord('w'): # move up 5 pixel
            M[1, 2] += -5
        elif key == ord('s'): # move down 5 pixel
            M[1, 2] += 5
        elif key == ord('r'): # rotate counter-clockwise 5 degree
            theta = np.radians(-5)
            R = np.array([[np.cos(theta), -np.sin(theta), 0], [np.sin(theta), np.cos(theta), 0], [0, 0, 1]])
            M = np.dot(R, M)
        elif key == ord('t'): # rotate clockwise 5 degree
            theta = np.radians(5)
            R = np.array([[np.cos(theta), -np.sin(theta), 0], [np.sin(theta), np.cos(theta), 0], [0, 0, 1]])
            M = np.dot(R, M)
        elif key == ord('f'): # flip across y-axis
            M[0, :] = -M[0, :]
        elif key == ord('g'): # flip across x-axis
            M[1, :] = -M[1, :]
        elif key == ord('x'): # shrink the size by 5% in x-axis
            M[0, :] *= 0.95
        elif key == ord('c'): # enlarge the size by 5% in x-axis
            M[0, :] *= 1.05
        elif key == ord('y'): # shrink the size by 5% in y-axis
            M[1, :] *= 0.95
        elif key == ord('u'): # enlarge the size by 5% in y-axis
            M[1, :] *= 1.05
        elif key == ord('h'):
            M = initial_state.copy()
        elif key == ord('q'):
            cv2.destroyAllWindows()
            break
    
        plane = get_transformed_image(img, M)
        cv2.imshow('plane', plane)


if __name__ == '__main__':
    img = cv2.imread('CV_Assignment_2_Images/smile.png', cv2.IMREAD_GRAYSCALE)
    interactive_transform(img)

    cv2.waitKey(0)
    cv2.destroyAllWindows()