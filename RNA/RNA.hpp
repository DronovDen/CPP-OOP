#pragma once
#include <cstring>
#include <iostream>
#include <unordered_map>

#define BIT_MASK 0x3
const size_t nucles_per_elem = (sizeof(size_t) * 8 / 2);

enum Nucl
{
  A = 0x0,
  C = 0x1,
  G = 0x2,
  T = 0x3
};

struct RNA_set;

class RNA
{
private:
  size_t *nucleref; //reference of nucleotids
  size_t uint_len;  //number of uints
  size_t n_number;  //number of nucles in RNA reference

  class reference //used for acces to nucleotids by their indexes in RNA chain
  {
  private:
    size_t position;
    size_t idx; //index of nucl in RNA chain
    size_t shift;
    RNA *rna;

  public:
    reference(size_t index, RNA *rna);
    ~reference();
    Nucl operator=(Nucl N);
    operator Nucl() const; //converting to type Nucl
  };

public:
  RNA(Nucl N, size_t capacity);
  RNA(size_t capacity);
  RNA();

  RNA(const RNA &other);

  ~RNA();

  size_t get_uints_number();

  size_t get_nucles_number();

  void resize();

  void push_back(Nucl N);

  Nucl pop_back();

  void trim(size_t last_index); //forgot everything is afer last_index

  RNA_set split(size_t index);

  Nucl get_complementary(Nucl N);

  bool is_complementary(RNA &r1);

  size_t cardinality(Nucl N);

  std::unordered_map<Nucl, int, std::hash<int>> cardinality();

  reference operator[](size_t pos);

  Nucl operator[](size_t pos) const;

  RNA &operator=(const RNA &other);

  friend bool operator==(const RNA &r1, const RNA &r2);

  friend bool operator!=(const RNA &r1, const RNA &r2);

  RNA operator!();

  friend RNA operator+(RNA &rna1, RNA &rna2);
};

struct RNA_set
{
  RNA *first = nullptr;
  RNA *second = nullptr;
};
