#include "RNA.hpp"

RNA::RNA(Nucl N, size_t capacity)
{
  this->uint_len = capacity * 2 / sizeof(size_t) / 8 + 1;
  this->n_number = capacity;
  this->nucleref = new size_t[uint_len];
  //memset(nucleref, 0, uint_len);
  for (size_t i = 0; i < n_number; i++)
  {
    (*this)[i] = N;
  }
}
RNA::RNA(size_t capacity)
{
  //this->uint_len = (capacity / nucles_per_elem) + (capacity % nucles_per_elem != 0);
  this->uint_len = capacity * 2 / sizeof(size_t) / 8 + 1;
  this->n_number = capacity;
  this->nucleref = new size_t[uint_len];
  memset(nucleref, 0, uint_len);
}
RNA::RNA()
{
  this->uint_len = 0;
  this->n_number = 0;
  this->nucleref = nullptr;
}

RNA::RNA(const RNA &other)
{
  this->n_number = other.n_number;
  this->uint_len = other.uint_len;
  this->nucleref = new size_t[uint_len];
  for (size_t i = 0; i < uint_len; i++)
  {
    this->nucleref[i] = other.nucleref[i];
  }
}

RNA::~RNA()
{
  if (nucleref)
  {
    delete[] nucleref;
    nucleref = nullptr;
  }
}

//----------Reference----------
RNA::reference::reference(size_t index, RNA *rna)
{
  this->position = index / nucles_per_elem;
  this->rna = rna;
  this->idx = index;
  this->shift = (size_t)((sizeof(size_t) * 8) - 2 - (index % nucles_per_elem) * 2);
}

RNA::reference::operator Nucl() const
{
  return (Nucl)(((rna->nucleref[position] & (BIT_MASK << shift))) >> shift);
}

Nucl RNA::reference::operator=(Nucl N)
{
  rna->nucleref[position] = ((rna->nucleref[(idx / nucles_per_elem)]) & (~(size_t)(3 << shift))) | (N << shift);
  return (Nucl)((rna->nucleref[position] & ((size_t)(3 << shift))) >> shift);
}

RNA::reference::~reference()
{
  this->rna = nullptr;
}
//-----------------------------

size_t RNA::get_uints_number()
{
  return this->uint_len;
}

size_t RNA::get_nucles_number()
{
  return this->n_number;
}

void RNA::resize()
{
  size_t *array = new size_t[uint_len * 2];
  memset(array, 0, uint_len * 2);
  for (int i = 0; i < uint_len; i++)
  {
    array[i] = nucleref[i];
  }
  delete[] nucleref;
  nucleref = array;
  uint_len = uint_len * 2;
}

void RNA::push_back(Nucl N)
{
  n_number += 1;
  if (n_number / nucles_per_elem + (n_number % nucles_per_elem >= 1) > uint_len)
  {
    resize();
  }
  (*this)[n_number - 1] = N;
}

Nucl RNA::pop_back()
{
  Nucl N = (*this)[n_number - 1];
  n_number--;
  uint_len = n_number * 2 / sizeof(size_t) / 8 + 1;
  size_t *temporary = nucleref;
  nucleref = new size_t[uint_len];
  for (int i = 0; i < uint_len; i++)
  {
    nucleref[i] = temporary[i];
  }
  delete[] temporary;
  return N;
}

void RNA::trim(size_t last_index)
{
  this->uint_len = last_index * 2 / sizeof(size_t) / 8 + 1;
  this->n_number = last_index;
  size_t *old_nucleref = this->nucleref;
  this->nucleref = new size_t[uint_len];
  memcpy(this->nucleref, old_nucleref, uint_len * sizeof(size_t));
  delete[] old_nucleref;
}

RNA_set RNA::split(size_t index)
{
  RNA_set set;
  RNA *second = new RNA(this->n_number - index);
  for (size_t i = 0; i < this->n_number - index; i++)
  {
    (*second)[i] = (*this)[i + index];
  }
  set.second = second;
  this->trim(index);
  set.first = new RNA(*this);
  return set;
}

Nucl RNA::get_complementary(Nucl N)
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
    if (r1[i] != get_complementary((*this)[i]))
      return false;
  }
  return true;
}

size_t RNA::cardinality(Nucl N)
{
  size_t counter = 0;
  for (size_t i = 0; i < n_number; i++)
  {
    if ((*this)[i] == N)
      counter++;
  }
  return counter;
}

std::unordered_map<Nucl, int, std::hash<int>> RNA::cardinality()
{
  std::unordered_map<Nucl, int, std::hash<int>> map;
  for (size_t i = 0; i < n_number; i++)
  {
    Nucl N = (*this)[i];
    map[N]++;
  }
  return map;
}

RNA::reference RNA::operator[](size_t position)
{
  return reference(position, this);
}

Nucl RNA::operator[](size_t position) const
{
  size_t idx = position * 2 / sizeof(size_t) / 8;
  size_t shift = ((sizeof(size_t) * 8) - 2 - (position % nucles_per_elem) * 2);
  return Nucl((this->nucleref[idx] & (BIT_MASK << shift)) >> shift);
}

RNA &RNA::operator=(const RNA &other)
{
  if (this->nucleref)
    delete[] this->nucleref;
  this->uint_len = other.uint_len;
  this->n_number = other.n_number;
  this->nucleref = new size_t[uint_len];
  for (size_t i = 0; i < uint_len; i++)
  {
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

  size_t shift = 8 * r1.uint_len - r1.n_number * 2;
  if ((r1.nucleref[r1.uint_len] >> shift) != (r1.nucleref[r1.uint_len] >> shift))
    return false;

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
  new_rna.nucleref = new size_t[new_rna.uint_len];
  for (size_t i = 0; i < n_number; i++)
  {
    new_rna[i] = (get_complementary((*this)[i]));
  }
  return new_rna;
}

RNA operator+(RNA &rna1, RNA &rna2)
{
  RNA new_rna(rna1);
  for (size_t i = 0; i < rna2.n_number; i++)
  {
    new_rna.push_back((Nucl)rna2[i]);
  }
  return new_rna;
}
