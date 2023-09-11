// =========================================================
// File: main.cpp
// Author: Daniel Emilio Fuentes Portaluppi
// Date: 15/06/22
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char *argv[])
{

  ifstream inputFile;
  ofstream outputFile;

  int C, O, N;

  if (argc != 3)
  {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open())
  {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  inputFile >> C >> O >> N;

  vector<Customer *> customers(C);
  vector<Operator *> operators(O);

  int x = 0, y = 0;
  int instruction, mOperatorId, mAge, mDiscountRate, mOpType, mIdCustomer1, mIdCustomer2, mTime, mQuantity;
  double mLimitAmount, mTalkingCharge, mMessageCost, mNetworkCharge, mAmount;
  string mName;

  for (int i = 0; i < N; i++)
  {
    inputFile >> instruction;

    switch (instruction)
    {
    case 1:
      inputFile >> mName >> mAge >> mOperatorId >> mLimitAmount;
      customers[x] = new Customer(x, mName, mAge, operators[mOperatorId], mLimitAmount);
      x++;
      break;

    case 2:
      inputFile >> mOpType >> mTalkingCharge >> mMessageCost >> mNetworkCharge >> mDiscountRate;
      if (mOpType == 1)
      {
        operators[y] = new VoxOperator(y, mTalkingCharge, mMessageCost, mNetworkCharge, mDiscountRate, VOX);
        y++;
      }
      else if (mOpType == 2)
      {
        operators[y] = new InternetOperator(y, mTalkingCharge, mMessageCost, mNetworkCharge, mDiscountRate, INTERNET);
        y++;
      }
      break;

    case 3:
      inputFile >> mIdCustomer1 >> mIdCustomer2 >> mTime;
      customers[mIdCustomer1]->talk(mTime, *customers[mIdCustomer2]);
      break;

    case 4:
      inputFile >> mIdCustomer1 >> mIdCustomer2 >> mQuantity;
      customers[mIdCustomer1]->message(mQuantity, *customers[mIdCustomer2]);
      break;

    case 5:
      inputFile >> mIdCustomer1 >> mAmount;
      customers[mIdCustomer1]->connection(mAmount);
      break;

    case 6:
      inputFile >> mIdCustomer1 >> mAmount;
      customers[mIdCustomer1]->pay(mAmount);
      break;

    case 7:
      inputFile >> mIdCustomer1 >> mOperatorId;
      customers[mIdCustomer1]->setOperator(operators[mOperatorId]);
      break;

    case 8:
      inputFile >> mIdCustomer1 >> mAmount;
      customers[mIdCustomer1]->getBill()->changeTheLimit(mAmount);

    default:
      break;
    }
  }

  for (int i = 0; i < O; i++)
  {
    outputFile << operators[i]->toString();
  }

  int talking = 0;
  int message = 0;
  double network = 0;

  int idTalking = 0;
  int idMessage = 0;
  int idNetwork = 0;

  for (int i = 0; i < C; i++)
  {
    outputFile << customers[i]->toString();

    // Finds the customers with most time, messages and networking used
    if (customers[i]->getTotalSpentTalkingTime() > talking)
    {
      talking = customers[i]->getTotalSpentTalkingTime();
      idTalking = customers[i]->getId();
    }
    if (customers[i]->getTotalMessageSent() > message)
    {
      message = customers[i]->getTotalMessageSent();
      idMessage = customers[i]->getId();
    }
    if (customers[i]->getTotalInternetUsage() > network)
    {
      network = customers[i]->getTotalInternetUsage();
      idNetwork = customers[i]->getId();
    }
  }

  // Writes the customers with most time, messages and networking used
  outputFile << customers[idTalking]->getName() << ": " << customers[idTalking]->getTotalSpentTalkingTime() << "\n";

  outputFile << fixed << std::setprecision(2) << customers[idMessage]->getName() << ": " << customers[idMessage]->getTotalMessageSent() << "\n";

  outputFile << fixed << std::setprecision(2) << customers[idNetwork]->getName() << ": " << customers[idNetwork]->getTotalInternetUsage() << "\n";

  // Close files
  inputFile.close();
  outputFile.close();

  for (int i = 0; i < customers.size(); ++i)
  {
    delete customers[i];
  }

  return 0;
}
