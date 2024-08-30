import cv2
import os
from datetime import datetime

# Define the directory where you want to save the images
save_directory = "/home/raspberry/camera_test"

# Ensure the directory exists
if not os.path.exists(save_directory):
    os.makedirs(save_directory)

# Initialize the camera
camera = cv2.VideoCapture(0)  # 0 is usually the default camera ID

if not camera.isOpened():
    print("Error: Could not access the camera.")
    exit()
    
try:
    while True:
        # Capture a frame
        ret, frame = camera.read()
        
        if not ret:
            print("Error: Failed to capture image.")
            break
        
        # Display the captured frame (optional)
        #cv2.imshow('Camera', frame)
        
        # Generate a unique filename with timestamp
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        filename = f'{save_directory}/image_{timestamp}.jpg'
        
        # Save the image
        cv2.imwrite(filename, frame)
        print(f'Saved image to {filename}')
        
        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    # Release the camera and close windows
    camera.release()
    cv2.destroyAllWindows()
