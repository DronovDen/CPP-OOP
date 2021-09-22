#pragma once
#include <stdint.h>
#include <cassert>
#include <cstring>
#include <iostream>

#define BIT_MASK 0x3

const size_t nucles_per_elem = (sizeof(uint32_t) * 8 / 2);

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
  uint32_t *nucleref; //reference of nucleotids
  size_t uint_len;  //number of uints 
  //size_t capacity; //max number of nucleotids
  size_t n_number; //number of nucles in RNA reference

public:
  // CONSTRUCTORS
  RNA(Nucl N, size_t capacity);
  RNA(size_t capacity);
  RNA();

  //COPY CONSTRUCTOR
  RNA(const RNA &other);

  // DESTRUCTOR
  ~RNA();

  size_t RNA::get_uints()

  size_t RNA::get_number_of_nucles()

  void resize();

  void push_back(Nucl N);

  void add();

  /* operator== ();
  operator!= ();
  operator ! ();
  operator[] ();

  isComplementary(RNK &);
  split(size_t index);

  DNK(RNK&, RNK&); */
};