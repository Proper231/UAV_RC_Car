import cv2
import math
import time
import serial  # Import the pyserial library
from ultralytics import YOLO

def send_signal_to_arduino(signal):
    try:
        # Open a serial connection to the Arduino
        arduino = serial.Serial('COM4', 9600, timeout=1)

        # Send a signal to the Arduino
        arduino.write(signal.encode())

        # Close the serial connection
        arduino.close()

        print(f"Signal '{signal}' sent to Arduino successfully.")

    except Exception as e:
        print(f"Error sending signal to Arduino: {e}")

def video_detection():
    model = YOLO("best.pt")
    cap = cv2.VideoCapture(0)  # Use 0 for default camera, or provide the camera index

    target_width = 640
    target_height = 480

    last_signal_time = 0  # Store the time of the last signal sent
    signal_interval = 10  # Interval in seconds

    while True:
        success, img = cap.read()
        if not success:
            print("Failed to capture frame.")
            break

        img = cv2.resize(img, (target_width, target_height))
        results = model(img, stream=True)

        if results is not None:
            for r in results:
                boxes = r.boxes
                for box in boxes:
                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    conf = math.ceil((box.conf[0] * 100)) / 100

                    if conf > 0.5:
                        class_name = model.names[int(box.cls[0])]
                        print(f"Detected: {class_name} (Confidence: {conf})")

                        # Draw a rectangle and label around the detected object
                        cv2.rectangle(img, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        label = f'{class_name} {conf:.2f}'
                        t_size = cv2.getTextSize(label, 0, fontScale=1, thickness=2)[0]
                        c2 = x1 + t_size[0], y1 - t_size[1] - 3
                        cv2.rectangle(img, (x1, y1), c2, (0, 255, 0), -1, cv2.LINE_AA)
                        cv2.putText(img, label, (x1, y1 - 2), 0, 1, [255, 255, 255], thickness=1, lineType=cv2.LINE_AA)

                        # Check if it's time to send a signal
                        current_time = time.time()
                        if current_time - last_signal_time >= signal_interval:
                            if class_name == 'stop':
                                send_signal_to_arduino('STOP_SIGNAL')
                                last_signal_time = current_time
                            elif class_name == 'yield':
                                send_signal_to_arduino('YIELD_SIGNAL')
                                last_signal_time = current_time
                            # Add more conditions for other signs as needed

        cv2.imshow('Detection', img)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()


# Example usage
video_detection()