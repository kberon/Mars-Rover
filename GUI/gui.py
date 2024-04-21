import tkinter as tk
import subprocess

def send_command(command):
    # This function sends the command to the rover using the subprocess module to call the control script.
    subprocess.run(['python', '../firmware/temp_motors/mwd.py', command], check=True)

# Create the main window
root = tk.Tk()
root.title("Rover Control Panel")

# Create buttons for each direction and assign the commands
forward_button = tk.Button(root, text="Forward", command=lambda: send_command('w'))
backward_button = tk.Button(root, text="Backward", command=lambda: send_command('s'))
left_button = tk.Button(root, text="Left", command=lambda: send_command('a'))
right_button = tk.Button(root, text="Right", command=lambda: send_command('d'))
stop_button = tk.Button(root, text="Stop", command=lambda: send_command('e'))

# Position the buttons on the GUI
forward_button.pack(pady=20)
backward_button.pack(pady=20)
left_button.pack(side=tk.LEFT, padx=40)
right_button.pack(side=tk.RIGHT, padx=40)
stop_button.pack(pady=20)

# Start the GUI event loop
root.mainloop()
