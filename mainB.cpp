#include <iostream>
#include <iomanip>
#include <random>

#include "SparseMatWMult.h"

using namespace std;

#define MAT_SIZE 3200
typedef SparseMatWMult<float> SpMat;

int main() {
    
    clock_t startTime, stopTime;
    double randFrac;
    int randRow, randCol, smallPercent;
    
    //for generating random numbers
    random_device random;
    default_random_engine engine(random()); //provides a random seed
    uniform_real_distribution<double> randFracDistribution(0.1,1);
    uniform_int_distribution<int> randIntDistribution(0,MAT_SIZE - 1);
    
    // sparse matrices
    SpMat matOrig(MAT_SIZE, MAT_SIZE);
    SpMat matAnsw(MAT_SIZE, MAT_SIZE);
    
    // generate small% non-default values between .1 and 1
    /*smallPercent = MAT_SIZE/20.0 * MAT_SIZE;
    
    for (int r = 0; r < smallPercent; r++) {
        randRow = randIntDistribution(engine);
        randCol = randIntDistribution(engine);
        randFrac = randFracDistribution(engine);

        matOrig.set(randRow, randCol, randFrac);
    }*/
    
    matOrig.set(0,0,2);
    matOrig.set(1,0,2);
    matOrig.set(2,1,2);
    matOrig.set(1,1,3);
    matOrig.set(2,0,1);
    
    // 10x10 submatrix in lower right of original
    matOrig.showSubSquare(MAT_SIZE - 10, 10);
    
    startTime = clock(); // ------------------ start
    matAnsw.matMult(matOrig, matOrig, MAT_SIZE);
    stopTime = clock(); // ---------------------- stop
    
    // 10x10 submatrix in lower right of solution
    matAnsw.showSubSquare(MAT_SIZE - 10, 10);
    
    //output time elapsed and size of matrix
    cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    cout << endl;
}
