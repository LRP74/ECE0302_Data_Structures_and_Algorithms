/** @file ExamInterface.hpp */
#ifndef EXAM_INTERFACE_
#define EXAM_INTERFACE_
#include <string>

// template <typename ItemType>
// class ExamInterface
// {
// public:
//    /** Gets the current score of the exam.
//    @return The score of the exam.*/
//    virtual ItemType getScore() const = 0;

// }; // end ExamInterface

//can an interface not be a template?
class GradeBook
{
   public:
      virtual bool addGrade(int grade, std::string studentName) =0;
      virtual double averageGrade() =0;  
   private:
      virtual void curve() =0;
};

// bool List::operator !=(const List& b) const
// {
//    if (b.size != size)
//    {
//       return true;   // if the lists aren't the same size then they can't be equal
//    }
//    for (int i = 0; i < size i++)
//    {
//       if (items[i] != b.items[i])   //if the current index i item does not equal the current index of the b item then not equal
//       {
//          return true;
//       }
      
//    }
   
//    return false;
   
// }





#endif