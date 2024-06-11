// Emily-Ann Willix
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
// ADDING A NEW COMMENT
namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D() : size_(0), sequence_(nullptr){};

    // Copy-constructor.
    Points2D(const Points2D &rhs){
       size_ = rhs.size_; 
       if (size_ == 0){
            sequence_ = nullptr;
       }else{
            sequence_ = new std::array<Object, 2> *sequence_;
            for(int i = 0, i < size_; i++){
                sequence_[i] = rhs.sequence_[i];
            }
       }
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs){
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs){
        size_ = rhs.size_;
        rhs.size_ = 0;
        if (size_ == 0){
            sequence_ = nullptr;
       }else{
            sequence_ = new std::array<Object, 2> *sequence_;
            for(int i = 0, i < size_; i++){
                sequence_[i] = rhs.sequence_[i];
            }
       }
       delete[] rhs.sequence_;
       rhs.sequence_ = nullptr;
    }
    

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs){
       std::swap(size_, rhs.size_);
       std::swap(sequence_, rhs.sequence_); 
    }

    ~Points2D(){
        delete[] sequence_;
        sequence_ = nullptr;
        size_ = 0;
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        // Provide code.
    }

    size_t size() const {
        // Code missing.
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        // Code missing.
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        // Code missing.
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        // Code missing.
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        // Code missing.
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_