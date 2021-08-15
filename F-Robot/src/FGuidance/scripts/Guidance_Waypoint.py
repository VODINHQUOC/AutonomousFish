#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
import numpy as np
from std_msgs.msg import Float32
from std_msgs.msg import Float32MultiArray
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt

class Waypoint:
    def __init__(self):
        self.Waypoint=np.array([[0,21],
                                [1,24],
                                [2,24],
                                [3,18],
                                [4,16]])
       
        self.x = [] 
        self.y = []
        self.pubY = rospy.Publisher('positionY', Float32MultiArray, queue_size=500)
        self.pubX = rospy.Publisher('positionX', Float32MultiArray, queue_size=500)
        self.get_waypoint(self.Waypoint)

    def get_waypoint(self,waypoint):
        num_point = len(waypoint[:,1])
        for i in range(num_point):
            self.x.append(waypoint[i,0])
            self.y.append(waypoint[i,1])
        rospy.loginfo(self.x)
        rospy.loginfo(self.y)
        self.f  = CubicSpline(self.x, self.y, bc_type='natural')
        self.x_new = np.linspace(0, 4, 401)
        self.y_new = self.f(self.x_new)

        self.pdata_y=np.array([len(self.y_new)])
        self.pdata_x=np.array([len(self.x_new)])

        self.pdata_y = np.append(self.pdata_y,self.y_new)
        self.pdata_x = np.append(self.pdata_x,self.x_new)

        self.PyMessage= Float32MultiArray()
        self.PxMessage= Float32MultiArray()

        self.PyMessage.data =self.pdata_y
        self.PxMessage.data =self.pdata_x

        rospy.loginfo(self.PyMessage)
        rospy.loginfo(self.PxMessage)
        
    def send_message(self):
        rospy.loginfo("Sending Messange Y: "+str(self.y_new[5]) )
        rospy.loginfo("Sending Messange X: "+str(self.x_new[5]) )
        rospy.loginfo("------------------------------")
        self.pubY.publish(self.PyMessage)
        self.pubX.publish(self.PxMessage)



def py_timer_callback(event):
    way.send_message()

if __name__ == "__main__":
    rospy.init_node('CubicSpline', anonymous=True)
    
    rospy.Timer(rospy.Duration(1),py_timer_callback,oneshot=False)
    print("Cubic calculating.....")
    global way
    way = Waypoint()
    
    
    print("Cubic sucess !!!")
    rospy.spin()
