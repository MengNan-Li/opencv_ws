#! coding:utf-8
import numpy as np
import cv2

# read the video
cap = cv2.VideoCapture('/media/lmn/D/opencv-4.3.0/samples/data/vtest.avi')

def nothing(x):  # 滑动条的回调函数
    pass
WindowName = 'result'
cv2.namedWindow(WindowName, cv2.WINDOW_AUTOSIZE)
cv2.createTrackbar('thresh', WindowName, 0, 1000, nothing)

def sub_mog2(img1, img2, thresh_mog):
  backSub_mog2 = cv2.createBackgroundSubtractorMOG2(
  history=1, varThreshold=thresh_mog, detectShadows=False)
  mask = backSub_mog2.apply(img1)
  mask = backSub_mog2.apply(img2)
  # eliminate the noise
  line = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 5), (-1, -1))
  mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, line)
  cv2.imshow("mask", mask)

  # find the max area contours
  contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
  object_counts = 0
  for c in range(len(contours)):
      area = cv2.contourArea(contours[c])
      if area < 50:
          continue
      rect = cv2.minAreaRect(contours[c])
      cv2.ellipse(img2, rect, (0, 255, 0), 2, 8)
      cv2.circle(img2, (np.int32(rect[0][0]), np.int32(rect[0][1])), 2, (255, 0, 0), 2, 8, 0)
      object_counts+=1
  return img2, mask, object_counts

def getPerson(image, opt=1):

    # get the front mask
    mask = fgbg.apply(image)

    # eliminate the noise
    line = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 5), (-1, -1))
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, line)
    cv2.imshow("mask", mask)

    # find the max area contours
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for c in range(len(contours)):
        area = cv2.contourArea(contours[c])
        if area < 150:
            continue
        rect = cv2.minAreaRect(contours[c])
        cv2.ellipse(image, rect, (0, 255, 0), 2, 8)
        cv2.circle(image, (np.int32(rect[0][0]), np.int32(rect[0][1])), 2, (255, 0, 0), 2, 8, 0)
    return image, mask



while True:
  img1 = cv2.imread('/home/lmn/cabinet_imgs/2020-05-27-11-12-42.png')
  img2 = cv2.imread('/home/lmn/cabinet_imgs/2020-05-27-10-13-03.png')
  thresh = cv2.getTrackbarPos('thresh', WindowName)
  # create the subtractor
  # fgbg = cv2.createBackgroundSubtractorMOG2(
  # history=1, varThreshold=thresh, detectShadows=False)
  # result, m_ = getPerson(img1)
  # result, m_ = getPerson(img2)
  result, m_ , counts= sub_mog2(img1,img2,thresh)
  print(counts)
  cv2.imshow(WindowName, result)
  cv2.waitKey(1)
'''
while True:
    ret, frame = cap.read()
    cv2.imwrite("input.png", frame)
    cv2.imshow('input', frame)
    result, m_ = getPerson(frame)
    cv2.imshow('result', result)
    k = cv2.waitKey(50)&0xff
    if k == 27:
        cv2.imwrite("result.png", result)
        cv2.imwrite("mask.png", m_)

        break
cap.release()
'''
cv2.destroyAllWindows()
