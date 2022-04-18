from adafruit_motorkit import MotorKit
from adafruit_motor import stepper
import socket

HOST_IP = "192.168.12.100"
PORT = 4242
MAX_STEPS = 250


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST_IP, PORT))
    print("waiting for connection")
    s.listen(1)
    (client_sock, addr) = s.accept()
    print("connected to " + str(addr))
    kit = MotorKit()
    cur_state = 0
    direction = None
    while True:
        msg = client_sock.recv(2048).decode()
        # split by command delimiter ";", omit empty strings
        cmds = [x for x in msg.split(';') if x]
        closed = 0
        print(cmds)
        try:
            closed = int(cmds[0])
        except ValueError:
            continue
        if closed > cur_state:
            direction = stepper.BACKWARD
        else:
            # need to release slack
            direction = stepper.FORWARD
        diff = abs(cur_state - closed)
        pct = diff/100.0
        steps = int(pct * MAX_STEPS)
        for _ in range(steps):
            kit.stepper2.onestep(style=stepper.DOUBLE, direction=direction)
        cur_state = closed




if __name__ == '__main__':
    main()