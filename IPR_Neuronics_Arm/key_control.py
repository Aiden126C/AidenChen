import keyboard
import time
import cv2
from GazeTracking.gaze_tracking import GazeTracking

gaze = GazeTracking()
webcam = cv2.VideoCapture(0)
vert = False
counter = 0

while True:
    _, frame = webcam.read()
    gaze.refresh(frame)

    new_frame = gaze.annotated_frame()
    text = ""

    
    if gaze.is_right():
        text = "Looking right"
        counter = 0
        if not vert:
            keyboard.press('e')
        else:
            keyboard.press('r')
    elif gaze.is_left():
        text = "Looking left"
        counter = 0
        if not vert:
            keyboard.press('s')
        else:
            keyboard.press('d')
    elif gaze.is_blinking():
        counter += 1
        if counter >= 10:
            #print("here")
            vert = not vert
            counter = 0
    elif gaze.is_center():
        text = "Looking center"
        keyboard.release('e')
        keyboard.release('s')
        keyboard.release('r')
        keyboard.release('d')
        counter = 0
    else:
        counter = 0

