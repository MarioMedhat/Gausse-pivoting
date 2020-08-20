// BY : MARIO MEDHAT
// GITHUB REPOSITORY LINK : https://github.com/MarioMedhat/Gausse-pivoting

// In this project what we target is to get an array as input 
// from the user and solve (get the value of) every variable

// what is gausse pivoting method?
// it is an algorithm applied to a matrix to get the value
// of every variable in a system of equations

// How it is working?
// to answer this question we are going to take an example
// and this is the same example used as the test case 

// 15  x1 + 17  x2 + 19   x3 = 3.89
// 0.3 x1 + 0.4 x2 + 0.55 x3 = 0.095 
// 1   x1 + 1.2 x2 + 1.5  x3 = 0.282

// to solve it we are going to put all these data into a matrix
// the matrix representation is the same as the equation order
// first we are going to update these 3 equations (matrix rows)
// the last one we want it to contain only one variable 'x3'
// then like that we solved x3
// the second equation to contain 2 variable 'x3' and 'x2'
// and as we got previously 'x3', now we can get 'x2'
// after that we can solve the fisrt equation for 'x1'

// the solution :
// first we will devide row 2 and row 3 by the coeficient of x1 
// and multiply them by the coeficient of x1 in row 1
// this number is going to be callced 'pivot_constant' in the code
// as the new coeficient of x1 will be in row 2 and row 3 the same of row 1

// then the matrix will be
// 15 17 19   3.89
// 15 20 27.5 4.75
// 15 18 22.5 4.23

// then we will make the following operations
// row 2 = row 2 - row 1
// row 3 = row 3 - row 1

// then the matrix will be
// 15 17 19   3.89
// 0  3  8.5  0.86
// 0  1  3.5  0.34

// then we are going to do the same steps done with x1 but for x2
// and these steps are going to be with row 2 and row 3 only
// as to make x2 in row 2 = 0

// then the matrix will be
// 15 17 19   3.89
// 0  3  8.5  0.86
// 0  0  2    0.16

// now we have x3 = 0.16/8 = 0.08
// x2 = ( 0.86 - ( 8.5 * x3 ) ) / 3 = 0.06
// x1 = ( 3.89 - ( 19 * x3 ) - ( 17 * x2 ) ) / 15 = 0.09

// and now lets start coding 

#include <iostream>
using namespace std;

// this is the function that calculates the gausse pivote
// it takes the input system matrix, number of variables, and the answer array
void gaus_with_pivoting(double system[][11], double answer[], int number) {

	// this is the constant that is equal to values 
	// that the rows are going to be multiplied by
	double pivot_constant = 0;

	// define the counter that indicates 
	// the row and column that we are working in
	int row_counter = 0;
	int col_counter = 0;

	// define the variable that indicates the index of the variable
	// that we want to make = 0 in the rest rows
	int step_counter = 0;

	// define the function main loop
	// quit when we reach the last variable as this is the only one
	// that we do not want to make = 0 in anny row
	while (step_counter < number - 1) {

		// make the row counter = the index of the element that we want to zero
		// when we wanted to zero x1 we updated row 2 and row 3 
		// when we wanted to zero x2 we updated row 3 
		// so as a general case, we update row from n where n is the variable index
		// to the last row

		// so we give the row counter a value of the element index
		row_counter = step_counter;

		// start updating the rows 
		while (row_counter < number) {

			// update the value of pivot constant
			pivot_constant = system[row_counter +1][step_counter] / system[step_counter][step_counter];

			// reset the column counter (element counter)
			col_counter = 0;

			// start updating each element in the row
			while (col_counter <= number) {

				// update each element in the row
				system[row_counter +1][col_counter] -= system[step_counter][col_counter] * pivot_constant;

				// increase the counter by 1 to go to next element
				col_counter++;

			}

			// increase the counter by 1 to go to next row
			row_counter++;
		}

		// increase the counter by 1 to go to next element
		step_counter++;
	}

	// reset the counters

	// column counter = 0 to update every element
	// this step could be skipped for column counter only as 
	// it will be updated automaticaly in every iteration
	col_counter = 0;

	// row counter to the number of variables - 1
	// to start from the last row to the first one
	row_counter = number - 1;

	// start calculating
	while (row_counter >= 0) {

		// give the colum counter a value of number - 1
		// as this is equal to the index of the last variable
		col_counter = number - 1;

		// go to the array of answers, in the index of the variable and
		// and save the value of the last element in the row
		answer[row_counter] = system[row_counter][number];

		// start a loop to subtitute the vaulues of the variables * their coeficient
		// and the condition to entre the loop is col_counter > row_counter
		// so as to make for the variables only after the one that we want to calculate
		while (col_counter > row_counter) {

			// make the subtraction
			answer[row_counter] = answer[row_counter] - (system[row_counter][col_counter] * answer[col_counter]);
			
			// go to previous variable
			col_counter--;

		}

		// last thing is to devide the value in the ansewr array 
		// by the coeficient of the variable in the row
		answer[row_counter] = answer[row_counter] / system[row_counter][col_counter];
		
		// go to previous row
		row_counter--;

	}

}


int main() {

	// test case
	double inp[10][11] = { {15   , 17 , 19 , 3.89 } ,{0.3 , 0.4    , 0.55 , 0.095} ,{1 , 1.2 , 1.5   , 0.282 } };
	int num = 3;
	double ans[10] = { 0 };

	gaus_with_pivoting(inp, ans, num);

	for (int i = 0; i < num; i++) {
		cout << ans[i];
		cout << "\n";
	}
	return 0;

}