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

# COM-poort openen naar de Nucleo van het m&m toestel.
# serialPort = serial.Serial('COM11', 115200)
# serialPort = serial.Serial('/dev/ttyACM0', 115200)

GestureRecognizerResult = mp.tasks.vision.GestureRecognizerResult

# Create a gesture recognizer instance with the live stream mode:
def print_result(gesture_recognition_result: GestureRecognizerResult, output_image: mp.Image, timestamp_ms: int):
    # print('gesture recognition result: {}'.format(result))
    # Zijn er gestures gedetecteerd?
    for gesture in gesture_recognition_result.gestures:
        # print(gesture[0].category_name, timestamp)
        # print()

        # Is er een 'peace sign' gedetecteerd? Data verzenden naar de m&m microcontroller.
        if gesture[0].category_name == "Victory": 
            print("Peace sign detected.")               
            # serialPort.write(b'm')

        # # Eerst Mediapipe image terug omzetten naar OpenCV (Numpy array).
        # frame = output_image.numpy_view()
        # Detectie landmarks tekenen.
        for hand_landmarks_one_hand in gesture_recognition_result.hand_landmarks:
            for landmark in hand_landmarks_one_hand:                
                x = int(landmark.x * frameWidth)
                y = int(landmark.y * frameHeight)
                # print("Z: ", landmark.z)          # Geeft een indicatie van volgorde in Z-as. Groter is dichter.
                cv2.circle(frame, (x,y), 3, (0, 255, 0), 3)
    
    # Beeld tonen.
    # cv2.imshow("Gesture recognition task with Mediapipe and OpenCV", frame)
    # cv2.imshow("Gesture recognition task with Mediapipe and OpenCV", output_image.numpy_view())

# TODO: werken met 'LIVE_STREAM' i.p.v. 'VIDEO' om zo meer real time te werken? Zie: https://ai.google.dev/edge/mediapipe/solutions/vision/gesture_recognizer/python#live-stream
# Gesture recognizer objecten maken.
VisionRunningMode = mp.tasks.vision.RunningMode
# OPM: pad kan aanpassingen vereisen als je op de Raspberry Pi werkt (Windows/Linux).
gesture_recognizer_base_options = python.BaseOptions(model_asset_path='gesture_recognizer.task')
# gesture_recognizer_base_options = python.BaseOptions(model_asset_path='Software/Peace detection/gesture_recognizer.task')
gesture_recognizer_options = vision.GestureRecognizerOptions(base_options=gesture_recognizer_base_options,
                                        running_mode=VisionRunningMode.LIVE_STREAM,
                                        num_hands=2,
                                        result_callback=print_result)
gesture_recognizer = vision.GestureRecognizer.create_from_options(gesture_recognizer_options)

# Webcam openen via OpenCV.
cap = cv2.VideoCapture(0)

# Frame grootte opvragen.
frameWidth = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
frameHeight = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)

# Indien video beschikbaar...
while(cap.isOpened()):
    # Volgende frame inlezen.
    ret, frame = cap.read()

    # Beeld spiegelen.
    frame = cv2.flip(frame, 1)
    
    # Convert the frame received from OpenCV to a MediaPipe’s Image object.
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame)

    # Detectie doen op 'video'.
    timestamp = int(cap.get(cv2.CAP_PROP_POS_MSEC))
    gesture_recognizer.recognize_async(mp_image, timestamp)


    # TODO: uitzoeken hoe je de detecties tekent op het videobeeld.
    # Beeld tonen.
    cv2.imshow("Gesture recognition task with Mediapipe and OpenCV", frame)
    # cv2.imshow("Gesture recognition task with Mediapipe and OpenCV", mp_image.numpy_view())

    # Wachten tot afsluiten...
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

# Alle resources vrijgeven.
cap.release()
cv2.destroyAllWindows()
# serialPort.close()