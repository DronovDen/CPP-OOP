#pragma once
#include <stdint.h>
#include <cassert>
#include <cstring>
#include <iostream>

#define BIT_MASK 0x3
const size_t nucles_per_elem = (sizeof(uint32_t) * 8 / 2);

enum Nucl
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
  size_t uint_len;    //number of uints
  size_t n_number;    //number of nucles in RNA reference


  //used for acces to nucleotids by their indexes in RNA chain
  class reference
  {
  private:
    size_t position; //index of nucl in RNA
    RNA *rna;

  public:
    reference(RNA *rna, size_t position);
    ~reference();
    reference &operator=(Nucl N); //needed for writing nucl by its index to an RNA chain 
    operator Nucl();
  };

public:
  RNA(Nucl N, size_t capacity);
  RNA(size_t capacity);
  RNA();

  RNA(const RNA &other);

  ~RNA();

  size_t RNA::get_uints();

  size_t RNA::get_number_of_nucles();

  void resize();

  void push_back(Nucl N);

  Nucl RNA::pop_back();

  void add();

  Nucl get_complementary(Nucl N);

  reference operator[](size_t pos);

  Nucl RNA::operator[](size_t pos) const;

  RNA &operator=(const RNA &other);

  friend bool operator==(const RNA &r1, const RNA &r2);

  friend bool operator!=(const RNA &r1, const RNA &r2);

  bool is_complementary(RNA &r1);

  RNA operator!();

  /* operator== ();--
  operator!= ();--
  operator ! ();--
  operator[] ();--

  isComplementary(RNK &);--
  split(size_t index);

  DNK(RNK&, RNK&); */
};