# Program to implement ransac to caliberate camera

from random import randint
from numpy import *
import numpy as np
from scipy import linalg
import math

A =[]

# 18 image points and world points
x1 = [[304, 306], [347, 368], [432, 352], [300, 58], [346, 381], [342, 393], [341, 406], [447, 360], [462, 367], [478,376], [712, 178], [674,220], [715,124],[718, 69], [720, 11], [589, 214], [494, 93], [594, 163]]
x2 = [[38, 322], [90,388], [188, 364], [39, 44], [88,400], [85,415], [82,430], [206, 371], [222,377], [238, 385], [458,187],[426,226], [459, 138], [461, 87],[462, 35],[351, 218], [258, 97], [355, 170]]

def addPointToA(x1,x2):									# I1 = H*I2
	l = [x2[0],x2[1],1,0,0,0,-x1[0]*x2[0], -x1[0]*x2[1], -x1[0]]
	A.append(l)
	l = [0,0,0,x2[0],x2[1],1,-x1[1]*x2[0], -x1[1]*x2[1], -x1[1]]
	A.append(l)
	
def prepareA():
	d ={}
	for i in range(4):
		t = randint(0,17)
		while t in d:
			t = randint(0,17)
		d[t] = 1
		addPointToA(x1[t], x2[t])

H = []

threshold = 0.1
def getTotalError():				# return error in calculated points using current projection matrix
	dist = 0
	for i in range(0,8,2):
		WP = [A[i][0], A[i][1]]
		y = np.dot(H, WP + [1]) 
		dist += (-1 * A[i][8] - y[0]/y[2]) * (-1 * A[i][8] - y[0]/y[2]) + (-1 * A[i+1][8] - y[1]/y[2]) * (-1 * A[i+1][8] - y[1]/y[2])		
	return math.sqrt(dist)
	
while 1:
	A = []
	prepareA()
	U,s,V = linalg.svd(A)
	H = V[-1].reshape((3,3))	
	print getTotalError()	
	if(getTotalError() <= threshold):
		break;
	
	
print 'Homography matrix is:'
print H

print 'Image points calculated using this camera matrix:'
for i in range(6):
	y = np.dot(H, x2[i] + [1])
	print 'Image 2 point: %s' % x2[i]
	print 'Image 1 Image point: %s' % x1[i]
	l = [y[0]/y[2], y[1]/y[2]]
	print 'Calculated Image 1 point: %s' % l
	print
