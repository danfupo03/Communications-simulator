// =========================================================
// File: operator.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Implementación de la clase padre, Operator
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingCharge() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

/*
Constructor con 6 parámetros. 
Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, ...
el costo por GB, el porcentaje de descuento y el tipo de operador. 
El resto de las variables debe inicializarse a 0.
*/
Operator::Operator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType _type){
  id = _id;
  talkingCharge = _talkingCharge;
  messageCost = _messageCost;
  networkCharge = _networkCharge;
  discountRate = _discountRate;
  type = _type;
  totalInternetUsage = 0;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
}

Operator::Operator(const Operator &op){ //Constructor
  id = op.id;
  talkingCharge = op.talkingCharge;
  messageCost = op.messageCost;
  networkCharge = op.networkCharge;
  discountRate = op.discountRate;
  type = op.type;
  totalInternetUsage = op.totalInternetUsage;
  totalSpentTalkingTime = op.totalSpentTalkingTime;
  totalMessageSent = op.totalMessageSent;
}

int Operator::getId() const{ //Getter
  return id;
}

int Operator::getDiscountRate() const{ //Getter
  return discountRate;
}

double Operator::getTalkingCharge() const{ //Getter
  return talkingCharge;
}

double Operator::getMessageCost() const{ //Getter
  return messageCost;
}

double Operator::getNetworkCharge() const{ //Getter
  return networkCharge;
}

int Operator::getTotalSpentTalkingTime() const{ //Getter
  return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const{ //Getter
  return totalMessageSent;
}

double Operator::getTotalInternetUsage() const{ //Getter
  return totalInternetUsage;
}

OperatorType Operator::getType() const{ //Getter
  return type;
}

/*
 Si la cantidad es mayor a 0, agrega la cantidad al tiempo total que se ha empleado en llamadas.
*/
void Operator::addTalkingTime(int minute){
  if(minute > 0){
    totalSpentTalkingTime += minute;
  }
}

/*
Si la cantidad es mayor a 0, agrega la cantidad al total de mensajes enviados.
*/
void Operator::addTotalMessageSent(int quantity){
  if(quantity > 0){
    totalMessageSent += quantity;
  }
}

/*
Si la cantidad es mayor a 0, agrega la cantidad a los GB's totales empleados.
*/
void Operator::addTotalInternetUsage(double amount){
  if(amount > 0){
    totalInternetUsage += amount;
  }
}

/*
Regresa un string con el siguiente formato: 
"Operator #id : totalSpentTalkingTime totalMessageSent totalInternetUsage". 
Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.
*/
string Operator::toString() const{
  stringstream aux;

  aux << fixed << setprecision(2);
  aux << "Operator " << id << ": " << fixed << setprecision(2) << totalSpentTalkingTime << " " << totalMessageSent << " " << totalInternetUsage << endl; 
  
  return aux.str();
}

#endif