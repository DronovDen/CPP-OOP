#include "RNA.hpp"

// CONSTRUCTORS
RNA::RNA(Nucl N, size_t capacity)
{
  this->uint_len = (capacity / nucles_per_elem) + (capacity % nucles_per_elem != 0);
  this->nucleref = new uint32_t[uint_len];
  memset(nucleref, 0, uint_len);
  this->n_number = capacity;
  for (size_t i = 0; i < n_number; i++)
  {
    nucleref[i / nucles_per_elem] |= (uint32_t)(N << (sizeof(uint32_t) * 8 - 2 - (i % uint_nucles) * 2));
  }
}

RNA::RNA(size_t capacity)
{
  this->uint_len = (capacity / nucles_per_elem) + (capacity % nucles_per_elem != 0);
  this->nucleref = new uint32_t[uint_len];
  memset(nucleref, 0, uint_len);
  this->n_number = capacity;
}

RNA::RNA()
{
  this->uint_len = 0;
  this->n_number = 0;
  this->nucleref = nullptr
}

//COPY CONSTRUCTOR
RNA::RNA(const RNA &other)
{
  for (size_t i = 0; i < other.len; i++)
  {
    nucleref.push_back(other.nucleref.get(i));
  }
  this->len = other.len;
}

// DESTRUCTOR
~RNA()
{
  if (nucleref)
  {
    delete[] nucleref;
    nucleref = nullptr;
  }
}

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
  for (int i = 0; i < uints; i++)
  {
    array[i] = nucleref[i];
  }
  delete[] nucleref;
  nucleref = array;
}

void RNA::push_back(Nucl N)
{
  new_n_num = n_number + 1;
  if (new_n_num / nucs_per_elem + (new_n_num % nucs_per_elem >= 1) > uint_len)
  {
    resize();
  }
  n_number = new_n_num;
  nucleref[n_number / nucles_per_elem] |=
      (N << (2 * (nucles_per_elem - (n_number % nucles_per_elem)));
}

Nucl RNA::pop_back()
{
  n_number--;
  return (Nucl)((data[len / nucles_per_elem] >> (nucles_per_elem - 1 - len % nucles_per_elem) * 2) &
                BIT_MASK);
}

void add();

/* operator== ();
  operator!= ();
  operator! ();
  operator[] ();

  isComplementary(RNK &);
  split(size_t index);

  DNK(RNK&, RNK&); */

int main()
{
  RNA a;
  return 0;
}