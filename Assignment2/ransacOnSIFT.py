# Program to implement ransac using matched points found out from SIFT/SURF to find homography between two images
# Name: Mohit Sharma
# Roll No. : 201505508

from random import randint
from numpy import *
import numpy as np
from scipy import linalg
import math

A =[]

# 18 points from both the images
x1 = [[489, 50], [518, 203], [541, 95], [528, 49], [556, 126], [322, 209], [478, 154], [552, 122], [548, 117], [400,216], [555, 184], [602,178], [617,16],  [493, 57], [532, 221], [483, 215], [388, 104], [509, 96]]
x2 = [[253, 54], [283,208], [305, 102], [294, 56], [319,134], [64,215], [241,159], [315, 130], [311,124], [156, 221], [319,190],[363,186], [374, 31],   [257, 61],[296, 226],[247, 221], [144, 102], [273, 101]]

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
def getTotalError():						# return error in calculated points using current homography matrix
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
