import cv2

video = cv2.VideoCapture("video.mov")

A = []

while(video.isOpened()):
    ret, frame = video.read()
    if not ret:
        break

    cv2.imshow("Video", frame)
    A.append(frame)

    if cv2.waitKey(1) == ord("q"):
        break

print("The video is ", len(A), " Frames long")

