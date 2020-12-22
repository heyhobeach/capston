import Tkinter
import tkMessageBox
import os
import subprocess
import threading
import time
#################################################################################

def run_rosfilter():
	subprocess.call("roslaunch turtlebot3_follow_filter turtlebot3_follow_filter.launch",shell=True)

#################################################################################
	
def okClick1():
	run_rosfilter()

#################################################################################

root = Tkinter.Tk()
label=Tkinter.Label(root,text="BigDate 2.0")
label.pack()
root.geometry("200x200")

#################################################################################

button1 = Tkinter.Button(root,text="Move ON",width=20,height=13,command=okClick1)
button1.pack()

#################################################################################

root.mainloop()

