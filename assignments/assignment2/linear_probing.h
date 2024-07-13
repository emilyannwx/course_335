#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace {

// Internal method to test if a positive number is prime.
bool IsPrimeL(size_t n) {
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
int NextPrimeL(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeL(n)) n += 2;  
  return n;
}

}  // namespace

// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrimeL(size))
    { MakeEmpty(); }
  
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


//   bool Insert(HashedObj && x) {
//     // Insert x as active
//     size_t current_pos = FindPos(x);
//     if (IsActive(current_pos))
//       return false;
    
//     array_[current_pos] = std::move(x);
//     array_[current_pos].info_ = ACTIVE;

//     // Rehash; see Section 5.5
//     if (++current_size_ > array_.size() / 2)
//       Rehash();

//     return true;
//   }

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

    //get number of probes (for testing)
    size_t GetProbeCount(const HashedObj & x) const {
    size_t probe_count = 0;
    size_t current_pos = InternalHash(x);
    
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
      current_pos += 1;  // Linear probing
      if (current_pos >= array_.size())
        current_pos -= array_.size();
        probe_count++;
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

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += 1;  // Compute ith probe.
      //offset += 2;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeL(2 * old_array.size()));
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
};
    





#endif  //LINEAR_PROBING_H