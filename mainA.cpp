#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

#define MAT_SIZE 200
typedef float* DynMat[MAT_SIZE];

//prototypes
void matShowDyn(const DynMat&, int, int);
void matMultDyn(const DynMat&, const DynMat&, DynMat&, int);

int main() {
    
    clock_t startTime, stopTime;
    double randFrac;
    int randRow, randCol, smallPercent;
    
    //for generating random numbers
    random_device random;
    default_random_engine engine(random()); //provides a random seed
    uniform_real_distribution<double> randFracDistribution(0.1,1);
    uniform_int_distribution<int> randIntDistribution(0,MAT_SIZE - 1);
    
    // non-sparse dynamic matrix
    DynMat matDyn, matDynAns;
    
    // allocate rows and initialize to 0
    for (int r = 0; r < MAT_SIZE; r++) {
        
        matDyn[r] = new float[MAT_SIZE];
        matDynAns[r] = new float[MAT_SIZE];
        
        for (int c = 0; c < MAT_SIZE; c++) {
            
            matDyn[r][c] = 0;
            matDynAns[r][c] = 0;
        }
    }
    
    // generate small% non-default values between .1 and 1
    smallPercent = MAT_SIZE/20.0 * MAT_SIZE;
    
    for (int r = 0; r < smallPercent; r++) {
        randRow = randIntDistribution(engine);
        randCol = randIntDistribution(engine);
        randFrac = randFracDistribution(engine);
        
        matDyn[randRow][randCol] = randFrac;
    }
    
    // 10x10 submatrix in lower right of original
    matShowDyn(matDyn, MAT_SIZE-10, 10);
    
    startTime = clock(); // ------------------ start
    matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
    stopTime = clock(); // ---------------------- stop
    
    // 10x10 submatrix in lower right of solution
    matShowDyn(matDynAns, MAT_SIZE - 10, 10);
    
    //output time elapsed and size of matrix
    cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    // clean up
    for (int r = 0; r < MAT_SIZE; r++)
    {
        delete matDyn[r];
        delete matDynAns[r];
    }
    
    cout << endl;
}

//outputs square submatrix
void matShowDyn(const DynMat &matrix, int start, int size)
{
    //checks bounds and sets defaults if bounds exceeded
    if (start < 0 || start + size > MAT_SIZE)
    {
        cout << "Out of bounds. Setting to default window..." << endl;
        start = 0;
        size = MAT_SIZE > 10 ? 10 : MAT_SIZE;
    }
    
    //outputs submatrix
    for (int r = start; r < start+size; r++)
    {
        for (int c = start; c < start+size; c++)
        {
            cout << setw(5) << fixed << setprecision(2);
            cout << matrix[r][c];
        }
        cout << endl;
    }
    cout << endl;
}

//matrix multiplication
void matMultDyn(const DynMat &mMat, const DynMat &nMat, DynMat &aMat, int size)
{
    double tempSum;
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tempSum = 0;
            for (int k = 0; k < size; k++)
            {
                tempSum += (mMat[i][k] * nMat[k][j]);
            }
            
            aMat[i][j] = tempSum;
        }
    }
}

/*
 The upper bound time complexity for matrix multiplication of MxM is O(N^3).
 The total running time is the running time of the statement inside the nested
 loops multiplied by the product of the sizes of all the loops. The statement
 within the loops is constant. The size of each loop is the same, N. Thus,
 1*N*N*N is N^3. We can also determine Θ(N^3) because the loop will
 never terminate early. Hence, the upper and lower bound is the same.
 
 1. What was the smallest M​ that gave you a non-zero time?
 99 with 0.01s
 
 2. What happened when you doubled M​ , tripled it, quadrupled it, etc? Give
 several M​ values and their times in a table.
 
 M value   Seconds
 100      0.01s
 200      0.04s
 300      0.19s
 400      0.39s
 500      0.86s
 600      1.31s
 700      2.20s
 800      3.38s
 900      6.06s
 1000      9.65s
 1100     12.54s
 
 3. How large an M​ can you use before the program refuses to run (exception or
 run-time error due to memory overload) or it takes so long you can't wait for
 the run?
 
 1200 took 17.66 seconds and I don't want to wait any longer.
 
 4. How did the data agree or disagree with your original time complexity
 estimate?
 
 The data agreed with my original estimate. After plotting the points
 on a graph, I saw they were comparable to O(N^3). The results became
 clearer once the 1 second threshold was broken.
 
 */
