#include <iostream>
#include <fstream>
#include <string>
#include "mymatrix.h"

using namespace std;




int main(){
    //Test NumRows and NumCols, default constructor
    cout<<"Test NumRows and NumCols, default constructor------"<<endl;
    mymatrix<int> tNC;
    cout<<"Default matrix: "<<endl;
    tNC._output();
    cout<<endl;
    cout<<"Number of rows: "<<tNC.numrows()<<endl;
    cout<<"Number of columns in row 1: "<<tNC.numcols(0)<<endl;
    
    
    
    
    
    //Test parameterized and copy constructor
    cout<<endl;
    cout<<"Test parameterized and copy constructor---------"<<endl;
    mymatrix<int> c1(6,6);
    for (int j=0;j<c1.numrows();j++){ //fill matrix with 5's
        for (int c=0;c<c1.numcols(j);c++){
            c1(j,c)=5;
        }
    }
    mymatrix<int> c2(c1); //copied matrix
    c1(2,2)=4;//change a value, to dinstinguish the two matrices
    cout<<"Matrix c1, after a value has been changed to 4: "<<endl;
    cout<<endl;
    c1._output();
    cout<<"Matrix c2, a copy of the original matrix c1: "<<endl;
    c2._output();
    
    
    
    
    
    
    
    //Test growcols
    cout<<endl;
    cout<<"Test growcols-------"<<endl;
    mymatrix<int> g1(6,6);
    for (int j=0;j<g1.numrows();j++){ //fill matrix with 5's
        for (int c=0;c<g1.numcols(j);c++){
            g1(j,c)=5;
        }
    }
    cout<<"Original matrix before growcols, filled with 5's: "<<endl;
    g1._output();
    cout<<endl;
    g1.growcols(2,10);//grow the 3rd row to 10 columns
    cout<<"Original matrix after growcols(2,10): "<<endl;
    g1._output();
    cout<<endl;
    g1.growcols(2,6);//"shrink" columns, the matrix should remain the same
    cout<<"attempt to shrink the matrix back to original (growcols(2,6)), shouldn't work: "<<endl;
    g1._output();
    
    
    
    
    
    
    
    
    //Test grow
    cout<<endl;
    cout<<"Test grow-----------------"<<endl;
    mymatrix<int> g2(5,5);
    for (int j=0;j<g2.numrows();j++){ //fill matrix with 5's
        for (int c=0;c<g2.numcols(j);c++){
            g2(j,c)=5;
        }
    }
    cout<<"Matrix before grow, filled with 5's: "<<endl;
    g2._output();
    cout<<endl;
    mymatrix<int> g10(g2);
    g10.grow(10,10);//grow copy of g1 matrix to 10x10
    cout<<"Grow g1 to 10x10: "<<endl;
    g10._output();
    cout<<endl;
    
    mymatrix<int> g22(g2);
    g22.grow(2,2);//atempt to "shrink" g1 to a 2x2
    cout<<"Attempt to shrink g1 to 2x2, shouldn't work: "<<endl;
    g22._output();
    cout<<endl;
    
    mymatrix<int> g102(g2);
    g102.grow(10,2);//copy of g1 should keep current 5x5, and add 5 new rows with 2 columns in each new row
    cout<<"Grow g1 by (10,2), should keep current 5x5 and add 5 new rows with 2 columns in each new row: "<<endl;
    g102._output();
    cout<<endl;
    
    mymatrix<int> g210(g2);
    g210.grow(2,10);//copy of g1 should keep current 5x5, and add 5 new columns in each row without deleting any rows
    cout<<"Grow g1 by (2,10), should keep current 5x5, and add 5 new columns in each row without deleting any rows: "<<endl;
    g210._output();
    cout<<endl;
    
    
    
    
    
    
    
    
    //Test size
    cout<<endl;
    cout<<"Test size--------------------------"<<endl;
    mymatrix<int> s1(6,6);
    cout<<"6x6 matrix: "<<endl;
    s1._output();
    cout<<endl;
    cout<<"Size of matrix: "<<s1.size()<<endl; //print out size of 6x6 matrix
    cout<<endl<<endl;
    s1.growcols(3,10);
    cout<<"Matrix after growcols(3,10): "<<endl;
    s1._output();
    cout<<endl;
    cout<<"Size of matrix after growcols: "<<s1.size()<<endl;
    
    
    
    
    
    
    
    
    //Test scalar
    cout<<endl;
    cout<<"Test scalar------------------------------"<<endl;
    mymatrix<int> s2(5,5);
    cout<<"5x5 matrix, filled with 4's: "<<endl;
    for (int j=0;j<s2.numrows();j++){ //fill matrix with 4's
        for (int c=0;c<s2.numcols(j);c++){
            s2(j,c)=4;
        }
    }
    s2._output();
    cout<<endl;
    cout<<"Matrix multiplied by scalar of 2: "<<endl;
    int scale=2;
    s2=s2*2;
    s2._output();
    cout<<endl;
    cout<<"Matrix then grown: "<<endl;
    s2.grow(8,8);
    s2._output();
    cout<<endl;
    cout<<"Grown matrix then has two elements changed to 10 and 15: "<<endl;
    s2(7,7)=10;
    s2(3,6)=15;
    s2._output();
    cout<<endl;
    cout<<"New matrix scaled by 3: "<<endl;
    s2=s2*3;
    s2._output();
    
    
    
    
    
    
    
    
    //Test matrix multiplication
    cout<<endl;
    cout<<"Test matrix multiplication---------------------"<<endl;
    mymatrix<int> mM(4,6);
    for (int j=0;j<mM.numrows();j++){ 
        for (int c=0;c<mM.numcols(j);c++){
            mM(j,c)=4;
        }
    }
    mM(0,0)=5;
    mM(3,3)=12;
    mM(1,2)=20;
    
    mymatrix<int> m2(6,6);
    for (int j=0;j<m2.numrows();j++){ 
        for (int c=0;c<m2.numcols(j);c++){
            m2(j,c)=5;
        }
    }
    m2(0,0)=13;
    m2(3,3)=6;
    m2(1,2)=5;
    m2(5,5)=25;
    m2(3,1)=16;
    cout<<endl;
    cout<<"Matrix 1: "<<endl; //matrix 1, with some changed values
    mM._output();
    cout<<endl;
    cout<<"Matrix 2: "<<endl;//matrix 2, with some changed values
    m2._output();
    cout<<endl;
    cout<<"Matrix 1 * Matrix 2: "<<endl;
    mymatrix<int> m3;
    m3=mM*m2;
    m3._output();
    
    
    
    
    
    
    
    
    //Combination test
    cout<<"Combination test------------------------------------"<<endl;
    mymatrix<int> mat1(5,5);
    for (int j=0;j<mat1.numrows();j++){ 
        for (int c=0;c<mat1.numcols(j);c++){
            mat1(j,c)=4;
        }
    }
    cout<<"First matrix: "<<endl;
    mat1._output();
    
    mat1(2,2)=10;
    mat1(4,1)=1;
    mat1(1,4)=17;
    for (int i=0;i<mat1.numrows();i++){//grow mat1 to 10 columns, for all its rows 
        mat1.growcols(i,10);
    }
    cout<<endl;
    cout<<"mat1 after growcols, all colums grown to toal of 10, and element editing: "<<endl;
    mat1._output();
    
    mat1.grow(9,10);
    cout<<endl;
    cout<<"mat1 after grow, should make matrix 9x10: "<<endl;
    mat1._output();
    
    mat1=mat1*3;
    cout<<"mat1*3: "<<endl;
    mat1._output();
    
    mymatrix<int> mat2(10,3);
    for (int j=0;j<mat2.numrows();j++){ 
        for (int c=0;c<mat2.numcols(j);c++){
            mat2(j,c)=2;
        }
    }
    mymatrix<int> mat3;
    mat3=mat1*mat2; //multiply matrices
    cout<<endl;
    cout<<"mat1*new 10x3 matrix mat2, should output a 9x3 matrix: "<<endl;
    mat3._output();
    
    
  
    
    
    
    //Test string
    cout<<endl;
    cout<<"Test string datatype---------------------------------------"<<endl;
    mymatrix<string> str;
    for (int j=0;j<str.numrows();j++){ //Fill matrix with "Hello"'s.
        for (int c=0;c<str.numcols(j);c++){
            str(j,c)="Hello";
        }
    }
    cout<<endl;
    cout<<"Default matrix filled with Hello strings: "<<endl;
    str._output();
    cout<<endl;
    cout<<"Grow matrix to 6x7, and change all string to Hi: "<<endl;
    str.grow(6,7);
    for (int j=0;j<str.numrows();j++){ //Fill matrix with "Hi"'s.
        for (int c=0;c<str.numcols(j);c++){
            str(j,c)="Hi";
        }
    }
    str._output();        
    
    
}