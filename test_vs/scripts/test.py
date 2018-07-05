# -*- coding:utf-8 -*-
import cv2.cv as cv

# 读图片
image=cv.LoadImage('headimage.png', cv.CV_LOAD_IMAGE_COLOR)#Load the image
#Or just: image=cv.LoadImage('img/image.png')
 
cv.NamedWindow('a_window', cv.CV_WINDOW_AUTOSIZE) #Facultative
cv.ShowImage('a_window', image) #Show the image
 
# 写图片
# cv.SaveImage("thumb.png", thumb)
cv.WaitKey(0) #Wait for user input and quit