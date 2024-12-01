# OPM: getest in python 3.10.0. Een hogere versie werkte niet op het ogenblik van testen.

import cv2
import mediapipe as mp
import serial       # pip install pyserial uitvoeren vooraf.
import math

# Afstand berekenen tussen twee punten.
def GetVectorLength(pointOne, pointTwo):
    # Via stelling van Pythagoras de vectorlengte berekenen.
    vectorLength = math.sqrt(
        math.pow(
            (pointOne.x - pointTwo.x),
            2
        ) + 
        math.pow(
            (pointOne.y - pointTwo.y),
            2
        )
    )

    # Absolute waarde nemen.
    return abs(vectorLength)

# COM-poort openen.
# serialPort = serial.Serial('COM1')
# serialPort.write(str.encode("Starting...\r\n"))
# serialPort.close()

# De mogelijkheid ophalen om de detecties van MediaPipe later te tekenen via OpenCV.
mp_drawing = mp.solutions.drawing_utils

# Holistic model importeren.
mp_holistic = mp.solutions.holistic

# Webcam openen via OpenCV.
cap = cv2.VideoCapture(0)
# cap = cv2.VideoCapture("linkerhandzwaai.mp4")
# cap = cv2.VideoCapture("beide handen zwaai en V.mp4")
# cap = cv2.VideoCapture("RTSP 1.mp4")
# cap = cv2.VideoCapture("RTSP 1.mkv")
# cap = cv2.VideoCapture('rtsp://VIVESCAM:VIVESCAM_1@10.198.120.59:554/videoMain')

# MediaPipe model combineren met OpenCV.
with mp_holistic.Holistic(min_detection_confidence = 0.5, min_tracking_confidence = 0.5) as holistic:
    while(cap.isOpened()):
        ret, frame = cap.read() 

        # # Herschalen indien nodig.
        # scale_percent = 40 # percent of original size
        # width = int(frame.shape[1] * scale_percent / 100)
        # height = int(frame.shape[0] * scale_percent / 100)
        # dim = (width, height)
        # frame = cv2.resize(frame, dim)

        # Beeld kleurconversie.
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # # Beeld spiegelen.
        # image = cv2.flip(image, 1)

        # Detectie.
        results = holistic.process(image)
        # print(results)

        # TODO: is dit niet overbodig?
        # Opnieuw kleurconversie.
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        # # Face landmarks tekenen.
        # mp_drawing.draw_landmarks(image, results.face_landmarks, mp_holistic.FACEMESH_TESSELATION, 
        #     mp_drawing.DrawingSpec(thickness=1, circle_radius=1),
        #     mp_drawing.DrawingSpec(thickness=1, circle_radius=1))
        # of
        # Contouren van gezicht tonen.
        # mp_drawing.draw_landmarks(image, results.face_landmarks, mp_holistic.FACEMESH_CONTOURS)

        # Hand landmarks tekenen.
        mp_drawing.draw_landmarks(image, results.right_hand_landmarks, mp_holistic.HAND_CONNECTIONS)
        # mp_drawing.draw_landmarks(image, results.right_hand_landmarks, mp_holistic.HAND_CONNECTIONS)

        if(results.right_hand_landmarks != None):
            # print(type(results.left_hand_landmarks))
            # print(f"pols: {results.left_hand_landmarks.landmark[0]}")
            # print(f"Top wijsvinger: x = {results.left_hand_landmarks.landmark[8].x:.2f}, y = {results.left_hand_landmarks.landmark[8].y:.2f}.", end="\t")

            polsDuim = GetVectorLength(results.right_hand_landmarks.landmark[0], results.right_hand_landmarks.landmark[4])
            print(f"duim: {polsDuim:.2f}, ", end="   ")

            polsWijsvinger = GetVectorLength(results.right_hand_landmarks.landmark[0], results.right_hand_landmarks.landmark[8])
            print(f"wijsvinger: {polsWijsvinger:.2f}, ", end="   ")

            polsMiddelvinger = GetVectorLength(results.right_hand_landmarks.landmark[0], results.right_hand_landmarks.landmark[12])
            print(f"middelvinger: {polsMiddelvinger:.2f}, ", end="   ")

            polsRingvinger = GetVectorLength(results.right_hand_landmarks.landmark[0], results.right_hand_landmarks.landmark[16])
            print(f"ringvinger: {polsRingvinger:.2f}, ", end="   ")

            polsPink = GetVectorLength(results.right_hand_landmarks.landmark[0], results.right_hand_landmarks.landmark[20])
            print(f"pink: {polsPink:.2f}, ", end="   ")

            if((polsDuim < (0.8 * polsWijsvinger)) and (polsRingvinger < (0.5 * polsWijsvinger)) and (polsPink < (0.5 * polsWijsvinger))):
                print("ok", end="")
    
            print()


            # # TODO: hier verder bekijken wat goed werkt.
            # if((results.left_hand_landmarks.landmark[3].x > results.left_hand_landmarks.landmark[2].x) and (results.left_hand_landmarks.landmark[4].x > results.left_hand_landmarks.landmark[2].x)):
            #     print("Duim open.")
            # else:
            #     print("Duim gesloten.")

        # # Eventueel Pose tekenen (met optioneel andere kleuren).
        # mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_holistic.POSE_CONNECTIONS, 
        #     mp_drawing.DrawingSpec(color=(255,255,0), thickness=2, circle_radius=2),
        #     mp_drawing.DrawingSpec(color=(255,0,0), thickness=2, circle_radius=2))

        # TODO: aanraken van wijsvinger en duim detecteren? Eerst met coördinaten, later met AI?
        # https://github.com/Kazuhito00/hand-gesture-recognition-using-mediapipe/blob/main/README_EN.md
        # En
        # https://www.youtube.com/watch?v=a99p_fAr6e4


        # Beeld tonen.
        cv2.imshow("Holistic Model Detections", image)

        if cv2.waitKey(10) & 0xFF == ord('q'):
            break


cap.release()
cv2.destroyAllWindows()

