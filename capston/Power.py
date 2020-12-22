import Tkinter
import tkMessageBox
import os
import subprocess
import threading
import time
#################################################################################

def run_roscore():
	subprocess.call("roscore",shell=True) #1.btn

#################################################################################
	
def okClick1():
	run_roscore()

#################################################################################

root = Tkinter.Tk()
label=Tkinter.Label(root,text="BigDate 2.0")
label.pack()
root.geometry("200x200")

#################################################################################

button1 = Tkinter.Button(root,text="Power ON",width=20,height=13,command=okClick1)
button1.pack()

#################################################################################

root.mainloop()

