![Tec de Monterrey](images/logotecmty.png)
# Problem Statement: Simulation of a Cellular Communication System.

## <span style="color: rgb(26, 99, 169);">What do I need to do?</span>
In this repository, you will find a series of folders and files that you will need for the project development.
* *test_cases*: In this directory, you will find input files (`input0.txt`, `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt`, `input6.txt`) that we will use to test the complete system. Additionally, there are expected outputs for each of the input files (`output0.txt`, `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt`, `output6.txt`).
* *unit_test*: In this directory are the unit test files for each of the classes that you have to develop. These test files allow you to verify if your implementation is correct.
* *header files*: Files in which the implementation of each class is carried out.
* `main.cpp`: File containing the `main` function. File reading/writing is done in this file.

In these files you must develop the implementation of each of the classes that make up the solution to the problem presented in this activity. At the top of each file, you must place your data in comments. For example:
```
// ===========================================================
// File: one_header.h
// Author: Edward Elric - A00123456
// Date: 01/01/2021
// Description: This file implements some functions.
// ===========================================================
```

## <span style="color: rgb(26, 99, 169);">Introduction</span>
As I'm sure you've already heard, we live in a world where technological revolutions happen every day. One of the most important revolutions was, without a doubt, cellular communication systems. In this project, we are going to implement a simple version of a cellular communication system.

In this system there are *customers*, *operators* and *invoices* that belong to a specific customer. Customers can talk to each other, send messages, or connect to the Internet through their mobile devices. Traders have unique costs for all of these actions. Each client will have a single invoice that stores and performs the necessary operations on their expenses.

Your solution will take input from a text file, perform the operations, and print the necessary information to an output text file. The name of both files will be taken as the program argument. In other words, **there will be no input given with the keyboard while the program is running**.

Please note that there will be several classes. Therefore, you will work with several header files. The names of the instance variables and methods will be provided in this document as well as in the class header found in each header file. Although this doesn't mean you can't add additional methods or fields.

### <span style="color: rgb(26, 99, 169);">**Classes**</span>
There are 5 classes interacting with each other in this project:
* `Customer`.
* `Operator`.
* `VoxOperator` (derived from `Operator`).
* `InternetOperator` (derived from `Operator`).
* `Bill`.

Note that it will be necessary to do the necessary calculations by using the corresponding methods in the `Customer`, `Operator` (and derivatives) or `Bill` classes, not in the main program.

#### <span style="color: rgb(26, 99, 169);">**Bill**</span>
The `Bill` class has the following state variables:
* `limitAmount`: Credit limit.
* `currentDebt`: Current debt.
* `totalMoneySpent`: Total money the customer has paid over time.

The class has the following methods:
* Constructor with one parameter (credit limit). This method must initialize the rest of the variables to 0.
* Copy builder.
* Accessor methods for all instance variables. (If you consider it necessary to add modification methods, go ahead).
* `add(double amount)`: Add charges to the invoice. If the quantity is less than or equal to 0, you should not make changes.
* `pay(double amount)`: Reduces the debt by the given amount. If the quantity is less than or equal to 0, you should not make changes. You can never pay more than the current debt.
* `changeTheLimit(double amount)`: Change the credit limit, as long as it is greater than the current debt. If the quantity is less than or equal to 0, you should not make changes.
* `check(double amount)`: Returns true if the amount plus the current debt does not exist the credit limit.

#### <span style="color: rgb(26, 99, 169);">**Operator**</span>
Although there are two types of operators, those that provide greater support for calls and messages (*VOX*) and those that provide greater support for Internet use (*INTERNET*), they all share common characteristics. The `Operator` class defines these characteristics. The state variables it has are:
* `id`: Unique identifier of the operator.
* `discountRate`: Discount percentage to apply.
* `talkingCharge`: The cost per call minute.
* `messageCost`: The cost per message sending.
* `networkCharge`: The cost per GB used.
* `totalSpentTalkingTime`: The total time spent on calls.
* `totalMessageSent`: The total messages that have been sent.
* `totalInternetUsage`: The total GB's used.
* `type`: Type of operator (VOX or INTERNET).

The class has the following methods:
* Constructor with 6 parameters. Receive the ID, the cost per call minute, the cost per message sending, the cost or by GB, the discount percentage and the type of operator. The rest of the variables must be initialized to 0.
* Copy builder.
* Accessor methods for all instance variables. (If you consider it necessary to add modification methods, go ahead).
* `addTalkingTime(int minute)`: If the amount is greater than 0, adds the amount to the total time spent on calls.
* `addTotalMessageSent(int quantity)`: If the quantity is greater than 0, add the quantity to the total messages sent.
* `addTotalInternetUsage(double amount)`: If the amount is greater than 0, add the amount to the total GB's used.
* `toString()`: Returns a string with the following format: "Operator #id : totalSpentTalkingTime totalMessageSent addTotalInternetUsage". All floating point quantities must have a precision of two decimal numbers.
* `virtual double calculateTalkingCost(int, int) = 0;`: Virtual function. It must be implemented in derived classes.
* `virtual double calculateMessageCost(int, int, int) = 0;`: Virtual function. It must be implemented in derived classes.
* `virtual double calculateNetworkCost(double) = 0;`: Virtual function. It must be implemented in derived classes.

#### <span style="color: rgb(26, 99, 169);">**VoxOperator**</span>
This type of operator specializes in those people who make more intensive use of calls and text messages. Derived from `Operator`.

The class has the following methods:
* Constructor with 6 parameters. Receive the ID, the cost per call minute, the cost per message sending, the cost per GB, the discount percentage and the type of operator. You must invoke the constructor of the parent class.
* Copy builder. You must invoke the constructor of the parent class.
* `calculateTalkingCost(int minute, int age)`: If the number of minutes or the age is less than 0, it will return 0. Otherwise, it calculates the cost of the call taking into account the defined cost per minute. If the person is under 18 or over 65, the defined discount applies.
* `double calculateMessageCost(int quantity, int thisOpId, int otherOpId)`: If the number of messages is less than 0, it will return 0. Otherwise, it calculates the cost of sending the messages taking into account the defined cost per sending. If the messages are sent to the same operator, the defined discount applies.
* `calculateNetworkCost(double amount)`: If the number of GB is greater than 0, calculate the cost per GB.

#### <span style="color: rgb(26, 99, 169);">**InternetOperator**</span>
This type of operator specializes in those people who make more intensive use of the Internet. Derived from `Operator`.

The class has the following methods:
* Constructor with 6 parameters. Receive the ID, the cost per call minute, the cost per message sending, the cost per GB, the discount percentage and the type of operator. You must invoke the constructor of the parent class.
* Copy builder. You must invoke the constructor of the parent class.
* `calculateTalkingCost(int minute, int age)`: If the number of minutes or the age is less than 0, it will return 0. Otherwise, it calculates the cost of the call taking into account the defined cost per minute. If the number of minutes is less than 2, the defined discount applies.
* `double calculateMessageCost(int quantity, int thisOpId, int otherOpId)`: If the number of messages is less than 0, it will return 0. Otherwise, it calculates the cost of sending the messages taking into account the defined cost per sending. If the number of messages sent is less than 3, the defined discount applies.
* `calculateNetworkCost(double amount)`: If the amount of GB is less than or equal to zero, it will return 0. Only the amount of GB that exceeds the 1 GB limit will be charged.

#### <span style="color: rgb(26, 99, 169);">**Customer**</span>
The `Customer` class has the following state variables:
* `id`: Client identifier.
* `name`: Name of the client.
* `age`: Age of the client.
* `totalSpentTalkingTime`: The total time this client has spent on calls.
* `totalMessageSent`: The total messages this client has sent.
* `totalInternetUsage`: The total GB's used by this client.
* `op`: Pointer to an object of the Operator class. The operator that provides service to this client.
* `bill`: Pointer to an object of the Bill class. The client's invoice.

The class has the following methods:
* Constructor with 5 parameters. Receive the id, name, age, operator and credit limit. The object of class *Bill* must be created.
* Copy builder.
* Destroyer. You must delete the invoice. All pointers must be set to null.
* Accessor methods for all instance variables. (If you consider it necessary to add modification methods, go ahead).
* Modification method for the *op* variable.
* `talk (int minutes, Customer &other)`: If the quantity is greater than 0 and `other` is a different client, the cost is calculated by the minutes the call lasted. If there is still a credit limit on the invoice, you will need to add the cost to the invoice and add the minutes used to the count of our customer and their operator. If our client's operator and the 'other' are different, this amount must also be added to the other operator.
* `message(int quantity, const Customer &other)`: If the quantity is greater than 0 and `other` is a different customer, the cost for the messages sent is calculated. If there is still a credit limit on the invoice, you will need to add the cost to the invoice and add the messages sent to the customer and operator count.
* `connection(double amount)`: If the amount is greater than 0, the cost for Internet use is calculated. If there is still a credit limit on the invoice, you will need to add the cost to the invoice and add the GB used to both the customer and operator counts.
* `toString()`: Returns a string with the following format: "Customer #id : totalMoneySpend currentDebt". All floating point quantities must have a precision of two decimal numbers.

#### <span style="color: rgb(26, 99, 169);">**main.cpp**</span>
General input and output operations will be performed in the *main.cpp* file. You will read the simulation operations from an input file, perform them, and print the results in the output file.

The operations are detailed below. The name of the input and output files will be given as program arguments via the command line. If the input file does not exist, the program terminates.

You must handle two vectors, one for pointers to `Customer` objects and another for pointers to `Operator` objects.

#### <span style="color: rgb(26, 99, 169);">**Input**</span>
You are going to read the input file element by element.

The first line has three integers, `C`, `O` and `N`. The number 'C' represents the number of clients that will be in the simulation. The second number, `O`, indicates the number of operators in the simulation. The third number, `N`, represents the number of events to simulate.

The next `N` lines will be some of the following operations:
1. Creating a new client.
2. Creating a new operator.
3. A customer can talk to another customer.
4. A client can send a message to another client.
5. A client can connect to the Internet.
6. A customer can pay his bills.
7. A customer can change operators.
8. A customer can change their Invoice limit.

##### <span style="color: rgb(26, 99, 169);">**1. Creating a new client**</span>
This line contains a 1 followed by the customer's name, age, carrier ID, and the customer's credit limit amount.

```
1 <name> <age> <operatorId> <limitingAmount>
```
Take into account that the client identifier will be the order of creation. For example, the first client created must have id 0 and position 0 of the vector must be placed. Additionally, there is no operation to create a `Bill` object (you must do it in the client's constructor).

##### <span style="color: rgb(26, 99, 169);">**2. Creating a new operator**</span>
This line contains a 2 followed by the type of operator (1 = VOX, 2 = INTERNET), charge per call, charge per message, charge for internet use and the discount to be applied.

```
2 <opType> <talkingCharge> <messageCost> <networkCharge> <discountRate>
```
Take into account that the operator identifier will be the order of creation. For example, the first operator created must have Id 0 and must be placed at position 0 of the vector.

##### <span style="color: rgb(26, 99, 169);">**3. A customer can talk to another customer**</span>
This line contains a 3 followed by the id of the first client (origin), the id of the second client (destination), and the time of the call.

```
3 <idCustomer1> <idCustomer2> <time>
```
##### <span style="color: rgb(26, 99, 169);">**4. A client sends a message to another client**</span>
This line contains a 4 followed by the id of the first client (source), the id of the second client (destination), and the number of messages sent.

```
4 <idCustomer1> <idCustomer2> <quantity>
```

##### <span style="color: rgb(26, 99, 169);">**5. A client connects to the Internet**</span>
This line contains a 5 followed by the client id and the amount of Internet used in GB.

```
5 <idCustomer> <amount>
```

##### <span style="color: rgb(26, 99, 169);">**6. A client pays his bills**</span>
This line contains a 6 followed by the customer id and the amount of money the customer wants to pay.

```
6 <idCustomer> <amount>
```
##### <span style="color: rgb(26, 99, 169);">**7. A client changes operator**</span>
This line contains a 7 followed by the customer id and the operator id.

```
7 <idCustomer> <idOperator>
```
##### <span style="color: rgb(26, 99, 169);">**8. A customer changes their invoice limit**</span>
This line contains an 8 continuous of the client id and the new limit.

```
8 <idCustomer> <amount>
```
#### <span style="color: rgb(26, 99, 169);">**Output**</span>
You need to calculate the following and print it to the output file.

For each operator, you should print the amount of call time they answered, the number of messages sent through that operator, and the amount of Internet usage in terms of GB provided by the operator.
```
Operator <id>: <talkingTime> <totalMessages> <totalMBs>
```

For each customer, you must print how much money they have spent on paying their bill and current debt at the end of the simulation.
```
Customer <id>: <totalMoneySpend> <currentDebt>
```
Subsequently, display the id of the client who talks the most and the amount of time in minutes (if two clients are the same, you should print the one with a smaller id).
```
<name of the customer>: <total talking time>
```
Next, display the id of the client that sends the most messages and the number of messages sent (if two clients are the same, you should print the one with a smaller id).
```
<name of the customer>: <number of messages>
```
Next, display the id of the client that connects to the Internet the most and the number of GBs (if two clients are the same, you should print the one with a smaller id).
```
<name of the customer>: <connection amount>
```
Finally, you must delete all existing pointers and close the input and output files.
