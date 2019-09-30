// Exercise7.43.h
// Ad
// Assume we have a class named NoDefault that has a constructor that takes an
// int, but has no default constructor. Define a class C that has a member of
// type NoDefault. Define the default constructor for C.

#ifndef EXERCISE_7_43_H
#define EXERCISE_7_43_H

class NoDefault
{
public:
  NoDefault(int i) {}
};

class C
{
public:
  C() : nd(0) {}

private:
  NoDefault nd;
};

#endif