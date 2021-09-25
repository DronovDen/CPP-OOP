#include "RNA.hpp"

//CONSTRUCTORS
RNA::RNA(Nucl N, size_t capacity)
{
  this->uint_len = capacity * 2 / sizeof(uint32_t) / 8 + 1;
  //this->uint_len = (capacity / nucles_per_elem) + (capacity % nucles_per_elem != 0);
  this->n_number = capacity;
  this->nucleref = new uint32_t[uint_len];
  memset(nucleref, 0, uint_len);
  for (size_t i = 0; i < n_number; i++)
  {
    (*this)[i] = N;
    //nucleref[i / nucles_per_elem] |= (uint32_t)(N << (sizeof(uint32_t) * 8 - 2 - (i % nucles_per_elem) * 2));
  }
}

RNA::RNA(size_t capacity)
{
  //this->uint_len = capacity * 2 / sizeof(uint32_t) / 8 + 1;
  this->uint_len = (capacity / nucles_per_elem) + (capacity % nucles_per_elem != 0);
  this->n_number = capacity;
  this->nucleref = new uint32_t[uint_len];
  memset(nucleref, 0, uint_len);
}

RNA::RNA()
{
  this->uint_len = 0;
  this->n_number = 0;
  this->nucleref = nullptr;
}

//COPY CONSTRUCTOR
RNA::RNA(const RNA &other)
{
  this->n_number = other.n_number;
  this->uint_len = other.uint_len;
  this->nucleref = new uint32_t[uint_len];
  for(size_t i = 0; i < uint_len; i++){
    this->nucleref[i] = other.nucleref[i];
  }
}

// DESTRUCTOR
RNA::~RNA()
{
  if (nucleref)
  {
    delete[] nucleref;
    nucleref = nullptr;
  }
}

//Reference--------------------
RNA::reference::reference(RNA *rna, size_t position)
{
  position = position;
  rna = rna;
}

RNA::reference::operator Nucl()
{
  size_t idx = position * 2 / sizeof(uint32_t) / 8;
  size_t shift = ((sizeof(uint32_t) * 8) - 2 - (position % nucles_per_elem) * 2);
  return (Nucl)((rna->nucleref[idx] & (BIT_MASK << shift)) >> shift);
}

RNA::reference &RNA::reference::operator=(Nucl N)
{
  size_t idx = position * 2 / sizeof(uint32_t) / 8;
  size_t shift = ((sizeof(uint32_t) * 8) - 2 - (position % nucles_per_elem) * 2);
  rna->nucleref[idx] = ((rna->nucleref[idx] & (~(BIT_MASK << shift)))) | (N << shift);
}

RNA::reference::~reference()
{
  this->rna = nullptr;
  this->position = 0;
}
//-----------------------------

size_t RNA::get_uints()
{
  return uint_len;
}

size_t RNA::get_number_of_nucles()
{
  return n_number;
}

void RNA::resize()
{
  uint32_t *array = new uint32_t[uint_len * 2];
  memset(array, 0, uint_len * 2);
  uint_len = uint_len * 2;
  for (int i = 0; i < uint_len; i++)
  {
    array[i] = nucleref[i];
  }
  delete[] nucleref;
  nucleref = array;
}

void RNA::push_back(Nucl N)
{
  size_t new_n_num = n_number + 1;
  if (new_n_num / nucles_per_elem + (new_n_num % nucles_per_elem >= 1) > uint_len)
  {
    resize();
  }
  n_number = new_n_num;
  (*this)[n_number] = N;
  /* nucleref[n_number / nucles_per_elem] |=
      (N << (2 * (nucles_per_elem - (n_number % nucles_per_elem)))); */
}

Nucl RNA::pop_back()
{
  Nucl N = (*this)[n_number];
  n_number--;
  uint_len = n_number * 2 / sizeof(uint32_t) / 8 + 1;
  uint32_t *temporary = nucleref;
  nucleref = new uint32_t[uint_len];
  for (int i = 0; i < uint_len; i++)
  {
    nucleref[i] = temporary[i];
  }
  delete[] temporary;
  return N;
  /* return (Nucl)((nucleref[uint_len / nucles_per_elem] >> (nucles_per_elem - 1 - uint_len % nucles_per_elem) * 2) &
                BIT_MASK); */
}

Nucl get_complementary(Nucl N)
{
  switch (N)
  {
  case A:
    return T;
  case G:
    return C;
  case C:
    return G;
  case T:
    return A;
  default:
    return A;
  }
}

bool RNA::is_complementary(RNA &r1)
{
  if (r1.n_number != n_number)
    return false;
  for (size_t i = 0; i < r1.uint_len; i++)
  {
    if (r1.nucleref[i] != ~nucleref[i])
      return false;
  }
  return true;
}

RNA::reference RNA::operator[](size_t position)
{
  return reference(this, position);
}

Nucl RNA::operator[] (size_t position) const{
  size_t idx = position * 2 / sizeof(uint32_t) / 8;
  size_t shift = ((sizeof(uint32_t) * 8) - 2 - (position % nucles_per_elem) * 2);
  return (Nucl)((this->nucleref[idx] & (BIT_MASK << shift)) >> shift);
}

RNA &RNA::operator= (const RNA& other){
  delete[] this->nucleref;
  this->uint_len = other.uint_len;
  this->n_number = other.n_number;
  for(size_t i = 0; i < uint_len; i++){
    this->nucleref[i] = other.nucleref[i];
  }
  return *this;
}

bool operator==(const RNA &r1, const RNA &r2)
{
  if (r1.n_number != r2.n_number)
    return false;
  for (size_t i = 0; i < r1.uint_len; i++)
  {
    if (r1.nucleref[i] != r2.nucleref[i])
      return false;
  }
  return true;
}

bool operator!=(const RNA &r1, const RNA &r2)
{
  return !(r1 == r2);
}

RNA RNA::operator!()
{
  RNA new_rna;
  new_rna.n_number = this->n_number;
  new_rna.uint_len = this->uint_len;
  new_rna.nucleref = new uint32_t[new_rna.uint_len];
  for (size_t i = 0; i < n_number; i++)
  {
    new_rna[i] = (get_complementary((*this)[i]));
  }
  return new_rna;
}

void add();

/* operator== ();
  operator!= ();
  operator! ();
  operator[] ();

  operator+ !!!!!!!!!!!!!!


  isComplementary(RNK &);
  split(size_t index);

  DNK(RNK&, RNK&); */