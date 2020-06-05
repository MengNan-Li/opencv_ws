from __future__ import print_function
import cv2
import argparse
import numpy as np

max_lowThreshold = 100
window_name = 'Edge Map'
title_trackbar = 'Min Threshold:'
ratio = 3
kernel_size = 3
def CannyThreshold(val):
    low_threshold = val
    img_blur = cv2.blur(src_gray, (5,5))
    detected_edges = cv2.Canny(img_blur, low_threshold, low_threshold*ratio, kernel_size)
    mask = detected_edges != 0
    dst = src * (mask[:,:,None].astype(src.dtype))
    
    # cv2.imshow(window_name, detected_edges)

    element = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3), (-1, -1))
    detected_edges = cv2.morphologyEx(detected_edges, cv2.MORPH_CLOSE, element, 2)

    # find the max area contours
    contours, hierarchy = cv2.findContours(detected_edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    object_counts = 0
    for inx, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        print(area)
        if area < 10:
            continue
        x,y,w,h = cv2.boundingRect(contour)
        cv2.drawContours(dst, contours, inx, (0,0,255), 1, 8, hierarchy)
        cv2.rectangle(dst, (x,y), (x+w,y+h), (0,255,0), 2)
        object_counts += 1
    print(object_counts)
    cv2.imshow(window_name, dst)

parser = argparse.ArgumentParser(description='Code for Canny Edge Detector tutorial.')
parser.add_argument('--input', help='Path to input image.', default='fruits.jpg')
args = parser.parse_args()
src = cv2.imread(cv2.samples.findFile(args.input))
if src is None:
    print('Could not open or find the image: ', args.input)
    exit(0)
src = src[20:275, 199:445]
src_gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
cv2.namedWindow(window_name)
cv2.createTrackbar(title_trackbar, window_name , 0, max_lowThreshold, CannyThreshold)
CannyThreshold(0)
cv2.waitKey()
