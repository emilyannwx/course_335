//Emily Ann Willix
#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>



namespace {

// Internal method to test if a positive number is prime.
bool IsPrimeD(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrimeD(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeD(n)) n += 2;  
  return n;
}

}  // namespace


// Double hashing  implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101, int r = 89) : array_(NextPrimeD(size)), R_(r)
    { MakeEmpty();
 }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  
  }
  bool Insert(HashedObj && x) {
     // Insert x as active
     size_t current_pos = FindPos(x);
     if (IsActive(current_pos))
       return false;

     array_[current_pos] = std::move(x);
     array_[current_pos].info_ = ACTIVE;

     // Rehash; see Section 5.5
     if (++current_size_ > array_.size() / 2)
       Rehash();

     return true;
   }
    
  
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
  // returns the size of the table
   size_t GetTableSize() const{
     return array_.size();
   }

  /
  size_t GetProbeCount(const HashedObj & x) const {
    size_t probe_count = 0;
    size_t offset = Hash2(x); //calculate new offset using hash function
    size_t current_pos = InternalHash(x);
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
        current_pos += offset;  //double hash
        if (current_pos >= array_.size())
            current_pos -= array_.size();
        ++probe_count;
    }
    return probe_count + 1; // +1 for the final probe (found or empty)
}
 

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  int R_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = Hash2(x); //calculate new offset using hash function
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += offset;  // double hash.
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeD(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  size_t Hash2(const HashedObj & x) const{
    static std::hash<HashedObj> hf;
   // std::cout << "Hash2 called with R_ = " << R_  << std::endl; // test output
    return R_ - (hf(x) % R_); 

  }
};

#endif  // DOUBLE_HASHING_H
