import numpy as np
import cv2

import time

def compute_avg_reproj_error(_M, _F):
    N = _M.shape[0]

    X = np.c_[ _M[:,0:2] , np.ones( (N,1) ) ].transpose()
    L = np.matmul( _F , X ).transpose()
    norms = np.sqrt( L[:,0]**2 + L[:,1]**2 )
    L = np.divide( L , np.kron( np.ones( (3,1) ) , norms ).transpose() )
    L = ( np.multiply( L , np.c_[ _M[:,2:4] , np.ones( (N,1) ) ] ) ).sum(axis=1)
    error = (np.fabs(L)).sum()

    X = np.c_[_M[:, 2:4], np.ones((N, 1))].transpose()
    L = np.matmul(_F.transpose(), X).transpose()
    norms = np.sqrt(L[:, 0] ** 2 + L[:, 1] ** 2)
    L = np.divide(L, np.kron(np.ones((3, 1)), norms).transpose())
    L = ( np.multiply( L , np.c_[ _M[:,0:2] , np.ones( (N,1) ) ] ) ).sum(axis=1)
    error += (np.fabs(L)).sum()

    return error/(N*2)

default_path = 'CV_Assignment_3_Data/'

def compute_F_raw(M):
    A = np.array([[x*xp, xp*y, xp, x*yp, y*yp, yp, x, y, 1]
                  for x, y, xp, yp in M])
    
    _, _, V = np.linalg.svd(A)
    F = V[-1].reshape(3, 3)

    return F / F[2, 2]

def normalize(M):

    # TODO: normalize 방법
    # 1. mean
    # 2. median
    mean = np.median(M, axis=0)
    
    # 1. std
    # 2. maximum으로 나누기
    # 3. (maximum - minimum)
    # max_dim = np.max(abs(M - mean), axis=0)
    scale = 1 / np.std(M - mean, axis=0)
    
    T = np.array([[scale[0], 0, -mean[0] * scale[0]],
                  [0, scale[1], -mean[1] * scale[1]],
                  [0, 0, 1]])
    
    M = M.copy()
    M -= mean
    M *= scale

    return M, T

def compute_F_norm(M):
    M1, T1 = normalize(M[:, :2])
    M2, T2 = normalize(M[:, 2:])

    F = compute_F_raw(np.hstack((M1, M2)))

    # U, S, V = np.linalg.svd(F)
    # S[2] = 0
    # F = U @ np.diag(S) @ V

    F = T2.T @ F @ T1
    return F / F[2, 2]

def compute_epipolar_lines(F, M):
    pts1 = np.hstack((M[:, :2], np.ones((len(M), 1))))
    pts2 = np.hstack((M[:, 2:], np.ones((len(M), 1))))

    line1 = (F.T @ pts2.T).T
    line1 = line1 / line1[:, 2].reshape(-1, 1)

    line2 = (F @ pts1.T).T
    line2 = line2 / line2[:, 2].reshape(-1, 1)

    return line1, line2

def compute_line_to_point_distance(lines, points):
    points = np.hstack((points, np.ones((len(points), 1))))
    return np.abs(np.sum(lines * points, axis=1)) / np.linalg.norm(lines[:, :2], axis=1)

def compute_F_mine(M, iters=5000):
    start = time.time()
    # baseline: compute_F_norm
    min_F = compute_F_norm(M)
    min_error = compute_avg_reproj_error(M, min_F)

    t_num = 3 * len(M) // 4
    for _ in range(iters):
        indices = np.random.choice(len(M), t_num, replace=False)
        
        F = compute_F_norm(M[indices])
        error = compute_avg_reproj_error(M, F)

        if  error < min_error:
            min_error = error
            min_F = F
        
        if time.time() - start > 4.95:
            break

    return min_F

def draw_circle_and_line(img1, img2, line1, line2, M):
    color = [
        (0, 0, 255),
        (0, 255, 0),
        (255, 0, 0),
    ]
    for idx, (x1, y1, x2, y2) in enumerate(M):
        x1, y1, x2, y2 = map(int, [x1, y1, x2, y2])
        cv2.circle(img1, (x1, y1), 5, color[idx], -1)
        cv2.circle(img2, (x2, y2), 5, color[idx], -1)

        lp = (0, int(-line1[idx, 2] / line1[idx, 1]))
        rp = (img1.shape[1], int(-(line1[idx, 2] + line1[idx, 0] * img1.shape[1]) / line1[idx, 1]))
        cv2.line(img1, lp, rp, color[idx], 1)

        lp = (0, int(-line2[idx, 2] / line2[idx, 1]))
        rp = (img2.shape[1], int(-(line2[idx, 2] + line2[idx, 0] * img2.shape[1]) / line2[idx, 1]))
        cv2.line(img2, lp, rp, color[idx], 1)

    new_img = np.hstack((img1, img2))
    return new_img

def draw_epipolar_lines(img1, img2, M, F):
    line1, line2 = compute_epipolar_lines(F, M)

    new_img = draw_circle_and_line(img1.copy(), img2.copy(), line1, line2, M)
    cv2.imshow('Epipolar Lines', new_img)

def reference_epi_lines(img1, img2, M, idx):
    F = cv2.findFundamentalMat(M[:, :2], M[:, 2:], cv2.FM_8POINT)[0]

    M = M[idx]
    pts1 = np.hstack((M[:, :2], np.ones((len(M), 1))))
    pts2 = np.hstack((M[:, 2:], np.ones((len(M), 1))))

    lines1 = cv2.computeCorrespondEpilines(pts2, 2, F)
    lines1 = lines1.reshape(-1, 3)
    lines1 = lines1 / lines1[:, 2].reshape(-1, 1)

    lines2 = cv2.computeCorrespondEpilines(pts1, 1, F)
    lines2 = lines2.reshape(-1, 3)
    lines2 = lines2 / lines2[:, 2].reshape(-1, 1)

    new_img = draw_circle_and_line(img1.copy(), img2.copy(), lines1, lines2, M)
    cv2.imshow('Epipolar Lines ref', new_img)

if __name__ == '__main__':

    # Part 1-1-e)
    def part_1_1_e(img_name1, img_name2, match_name):
        # img1 = cv2.imread(default_path + img_name1)
        # img2 = cv2.imread(default_path + img_name2)

        M = np.loadtxt(default_path + match_name)

        print(f'Average Reprojection Errors ({img_name1} and {img_name2})')
        F_raw = compute_F_raw(M)
        print('   Raw  =', compute_avg_reproj_error(M, F_raw))
        F_norm = compute_F_norm(M)
        print('   Norm =', compute_avg_reproj_error(M, F_norm))
        
        start = time.time()
        F_mine = compute_F_mine(M)
        end = time.time()
        print('   Mine =', compute_avg_reproj_error(M, F_mine))
        print('compute_F_mine time:', end - start, '\n')

        return F_mine
    F_temple_mine = part_1_1_e('temple1.png', 'temple2.png', 'temple_matches.txt')
    F_house_mine = part_1_1_e('house1.jpg', 'house2.jpg', 'house_matches.txt')
    F_library_mine = part_1_1_e('library1.jpg', 'library2.jpg', 'library_matches.txt')

    # Part 1-2
    def part_1_2(img_name1, img_name2, match_name, F):
        img1 = cv2.imread(default_path + img_name1)
        img2 = cv2.imread(default_path + img_name2)
        M = np.loadtxt(default_path + match_name)

        t_cnt = 3
        while True:
            idx = np.random.choice(len(M), t_cnt, replace=False)
            draw_epipolar_lines(img1.copy(), img2.copy(), M[idx], F)
            # reference_epi_lines(img1.copy(), img2.copy(), M, idx)
            if cv2.waitKey(0) == ord('q'):
                break
    part_1_2('temple1.png', 'temple2.png', 'temple_matches.txt', F_temple_mine)
    part_1_2('house1.jpg', 'house2.jpg', 'house_matches.txt', F_house_mine)
    part_1_2('library1.jpg', 'library2.jpg', 'library_matches.txt', F_library_mine)

    cv2.destroyAllWindows()