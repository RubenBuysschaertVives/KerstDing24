# Deze code werkt 'asynchroon' (LIVE_STREAM mode) en daardoor is het mogelijk om met minder rekenkracht, toch 
# een vlottere ervaring te creëren (in tegenstelling tot peace_video.py).

# https://ai.google.dev/edge/mediapipe/solutions/vision/gesture_recognizer/index
# Codevoorbeeld via: https://colab.research.google.com/github/googlesamples/mediapipe/blob/main/examples/gesture_recognizer/python/gesture_recognizer.ipynb#scrollTo=OMjuVQiDYJKF
# Model via: https://storage.googleapis.com/mediapipe-models/gesture_recognizer/gesture_recognizer/float16/1/gesture_recognizer.task

import urllib
import cv2
import mediapipe as mp
import serial       # pip install pyserial uitvoeren vooraf.
import math
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
import time

# Constantes.
M_AND_M_DELAY = 9

# Globale variabelen.
result = None
busy = False
last_peace_detection = 0

# COM-poort openen naar de Nucleo van het m&m toestel.
serial_port = serial.Serial('COM11', 115200)
# serialPort = serial.Serial('/dev/ttyACM0', 115200)

# Webcam openen via OpenCV.
capture = cv2.VideoCapture(0)

# Frame grootte opvragen.
frame_width = capture.get(cv2.CAP_PROP_FRAME_WIDTH)
frame_height = capture.get(cv2.CAP_PROP_FRAME_HEIGHT)

# Maak een 'gesture recognizer instance' voor live stream mode.
def detection_callback(gesture_recognition_result, output_image, timestamp_ms):
    # Globale busy variabele ophalen.
    global busy
    global last_peace_detection

    # Resultaat globaal beschikbaar stellen.
    global result 
    result = gesture_recognition_result

    # Zijn er gestures gedetecteerd?
    for gesture in gesture_recognition_result.gestures:
        # print(gesture[0].category_name, timestamp)
        # print()

        # Is er een 'peace sign' gedetecteerd en is de wachttijd voorbij? Data verzenden naar de m&m microcontroller.
        if gesture[0].category_name == "Victory": 
            print("Peace sign detected.", timestamp)
            if(time.time() > last_peace_detection + M_AND_M_DELAY):        
                serial_port.write(b'm')
                print("m&m request sent to microcontroller.")
                last_peace_detection = time.time()

    # Aangeven dat de verwerking voorbij is (en een nieuwe mag beginnen in de 'hoofdlus').
    busy = False

# Werken met 'LIVE_STREAM' i.p.v. 'VIDEO' om zo meer real time te werken.
# Zie: https://ai.google.dev/edge/mediapipe/solutions/vision/gesture_recognizer/python#live-stream
# Gesture recognizer objecten maken.
# OPM: pad kan aanpassingen vereisen als je op de Raspberry Pi werkt (Windows/Linux).
gesture_recognizer_base_options = python.BaseOptions(model_asset_path='gesture_recognizer.task')
# gesture_recognizer_base_options = python.BaseOptions(model_asset_path='Software/Peace detection/gesture_recognizer.task')
gesture_recognizer_options = vision.GestureRecognizerOptions(base_options=gesture_recognizer_base_options,
                                        running_mode=mp.tasks.vision.RunningMode.LIVE_STREAM,
                                        num_hands=2,
                                        result_callback=detection_callback)
gesture_recognizer = vision.GestureRecognizer.create_from_options(gesture_recognizer_options)

# Indien video beschikbaar...
while(capture.isOpened()):
    # Volgende frame inlezen.
    ret, frame = capture.read()

    # Beeld spiegelen.
    frame = cv2.flip(frame, 1)
    
    # Convert the frame received from OpenCV to a MediaPipe’s Image object.
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame)

    # Detectie doen op 'live stream' (als er geen detectie meer bezig is).
    timestamp = int(capture.get(cv2.CAP_PROP_POS_MSEC))
    if busy == False:
        gesture_recognizer.recognize_async(mp_image, timestamp)
    busy = True

    # Detectie landmarks tekenen als er gevonden werden.
    if result != None:
        for hand_landmarks_one_hand in result.hand_landmarks:
            for landmark in hand_landmarks_one_hand:                
                x = int(landmark.x * frame_width)
                y = int(landmark.y * frame_height)
                # Z geeft een indicatie van volgorde in Z-as. Groter is dichter bij de camera.
                # print("Z: ", landmark.z)

                if(time.time() > last_peace_detection + M_AND_M_DELAY):
                    # Groene cirkels tekenen als het langer dan 10 seconden geleden is dat er een m&m werd afgeleverd.
                    cv2.circle(frame, (x,y), 3, (0, 255, 0), 3)
                else:
                    # Rode cirkels tekenen als het minder lang dan 10 seconden geleden is dat er een m&m werd afgeleverd.
                    cv2.circle(frame, (x,y), 3, (0, 0, 255), 3)

    # Berekenen hoe lang het nog duurt vooraleer er een nieuw m&m mag uitgedeeld worden.
    waiting_time = last_peace_detection + M_AND_M_DELAY - time.time()
    # Is de wachttijd voorbij? Toon nul in het groen. Anders de resterende seconden in het rood.
    if waiting_time < 0:
        waiting_time = 0
        waiting_time_color = (0,255,0)      # Groen.
    else:
        waiting_time_color = (0,0,255)      # Rood.
    cv2.putText(frame, f"{waiting_time:.1f}", org=(int(frame_width - 70), int(frame_height - 30)), fontFace=cv2.FONT_HERSHEY_SIMPLEX, fontScale=1, color=waiting_time_color, thickness=4)
    # Beeld tonen.
    cv2.imshow("Gesture recognition with Mediapipe and OpenCV", frame)

    # Wachten tot afsluiten...
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

# Alle resources vrijgeven.
capture.release()
cv2.destroyAllWindows()
serial_port.close()