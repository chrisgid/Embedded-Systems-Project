#include "math.h"
#include "string.h"
#include "mylpclib.h"

double sobelOut[80];
double edgesOut[80];

//Print array Q to UART for testing purposes
//newline = 1 to print each element on a new line
void printArray(double *Q, int elems, int newline){
    int i;
    char mystring[50] = "";

    sprintf(mystring, "\r\n\n");
    sendUART(mystring);

    for(i = 0; i < elems; i++){
        if(newline == 1){
            sprintf(mystring, "\r\nElem[%i]: %.1f", i, Q[i]);
	        sendUART(mystring);
        }else {
            sprintf(mystring, " Elem[%i]: %.1f", i, Q[i]);
	        sendUART(mystring);
        }
    }
}

//Sets element values to left of index to same value as index
void setLeft(double *Q, int elems, int index){
    int i;
    double val = Q[index];
    for(i = (index - 1); i > -1; i--){
        Q[i] = val;
    }
}

//Sets element values to right of index to same value as index
void setRight(double *Q, int elems, int index){
    int i;
    double val = Q[index];
    for(i = (index + 1); i < elems; i++){
        Q[i] = val;
    }
}


//Apply a 1D kernel to a 1D array (sobel)
//Q: Array for , elems: elements in Q
void sobel1D(double *Q, int elems){
    int kernel[3] = {-1, 0, 1};
    int i, j, kmiddle;
    int ksize = sizeof(kernel)/sizeof(kernel[0]);
    double total;

    kmiddle = 1; //Middle of kernel (0-2)

    for(i = 0; i < elems; i++){
        total = 0;

        if(i == 0){ //for first element
            total = 0;
        }else if(i == (elems - 1)){ //for last element
            total = 0;
        }else { //other elements
            for(j = 0; j < ksize; j++){
                total += (kernel[j] * Q[i+j-1]);
            }
        }

        sobelOut[i-1+kmiddle] = total;
    }
}


//Find edges in an array using a threshold and thin to 1 'pixel' thickness
//Requires soble1D()
void edges(double *Q, int elems, int threshold){
    int i;
    double diff;

    sobel1D(Q, elems);  //calcs sobel for Q and puts in sobelOut

    for(i = 0; i < (elems - 1); i++){
        diff = fabs(sobelOut[i] - sobelOut[i+2]);   //fabs() requires math.h
        //fabs() returns absolute val of double
        if (diff >= threshold){
            edgesOut[i + 1] = 1;   //edge here
        } else {
            edgesOut[i+1] = 0;   //no edge here
        }
    }
    thinEdges(elems);
}

//Thin edges in edgesOut to 1 'pixel' thickness
void thinEdges(int elems){
    int i,j;
    int startOfEdge, endOfEdge, widthOfEdge, middleOfEdge;

    for(i = 0; i < (elems - 1); i++){     //for each element

        if(edgesOut[i] == 1){         //if an edge found

            startOfEdge = i;
            j = startOfEdge;

            while(edgesOut[j] == 1){  //find last in sequence of edges
                endOfEdge = j;
                j++;
            }

            widthOfEdge = endOfEdge - startOfEdge + 1; //'width' of edge

            if(widthOfEdge > 1){ //if width of edge is more than 1

                middleOfEdge = startOfEdge - 1  + ((widthOfEdge + 1) / 2);

                for(j = startOfEdge; j < (endOfEdge + 1); j++){

                    if(j != middleOfEdge){
                        edgesOut[j] = 0;
                    }

                }
            }
        }
    }
}

//Returns 1 if edge at Q[index]
int isEdge(double *Q, int index){
    if(Q[index] == 1){
        return 1;
    }
    return 0;
}

//Returns 1 if edge in range of specified indexes in array Q
int isEdgeInRange(double *Q, int startIndex, int endIndex){
    int i, temp;

    if(startIndex > endIndex){//Swap values if start > end
        temp = startIndex;
        startIndex = endIndex;
        endIndex = temp;
    }

    for(i = startIndex; i < endIndex; i++){
        if(isEdge(Q, i) == 1){
            return 1;
        }
    }
    return 0;
}

//Find the initial distance of the object for tracking
double findObject(void){
    char button;

    initServo(1);
    setServo(40);       //initialse and set servo to middle position

    while(1){
        button = KeypadTest();            //Wait for # as keypad input
        if(button == '#'){
            break;
        }
    }

    return irMedian();    //return distance of the object
}

//Start tracking mode
void trackingMode(int threshold){
    const int LEFT = 1;
    const int RIGHT = -1;
    const int NONE = 0;

    double sweep[80];

    int delay, edge, sweepdir, edgerange, servopos, i;

    sweep[40] = findObject();         //Get start distance from findObject

    sweepdir = LEFT;                //Set inital sweep direction to left
    edge = NONE;                    //Not at edge at start
    delay = 25;                     //systicktimer delay
    edgerange = 2;                  //range to check for edges in

    //Do 1 full sweep and record before starting tracking
    setServo(0);
    SystickTimer(delay * 5);

    for(i = 0; i < 80; i++){
        setServo(i);
        SystickTimer(delay);
        sweep[i] = irMedian();
    }

    edges(sweep, 80, threshold);   //find edges in sweep

    //Set servo to middle postition
    setServo(40);
    SystickTimer(delay * 5);

    //START TRACKING LOOP
    while(1){

		//Not at edge
        if(edge == NONE){
			
			//Left sweep
            if(sweepdir == LEFT){
                turnServo(LEFT);
                servopos = servoPosition();
                SystickTimer(delay);
                sweep[servopos] = irMedian();

                setRight(sweep, 80, servopos);
                edges(sweep, 80, threshold);

                if(isEdgeInRange(edgesOut, servopos, (servopos - edgerange))){
                    edge = LEFT;
                }else if(servoAtEdge() == 1){ //If at edge of scan range, change direction
                    sweepdir = RIGHT;
                    setLeft(sweep, 80, servopos);
                }

			//Right Sweep
            }else if(sweepdir == RIGHT){

                turnServo(RIGHT);
                servopos = servoPosition();
                SystickTimer(delay);
                sweep[servopos] = irMedian();

                setLeft(sweep, 80, servopos);
                edges(sweep, 80, threshold);

                if(isEdgeInRange(edgesOut, servopos, (servopos + edgerange))){
                    edge = RIGHT;
                } else if(servoAtEdge() == 1){ //If at edge of scan range, change direction
                    sweepdir = LEFT;
                    setRight(sweep, 80, servopos);
                }
            }
		
		//Found left edge with left sweepdir
        }else if(edge == LEFT && sweepdir == LEFT){

            sweepdir = RIGHT;
            edge = NONE;

            for(i = 0; i < edgerange * 2; i++){
                turnServo(RIGHT);
                servopos = servoPosition();
                SystickTimer(delay);
                sweep[servopos] = irMedian();
            }

            setRight(sweep, 80, servopos);
            edges(sweep, 80, threshold);

		//Found right edge with right sweepdir
        }else if(edge == RIGHT && sweepdir == RIGHT){

            sweepdir = LEFT;
            edge = NONE;

            for(i = 0; i < edgerange * 2; i++){
                turnServo(LEFT);
                servopos = servoPosition();
                SystickTimer(delay);
                sweep[servopos] = irMedian();
            }

            setLeft(sweep, 80, servopos);
            edges(sweep, 80, threshold);
        }
    }
}
