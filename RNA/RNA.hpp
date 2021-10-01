#pragma once
#include <stdint.h>
#include <cassert>
#include <cstring>
#include <iostream>
#include <unordered_map>

//using namespace std;

#define BIT_MASK 0x3
const size_t nucles_per_elem = (sizeof(uint32_t) * 8 / 2);

struct RNA_set
{
  RNA *first = nullptr;
  RNA *second = nullptr;
};

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

  class reference //used for acces to nucleotids by their indexes in RNA chain
  {
  private:
    size_t position; //index of nucl in RNA chain
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

  size_t RNA::get_uints_number(RNA &rna);

  size_t RNA::get_nucles_number(RNA &rna);

  void resize();

  void push_back(Nucl N);

  Nucl RNA::pop_back();

  void trim(size_t last_index);

  RNA_set split(size_t index);

  void add();

  Nucl get_complementary(Nucl N);

  bool is_complementary(RNA &r1);

  size_t cardinality(Nucl N);

  std::unordered_map<Nucl, int, std::hash<int>> cardinality();

  reference operator[](size_t pos);

  Nucl RNA::operator[](size_t pos) const;

  RNA &operator=(const RNA &other);

  friend bool operator==(const RNA &r1, const RNA &r2);

  friend bool operator!=(const RNA &r1, const RNA &r2);

  RNA operator!();

  friend RNA operator+(RNA &rna1, RNA &rna2);

  /* 
  operator== ();--
  operator!= ();--
  operator ! ();--
  operator[] ();--

  isComplementary(RNK &);--
  split(size_t index);

  DNK(RNK&, RNK&); 
  */
};

//RNA operator+(RNA &rna1, RNA &rna2);