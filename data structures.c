#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
// Structure for Car 
typedef struct Car { 
 char registration_number[20];
 struct Car* next;
} Car;
// Structure for Parking Lot 
typedef struct ParkingLot { 
 int capacity;
 int current_parked;
 Car* stack; // Stack for parked cars (Last In, First Out)
 Car* queue; // Queue for waiting cars (First In, First Out)
 Car* parked_cars; // Linked list of parked cars
} ParkingLot;
// Function to create a new car 
Car* create_car(const char* registration_number) { 
 Car* new_car = (Car*)malloc(sizeof(Car));
 strcpy(new_car->registration_number, 
registration_number);
 new_car->next = NULL;
 return new_car;
} 
// Function to initialize the parking lot 
void initialize_parking_lot(ParkingLot* lot, int capacity) { 
 lot->capacity = capacity;
 lot->current_parked = 0;
 lot->stack = NULL;
 lot->queue = NULL;
 lot->parked_cars = NULL;
} 
// Function to park a car 
void park_car(ParkingLot* lot, const char* 
registration_number) { 
 if (lot->current_parked < lot->capacity) { 
 // Create new car and add to stack (last in) 
 Car* new_car = create_car(registration_number);
 new_car->next = lot->stack;
 lot->stack = new_car;
 // Add to the linked list of parked cars 
 new_car->next = lot->parked_cars;
 lot->parked_cars = new_car;
 printf("Car %s parked in the parking lot.\n", 
registration_number);
 lot->current_parked++;
 } else { 
 // If parking lot is full, add car to queue 
 Car* new_car = create_car(registration_number);
 new_car->next = lot->queue;
 lot->queue = new_car;
 printf("Parking lot is full! Car %s added to the queue.\n", 
registration_number);
 } 
} 
// Function to remove a car from the parking lot 
void exit_car(ParkingLot* lot) { 
 if (lot->stack == NULL) { 
 printf("No cars in the parking lot.\n");
 return;
 } 
 // Pop car from stack (last in, first out) 
 Car* car_to_exit = lot->stack;
 lot->stack = lot->stack->next;
 printf("Car %s has exited the parking lot.\n", car_to_exit-
>registration_number);
 // Remove from the linked list of parked cars 
 Car* current = lot->parked_cars;
 if (current != NULL && strcmp(current-
>registration_number, car_to_exit->registration_number) == 
0) { 
 lot->parked_cars = current->next;
 } else { 
 while (current->next && strcmp(current->next-
>registration_number, car_to_exit->registration_number) != 0) 
{ 
 current = current->next;
 } 
 if (current->next) { 
 current->next = current->next->next;
 } 
 } 
 free(car_to_exit);
 lot->current_parked--;
 // If there are waiting cars, park the first car in the queue 
 if (lot->queue != NULL) { 
 Car* waiting_car = lot->queue;
 lot->queue = lot->queue->next;
 printf("Car %s has entered the parking lot from the 
queue.\n", waiting_car->registration_number);
 park_car(lot, waiting_car->registration_number);
 free(waiting_car);
 } 
} 
// Function to display the parked cars 
void display_parked_cars(ParkingLot* lot) { 
 if (lot->parked_cars == NULL) { 
 printf("No cars are parked.\n");
 return;
 } 
 printf("Currently parked cars:\n");
 Car* current = lot->parked_cars;
 while (current != NULL) { 
 printf("Car %s\n", current->registration_number);
 current = current->next;
 } 
} 
// Main function 
int main() { 
 ParkingLot lot;
 initialize_parking_lot(&lot, 3); // Parking lot with 3 spots
 // Test the parking system 
 park_car(&lot, "AB123CD");
 park_car(&lot, "EF456GH");
 park_car(&lot, "IJ789KL");
 // Display currently parked cars 
 display_parked_cars(&lot);
 // Exit a car 
 exit_car(&lot);
 // Park another car after one exits 
 park_car(&lot, "MN012OP");
 // Display currently parked cars again 
 display_parked_cars(&lot);
 // Exit another car 
 exit_car(&lot);
 // Display parked cars 
 display_parked_cars(&lot);
 return 0;
}