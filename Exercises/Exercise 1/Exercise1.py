#!/usr/bin/env python
# python Exercise.py

from threading import Thread

i = 0

def thread_1_function():
    
    global i
    for j in range(1000000):
    	i+=1
    print("Hello from a thread 1!\n")




def thread_2_function():
    
    global i
    for k in range(1000000):
    	i-=1
    print("Hello from a thread 2!\n")



def main():
    thread_1 = Thread(target = thread_1_function, args = (),)
    thread_2 = Thread(target = thread_2_function, args = (),)

    thread_1.start()
    thread_2.start()

    print("Tid skrives jeg?\n")
    
    thread_1.join()
    thread_2.join()
    print(i)


main()