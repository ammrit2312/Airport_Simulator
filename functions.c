#include<stdio.h>
#include<unistd.h>//for time delay
#include<time.h>
#include<stdlib.h>

/*After each iteration of the loop the program pauses for 10 seconds. Moreover our program runs just for 12 iterations.*/


//This structure will store details of the airplanes used for landing and takeoff
typedef struct Airplane{
    int id;         //this will store the plane number
    //char name[100];
    struct Airplane * next;
}airplane;

/*Function Declaration*/
void plane_add(airplane * flight101, int number);
int length(airplane * flight101);
int plane_delete(airplane ** flight101);
void airport();

//this will help us find the length till the last node of the structure
int length(airplane * flight101){

    int count = 0;
    airplane * current = flight101;     //flight101->next;

    while(current->next != NULL){
        //if we don't get next of a pointer as NULL till then we will reassign it
        count++;
        current = current->next;
    }

    return count;
}

//this function works on adding flight numbers to different structs we made
void plane_add(airplane * flight101, int number){

    airplane * current = flight101;

    while(current->next != NULL){
        current = current->next;
    }

    current->next = malloc(sizeof(airplane));
    current->next->id = number;
    current->next->next = NULL;
    //putting values into the last node
}

//this function works on deleting the first flight from different structs and return its id
int plane_delete(airplane ** flight101){
    //-1 will be returned if 1st is only NULL
    int plane_no = -1;
    airplane * next_plane = NULL;

    if(*flight101 == NULL){
        return -1;
    }
    
    //this will take in the flight number and assigned then to the head and then free head
    next_plane = (*flight101)->next;
    plane_no = (*flight101)->id;
    free(*flight101);
    *flight101 = next_plane;

    return plane_no;

}

//this function will do all the initial work and call all the different functions and also print the required statements
void airport(){
    int takeoff = 0;    //these two variables will keep the count of the number of airplanes
    int landing = 0;
 

    //this is the declaration of takeoff structre
    airplane * takeoff_queue = malloc(sizeof(airplane));
    takeoff_queue->id = (rand()%(500-100+1))+100;
    
    
    //this is the declaration of landing structre
    airplane * landing_queue = malloc(sizeof(airplane));
    landing_queue->id = (rand()%(500-100+1))+100;

    srand(time(NULL));//necessary for making the random values different everytime
    
    //inputting the first value
    int plane_no = (rand()%(500-100+1))+100;
    
    //now inputting the values keeping in mind that the total number of planes in the
    //takeoff_queue for one time can only be 10 same for landing_queue
    for(int start = 0; start<(rand()%10); start++){
        //printf("%d\n",rand()%10);
        plane_add(takeoff_queue, plane_no);
        plane_no = (rand()%(500-100+1))+100;
    } 
    //random numbers generated are between 100 & 500 (these will act as flight numbers)
    for(int start = 0; start<(rand()%10); start++){

        plane_add(landing_queue, plane_no);
        plane_no = (rand()%(500-100+1))+100;
    }

    //starting of the main part of the program
    int count = 0;
    printf("\n\nWelcome to the Labyrinth\n\n");
    //keeping Labyrinth as the name of the airport
    
    //our simulation runs 12 times only and with 10 seconds gap between each simulation
    while(count<=12){

        //taking the condition when the landing_queue is NULL or of length 1 o then only 1 runway will be used for landing so 2 for takeoff
        if(landing_queue==NULL || length(landing_queue)==1 ){
            //dealing with ony takeoff right now all cases re being considered according to what to be printed
            printf("Departures:\n----------\n\n");
            //printf("%d\n",length(takeoff_queue));
            if(length(takeoff_queue)>0){
                takeoff+=1;
                //if >0 then at least one takeoff takes place
                int length_takeoff_queue = length(takeoff_queue);//this will help to check conditions later
                int number_takeoff = plane_delete(&takeoff_queue);
                printf("The Flight Departing right now is Flight #%d.\n\n",number_takeoff);
                if(length_takeoff_queue>=2){
                    takeoff+=1;
                    //this time as it is greater than 2 or equal to it then one more takesoff
                    number_takeoff = plane_delete(&takeoff_queue);
                    printf("The Flight Departing right now is Flight #%d.\n\n",number_takeoff);
                    //more information is filed on the basis of structure size
                    if(length_takeoff_queue==3){
                        printf("Departure Updates:\nFlight Number #%d is now Boarding.\nPlease Get to your respective Gates.\n",takeoff_queue->id);
                        printf("No more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                    }
                    else if(length_takeoff_queue>3){
                        printf("Departure Updates:\nFlight Number #%d is now Boarding.\nPlease Get to your respective Gates.\n",takeoff_queue->id);
                        printf("Flight Number #%d is starting Security.\nPlease Get your Securtiy Done.\n\n",takeoff_queue->next->id);
                    }
                    else{
                        printf("Departure Updates:\nNo more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                    }
                }
                else{
                    printf("Departure Updates:\nNo more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                }
            }
            else{
                printf("Departure Updates:\nNo Flight Scheduled for Departure Right Now.\nNew Updates will be provided soon.\n\n");
            }
            
            //for arrival
            printf("Arrivals:\n--------\n\n");
            
            //if NULL then nothing to be landed
            if(landing_queue==NULL){
                printf("No Flight Scheduled for Arrival Right Now.\nNew Updates will be provided soon.\n\n");
            }
            else{
                landing+=1;
                // as even if we have any flight to it won't be more than one because of the condition
                int number_landing = plane_delete(&landing_queue);
                printf("The Flight Arriving Right Now is Flight #%d.\n\n",number_landing);
                printf("Arrival Updates:\nNo more Flights Scheduled for Arrival right now.\nNew Update will be provided soon.\n\n");
            }
        }
        
        //taking the condition here that there is more than 1 flights in the landing_queue
        else {
            printf("Departures:\n----------\n\n");
            if(length(takeoff_queue)>0){
                takeoff+=1;
                //if any takeoff planes then this will be printed
                int length_takeoff_queue = length(takeoff_queue);//this will help to check conditions later
                int number_takeoff = plane_delete(&takeoff_queue);
                printf("The Flight Departing right now is Flight #%d.\n\n",number_takeoff);
                if(length_takeoff_queue>=2){
                    if(length(landing_queue)==0){
                        takeoff+=1;
                        //this makes sure that when landing_queue length is 0 then if takeoff has one more flight then it flows
                        int number_takeoff = plane_delete(&takeoff_queue);
                        printf("The Flight Departing right now is Flight #%d.\n\n",number_takeoff);
                    }
                    if(length(takeoff_queue)>0){
                        //to check if any flight is there then only the next info can be printed
                        printf("Departure Updates:\nFlight Number #%d is now Boarding.\nPlease Get to your respective Gates.\n",takeoff_queue->id);
                        if(length_takeoff_queue>=3){
                            //more flights then another info is printed
                            printf("Flight Number #%d is starting Security.\nPlease Get your Securtiy Done.\n\n",takeoff_queue->next->id);
                        }
                        else {
                            //this information is printed accordingly
                            printf("No more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                        }
                    }
                    else{
                    printf("Departure Updates:\nNo more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                    }
                }
                else{
                    printf("Departure Updates:\nNo more Flights Scheduled for Departure right now.\nNew Update will be provided soon.\n\n");
                }
            }
            else{
                printf("Departure Updates:\nNo Flight Scheduled for Departure Right Now.\nNew Updates will be provided soon.\n\n");
            }
            
            //for arrival
            printf("Arrivals:\n--------\n\n");
            //no flights scheduled for arrival although not required
            if(landing_queue==NULL){
                printf("No Flight Scheduled for Arrival Right Now.\nNew Updates will be provided soon.\n\n");
            }
            else if(length(landing_queue)>0){
                landing+=1;
                //checking of that much flights have requested to land
                int length_landing_queue = length(landing_queue);
                int number_landing = plane_delete(&landing_queue);
                printf("The Flight Arriving Right Now is Flight #%d.\n\n",number_landing);
                if(length_landing_queue>1){
                    landing+=1;
                    //if one more flight can be accomadated
                    int number_landing = plane_delete(&landing_queue);
                    printf("The Flight Arriving Right Now is Flight #%d.\n\n",number_landing);
                    if(length_landing_queue>2){
                        //more updates depending on size of the this structure
                        printf("Arrival Updates:\nFlight #%d will be arriving shortly.\n\n",landing_queue->id);
                    }
                    else{
                        printf("Arrival Updates:\nNo Flight Scheduled for Arrival Right Now.\nNew Updates will be provided soon.\n\n");
                    }
                }
                else{
                    printf("Arrival Updates:\nNo Flight Scheduled for Arrival Right Now.\nNew Updates will be provided soon.\n\n");
                }
            }
            else{
                printf("Arrival Updates:\nNo Flight Scheduled for Arrival Right Now.\nNew Updates will be provided soon.\n\n");
            }
        }
        
        
        //these 2 loops will put new flights to our respective structures
        if(length(takeoff_queue)<10){
            
            //making sure that at a time till only 3 maximum flights can be added so like 0,1,2,3 only these many flights can be added at a time
            for(int count = 0;count<(rand()%4);count++){
                plane_add(takeoff_queue,(rand()%(500-100+1))+100);
            }
        }
        
        //similar for the landing_queue
        if(length(landing_queue)<10){

            for(int count = 0;count<(rand()%4);count++){
                plane_add(landing_queue,(rand()%(500-100+1))+100);
            }
        }
        printf("-------------------------------------------------------------------\n\n");
        count++;
        
        //this will put a sleep of 10 seconds thus pausing the program for 10 seconds before going for another iteration in the loop
        sleep(10);
    }
    //printing of summary
    printf("Summary of Labyrinth:\n\tNumber of Flight Takeoffs:\t%d\n\tNumber of Flights Arrived:\t%d\n\tTotal Number of Flight Activities:\t%d\n\t",takeoff,landing,takeoff+landing);
    printf("Number of Flights left to Takeoff:\t%d\n\tNumber of Flights left to Land:\t%d\n",length(takeoff_queue),length(landing_queue));

}
