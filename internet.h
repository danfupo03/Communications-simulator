// =========================================================
// File: vox.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 15/06/22
// Description: Implementación de la subclase InternetOperator que deriva de Operator
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 1.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

/*
Constructor con 6 parámetros. 
Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, ...
el costo por GB, el porcentaje de descuento y el tipo de operador. 
Debe invocar al constructor de la clase superior.
*/
InternetOperator::InternetOperator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType INTERNET):Operator(_id, _talkingCharge, _messageCost, _networkCharge, _discountRate, VOX){
}

InternetOperator::InternetOperator(const InternetOperator &Iop):Operator(Iop){ //Constructor
}

/*
Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. 
En caso contrario, calcula el costo de la llamada tomando en cuenta el costo por minuto definido. 
Si la cantidad de minutos es menor a 2, le aplica el descuento definido.
*/
double InternetOperator::calculateTalkingCost(int minute, int age){
  double cost = 0;
  if(minute > 0 && age > 0){
    cost = minute * talkingCharge;
  }
  
  if(minute < 2){
    cost -= cost * discountRate/100;
  }
  return cost;
}

/*
Si la cantidad de mensajes es menor igual a 0, regresará 0. 
En caso contrario, calcula el costo de enviar los mensajes tomando en cuenta el costo por envío definido. 
Si la cantidad de mensajes enviados es menor a 3, le aplica el descuento definido.
*/
double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  double cost = 0;
  if(quantity > 0){
    cost = quantity * messageCost;
  }
  else if(quantity < 3){
    cost -= cost * discountRate/100;
  }
  return cost;
}

/*
Si la cantidad de GB es menor o igual a cero, regresará 0. 
Sólo se cobrará la cantidad de GB que exceda el limite de 1 GB.
*/
double InternetOperator::calculateNetworkCost(double amount){
  double cost = 0;
    if(amount > LIMITGB){
        cost = (amount - LIMITGB) * networkCharge;
    }
    return cost;
}

#endif
