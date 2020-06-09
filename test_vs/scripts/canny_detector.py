from __future__ import print_function
import cv2
import argparse
import numpy as np
import os
from matplotlib import pyplot as plt


def find_files(path):
    return [f for f in os.listdir(path) if os.path.isfile(path + '/' + f) and f.endswith('png')]


max_lowThreshold = 100
window_name = 'Edge Map'
title_trackbar = 'Min Threshold:'
ratio = 3
kernel_size = 3
def CannyThreshold(val, view_enable):
    low_threshold = val
    img_blur = cv2.blur(roi_gray, (5,5))
    detected_edges = cv2.Canny(img_blur, low_threshold, low_threshold*ratio, kernel_size)
    mask = detected_edges != 0
    dst = roi * (mask[:,:,None].astype(roi.dtype))
    
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
    if view_enable:
      cv2.imshow(window_name, dst)
      # cv2.imshow("roi", roi)

parser = argparse.ArgumentParser(description='Code for Canny Edge Detector tutorial.')
parser.add_argument('--input', help='Path to input image or dir.', default='fruits.jpg')
args = parser.parse_args()

if os.path.isdir(args.input):
  for f in find_files(args.input):
    img_path = os.path.join(args.input, f)
    src = cv2.imread(img_path)
    cv2.rectangle(src, (215,25), (425, 250), (0,255,0), 1, 4)
    cv2.imshow("src", src)
    if src is None:
        print('Could not open or find the image: ', args.input)
        exit(0)
    roi = src[25:250, 215:425]
    roi_gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    cv2.namedWindow(window_name)
    cv2.createTrackbar(title_trackbar, window_name , 0, max_lowThreshold, CannyThreshold)
    CannyThreshold(50, True)
    cv2.waitKey()
else:
  src = cv2.imread(cv2.samples.findFile(args.input))
  if src is None:
      print('Could not open or find the image: ', args.input)
      exit(0)
  roi = src[20:275, 199:445]
  roi_gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
  cv2.namedWindow(window_name)
  cv2.createTrackbar(title_trackbar, window_name , 0, max_lowThreshold, CannyThreshold)
  CannyThreshold(50, True)
  cv2.waitKey()
