
import os
import time 
os.system ("sudo pigpiod")
time.sleep(1)
import pigpio
import argparse

ESC=4  #Connect the ESC in this GPIO pin 
# for calibration:
MAX_VALUE = 2000
MIN_VALUE = 1280
# once calibrated, minimum pulsewidth that starts the HDD motor
MIN_PULSEWIDTH = 1300
BRAKE_PULSEWIDTH = 1250

def main():
    args = parse_args()
    pi = pigpio.pi()
    pi.set_servo_pulsewidth(ESC, 0) 
    
    if args.manual_control:
        arm(pi, manual_drive)
    elif args.calibrate:
        calibrate(pi)
    elif args.arm:
        arm(pi, control)
    elif args.brake_toggle:
        switch_brake(pi)
    else:
        control(pi)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--calibrate", action="store_true")
    parser.add_argument("-m", "--manual_control", action="store_true")
    parser.add_argument("-a", "--arm", action="store_true")
    parser.add_argument("-b", "--brake_toggle", action="store_true")
    parser.add_argument("-d", "--disable", action="store_true")
    return parser.parse_args()

def manual_drive(pi): #You will use this function to program your ESC if required
    print("You have selected manual option so give a value between 0 and you max value")
    while True:
        inp = input()
        if inp == "stop":
            stop(pi)
            break
        elif inp == "control":
            control(pi)
            break
        elif inp == "arm":
            arm(pi, manual_drive)
            break	
        else:
            time.sleep(1)
            pi.set_servo_pulsewidth(ESC,inp)
                
def calibrate(pi):   #This is the auto calibration procedure of a normal ESC
    print("calibrating...")
    pi.set_servo_pulsewidth(ESC, 0)
    print("Disconnect the battery and press Enter")
    inp = input()
    if inp == '':
        pi.set_servo_pulsewidth(ESC, MAX_VALUE)
        print("Connect the battery NOW.. when you start hearing four short beeps, press enter")
        inp = input()
        pwidth = MAX_VALUE - 10
        while pwidth > MIN_VALUE:
            
            pi.set_servo_pulsewidth(ESC, pwidth)
            time.sleep(0.05)
            print("pulse width: " + str(pwidth) + '\r')
            pwidth -= 10
        pi.set_servo_pulsewidth(ESC, MIN_VALUE)
        input("when you hear 2 short beeps followed by 2 longer beeps, the calibration is complete. you may power off the ESC and press enter")
        print("calibration complete")
        exit(0)
            
def control(pi): 
    print("I'm Starting the motor, I hope its calibrated and armed, if not restart by giving 'stop'")
    # time.sleep(1)
    speed = 1400    # change your speed if you want to.... it should be between 700 - 2000
    print("Controls - d to decrease speed & i to increase speed OR dd to decrease a lot of speed & ii to increase a lot of speed")
    while True:
        pi.set_servo_pulsewidth(ESC, speed)
        inp = input()
        
        if inp == "dd":
            speed -= 100    # decrementing the speed like hell
            print("speed = " + str(speed))
        elif inp == "ii":    
            speed += 100    # incrementing the speed like hell
            print("speed = " + str(speed))
        elif inp == "i":
            speed += 10     # incrementing the speed 
            print("speed = " + str(speed))
        elif inp == "d":
            speed -= 10     # decrementing the speed
            print("speed = " + str(speed))
        elif inp == "stop":
            stop(pi)          #going for the stop function
            break
        elif inp == "manual":
            manual_drive(pi)
            break
        elif inp == "arm":
            arm(pi, control)
            break	
        else:
            print('Invalid input')
            
def arm(pi, callback, extra_args={}): #This is the arming procedure of an ESC 
    pi.set_servo_pulsewidth(ESC, MIN_VALUE)
    print("Connect the battery")
    print("Once connected, you should hear two beeps, lower then higher. Once this happens, press enter")
    i = input()
    callback(pi)

def stop(pi): #This will stop every action your Pi is performing for ESC ofcourse.
    pi.set_servo_pulsewidth(ESC, 0)
    pi.stop()


def switch_brake(pi):
    pi.set_servo_pulsewidth(ESC, MAX_VALUE)
    input("Plug in the ESC. When you start hearing four sets of 3 beeps, press enter")
    pi.set_servo_pulsewidth(ESC, MIN_PULSEWIDTH)
    input("When you hear two beeps, unplug the ESC and press enter")
    pi.set_servo_pulsewidth(ESC, 0)





if __name__ == '__main__':
    main()