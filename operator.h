// =========================================================
// File: operator.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Implementation of the Operator class
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum
{
  VOX,
  INTERNET
} OperatorType;

class Operator
{
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator &);

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

/**
 * @brief Construct a new Operator:: Operator object
 *
 * @param _id
 * @param _talkingCharge
 * @param _messageCost
 * @param _networkCharge
 * @param _discountRate
 * @param _type
 */
Operator::Operator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType _type)
{
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

/**
 * @brief Construct a new Operator:: Operator object
 *
 * @param op
 */
Operator::Operator(const Operator &op)
{ // Constructor
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

/**
 * @brief Getter of the id
 *
 * @return int
 */
int Operator::getId() const
{ // Getter
  return id;
}

/**
 * @brief Getter of the discount rate
 *
 * @return int
 */
int Operator::getDiscountRate() const
{ // Getter
  return discountRate;
}

/**
 * @brief Getter of the talking charge
 *
 * @return double
 */
double Operator::getTalkingCharge() const
{ // Getter
  return talkingCharge;
}

/**
 * @brief Getter of the message cost
 *
 * @return double
 */
double Operator::getMessageCost() const
{ // Getter
  return messageCost;
}

/**
 * @brief Getter of the network charge
 *
 * @return double
 */
double Operator::getNetworkCharge() const
{ // Getter
  return networkCharge;
}

/**
 * @brief Getter of the total spent talking time
 *
 * @return int
 */
int Operator::getTotalSpentTalkingTime() const
{ // Getter
  return totalSpentTalkingTime;
}

/**
 * @brief Getter of the total message sent
 *
 * @return int
 */
int Operator::getTotalMessageSent() const
{ // Getter
  return totalMessageSent;
}

/**
 * @brief Getter of the total internet usage
 *
 * @return double
 */
double Operator::getTotalInternetUsage() const
{ // Getter
  return totalInternetUsage;
}

/**
 * @brief Getter of the type
 *
 * @return OperatorType
 */
OperatorType Operator::getType() const
{ // Getter
  return type;
}

/**
 * @brief Adds the talking time to the total spent talking time
 *
 * @param minute
 */
void Operator::addTalkingTime(int minute)
{
  if (minute > 0)
  {
    totalSpentTalkingTime += minute;
  }
}

/**
 * @brief Adds the total message sent
 *
 * @param quantity
 */
void Operator::addTotalMessageSent(int quantity)
{
  if (quantity > 0)
  {
    totalMessageSent += quantity;
  }
}

/**
 * @brief Adds the total internet usage
 *
 * @param amount
 */
void Operator::addTotalInternetUsage(double amount)
{
  if (amount > 0)
  {
    totalInternetUsage += amount;
  }
}

/**
 * @brief Returns a string with the information of the operator
 *
 * @return string
 */
string Operator::toString() const
{
  stringstream aux;

  aux << fixed << setprecision(2);
  aux << "Operator " << id << ": " << fixed << setprecision(2) << totalSpentTalkingTime << " " << totalMessageSent << " " << totalInternetUsage << endl;

  return aux.str();
}

#endif