import numpy as np
import cv2
import time

def get_features(img):
    orb = cv2.ORB_create()
    kp = orb.detect(img, None)
    kp, des = orb.compute(img, kp)
    return kp, des

def matching(des1, des2):
    des1 = np.unpackbits(des1, axis=1)
    des2 = np.unpackbits(des2, axis=1)

    dists = np.bitwise_xor(des2[:, None], des1).sum(axis=-1).astype(np.float32)
    match_indices = dists.argmin(axis=1)

    matches = []
    for i, j in enumerate(match_indices):
        matches.append(cv2.DMatch(i, j, dists[i, j]))
    
    return sorted(matches, key=lambda x:x.distance)

def matching_with_ratio(des1, des2, th=0.8):
    des1 = np.unpackbits(des1, axis=1)
    des2 = np.unpackbits(des2, axis=1)

    targets = []
    for i, d2 in enumerate(des2):
        dists = [cv2.DMatch(i, j, np.count_nonzero(d2 != d1)) for j, d1 in enumerate(des1)]
        dists = sorted(dists, key=lambda x:x.distance)

        # if first matched feature and second matched feature have similar distance then it is not a good match
        if dists[0].distance / dists[1].distance < th:
            targets.append(dists[0])

    return sorted(targets, key=lambda x:x.distance)

def normalize_matrix(points):
    centroid = np.mean(points, axis=0)
    points = points - centroid

    scale = np.sqrt(2) / np.max(np.linalg.norm(points, axis=1))
    points = points * scale

    return np.array([[scale, 0, -centroid[0] * scale],
                     [0, scale, -centroid[1] * scale],
                     [0, 0, 1]]), points

def get_points(kp1, kp2, matches, normalized=False):
    srcP = np.array([[*kp1[m.trainIdx].pt] for m in matches])
    dstP = np.array([[*kp2[m.queryIdx].pt] for m in matches])
    if normalized:
        T_s, srcP = normalize_matrix(srcP)
        T_d, dstP = normalize_matrix(dstP)
        return srcP, dstP, T_s, T_d
    return srcP, dstP

def compute_homography(srcP, dstP):
    A = np.array([[[-x, -y, -1, 0, 0, 0, x*xp, y*xp, xp],
                  [0, 0, 0, -x, -y, -1, x*yp, y*yp, yp]]
                  for (x, y), (xp, yp) in zip(srcP, dstP)]).reshape(-1, 9)

    _, _, V = np.linalg.svd(A)
    H = V[-1].reshape(3, 3)

    return H / H[2, 2]

def compute_homography_ransac(srcP, dstP, th):
    max_inliers = -1
    result_H = None

    srcP2 = np.append(srcP, np.ones((len(srcP), 1)), axis=1)
    dstP2 = np.append(dstP, np.ones((len(dstP), 1)), axis=1)

    iter = 15000
    for _ in range(iter):
        idx = np.random.choice(len(srcP), 4, replace=False)
        H = compute_homography(srcP[idx], dstP[idx])

        tmp = H @ srcP2.T
        tmp /= tmp[2] + 1e-8
        inliers_cnt = np.sum(np.linalg.norm(tmp.T - dstP2, axis=1) <= th)

        if inliers_cnt > max_inliers:
            max_inliers = inliers_cnt
            result_H = H
    return result_H

def gradation_blending(composed, img1, img2, boundary, w):
    h = img1.shape[0]

    mask = np.zeros((h, w), dtype=np.float32)
    mask[:, :] = np.linspace(1, 0, w, axis=0).astype(np.float32)

    for i in range(boundary-w, boundary):
        t = i - (boundary-w)
        composed[:, i] = img1[:, i] * mask[:, t] + img2[:, i] * (1 - mask[:, t])
    
    return composed


if __name__ == '__main__':
    img_cover = cv2.imread('CV_Assignment_2_Images/cv_cover.jpg', cv2.IMREAD_GRAYSCALE)
    img_desk = cv2.imread('CV_Assignment_2_Images/cv_desk.png', cv2.IMREAD_GRAYSCALE)
    
    kp_cover, des_cover = get_features(img_cover)
    kp_desk, des_desk = get_features(img_desk)

    # 2-1 --------------------------------------------------------------------------------
    matches = matching(des_cover, des_desk)
    top_k = 10
    img_matches = cv2.drawMatches(img_desk, kp_desk, img_cover, kp_cover, matches[:top_k], None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    cv2.imshow('matches', img_matches)
    # ------------------------------------------------------------------------------------


    # 2-4 --------------------------------------------------------------------------------
    # homography with normalization
    matches = matching_with_ratio(des_cover, des_desk, 0.8)
    N = 15
    srcP, dstP, T_s, T_d = get_points(kp_cover, kp_desk, matches[:N], normalized=True)

    H = compute_homography(srcP, dstP)
    H = np.linalg.inv(T_d) @ H @ T_s

    warped_img = cv2.warpPerspective(img_cover, H, (img_desk.shape[1], img_desk.shape[0]))
    composed_warp = img_desk.copy()
    composed_warp[warped_img > 0] = warped_img[warped_img > 0]
    img_window = np.hstack((warped_img, composed_warp))
    cv2.imshow('Homography with normalization', img_window)

    # homography with RANSAC
    srcP, dstP = get_points(kp_cover, kp_desk, matches)

    start = time.time()
    H_ransac = compute_homography_ransac(srcP, dstP, 4)
    end = time.time()
    print('Part 2-4: RANSAC time:', end - start)
    
    warped_img_ransac = cv2.warpPerspective(img_cover, H_ransac, (img_desk.shape[1], img_desk.shape[0]))
    composed_warp_ransac = img_desk.copy()
    composed_warp_ransac[warped_img_ransac > 0] = warped_img_ransac[warped_img_ransac > 0]
    img_window_ransac = np.hstack((warped_img_ransac, composed_warp_ransac))
    cv2.imshow('Homography with RANSAC', img_window_ransac)

    # harry potter cover with RANSAC
    hp_cover = cv2.imread('CV_Assignment_2_Images/hp_cover.jpg', cv2.IMREAD_GRAYSCALE)
    hp_cover = cv2.resize(hp_cover, (img_cover.shape[1], img_cover.shape[0])) # resizing to match the size of img_cover

    warped_img_ransac_hp = cv2.warpPerspective(hp_cover, H_ransac, (img_desk.shape[1], img_desk.shape[0]))    
    composed_warp_ransac_hp = img_desk.copy()
    composed_warp_ransac_hp[warped_img_ransac_hp > 0] = warped_img_ransac_hp[warped_img_ransac_hp > 0]
    img_window_ransac_hp = np.hstack((warped_img_ransac_hp, composed_warp_ransac_hp))
    cv2.imshow('hp_cover with RANSAC', img_window_ransac_hp)
    # ------------------------------------------------------------------------------------


    # 2-5 --------------------------------------------------------------------------------
    def part2_5(srcImg, dstImg):
        # Get features
        kp1, des1 = get_features(srcImg)
        kp2, des2 = get_features(dstImg)

        # Matching
        matches = matching_with_ratio(des1, des2, 0.8)
        srcP, dstP = get_points(kp1, kp2, matches)

        start = time.time()
        H = compute_homography_ransac(srcP, dstP, 3)
        end = time.time()
        print('Part 2-5: RANSAC time:', end - start)
        
        h1, w1 = dstImg.shape[:2]
        h2, w2 = srcImg.shape[:2]
        img2_warped = cv2.warpPerspective(srcImg, H, (w1 + w2, h1))

        # Create a panorama by concatenating dstImg and the warped srcImg
        panorama = np.zeros((h1, w1 + w2), dtype=np.uint8)
        panorama[img2_warped > 0] = img2_warped[img2_warped > 0]
        panorama[:h1, :w1] = dstImg

        # Cut the black part
        min_c = w1+w2
        for r in range(h1):
            for c in range(w1+w2-1, 0, -1):
                if panorama[r, c] != 0 and min_c >= c and c > w1:
                    min_c = c
                    break
        panorama = panorama[:, :min_c]
        
        # without blending
        cv2.imshow('stiched without blending', panorama)
        
        # with blending
        tmp_img1 = np.hstack((dstImg, np.zeros((h1, img2_warped.shape[1] - w1))))
        panorama = gradation_blending(panorama, tmp_img1, img2_warped, boundary=w1, w=120)
        cv2.imshow('stiched with blending', panorama)

    img_dh10 = cv2.imread('CV_Assignment_2_Images/diamondhead-10.png', cv2.IMREAD_GRAYSCALE)
    img_dh11 = cv2.imread('CV_Assignment_2_Images/diamondhead-11.png', cv2.IMREAD_GRAYSCALE)
    part2_5(img_dh11, img_dh10)
    # ------------------------------------------------------------------------------------

    cv2.waitKey(0)
    cv2.destroyAllWindows()