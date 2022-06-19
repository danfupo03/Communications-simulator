/// =========================================================
// File: customer.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 15/06/22
// Description: Implementación de la clase Costumer
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

using namespace std;

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  string name;
  Operator* op;
  Bill* bill;

public:
  Customer(int, string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

/*
Constructor con 5 parámetros. 
Recibe el id, el nombre, la edad, el operador y el límite de crédito. 
Se debe crear el objeto de la clase Bill.
*/
Customer::Customer(int _id, string _name, int _age, Operator *_op, double creditLimit){
  id = _id;
  name = _name;
  age = _age;
  op = _op;
  bill = new Bill(creditLimit);
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0;
}

Customer::Customer(const Customer &c){ //Constructor
  id = c.id;
  name = c.name;
  age = c.age;
  op = c.op;
  bill = c.bill;
  totalSpentTalkingTime = c.totalSpentTalkingTime;
  totalMessageSent = c.totalMessageSent;
  totalInternetUsage = c.totalInternetUsage;
}

/*
Destructor. 
Debe eliminar la factura. 
Todos los apuntadores debe ser igualados a nulo.
*/
Customer::~Customer(){
  delete bill;
  bill = NULL;
  op = NULL;
}

int Customer::getId() const{ //Getter
  return id;
}

int Customer::getAge() const{ //Getter
  return age;
}

int Customer::getTotalSpentTalkingTime() const{ //Getter
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const{ //Getter
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const{ //Getter
  return totalInternetUsage;
}

string Customer::getName() const{ //Getter
  return name;
}

Operator* Customer::getOperator() const{ //Getter
  return op;
}

Bill* Customer::getBill() const{ //Getter
  return bill;
}

void Customer::setOperator(Operator* _op){ //Setter
  op = _op;
}

/*
Regresa un string con el siguiente formato: 
"Customer #id : totalMoneySpend currentDebt". 
Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.
*/
string Customer::toString() const{
  stringstream aux;

  aux << fixed << setprecision(2);
  aux << "Customer " << id << ": " << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt()<<endl;  
  return aux.str();
}

/*
Si la cantidad es mayor a 0 y other es un cliente diferente, se calcula el costo por los minutos que duró la llamada. 
Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agregar los minutos empleados ...
al conteo de nuestro cliente y su operador. 
Si el operador de nuestro cliente y el other son diferentes, también deberá de agregarse esta cantidad al otro operador.
*/
void Customer::talk(int minutes, Customer &other){
  double cost = 0;
  if(minutes > 0 && id != other.id){
    cost = op->calculateTalkingCost(minutes, age);
    if(bill->check(cost)){
      bill->add(cost);
      totalSpentTalkingTime += minutes;
      op->addTalkingTime(minutes);
      if(other.op->getId() != op->getId()){
        other.op->addTalkingTime(minutes);
      }
    }
  }
}

/*
Si la cantidad es mayor a 0 y other es un cliente diferente, se calcula el costo por los mensajes enviados. 
Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agrega los mensajes enviados ... 
en el conteo del cliente y del operador.
*/
void Customer::message(int quantity, const Customer &other){
  double cost = 0;
  if(quantity>0 && id != other.id){
    cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
    if(bill->check(cost)){
      bill->add(cost);
      totalMessageSent += quantity;
      op->addTotalMessageSent(quantity);
    }
  }
}

/*
Si la cantidad es mayor a 0, se calcula el costo por el uso de Internet. 
Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agrega los GB utilizados tanto ... 
en el conteo del cliente y del operador.
*/
void Customer::connection(double amount){
  double cost = 0;
  if(amount>0){
    cost = op->calculateNetworkCost(amount);
    if(bill->check(cost)){
      bill->add(cost);
      totalInternetUsage += amount;
      op->addTotalInternetUsage(amount);
    }
  }
}

void Customer::pay(double amount){
  bill->pay(amount);
}

#endif