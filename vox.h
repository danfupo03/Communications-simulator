// =========================================================
// File: vox.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Implementation of the VoxOperator subclass 
//              that derives from Operator
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator
{
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator &);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

/**
 * @brief Construct a new Vox Operator:: Vox Operator object
 *
 * @param _id
 * @param _talkingCharge
 * @param _messageCost
 * @param _networkCharge
 * @param _discountRate
 * @param VOX
 */
VoxOperator::VoxOperator(int _id, double _talkingCharge, double _messageCost, double _networkCharge, int _discountRate, OperatorType VOX)
    : Operator(_id, _talkingCharge, _messageCost, _networkCharge, _discountRate, VOX)
{
}

/**
 * @brief Construct a new Vox Operator:: Vox Operator object
 *
 * @param Vop
 */
VoxOperator::VoxOperator(const VoxOperator &Vop) : Operator(Vop)
{ // Constructor
}

/**
 * @brief Calculates the cost of talking
 *
 * @param minute
 * @param age
 * @return double
 */
double VoxOperator::calculateTalkingCost(int minute, int age)
{
  double cost = 0;
  if (minute > 0 && age > 0)
  {
    cost = minute * talkingCharge;
  }
  if (age < 18 || age > 65)
  {
    cost -= cost * discountRate / 100;
  }
  return cost;
}

/**
 * @brief Calculates the cost of sending a message
 *
 * @param quantity
 * @param thisOpId
 * @param otherOpId
 * @return double
 */
double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId)
{
  double cost = 0;
  if (quantity > 0)
  {
    cost = quantity * messageCost;
  }
  if (thisOpId == otherOpId)
  {
    cost -= cost * discountRate / 100;
  }
  return cost;
}

/**
 * @brief Calculates the cost of internet usage
 *
 * @param amount
 * @return double
 */
double VoxOperator::calculateNetworkCost(double amount)
{
  if (amount > 0)
  {
    return amount * networkCharge;
  }
  else
  {
    return 0;
  }
}

#endif
