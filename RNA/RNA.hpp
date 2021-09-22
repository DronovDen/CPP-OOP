#pragma once
#include <stdint.h>
#include <cassert>
#include <cstring>
#include <iostream>

#define BIT_MASK 0x3

enum Nucl : uint32_t
{
    A = 0x0,
    C = 0x1,
    G = 0x2,
    T = 0x3
};

class RNA
{
private:
  uint32_t* nucleref;
  size_t uint_len;
  //size_t capacity; //max number of nucleotids
  size_t n_number; //number of nucles in RNA reference

public:
  // CONSTRUCTORS
  RNA(Nucl N, size_t const capacity);
  RNA();

  //COPY CONSTRUCTOR
  RNA(const RNA &other);

  // DESTRUCTOR
  ~RNA();

  void add();

  /* operator== ();
  operator!= ();
  operator ! ();
  operator[] ();

  isComplementary(RNK &);
  split(size_t index);

  DNK(RNK&, RNK&); */
};