import serial

def send_hex_file(file_path, com_port):
    # Open the serial port
    ser = serial.Serial(com_port, baudrate=115200, timeout=.2)

    with open('/home/hosam/Desktop/test_send.hex', 'r') as file:
        for line in file:
            line = line.strip()  # Remove leading/trailing whitespace and newline characters

            # Send the line over UART
            ser.write(line.encode())  # Convert the line to bytes and send
            ser.write(b'#')   # Convert the line to bytes and send
            print("Sent:", line)
            
            # Wait for the response
            while True:
                response = ser.readline().decode().strip()
                print("Received:", response)
                if response == "OK":
                    print("Received 'OK', continuing...")
                    break  # Exit the loop when "OK" is received
           # if response != "OK":
              #  print("Error: Expected 'OK' response, received:", response)
               # break
          #  else:
           #     print("OK")
    # Close the serial port
    ser.close()

# Usage example
file_path = 'path/to/hex_file.hex'
com_port = '/dev/ttyUSB0'
send_hex_file(file_path, com_port)

