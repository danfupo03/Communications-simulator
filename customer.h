/// =========================================================
// File: customer.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 15/06/22
// Description: Implementation of the Customer class
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

using namespace std;

class Customer
{
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  string name;
  Operator *op;
  Bill *bill;

public:
  Customer(int, string, int, Operator *, double);
  Customer(const Customer &);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  string getName() const;
  Operator *getOperator() const;
  Bill *getBill() const;

  void setOperator(Operator *);

  string toString() const;

  void talk(int, Customer &);
  void message(int, const Customer &);
  void connection(double);
  void pay(double);
};

/**
 * @brief Construct a new Customer:: Customer object
 *
 * @param _id
 * @param _name
 * @param _age
 * @param _op
 * @param creditLimit
 */
Customer::Customer(int _id, string _name, int _age, Operator *_op, double creditLimit)
{
  id = _id;
  name = _name;
  age = _age;
  op = _op;
  bill = new Bill(creditLimit);
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0;
}

/**
 * @brief Construct a new Customer:: Customer object
 *
 * @param c
 */
Customer::Customer(const Customer &c)
{ // Constructor
  id = c.id;
  name = c.name;
  age = c.age;
  op = c.op;
  bill = c.bill;
  totalSpentTalkingTime = c.totalSpentTalkingTime;
  totalMessageSent = c.totalMessageSent;
  totalInternetUsage = c.totalInternetUsage;
}

/**
 * @brief Destroy the Customer:: Customer object
 *
 */
Customer::~Customer()
{
  delete bill;
  bill = NULL;
  op = NULL;
}

/**
 * @brief Get the Id object
 *
 * @return int
 */
int Customer::getId() const
{ // Getter
  return id;
}

/**
 * @brief Get the Age object
 *
 * @return int
 */
int Customer::getAge() const
{ // Getter
  return age;
}

/**
 * @brief Get the Total Spent Talking Time object
 *
 * @return int
 */
int Customer::getTotalSpentTalkingTime() const
{ // Getter
  return totalSpentTalkingTime;
}

/**
 * @brief Get the Total Message Sent object
 *
 * @return int
 */
int Customer::getTotalMessageSent() const
{ // Getter
  return totalMessageSent;
}

/**
 * @brief Get the Total Internet Usage object
 *
 * @return int
 */
double Customer::getTotalInternetUsage() const
{ // Getter
  return totalInternetUsage;
}

/**
 * @brief Get the Name object
 *
 * @return string
 */
string Customer::getName() const
{ // Getter
  return name;
}

/**
 * @brief Get the Operator object
 *
 * @return Operator*
 */
Operator *Customer::getOperator() const
{ // Getter
  return op;
}

/**
 * @brief Get the Bill object
 *
 * @return Bill*
 */
Bill *Customer::getBill() const
{ // Getter
  return bill;
}

/**
 * @brief Set the Operator object
 *
 * @param _op
 */
void Customer::setOperator(Operator *_op)
{ // Setter
  op = _op;
}

/**
 * @brief Convert the object to string
 *
 * @return string
 */
string Customer::toString() const
{
  stringstream aux;

  aux << fixed << setprecision(2);
  aux << "Customer " << id << ": " << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt() << endl;
  return aux.str();
}

/**
 * @brief Function that simulates a call between two customers
 *
 * @param minutes
 * @param other
 */
void Customer::talk(int minutes, Customer &other)
{
  double cost = 0;
  if (minutes > 0 && id != other.id)
  {
    cost = op->calculateTalkingCost(minutes, age);
    if (bill->check(cost))
    {
      bill->add(cost);
      totalSpentTalkingTime += minutes;
      op->addTalkingTime(minutes);
      if (other.op->getId() != op->getId())
      {
        other.op->addTalkingTime(minutes);
      }
    }
  }
}

/**
 * @brief Function that simulates a message between two customers
 *
 * @param quantity
 * @param other
 */
void Customer::message(int quantity, const Customer &other)
{
  double cost = 0;
  if (quantity > 0 && id != other.id)
  {
    cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
    if (bill->check(cost))
    {
      bill->add(cost);
      totalMessageSent += quantity;
      op->addTotalMessageSent(quantity);
    }
  }
}

/**
 * @brief Function that simulates a connection between a customer and the internet
 *
 * @param amount
 */
void Customer::connection(double amount)
{
  double cost = 0;
  if (amount > 0)
  {
    cost = op->calculateNetworkCost(amount);
    if (bill->check(cost))
    {
      bill->add(cost);
      totalInternetUsage += amount;
      op->addTotalInternetUsage(amount);
    }
  }
}

/**
 * @brief Function that simulates a payment of a customer
 *
 * @param amount
 */
void Customer::pay(double amount)
{
  bill->pay(amount);
}

#endif