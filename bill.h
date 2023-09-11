// =========================================================
// File: bill.h
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 14/06/22
// Description: Declaration of the Bill class
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill
{
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill &);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

/**
 * @brief Construct a new Bill:: Bill object
 *
 */
Bill::Bill()
{
  limitAmount = 0;
  currentDebt = 0;
  totalMoneySpent = 0;
}

/**
 * @brief Construct a new Bill:: Bill object
 *
 * @param limit
 */
Bill::Bill(double limit)
{
  if (limit <= 0)
  {
    limit = 0;
  }
  limitAmount = limit;
  currentDebt = 0;
  totalMoneySpent = 0;
}

/**
 * @brief Construct a new Bill:: Bill object
 *
 * @param other
 */
Bill::Bill(const Bill &other)
{ // Constructor
  limitAmount = other.limitAmount;
  currentDebt = other.currentDebt;
  totalMoneySpent = other.totalMoneySpent;
}

/**
 * @brief Get the Limit Amount object
 *
 * @return double
 */
double Bill::getLimitAmount() const
{ // Getter
  return limitAmount;
}

/**
 * @brief Get the Current Debt object
 *
 * @return double
 */
double Bill::getCurrentDebt() const
{ // Getter
  return currentDebt;
}

/**
 * @brief Get the Total Money Spent object
 *
 * @return double
 */
double Bill::getTotalMoneySpent() const
{ // Getter
  return totalMoneySpent;
}

/**
 * @brief Add to the current debt
 *
 * @param amount
 */
void Bill::add(double amount)
{
  if (amount > 0)
  {
    currentDebt += amount;
  }
}

/**
 * @brief Pay the current debt
 *
 *
 * @param amount
 */
void Bill::pay(double amount)
{
  if (amount > 0)
  {
    if (amount > currentDebt)
    {
      amount = currentDebt;
    }
    totalMoneySpent += amount;
    currentDebt -= amount;
  }
}

/**
 * @brief Change the limit of the bill
 *
 * @param limit
 */
void Bill::changeTheLimit(double limit)
{
  if (limit > currentDebt)
  {
    limitAmount = limit;
  }
}

/**
 * @brief Check if the amount is less than the limit
 *
 * @param amount
 * @return true
 * @return false
 */
bool Bill::check(double amount) const
{
  if (amount + currentDebt < limitAmount)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#endif
