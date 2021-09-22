#include "RNA.hpp"

  // CONSTRUCTORS
  RNA::RNA(Nucl N, size_t const capacity)
  {
    n_number = capacity;
    uint_len = capacity * 2 / sizeof(uint32_t) / 8 + 1;
    if (capacity == 0)
      nucleref = nullptr;
    nucleref = new uint32_t[uint_len];
    for(size_t i = 0; i < n_number; i++){
      
    }
  }

  RNA::RNA()
  {
    this->uint_len = 0;
    this->n_number = 0;
    this->nucleref = nullptr
  }

  //COPY CONSTRUCTOR
  RNA::RNA(RNA &other)
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
    this->nucleref.~bit_vec();
    std::cout << "RNA";
  }

  void add();

  /* operator== ();
  operator!= ();
  operator ! ();
  operator[] ();

  isComplementary(RNK &);
  split(size_t index);

  DNK(RNK&, RNK&); */
};

int main()
{
  RNA a;
  return 0;
}