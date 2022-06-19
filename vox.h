// =========================================================
// File: vox.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Implementación de la subclase VoxOperator que deriva de Operator
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

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
VoxOperator::VoxOperator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType VOX)
:Operator(_id, _talkingCharge, _messageCost, _networkCharge, _discountRate, VOX){
}

VoxOperator::VoxOperator(const VoxOperator &Vop):Operator(Vop){ //Constructor
}

/*
Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. 
En caso contrario, calcula el costo de la llamada tomando en cuenta el costo por minuto definido. 
Si la persona es menor a 18 o mayor a 65, le aplica el descuento definido.
*/
double VoxOperator::calculateTalkingCost(int minute, int age){
  double cost = 0;
  if(minute > 0 && age > 0){
    cost = minute * talkingCharge;
  }
  if(age < 18 || age > 65){
    cost -= cost * discountRate/100;
  }
  return cost;
}

/*
Si la cantidad de mensajes es menor igual a 0, regresará 0. 
En caso contrario, calcula el costo de enviar los mensajes tomando en cuenta el costo por envío definido. 
Si los mensajes son enviados al mismo operador, le aplica el descuento definido.
*/
double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  double cost = 0;
  if(quantity > 0){
    cost = quantity * messageCost;
  }
  if(thisOpId == otherOpId){
    cost -= cost * discountRate/100;
  }
  return cost;
}

/*
Si la cantidad de GB es mayor a 0, calcula el costo por GB.
*/
double VoxOperator::calculateNetworkCost(double amount){
  if(amount > 0){
    return amount * networkCharge;
  }
  else{
    return 0;
  }
}

#endif
