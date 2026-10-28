#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define MAX_SERVICES 500

// Structure for customer details
struct Customer {
    int customerId;
    char customerName[100];
    char phoneNumber[20];
};

// Structure for vehicle details
struct Vehicle {
    int customerId;
    char vehicleNumber[30];
    char vehicleModel[50];
};

// Structure for service details
struct Service {
    int customerId;
    char serviceType[50];
    double partsCost;
    double labourCharges;
    double totalBill;
};

// Arrays to store records
struct Customer customers[MAX_CUSTOMERS];
struct Vehicle vehicles[MAX_CUSTOMERS];
struct Service services[MAX_SERVICES];

int customerCount = 0;
int serviceCount = 0;

// Function declarations
void registerCustomer();
void displayAllCustomers();
void addService();
void displayCustomerDetails();

struct Customer* findCustomer(int id);

void displayBill(struct Customer *c,
                 struct Vehicle *v,
                 struct Service *s);

// Read a string
void readString(char str[], int size) {
    fgets(str, size, stdin);

    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

// Read an integer
int readInt() {
    int value;

    scanf("%d", &value);

    while (getchar() != '\n');

    return value;
}

// Read a non-negative amount
double readAmount(char message[]) {
    double amount;

    do {
        printf("%s", message);
        scanf("%lf", &amount);

        while (getchar() != '\n');

        if (amount < 0) {
            printf("Amount must be non-negative.\n");
        }

    } while (amount < 0);

    return amount;
}

// Find customer using ID
struct Customer* findCustomer(int id) {
    int i;

    for (i = 0; i < customerCount; i++) {
        if (customers[i].customerId == id) {
            return &customers[i];
        }
    }

    return NULL;
}


//check Phone Number
int checkPhoneNumber(char phone[]){
     int sizeOfPhoneNumber = strlen(phone);

    // Check length
    if (sizeOfPhoneNumber != 10) {
        return 0;
    }

    // Check digits
    for (int i = 0; i < sizeOfPhoneNumber; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }

    return 1;
}

//check vehicle Number
int checkVehicleNumber(char vehicleNumber[],int n){

    int totalChar = 0;

    for(int i=0;i<n;i++){
        if(vehicleNumber[i] == '\0') break;
        if(vehicleNumber[i] >= 'a' && vehicleNumber[i] <='z'){
            vehicleNumber[i] = vehicleNumber[i] - 32;
        }
        totalChar++;
    }

    if(totalChar != 10){
        return 0;
    }

    if(vehicleNumber[0] < 'A' || vehicleNumber[0] >'Z') return 0;
    if(vehicleNumber[1] < 'A' || vehicleNumber[1] >'Z') return 0;
    if(vehicleNumber[2] < '0' || vehicleNumber[2] >'9') return 0;
    if(vehicleNumber[3] < '0' || vehicleNumber[3] >'9') return 0;
    if(vehicleNumber[4] < 'A' || vehicleNumber[4] >'Z') return 0;
    if(vehicleNumber[5] < 'A' || vehicleNumber[5] >'Z') return 0;
    if(vehicleNumber[6] < '0' || vehicleNumber[6] >'9') return 0;
    if(vehicleNumber[7] < '0' || vehicleNumber[7] >'9') return 0;
    if(vehicleNumber[8] < '0' || vehicleNumber[8] >'9') return 0;
    if(vehicleNumber[9] < '0' || vehicleNumber[9] >'9') return 0;
    
    // Check for duplicate vehicle number
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(vehicles[i].vehicleNumber,
                   vehicleNumber) == 0) {
            return 2;
        }
    }

    return 1;
}

// 1. Register customer
void registerCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Customer limit reached.\n");
        return;
    }

    char name[100];
    char phone[20];
    char vehicleNumber[30];
    char vehicleModel[50];

    printf("\n===== CUSTOMER REGISTRATION =====\n");

    printf("Enter customer name: ");
    readString(name, sizeof(name));

    if (name[0] == '\0') {
        printf("Customer name cannot be empty.\n");
        return;
    }

    printf("Enter phone number: ");
    readString(phone, sizeof(phone));

    
    if (phone[0] == '\0') {
        printf("\nPhone number cannot be empty.\n");
        return;
    }

    //Validation for phone number
    int phoneNumberValidation = checkPhoneNumber(phone);

    if(phoneNumberValidation == 0){
        printf("\nGiven phone number is Invalid.\n");
        return;
    }
    else if(phoneNumberValidation == 2){
        printf("\nDuplicate phone number found.\n");
        return;
    }
   
    printf("Enter vehicle number: ");
    readString(vehicleNumber, sizeof(vehicleNumber));

    if (vehicleNumber[0] == '\0') {
        printf("\nVehicle number cannot be empty.\n");
        return;
    }


    //check for the invalid vehicle number
    int n = sizeof(vehicleNumber)/sizeof(vehicleNumber[0]);
    int vehicleValidation = checkVehicleNumber(vehicleNumber,n);
    if(vehicleValidation == 0){
        printf("\nInvalid Vehicle Number.\n");
        return;
    }else if(vehicleValidation == 2){
        printf("\nThis vehicle is already registered.\n");
        return;
    }


    printf("Enter vehicle model: ");
    readString(vehicleModel, sizeof(vehicleModel));

    if (vehicleModel[0] == '\0') {
        printf("Vehicle model cannot be empty.\n");
        return;
    }

    // Store customer details
    customers[customerCount].customerId = customerCount + 1;

    int id = customers[customerCount].customerId;

    int j = 0;
    while (name[j] != '\0') {
        customers[customerCount].customerName[j] = name[j];
        j++;
    }
    customers[customerCount].customerName[j] = '\0';

    j = 0;
    while (phone[j] != '\0') {
        customers[customerCount].phoneNumber[j] = phone[j];
        j++;
    }
    customers[customerCount].phoneNumber[j] = '\0';

    // Store vehicle details
    vehicles[customerCount].customerId = id;

    j = 0;
    while (vehicleNumber[j] != '\0') {
        vehicles[customerCount].vehicleNumber[j] = vehicleNumber[j];
        j++;
    }
    vehicles[customerCount].vehicleNumber[j] = '\0';

    j = 0;
    while (vehicleModel[j] != '\0') {
        vehicles[customerCount].vehicleModel[j] = vehicleModel[j];
        j++;
    }
    vehicles[customerCount].vehicleModel[j] = '\0';

    customerCount++;

    printf("\nCustomer registered successfully!\n");
    printf("Customer ID: %d\n", id);
}

// 2. Display all customers
void displayAllCustomers() {
    if (customerCount == 0) {
        printf("No customers registered.\n");
        return;
    }

    printf("\n===== ALL CUSTOMERS =====\n");

    int i, j;

    for (i = 0; i < customerCount; i++) {
        int total = 0;

        printf("\nCustomer ID: %d\n", customers[i].customerId);
        printf("Name: %s\n", customers[i].customerName);
        printf("Phone: %s\n", customers[i].phoneNumber);

        printf("Vehicle Number: %s\n",
               vehicles[i].vehicleNumber);

        printf("Vehicle Model: %s\n",
               vehicles[i].vehicleModel);

        for (j = 0; j < serviceCount; j++) {
            if (services[j].customerId == customers[i].customerId) {
                total++;
            }
        }

        printf("Total Services: %d\n", total);
    }
}

// 3. Add a service
void addService() {
    if (customerCount == 0) {
        printf("Register a customer first.\n");
        return;
    }

    if (serviceCount >= MAX_SERVICES) {
        printf("Service limit reached.\n");
        return;
    }

    printf("Enter customer ID: ");
    int id = readInt();

    struct Customer *c = findCustomer(id);

    if (c == NULL) {
        printf("Customer not found.\n");
        return;
    }

    printf("\n===== SELECT SERVICE =====\n");
    printf("1. General Service - Rs. 500 labour\n");
    printf("2. Oil Change - Rs. 300 labour\n");
    printf("3. Engine Repair - Rs. 1500 labour\n");
    printf("4. Brake Service - Rs. 700 labour\n");
    printf("Enter service choice: ");

    int choice = readInt();

    switch (choice) {
        case 1:
            sprintf(services[serviceCount].serviceType,
                    "General Service");
            services[serviceCount].labourCharges = 500;
            break;

        case 2:
            sprintf(services[serviceCount].serviceType,
                    "Oil Change");
            services[serviceCount].labourCharges = 300;
            break;

        case 3:
            sprintf(services[serviceCount].serviceType,
                    "Engine Repair");
            services[serviceCount].labourCharges = 1500;
            break;

        case 4:
            sprintf(services[serviceCount].serviceType,
                    "Brake Service");
            services[serviceCount].labourCharges = 700;
            break;

        default:
            printf("Invalid service choice.\n");
            return;
    }

    services[serviceCount].customerId = id;

    services[serviceCount].partsCost =
        readAmount("Enter spare parts cost (Rs.): ");

    services[serviceCount].totalBill =
        services[serviceCount].partsCost +
        services[serviceCount].labourCharges;

    serviceCount++;

    printf("\nService added successfully!\n");

    // Display the bill for the latest service
    displayBill(c, &vehicles[id - 1], &services[serviceCount - 1]);
}

// 4. Display bill
void displayBill(struct Customer *c,
                 struct Vehicle *v,
                 struct Service *s) {

    printf("\n========== SERVICE BILL ==========\n");

    printf("Customer ID: %d\n", c->customerId);
    printf("Customer Name: %s\n", c->customerName);
    printf("Phone Number: %s\n", c->phoneNumber);

    printf("Vehicle Number: %s\n", v->vehicleNumber);
    printf("Vehicle Model: %s\n", v->vehicleModel);

    printf("----------------------------------\n");
    printf("Service Type: %s\n", s->serviceType);
    printf("Parts Cost: Rs. %.2f\n", s->partsCost);
    printf("Labour Charges: Rs. %.2f\n", s->labourCharges);
    printf("----------------------------------\n");
    printf("TOTAL BILL: Rs. %.2f\n", s->totalBill);
    printf("==================================\n");
}

// 5. Display customer service history
void displayCustomerDetails() {
    if (customerCount == 0) {
        printf("No customers registered.\n");
        return;
    }

    printf("Enter customer ID: ");
    int id = readInt();

    struct Customer *c = findCustomer(id);

    if (c == NULL) {
        printf("Customer not found.\n");
        return;
    }

    struct Vehicle *v = &vehicles[id - 1];

    printf("\n===== CUSTOMER SERVICE HISTORY =====\n");
    printf("Customer ID: %d\n", c->customerId);
    printf("Customer Name: %s\n", c->customerName);
    printf("Phone Number: %s\n", c->phoneNumber);
    printf("Vehicle Number: %s\n", v->vehicleNumber);
    printf("Vehicle Model: %s\n", v->vehicleModel);

    int i;
    int found = 0;
    double totalAmount = 0;

    for (i = 0; i < serviceCount; i++) {
        if (services[i].customerId == id) {
            found = 1;

            printf("\nService Record #%d\n", i + 1);
            printf("Service Type: %s\n",
                   services[i].serviceType);
            printf("Parts Cost: Rs. %.2f\n",
                   services[i].partsCost);
            printf("Labour Charges: Rs. %.2f\n",
                   services[i].labourCharges);
            printf("Total Bill: Rs. %.2f\n",
                   services[i].totalBill);

            totalAmount += services[i].totalBill;
        }
    }

    if (found == 0) {
        printf("No services recorded for this customer.\n");
        return;
    }

    printf("----------------------------------\n");
    printf("TOTAL OF ALL SERVICES: Rs. %.2f\n", totalAmount);
    printf("==================================\n");
}

// Main function
int main() {
    int choice;

    do {
        printf("\n===== VEHICLE SERVICE MANAGEMENT SYSTEM =====\n");
        printf("1. Register Customer\n");
        printf("2. Display All Customers\n");
        printf("3. Add Vehicle Service\n");
        printf("4. Generate Bill / Service History\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        choice = readInt();

        switch (choice) {
            case 1:
                registerCustomer();
                break;

            case 2:
                displayAllCustomers();
                break;

            case 3:
                addService();
                break;

            case 4:
                displayCustomerDetails();
                break;

            case 5:
                printf("Thank you for using the system!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    return 0;
}
