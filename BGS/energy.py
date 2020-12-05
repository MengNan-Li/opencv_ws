#!usr/bin/python
import cv2
from pywt import dwt2

import numpy as np
imgs = ["1.png", "2.png"]

def get_energy(file):
    img=cv2.imread("/home/lmn/" + file)
    roi = img[80:275, 199:445 ]
    im = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    _, (cH, cV, cD) = dwt2(im.T, 'db1')
    # a - LL, h - LH, v - HL, d - HH as in matlab
    Energy = (cH**2 + cV**2 + cD**2).sum()/im.size
    print(Energy)

for img in imgs:
    get_energy(img)
