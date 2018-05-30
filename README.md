# Embedded-Systems-Project

This is the Embedded Systems Project I contributed to in my second year of university as part of a team of four. Most of the code worked on by the group can be found in [mylpclib.c](mylpclib.c), and the individual project code produced entirely by myself can be found in [individualproj.c](individualproj.c)

Technical information about the project can be found in [Technical Report.docx](https://github.com/chrisgid/Embedded-Systems-Project/blob/master/Technical%20Report.docx)

### Group Project Goals	(Taken from [Technical Report.docx](https://github.com/chrisgid/Embedded-Systems-Project/blob/master/Technical%20Report.docx))

The group project goals were to implement a working solution using the MBED board, servo and connected infrared and ultrasonic sensors for each of the following points:  
* A ‘tape measure mode’ that measures distance and outputs a constantly updated value to LCD display  
* A ‘calibration mode’ that can be used to calibrate the distance measurements of both the infrared and ultrasonic distance sensors, with a user interface to guide a user through calibration  
* A ‘scan mode’ that rotates the servo taking distance measurements at at least 20 points through its rotation  
* A ‘multi view mode’ that can combine multiple scan sweeps of an object at different rotations to create an all-round profile of the object  
* A user interface combining a keypad and LCD to allow relevant parameters to be modified and to display relevant information that ties in with the above four modes.  
* Raw data that is displayed on an external PC  
* Graphical representation of scan data and mode, with real time updates

Each of these goal were to be completed to a satisfactorily working standard or better, with equal and fair contribution from each of the four group members.


### Individual Project Goals (Taken from [Technical Report.docx](https://github.com/chrisgid/Embedded-Systems-Project/blob/master/Technical%20Report.docx))

The individual project goals were to implement a working object tracker using the MBED board, servo and connected infrared and ultrasonic sensors. This solution should interface with existing group solutions, building on them to create the tracker. The object tracker should follow an object that is placed in front of the sensors by sweeping the servo back and forth detecting each edge of the object.
