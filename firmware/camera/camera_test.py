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

# Define the desired size for the resized frames
width, height = 320, 240  # Example size; adjust as needed

# Create a window with a specific name
cv2.namedWindow('Camera', cv2.WINDOW_AUTOSIZE)

try:
    while True:
        # Capture a frame
        ret, frame = camera.read()
        
        if not ret:
            print("Error: Failed to capture image.")
            break
        
        # Resize the frame
        resized_frame = cv2.resize(frame, (width, height))
        
        # Display the resized frame
        cv2.imshow('Camera', resized_frame)
        
        # Generate a unique filename with timestamp
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        filename = f'{save_directory}/image_{timestamp}.jpg'
        
        # Save the resized image
        cv2.imwrite(filename, resized_frame)
        print(f'Saved image to {filename}')
        
        # Check for key press and window close event
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):  # Break the loop if 'q' is pressed
            break
        if cv2.getWindowProperty('Camera', cv2.WND_PROP_VISIBLE) < 1:  # Check if window was closed
            break

finally:
    # Release the camera and close windows
    camera.release()
    cv2.destroyAllWindows()
