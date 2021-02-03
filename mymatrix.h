/*mymatrix.h*/

// 
// << Raj Kapadia >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)
  ROW* helperR; 
  

public:
  /*
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T. Creates an object.
  //*/
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  /*
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R (parameter) rows, 
  // where each row has C (parameter) columns. All elements are initialized to 
  // the default value of T. Creates an object.
  */
  mymatrix(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");

    Rows = new ROW[R];  // an array with R ROW structs:
    NumRows = R;

    // initialize each row to have C columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  // an array with C elements of type T:
      Rows[r].NumCols = C;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }


  /*
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //   Takes another matrix as a parameter to copy. Creates an object.
  */
  mymatrix(const mymatrix<T>& other)
  {
    Rows = new ROW[other.numrows()];  // an array with the same number of ROW structs as parameter matrix:
    NumRows = other.numrows();

    
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[other.numcols(r)];  // an array with same number of elements of type T as parameter matrix's row:
      Rows[r].NumCols = other.numcols(r);

      // copy elements over:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = other.Rows[r].Cols[c];  
      }
    }
  }


  /*
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  */
  int numrows() const
  {
    return NumRows;
  }
  

  /*
  // numcols
  //
  // Returns the # of columns in row r (parameter).  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  */
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");
    return Rows[r].NumCols;
  }


  /*
  // growcols
  //
  // Grows the # of columns in row r (parameter) to at least C (parameter).  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  // Returns nothing, modifies existing object.
  */
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
      
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");
      
    if (C<=Rows[r].NumCols){ //stop function if program is trying to shrink or keep the number of columns the same
        return;
    }
    else{
        
          T *helper = new T[C];//declare new temp column structure, with C length
          
          for (int i=0;i<Rows[r].NumCols;i++){ //loop through the current column struct, copy elements into new struct
              helper[i]=Rows[r].Cols[i];
          }
          for (int j=Rows[r].NumCols;j<C;j++){//add default values to new column struct, until index C
              helper[j]=T{};
          }
          
          delete[] Rows[r].Cols;
          Rows[r].Cols=helper;     //Makes current column struct equal temp struct, temp struct deleted
          Rows[r].NumCols=C;       
    }
  }


  /*
  // grow
  //
  // Grows the size of the matrix so that it contains at least R (parameter) rows,
  // and every row contains at least C (parameter) columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // Returns nothing, modifies existing object.
  */ 
  void grow(int R, int C)
  {
    if (R < 1)
      throw invalid_argument("mymatrix::grow: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::grow: # of cols");
      
    int counter=0;
    if (R<=NumRows){ //Runs if we're not adding new rows
        mymatrix<T> helperM(NumRows,1);//temp matrix with same number of rows as this matrix
        for (int r=0;r<NumRows;r++){
                    if (C <= Rows[r].NumCols){
                        helperM.growcols(r,Rows[r].NumCols);//grows temp's columns to this column length                                        
                    }
                    else{
                        helperM.growcols(r,C); //grows temp's column to C length, adds new columns basically                       
                    }
                    for (int j=0;j<Rows[r].NumCols;j++){                           
                        helperM.Rows[r].Cols[j]=Rows[r].Cols[j];   } //copies elements over            
        }
        *this=helperM;
     }
    else{//Runs if we're adding new rows
        mymatrix<T> helperM(R,1);//temp matrix with R number of rows
        for (int r=0;r<R;r++){
            
            if (r<NumRows){
                    if (C <= Rows[r].NumCols){
                        helperM.growcols(r,Rows[r].NumCols);
                                            
                    }
                    else{
                        helperM.growcols(r,C);
                    }
                    for (int j=0;j<Rows[r].NumCols;j++){                           
                            helperM.Rows[r].Cols[j]=Rows[r].Cols[j];   }              
            }
            else if (r>=NumRows){
                for (int c=0;c<C;c++){ //loop to increment NumRows using counter variable everytime we add new rows
                        helperM.growcols(r,C);
                        counter++;
                }   
            }
            
        }
        NumRows=counter;
        *this=helperM;     
     }
  }


  /*
  // size
  //
  // Returns the total # of elements in the matrix.
  */
  int size() const
  {
    int matSize=0;
    for (int r = 0; r < NumRows; ++r)
    {
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        matSize++;
      }
    }

    return matSize;
  }


  /*
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //    Takes r and c as parameters, corresponding to matrix row and column.
  */
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");
      
    return Rows[r].Cols[c];
  }


  /*
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //    Takes r and c as parameters, corresponding to matrix row and column.
  */
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    return at(r,c); //calls .at() function, since it serves the same purpose
  }

  /*
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value (parameter),
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  */
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result(*this);//make temp matrix, copy of current matrix

    for (int r = 0; r < NumRows; ++r)
    {
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        result.Rows[r].Cols[c]=Rows[r].Cols[c]*scalar;//multiply each element in matrix by scalar value
      }
      
    }
    return result;
  }


  /*
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  // Takes another matrix as a parameter, returns a new matrix. 
  */
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    

    //
    // both matrices must be rectangular for this to work:
    //

    // if (this matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: this not rectangular");
       for (int i=0;i<this->NumRows;i++){
           if (this->Rows[i].NumCols!=this->Rows[0].NumCols)
               throw runtime_error("mymatrix::*: this not rectangular");
       }
    
    // if (other matrix is not rectangular)
    //   throw runtime_error("mymatrix::*: other not rectangular");
        for (int i=0;i<other.NumRows;i++){
           if (other.Rows[i].NumCols!=other.Rows[0].NumCols)
               throw runtime_error("mymatrix::*: other not rectangular");
       }
    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    // if (this matrix's # of columns != other matrix's # of rows)
    //   throw runtime_error("mymatrix::*: size mismatch");
       if (this->Rows[0].NumCols!= other.numrows())
           throw runtime_error("mymatrix::*: size mismatch");
    //
    // Okay, we can multiply:
    //
       mymatrix<T> result(this->NumRows,other.Rows[0].NumCols); //make temp matrix
       for (int r=0;r<this->NumRows;r++){ //loop through the two matrices, multiplying/adding as necessary
                                          //and adding the results to temp matrix. Uses TA provided psuedocode and 
                                          //matrix multiplication formula. 
           for (int c=0;c<other.Rows[0].NumCols;c++){
               for (int i=0;i<other.NumRows;i++){
                   result(r,c) += (this->Rows[r].Cols[i]*other.Rows[i].Cols[c]);
               }
           }
       }
    

    return result;
  }


  /*
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  // Returns nothing, just loops through the matrix and prints every element.
  */
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};

