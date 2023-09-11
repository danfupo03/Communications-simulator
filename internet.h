// =========================================================
// File: vox.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 15/06/22
// Description: Implementation of the VoxOperator subclass
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator
{
private:
  const double LIMITGB = 1.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator &);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

/**
 * @brief Construct a new Internet Operator:: Internet Operator object
 *
 * @param _id
 * @param _talkingCharge
 * @param _messageCost
 * @param _networkCharge
 * @param _discountRate
 * @param INTERNET
 */
InternetOperator::InternetOperator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType INTERNET) : Operator(_id, _talkingCharge, _messageCost, _networkCharge, _discountRate, VOX)
{
}

/**
 * @brief Construct a new Internet Operator:: Internet Operator object
 *
 * @param Iop
 */
InternetOperator::InternetOperator(const InternetOperator &Iop) : Operator(Iop)
{ // Constructor
}

/**
 * @brief Calculates the cost of talking
 *
 * @param minute
 * @param age
 * @return double
 */
double InternetOperator::calculateTalkingCost(int minute, int age)
{
  double cost = 0;
  if (minute > 0 && age > 0)
  {
    cost = minute * talkingCharge;
  }

  if (minute < 2)
  {
    cost -= cost * discountRate / 100;
  }
  return cost;
}

/**
 * @brief Calculates the cost of messages
 *
 * @param quantity
 * @param thisOpId
 * @param otherOpId
 * @return double
 */
double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId)
{
  double cost = 0;
  if (quantity > 0)
  {
    cost = quantity * messageCost;
  }
  else if (quantity < 3)
  {
    cost -= cost * discountRate / 100;
  }
  return cost;
}

/**
 * @brief Calculates the cost of network
 *
 * @param amount
 * @return double
 */
double InternetOperator::calculateNetworkCost(double amount)
{
  double cost = 0;
  if (amount > LIMITGB)
  {
    cost = (amount - LIMITGB) * networkCharge;
  }
  return cost;
}

#endif
