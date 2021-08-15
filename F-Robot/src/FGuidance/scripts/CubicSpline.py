#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
import numpy as np
from std_msgs.msg import Float32
from std_msgs.msg import Float32MultiArray
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt

MA=np.zeros([16,16], dtype=float)

Waypoint=np.array([[0,21],
                   [1,24],
                   [2,24],
                   [3,18],
                   [4,16]])



def talker():
    x=[0,1,2,3,4]
    y=[21,24,24,18,16]
    f = CubicSpline(x, y, bc_type='natural')
    global y_new
    global x_new
    x_new = np.linspace(0, 4, 401)
    y_new = f(x_new)
    
    plt.plot(x_new, y_new, 'b')
    plt.plot(x, y, 'ro')
    plt.show()
    pdata=np.array([len(y_new)])
    pdata1=np.array([len(x_new)])

    pdata = np.append(pdata,y_new)
    pdata1 = np.append(pdata1,x_new)
    # print(pdata)
    global PyMessage,PxMessage
    PyMessage= Float32MultiArray()
    PxMessage= Float32MultiArray()

    PyMessage.data =pdata
    PxMessage.data =pdata1


    global pubY
    global pubX 

    pubY = rospy.Publisher('positionY', Float32MultiArray, queue_size=500)
    pubX = rospy.Publisher('positionX', Float32MultiArray, queue_size=500)

    
    rate = rospy.Rate(1) # 1hz

    rospy.loginfo(PyMessage)
    rospy.loginfo(PxMessage)
    
    # while not rospy.is_shutdown():
    #     rate.sleep()

def py_timer_callback(event):
    rospy.loginfo("Sending Messange 1s :"+str(x_new[5]) )
    rospy.loginfo("Sending Messange 1s :"+str(y_new[5]) )
    pubY.publish(PyMessage)
    pubX.publish(PxMessage)

if __name__ == "__main__":
    rospy.init_node('CubicSpline', anonymous=True)
    
    rospy.Timer(rospy.Duration(1),py_timer_callback,oneshot=False)

    
    print("Cubic calculating.....")
    talker()
    print("Cubic sucess !!!")
    rospy.spin()

