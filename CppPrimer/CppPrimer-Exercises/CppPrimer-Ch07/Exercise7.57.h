// Exercise7.57.h
// Ad
// Write your own version of the Account class.

#ifndef EXERCISE_7_57_H
#define EXERCISE_7_57_H

#include <string>

class Account
{
public:
  Account() = default;
  Account(std::string onr, double amo) : owner(onr), amount(amo) {}
  const std::string getOwner() { return owner; }
  const double getAmount() { return amount; }
  void calculate() { amount += amount * interestRate; }
  static double rate() { return interestRate; }
  static void rate(double newRate) { interestRate = newRate; }

private:
  std::string owner;
  double amount;
  static double interestRate;
  static double initRate() { return 0.1; }
};

// the following definition should be put in the corresponding source file
double Account::interestRate = initRate();

#endif