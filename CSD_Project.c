#include <stdio.h>
#include<string.h>
#include <stdlib.h>

//storing multiple data in the form of structures for convieience 
typedef struct flight{
    char name[80];
    char start[50];
    char destination[50];
    int seat_capacity;
    int seat_availability;
}flight;

typedef struct passenger{
    char name[80];
    long ph_number;
    int age;
    int PNR;
    char flight_name[50];
    int flight_number;
}passengers;
//flight_number is a connector between the passenger and the flight which is booked


//defining global arrays
flight *flight_details=NULL;
passengers *passenger_details=NULL;

//defining global variables
int PNR_initial=234543;
int passengerCount = 0;
int Emp_Code=20241129;
int Flightcount=0;
int passenger_count=0;


//Making seperate functions to complete the tasks so that it's more efficient:

void view_all_flights(flight flight_details[], int flightCount){
    printf("These are our available Flights:\n");
    for (int i = 0; i < flightCount; i++) {
        printf("%d. Name: %s, Start: %s, Destination: %s, Seats Available: %d\n",
               i + 1, flight_details[i].name, flight_details[i].start,flight_details[i].destination,flight_details[i].seat_availability);
    }
}

void bookflight(flight flight_details[],passengers **passenger_details,int *passenger_count,int Flightcount,int *PNR_initial){
    int serialnum,num_passengers;//Defined some local variables

    view_all_flights(flight_details,Flightcount);
    printf("\n\n");
    //Printing the details of the flights for the passenger to choose from

    printf("Enter the serial number of the flight you want to Book");
    scanf("%d",&serialnum);

    if (serialnum>=1 && serialnum<=Flightcount){

        printf("Enter the number of tickets you want to book: ");
        scanf("%d",&num_passengers);
        printf("\n");

        //checking if enough seats are available on the desired flight. 
        if (num_passengers<=flight_details[serialnum-1].seat_availability){
            
            passengers temp;

            for (int i=0;i<num_passengers;i++){
                int p=20-flight_details[serialnum-1].seat_availability;//index at which the passenger details will be stored

                //Taking input of the passenger details
                printf("Enter the name of Passenger %d: ",i+1);
                scanf(" %[^\n]s",temp.name);

                printf("Enter the phone number of Passenger %d: ",i+1);
                scanf("%ld",&temp.ph_number);

                printf("Enter the age of Passenger %d: ",i+1);
                scanf("%d",&temp.age);
                printf("\n");

                temp.PNR=*PNR_initial;
                temp.flight_number=serialnum;                
                strcpy(temp.flight_name,flight_details[serialnum-1].name);
                    
            
                if (*passenger_count==0){
                    *passenger_details=(passengers*)malloc(sizeof(passengers));
                }
                else{
                    *passenger_details=(passengers*)realloc(*passenger_details,(*passenger_count+1)*sizeof(passengers));
                    }

                (*passenger_details)[*passenger_count]=temp;
                (*passenger_count)++;

        
                flight_details[serialnum-1].seat_availability--;//Decreaing the number of available seats in the desired flight after the booking is done
            }
        }

        printf("Booking Confirmed!!\nYour PNR number is %d\n\n",*PNR_initial);
        (*PNR_initial)++;
        //PNR_initial is incremented to give different PNR_number for the next booking
        
    }
    else{
        printf("Sorry we don't have enough seats!\n\n\n");
    }
}

void cancel_flight(flight flight_details[],passengers passenger_details[],int *passenger_count){
    int pnr,start,num=0;//Declaring some local variables

    printf("Enter Your PNR number:");
    scanf("%d",&pnr);
    printf("\n");

    //checking the number of passengers in the with the given PNR and generating the index of the last passenger with the same PNR
    for (int i=0;i<(*passenger_count);i++){
        if (passenger_details[i].PNR==pnr){
            start=i;
            num++; 
        }
    }
    start=start-num+1;
    if (num==1){
        int confirm;//Declaring a local variable
        
        //Asking for confirmation to cancel the bookings
        printf("\n");
        printf("Press 1 if you want to cancel the following booking\nName:%s\nPhone Number:%ld\nAge:%d\nFlight Name:%s\nFlight Number:%d\n",passenger_details[start].name,passenger_details[start].ph_number,passenger_details[start].age,passenger_details[start].flight_name,passenger_details[start].flight_number);
        scanf("%d",&confirm); 

        //Changing the indices of the next bookings after the confirmation is received and adding one seat to the number of seats available for each cancelation
        if (confirm == 1){
            for(int j=start+1;j<(*passenger_count);j++){
                passenger_details[j-1]=passenger_details[j];
            }
            flight_details[passenger_details[start].flight_number-1].seat_availability++;
            (*passenger_count)--;
        }
    }
    else if (num==0){
        printf("You don't have any bookings with this PNR number");
    }
    else if(num){
        int confirm,c1;//Declaring some local variables

        //Asking if all the tiv=ckets are to be cancelled
        printf("\n");
        printf("You have %d bookings\n Press 1 if you want to cancel all of them",num);
        scanf("%d",&confirm);

        //Printing the details of the passengers whose tickets are booked with that PNR and confirming if all are to be cancelled
        if(confirm == 1 ){
            for (int j=0;j<num;j++){
                printf("Passenger %d\nName:%s\nPhone Number:%ld\nAge:%d\nFlight Name:%s\nFlight Number:%d\n\n",j+1,passenger_details[start+j].name,passenger_details[start+j].ph_number,passenger_details[start+j].age,passenger_details[start+j].flight_name,passenger_details[start+j].flight_number);
            }
            printf("\n");
            printf("Press 1 for confirmation to cancel tickets for the above passengers");
            scanf("%d",&c1);
            printf("\n");

            //Shifting the details of the next passengers to previous indices according to the number of tickets that were cancelled and also increasing the number of seats available in that flight
            if (c1 == 1 ){
                for(int j=start+1;j<(*passenger_count);j++){
                    passenger_details[j-num]=passenger_details[j];
                }
                flight_details[passenger_details[start].flight_number-1].seat_availability+=num;
                (*passenger_count)-=num;
            }
        }

        //Code snippet to delete only specific passengers with the given PNR number
        else{
            int num2=0;
            int w=passenger_details[start].flight_number-1;

            //Printing the details of passengers, asking for confirmation, changing the indices and incrementing the number of availble seats in the given flight one at a time.
            for (int j=0;j<num;j++){

                printf("Passenger %d\nName:%s\nPhone Number:%ld\nAge:%d\nFlight Name:%s\nFlight Number:%d\n\n",j+1,passenger_details[start+num2].name,passenger_details[start+num2].ph_number,passenger_details[start+num2].age,passenger_details[start+num2].flight_name,passenger_details[start+num2].flight_number);
                printf("Do you want to cancel tickets for %s",passenger_details[start+j+num2].name);
                num2++;
                scanf("%d",&c1);
                printf("\n");

                if (c1){
                    num2--;
                    for(int k=start+num2+1;k<(*passenger_count);k++){
                        passenger_details[k-1]=passenger_details[k];
                    }
                flight_details[w].seat_availability++;
                (*passenger_count)--;
                }
            }
        }
    }
    else{
        printf("You don't have any bookings with this PNR Number.\nPlease re-check the number");
        printf("\n");
    }
}

void update_info(passengers passenger_details[], int passengerCount) {
    int pnr;
    printf("Enter the PNR of the passenger to update: ");
    scanf("%d", &pnr);
    printf("\n\n");

    int found=0;
    for (int i = 0; i < passengerCount; i++) {
        if (passenger_details[i].PNR == pnr) {
            printf("Passenger found: %s\n, Age: %d\n, Phone: %ld\n\n", passenger_details[i].name, passenger_details[i].age, passenger_details[i].ph_number);
            printf("Enter new name: ");
            scanf(" %[^\n]s", passenger_details[i].name);
            printf("Enter new age: ");
            scanf("%d", &passenger_details[i].age);
            printf("Enter new phone number: ");
            scanf("%ld", &passenger_details[i].ph_number);
            printf("\n");
            printf("Information updated successfully!\n");
            found++;
        }
        else{
            if (found){
                return;
            }
        }
    }
    printf("Passenger with PNR %d not found, Please recheck and try again.\n", pnr);
}

void viewpassengers(flight flight_details[], passengers passenger_details[], int passengerCount, int flightID) {
    printf("Passengers for Flight %s:\n\n", flight_details[flightID - 1].name);
    for (int i = 0; i < passengerCount; i++) {
        if (passenger_details[i].flight_number == flightID) {
            printf("Name: %s, Age: %d, Phone: %ld, PNR: %d\n",
                   passenger_details[i].name, passenger_details[i].age, passenger_details[i].ph_number, passenger_details[i].PNR);
        }
    }
}  


void Add_Flight(flight **flight_details,int admin_code,int *Flightcount){
    int code;
    printf("Enter the admin code:");
    scanf("%d",&code);
    printf("\n");

    if (code==admin_code){
        flight temp;

        printf("Enter the Name of the Filght:");
        scanf("%s",temp.name);
        printf("Enter the start Location:");
        scanf("%s",temp.start);
        printf("Enter the Destination:");
        scanf("%s",temp.destination);
        printf("Enter the Seat Capacity:");
        scanf("%d",&temp.seat_capacity);
        temp.seat_availability=temp.seat_capacity;
        //Storing the data into a variable temp

        //Using Dynamic Memory Allocation
        if (*Flightcount==0){
            *flight_details=(flight*)malloc(sizeof(flight));
        }
        else{
            *flight_details=(flight*)realloc(*flight_details,(*Flightcount+1)*sizeof(flight));
        }
        (*flight_details)[*Flightcount]=temp;
        (*Flightcount)++;
        printf("\n");
        printf("Flight added Successfully!!");

        //Using File handling to make permanent changes in the text file
        FILE *fptr;
        fptr=fopen("Flight_details.txt","a+");
        
        if (fptr==NULL){
            printf("The file is not opened");
        }
        else{
            
            fprintf(fptr, "%s %s %s %d %d\n",temp.name,temp.start,temp.destination,temp.seat_capacity,temp.seat_availability);
            fclose(fptr);
        }
    
    }
    else{
        printf("You are not authorised to make changes to the Flights");
        printf("\n");
    }
    
}

void all_flights(flight **flight_details,int *Flightcount) {
    //Using file handling to access the file data from a text file
    FILE *fptr;
    fptr=fopen("Flight_details.txt","r");
    if (fptr==NULL){
        printf("The file is not opened");
    }
    else{
        flight temp;
        while (fscanf(fptr, "%s %s %s %d %d",temp.name,temp.start,temp.destination,&temp.seat_capacity,&temp.seat_availability) == 5) { 
            if (*Flightcount==0){
                *flight_details=(flight*)malloc(sizeof(flight));
            }
            else{
                *flight_details=(flight*)realloc(*flight_details,(*Flightcount+1)*sizeof(flight));
            }
            (*flight_details)[*Flightcount]=temp;
            (*Flightcount)++;
        }
        fclose(fptr);
    }
    

}

void all_passengers(passengers **passenger_details,int *passenger_count) {
    //Using file Handling to access the passenger data stored in a text file
    FILE *fptr;
    fptr=fopen("Passenger_details.txt","a+");
    if (fptr==NULL){
        printf("No Such Data Exists");
    }
    else{
        passengers temp;
        while (fscanf(fptr, "%s %ld %d %d %s %d",temp.name,&temp.ph_number,&temp.age,&temp.PNR,temp.flight_name,&temp.flight_number) == 6) 
        { 
            if (*passenger_count==0){
                *passenger_details=(passengers*)malloc(sizeof(passengers));
            }
            else{
                *passenger_details=(passengers*)realloc(*passenger_details,(*passenger_count+1)*sizeof(passengers));
            }

            (*passenger_details)[*passenger_count]=temp;
            (*passenger_count)++;
        }
        //Used variable temp to temporarily store the data and also made use of Dynamic Memory Allocation

        fclose(fptr);
    }

}

void Permanent_Change(passengers passenger_details[],int passenger_count,flight flight_details[],int Flightcount){

    //Using file handling method to permanently store the data  present in passenger_details[] and flight_details[]

    FILE *fptrflight;
    fptrflight=fopen("Flight_details.txt","w");
        
    if (fptrflight==NULL){
        printf("The file is not opened");
    }
    else{
        for(int i=0;i<Flightcount;i++){
            fprintf(fptrflight, "%s %s %s %d %d\n",flight_details[i].name,flight_details[i].start,flight_details[i].destination,flight_details[i].seat_capacity,flight_details[i].seat_availability);
        }
        fclose(fptrflight);
            
    }

    FILE *fptrpassengeer;
    fptrpassengeer=fopen("Passenger_details.txt","w");
    if (fptrpassengeer==NULL){
        printf("The file is not opened");
    }
    else{
        for(int i=0;i<passenger_count;i++){
            fprintf(fptrpassengeer, "%s %ld %d %d %s %d\n",passenger_details[i].name,passenger_details[i].ph_number,passenger_details[i].age,passenger_details[i].PNR,passenger_details[i].flight_name,passenger_details[i].flight_number);
        }
        fclose(fptrpassengeer);
            
    }


}
//Main body of the function that appears to the user:
int main()
{
    int task;

    all_flights(&flight_details,&Flightcount);
    all_passengers(&passenger_details,&passenger_count);
    if (passenger_count){
        PNR_initial=passenger_details[passenger_count-1].PNR+1;    
    }
    printf("\nHello welcome to our Flight Reservation System, let us know how we can help you today!!\n");

    do
    {
        printf("\n1. View all Flights\n2. Book Tickets\n3. View Passengers\n4. Update your exsisting information\n5.Cancel Flight\n6.Add Flight\n7.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &task);
        printf("\n");
    
    switch(task)
    { 
        case 1:
            view_all_flights(flight_details,Flightcount);
            break;

        case 2: 
            bookflight(flight_details, &passenger_details,&passenger_count,Flightcount,&PNR_initial);
            break;

        case 3:
            int flightID;
            printf("Please enter your FlightID: ");
            scanf("%d", &flightID);
            viewpassengers(flight_details, passenger_details, passenger_count, flightID);
            break;

        case 4:
            update_info(passenger_details, passenger_count);
            break;

        case 5:
            cancel_flight(flight_details,passenger_details,&passenger_count);
            break;
        
        case 6:
            Add_Flight(&flight_details,Emp_Code,&Flightcount);
            break;

        case 7:
            Permanent_Change(passenger_details,passenger_count,flight_details,Flightcount);
            printf("Glad we could be of help, have a happy journey.\n Sucessfully exited.\n");
            break;

        default:
            printf("Invalid input, please try again.\n");
        
    }
    }
    while(task!=7);

    free(flight_details);
    free(passenger_details);

    return 0;
}