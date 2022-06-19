// =========================================================
// File: bill.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Declaracion de la clase Bill
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

Bill::Bill() { //Constructor
  limitAmount = 0;
  currentDebt = 0;
  totalMoneySpent = 0;
}

Bill::Bill(double limit){ //Constructor con un parametro (limit) e inicializa el resto de variables en 0
  if (limit <= 0 ) {
    limit = 0;
  }
  limitAmount = limit;
  currentDebt = 0;
  totalMoneySpent = 0;
}


Bill::Bill(const Bill &other) { //Constructor 
  limitAmount = other.limitAmount;
  currentDebt = other.currentDebt;
  totalMoneySpent = other.totalMoneySpent;
}

double Bill::getLimitAmount() const { //Getter
  return limitAmount;
}

double Bill::getCurrentDebt() const { //Getter
  return currentDebt;
}

double Bill::getTotalMoneySpent() const { //Getter
  return totalMoneySpent;
}

/* 
Agrega cargos a la factura. 
Si la cantidad es menor o igual 0, no debera hacer cambios. 
*/
void Bill::add(double amount){
  if(amount > 0) {
    currentDebt += amount;
  }
}

/* 
Reduce la deuda en la cantidad dada. 
Si la cantidad es menor o igual a 0, no debera hacer cambios. 
Nunca se podra pagar más cantidad que la deuda actual. 
*/
void Bill::pay(double amount){
  if (amount > 0) {
    if (amount > currentDebt) {
      amount = currentDebt;
    }
    totalMoneySpent += amount;
    currentDebt -= amount;
  }
}


/*
Cambia el limite de crédito, siempre y cuando sea mayor a la deuda actual. 
Si la cantidad es menor o igual a 0, no debera hacer cambios.
*/
void Bill::changeTheLimit(double limit){
  if(limit > currentDebt){
    limitAmount = limit;
  }
}

/*
Regresa verdadero si la cantidad mas la deuda actual no excede el limite de credito.
*/
bool Bill::check(double amount) const{
  if(amount + currentDebt < limitAmount){
    return true;
  }
  else{
    return false;
  }
}

#endif
