# program to implement DLT method to find homography between two images
# Name: Mohit Sharma
# Roll No. : 201505508


from numpy import *
import numpy as np
from scipy import linalg

A =[]
#x1 = [[304, 306], [347, 368], [432, 352], [300, 58]]					# I1
#x2 = [[38, 322], [90,388], [188, 364], [39, 44]]					# I2

#x1 = [[160,43], [165,269], [498,374],[511,103]]					#perspective projection, p1
#x2 = [[0,0], [0,400], [600,400], [600,0]]				

#x1 = [[250,750], [608,747], [843,100],[685,93]]					#perspective projection, p2
#x2 = [[0,0], [0,400], [600,400], [400,6]]				

#x1 = [[219,382], [230,461], [510,568],[518,486]]					#perspective projection, p3
#x2 = [[0,0], [0,400], [600,400], [600,0]]				

#x1 = [[494,177],  [154,200], [809,418], [1231, 382],]					#perspective projection, green field
#x2 = [[498,0], [0,0], [0,504],[498,504]]

#x1 = [[0,186], [0,214], [790,539], [1026,431]]						#perspective projection, pool
#x2 = [[0,0], [0,334],[1170,334], [1170,0]]

x1 = [[245,29], [79,76], [508,187], [639,105]]						#perspective projection, pool table
x2 = [[1920,0], [0,0],	 [0,1200],[1920,1200]]

x1 = [[759,427], [835,536], [772,816],[759,972]]
x2 = [[10,225], [66,306], [28,537], [20,659]]						#perspective projection, pool table


def addPointToA(x1,x2):									# I1 = H*I2
	l = [x2[0],x2[1],1,0,0,0,-x1[0]*x2[0], -x1[0]*x2[1], -x1[0]]
	A.append(l)
	l = [0,0,0,x2[0],x2[1],1,-x1[1]*x2[0], -x1[1]*x2[1], -x1[1]]
	A.append(l)
	
def prepareA():										#prepare matrix A for selected points
	for i in range(len(x1)):
		addPointToA(x1[i], x2[i])

prepareA()

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
