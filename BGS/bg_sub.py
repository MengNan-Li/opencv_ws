from __future__ import print_function
import cv2
import numpy as np
import argparse

parser = argparse.ArgumentParser(description='This program shows how to use background subtraction methods provided by \
                                              OpenCV. You can process both videos and images.')
parser.add_argument('--input', type=str, help='Path to a video or a sequence of image.', default='vtest.avi')
parser.add_argument('--algo', type=str, help='Background subtraction method (KNN, MOG2).', default='MOG2')
args = parser.parse_args()




## [create]
#create Background Subtractor objects
if args.algo == 'MOG2':
    backSub_mog2 = cv2.createBackgroundSubtractorMOG2()
    # backSub_mog2 = cv2.createBackgroundSubtractorMOG2(
    # history=2, varThreshold=100, detectShadows=False)
else:
    backSub = cv2.createBackgroundSubtractorKNN()
## [create]


def sub_mog2(img2, thresh_mog):
  # mask = backSub_mog2.apply(img1)
  mask = backSub_mog2.apply(img2)
  # eliminate the noise
  line = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 5), (-1, -1))
  mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, line)

  # find the max area contours
  contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
  object_counts = 0
  for c in range(len(contours)):
      area = cv2.contourArea(contours[c])
      if area < 30:
          continue
      
      rect = cv2.minAreaRect(contours[c])
      if min(rect[1][0], rect[1][1]) < 6:
        continue

      cv2.ellipse(img2, rect, (0, 255, 0), 2, 8)
      cv2.circle(img2, (np.int32(rect[0][0]), np.int32(rect[0][1])), 2, (255, 0, 0), 2, 8, 0)
      object_counts+=1
  return img2, mask, object_counts

## [capture]
capture = cv2.VideoCapture(cv2.samples.findFileOrKeep(args.input))
if not capture.isOpened:
    print('Unable to open: ' + args.input)
    exit(0)
## [capture]

while True:
    ret, frame = capture.read()
    frame = frame[117:197, 220:300]
    if frame is None:
        break

    ## [apply]
    #update the background model
    # fgMask = backSub.apply(frame)
    frame, fgMask, obhect_count = sub_mog2(frame, 5)
    ## [apply]

    ## [display_frame_number]
    #get the frame number and write it on the current frame
    # cv.rectangle(frame, (10, 2), (100,20), (255,255,255), -1)
    # cv.putText(frame, str(capture.get(cv.CAP_PROP_POS_FRAMES)), (15, 15),
    #            cv.FONT_HERSHEY_SIMPLEX, 0.5 , (0,0,0))
    ## [display_frame_number]

    ## [show]
    #show the current frame and the fg masks
    cv2.imshow('Frame', frame)
    cv2.imshow('FG Mask', fgMask)
    ## [show]

    keyboard = cv2.waitKey(30)
    if keyboard == 'q' or keyboard == 27:
        break
