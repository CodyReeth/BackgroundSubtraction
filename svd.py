import numpy as np
import matplotlib.pyplot as plt
from scipy.sparse.linalg import svds
import cv2

video = cv2.VideoCapture("video.mov")

A = []

while(video.isOpened()):
    ret, frame = video.read()
    if not ret:
        break
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow("Video", frame)

    #gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_frame = cv2.resize(frame, (1028, 1028))
    gray_frame = gray_frame.astype(np.float32)
    gray_frame = gray_frame.flatten()

    A.append(gray_frame)
    if cv2.waitKey(1) == ord("q"):
        break
video.release()
X = np.column_stack(A)

#print("The video is ", len(A), " Frames long")

print(X.shape)
Q,S,Vt = svds(X.astype(float), k=100)

L = 99
Xhat = Q[:, :L] @  np.diag(S[:L]) @ Vt[:L,:]

for i in range(Xhat.shape[1]):

    frame = Xhat[:, i]
    frame = frame.reshape(1028, 1028)

    frame = cv2.normalize(frame, None, 0, 255, cv2.NORM_MINMAX)
    frame = frame.astype(np.uint8)

    cv2.imshow("Foreground", frame)

    if cv2.waitKey(33) == ord("q"):
        break

cv2.destroyAllWindows()
