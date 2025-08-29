import time
import websocket

# delay is in seconds
movements=[
    {"position":[0,100,150,90,60,60], "delay":0.1},
    {"position":[0,90,150,90,60,0], "delay":0.1},
    {"position":[0,120,90,90,90,0], "delay":0.1},
    {"position":[90,120,120,90,90,0], "delay":0.1},
    {"position":[90,90,150,90,90,0], "delay":0.1},
    {"position":[90,90,150,90,90,60], "delay":0.1},
    {"position":[90,120,90,90,90,60], "delay":0.1},

   
]

#connect to the websocket server
ws = websocket.WebSocket()
IP = "" #this IP is printed on the Serial port of ESP32.
ws.connect("ws://192.168.80.226" + IP )

print("Connected to the server!!")

try:
    for move in movements:
        position = move["position"]
        delay = move["delay"]
        
        # Send the angles to the ESP32
        command = ', '.join(map(str, position)) + ',\n'
        print(command)
        ws.send(command.encode())
        
        # Wait for "done" message from the ESP32
        response = ws.recv()
        print(response)
        if response == "done":
            print("Received confirmation from ESP32.")
        else:
            print("Unexpected response from ESP32:", response)
            break
        
        print("Waiting for", delay, "seconds...")
        import time
        time.sleep(delay)
    ws.close()

except KeyboardInterrupt:
    # Close socket connection when Ctrl+C is pressed
    ws.close()
    print("\nSocket connection closed.")
