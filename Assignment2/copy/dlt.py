# program to implement DLT method to caliberate the camera

from numpy import *
import numpy as np
from scipy import linalg

A =[]
x1 = [[494,177], [809,418], [1231, 382], [154,200]]
x2 = [[0,0], [800,450], [800,0],[0,450]]
#x1 = [[304, 306], [347, 368], [432, 352], [300, 58]]	# 1
#x2 = [[38, 322], [90,388], [188, 364], [39, 44]]	# I2


def addPointToA(x1,x2):									# I1 = H*I2
	l = [x2[0],x2[1],1,0,0,0,-x1[0]*x2[0], -x1[0]*x2[1], -x1[0]]
	A.append(l)
	l = [0,0,0,x2[0],x2[1],1,-x1[1]*x2[0], -x1[1]*x2[1], -x1[1]]
	A.append(l)
	
def prepareA():										#prepare matrix A for selected points
	for i in range(len(x1)):
		addPointToA(x1[i], x2[i])

prepareA()

print A
U,s,V = linalg.svd(A)

print 'Homography matrix is:'
H = V[-1].reshape((3,3))
print H
x2=[[0,0], [800,450]]
print 'Image 1 calculated using this homography matrix:'
for i in range(len(x2)):
	y = np.dot(H, x2[i] + [1])
	print 'Image 2 point: %s' % x2[i]
	print 'Image 1 point: %s' % x1[i]
	l = [y[0]/y[2], y[1]/y[2]]
	print 'Calculated image 1 point: %s' % l
	print
