#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>


using namespace std;

const int mSize = 10; //to avoid variable parameters 
int r1, c1,	//matrix 1 dimensions
r2, c2, //matrix 2 dimensions
r3, c3; //dimentions of resultant matrix
				//declaring the matrices outside to avoid passing them, into functions
				//so they can have global scope

string propertyCheck; //for some singular matrix operations
double matone[mSize][mSize];
double mattwo[mSize][mSize];
double matResult[mSize][mSize];

//declaring user defined function prototypes
void matrixInitializer(double[][mSize], int rows, int columns);	//matrix input
void matDisplay(double[][mSize], int rows, int columns); //matrix console output

//menus
int mainMenu(void);
int subMenu1(void);
void about(void);
int sMatOp(void); //menu for single matrix operations
int mMatOp(void); //menu for multiple matrix operations

//operation-functions
void addition(void);
void subtraction(void);
void multiplication();
double determinant(double[][10], int);
void singularityCheck();
void scalarMultiplication(double[][10], double);

//filing functions
void fileCreation(void);
string operationGet(int);
void addToFile(string fileName, int operationType);	//will append results to the history file
void fileReader(string fileName);
void fileEraser();

//main-function
int main() {
	//variable declartions

	int back;
	int operation;
	int intHolder;
	string operationType;
	double det = 0.0; //determinant
	double scalarMultiplier;

jump1:
	system("cls");
	cout << "______________________________________________________________________________________________________________________________________\n";
	cout << endl;
	cout << "						MATRIX - CALCULATOR - PROJECT\n";
	cout << endl;
	cout << "______________________________________________________________________________________________________________________________________\n";
	cout << "\n";
	//-------------------------------<MENU_SELECTOR>-----------------------------------

	int mainSlctr = mainMenu();
	int subSlctr;

	//main-menu-switch
	switch (mainSlctr)
	{

	case 1:
		subSlctr = subMenu1();

		break;

	case 2:
		//<------------------file-reader-will-come-here-------------
		//----------------------------------------------------------
		//*********************
		cout << "_______________________________________________________________________________________\n";
		fileReader("history.txt");



		cout << "go back [1]\n";
		cout << "clear file data [-1]\n";
		cin >> back;
		if (back == 1)
			goto jump1;
		else if (back == -1) {
			fileEraser();
			goto jump1;
		}

		break;

	case 3:
		system("cls");
		about();

		goto end;
		break;

	default:

		break;
	}


	//-----------------------------<******>--------------------------------

	//---------------------------<getting--matrices>-------------------------------


	//submenu-matrix-type-operation-type switch
	switch (subSlctr) {

	case 1:
		//--------------------------<double-matrix-input>------------------------
		//               <<----matrix-1-initialization---->>
		cout << "_________________________________\n";
		cout << "MATRIX ONE\n";
		cout << "enter rows (max 10)\n";
		cin >> r1;
		while (r1 > 10 || r1 < 0) {
			cout << "invalid input try again\n";
			cin >> r1;
		}
		cout << "Enter columns (max 10)\n";
		cin >> c1;
		while (c1 > 10 || c1 < 0) {
			cout << "invalid input try again\n";
			cin >> c1;
		}
		matrixInitializer(matone, r1, c1);


		//               <<----matrix-2-initialization---->>
		cout << "_________________________________\n";
		cout << "MATRIX TWO\n";
		cout << "enter rows (max 10)\n";
		cin >> r2;
		while (r2 > 10 || r2 < 0) {
			cout << "invalid entry, try again\n";
			cin >> r2;
		}

		cout << "Enter columns (max 10)\n";
		cin >> c2;
		while (c2 > 10 || 2 < 0) {
			cout << "invalid entry, try again\n";
			cin >> c2;
		}
		matrixInitializer(mattwo, r2, c2);

		// 				<<----displaying matrices----->>
		cout << "_______________________________\n";
		cout << "matrix-A is:\n";			//matrix one
		matDisplay(matone, r1, c1);
		cout << endl;
		cout << "_______________________________\n";

		cout << "matrix-B is:\n";			//matrix two
		matDisplay(mattwo, r2, c2);
		cout << endl;


		//---------<operation-menu>----------
		operation = mMatOp();
		break;

	case 2:
		//               <<----matrix-1-initialization---->>
		cout << "______________________________\n";
		cout << "MATRIX ONE\n";
		cout << "enter rows\n";
		cin >> r1;
		cout << "Enter columns\n";
		cin >> c1;
		cout << "______________________________\n";
		matrixInitializer(matone, r1, c1);

		cout << "matrix-1 is:\n";
		matDisplay(matone, r1, c1);

		//-----------<operation-menu>--------------
		cout << "____________________________________________________________________\n";
		intHolder = sMatOp();
		operation = intHolder;

	case 3:
		system("cls");
		goto jump1;
		break;

	default:
		break;
	}

	//--------------------------operations---------------------------------
	cout << "______________________________________________________________\n";

	switch (operation) {
	case 1: //addition
	//checking for compatibilty
		if (r1 != r2 || c1 != c2) {
			cout << "These matrices can not be added\n";
			break;
		}
		else {
			//code for addition
			c3 = c1, r3 = r1; 	//same dimensions
			addition();
			cout << "The resulting matrix R is:\n";
			matDisplay(matResult, r3, c3);
		}


		break;
	case 2: //subtraction

	//checking for compatibilty
		if (r1 != r2 || c1 != c2) {
			cout << "These matrices can not be subtracted\n";
			goto end;
		}
		else {
			//code for subtraction
			c3 = c1, r3 = r1; 	//same dimensions
			subtraction();
			cout << "The resulting matrix R is:\n";
			matDisplay(matResult, r3, c3);
		}
		break;
	case 3: //multiplication
		//checking for compatibility
		if (c1 != r2) {
			cout << "These matrices are not compatible for multiplication\n";
		}
		else {
			r3 = r1, c3 = r2;
			multiplication();
			cout << "The resulting matrix R is:\n";
			matDisplay(matResult, r3, c3);
		}

		break;
	case 4: //singularity check
		det = determinant(matone, c1);
		cout << propertyCheck;

		break;
	case 5:	//determinant check
		if (c1 != r1) {
			cout << "can not find determinant, not a square matrix";
		}
		else
			det = determinant(matone, c1);

		cout << propertyCheck;
	case 6:
		cout << "Enter the scalar multiplier";
		cin >> scalarMultiplier;
		scalarMultiplication(matone, scalarMultiplier);
		
		cout << "The result is";

		matDisplay(matone, r1, c1);

	default:
		break;
	}
	//------------------------------</operations>----------------------------------------
	//-------------------------<output>and<fileSaving>-----------------------------

	switch (operation) {
	case 0:
		goto jump1;
		break;


	}
	//if the program runs successfully till here, a file will be created to store the result 
	//<------------------------------Filing-storing-the-results---------------------------->

	fileCreation();
	//appending infromation of the current session to the file

	addToFile("history.txt", operation);

	cout << "perform another operation? (Y/n)\n";
	char again;
	cin >> again;
	if (again == 'y' || again == 'Y')
		goto jump1;

end:
	cin.get();
	return 0;
}
/*<--------------<user-defined function definitions------------------>
  <------------------------------------------------------------------>*/


  //matrix-functions
void matrixInitializer(double arr[][mSize], int row, int col) {
	cout << "Enter the entries\n";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << "row " << i + 1 << " col " << j + 1 << " :";
			cin >> arr[i][j];
		}

	}
}
void matDisplay(double arr[][mSize], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i][j];
			if (j < col - 1)
				cout << '	';
		}
		cout << endl;
	}
}
//menu-functions
int mainMenu(void) {
	int slctr;
	cout << "_________\n";
	cout << "MAIN MENU\n";
	cout << "---------\n";
	cout << endl;
	cout << setw(1) << "choose a menu by entering the corresponding number\n";
	cout << endl;
	cout << setw(1) << "1.Perform operations. [1]\n";
	cout << setw(1) << "2.View History. [2]\n";
	cout << setw(1) << "3.Exit. [3]\n";
	cout << endl;


	cout << setw(1);
	cin >> slctr;
	while ((slctr != 1) && (slctr != 2) && (slctr != 3)) {
		cout << "invalid entry, try again\n";
		cin >> slctr;
	}
	cout << endl;
	return slctr;
}
int subMenu1() {
	int slctr;
	cout << "______________________________________________________________________________________________\n";
	cout << setw(2) << "multi-matrix operations [1]\n";
	cout << setw(2) << "single-matrix operations [2]\n";
	cout << setw(2) << "back to main menu [3]\n";
	cout << setw(3);
	cin >> slctr;
	while ((slctr != 1) && (slctr != 2) && (slctr != 3)) {
		cout << "invalid entry, try again\n";
		cin >> slctr;
	}
	cout << endl;
	return slctr;
}
int mMatOp() {
	int choice;
	cout << setw(3) << "CHOOSE AN OPERATION (press the corresponding number)\n";
	cout << endl;
	cout << setw(3) << "Matrix Addition [1]\n";
	cout << setw(3) << "Matrix Subtraction [2]\n";
	cout << setw(3) << "Matrix Multiplication [3]\n";
	cout << endl;
	cin >> choice;
	cout << endl;
	while (choice < 1 || choice > 3) {
		cout << "invalid input, try again\n";
		cin >> choice;
	}

	return choice;

}
int sMatOp() {
	int choice;
	cout << "CHOOSE AN OPERATION\n";
	cout << endl;
	cout << "Singularity Check [1]\n";
	cout << "Find determinant [2]\n";
	cout << "Find transpose [3]\n";
	cout << "Find Inverse [4]\n";
	cout << "Find adjoint [5]\n";
	cout << "check for row echelon form [6]\n";
	cout << "check for reduced row echelon form [7]\n";
	cout << "back to main menu [0] \n";
	cout << endl;
	cin >> choice;
	while (choice < 0 || choice > 7) {
		cout << "invalid input, try again\n";
		cin >> choice;
	}
	if (choice == 0)
		return 0;
	else
		return choice + 3;

}
void about() {
	cout << "matrix calculator version 2.0\nAll rights reserved.\n";
}
//operation-functions
void singularityCheck(void) {
	if (r1 != c1) {
		propertyCheck = "not a square matrix, only square matrices can be singular\n";
		
	}
	else {
		if (determinant(matone, c1) == 0)
			propertyCheck = "This matrix is singular\n";
		else
			propertyCheck = "This matrix is non-singular\n";
	}

}
void addition(void) {
	for (int i = 0; i < r3; i++) {
		for (int j = 0; j < c3; j++) {
			matResult[i][j] = matone[i][j] + mattwo[i][j];
		}
	}
}
void subtraction(void) {
	if (r1 != r2 || c1 != c2) {
		cout << "These matrices can not be added\n";


	}
	else {

		for (int i = 0; i < r1; i++) {
			for (int j = 0; j < c1; j++) {
				matResult[i][j] = matone[i][j] - mattwo[i][j];
			}
		}

	}
}
void multiplication() {
	for (int i = 0; i < r1; ++i)
		for (int j = 0; j < c2; ++j)
			for (int k = 0; k < c1; ++k)
			{
				matResult[i][j] += matone[i][k] * mattwo[k][j];
			}
}
void scalarMultiplication( double arr[][10], double n) {
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			matResult[i][j] = n * arr[i][j];
			
		}
	}
}
double determinant(double matrix[][10], int n) {

	
		double det = 0;
		double submatrix[10][10];
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++) {
				submatrix[i][j] = 0.0;
			}

		if (n == 2)
			return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
		else {
			//using recursion to fin
			for (int x = 0; x < n; x++) {
				int subi = 0;
				for (int i = 1; i < n; i++) {
					int subj = 0;
					for (int j = 0; j < n; j++) {
						if (j == x)
							continue;
						submatrix[subi][subj] = matrix[i][j];
						subj++;
					}
					subi++;
				}
				det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
			}
		}
		return det;
	}
}
//filing-functions
void fileCreation(void) {
	fstream resultFile;
	resultFile.open("history.txt", ios::in);
	//opening the file to check if it exists
	if (resultFile.fail()) {
		//creating the file if it does not exist

		resultFile.open("history.txt", ios::out);
		resultFile << "HISTORY\n";
		resultFile << "\n\n";

		//file created


	}
	//closing the file
	resultFile.close();

}
string operationGet(int n) {
	string type;
	switch (n) {
	case 1:
		type = "addition";
		break;

	case 2:
		type = "subtraction";
		break;

	case 3:
		type = "multiplication";
		break;
	case 4:
		type = "singularity check";
		break;
	case 5:
		type = "find determinant";
		break;

	case 6:
		type = "Scalar multiplication";
		break;

	case 7:
		type = "transpose";
		break;

	case 8:
		type = "adjoint";
		break;

	case 9:
		type = "echelon form check";
		break;

	case 10:
		type = "reduced echelon form check";
		break;
	}
	return type;
}

void fileReader(string filename) {
	fstream historyFile;
	string input;
	historyFile.open("history.txt", ios::in);
	if (historyFile) {



		while (getline(historyFile, input)) {
			cout << input << endl;
		}

	}
	historyFile.close();
}
void addToFile(string filename, int number) {	//to do <file-appender>
	string operationType = operationGet(number);
	fstream historyFile;
	historyFile.open("history.txt", ios::app);
	//the file is now open to appendse 8:


	//getting the current system time

	historyFile << "\n\n";
	historyFile << "operation performed on:	" << __TIME__ << "/" << __DATE__ << "\n";
	historyFile << "operation type:	" << operationType << "\n\pn";


	//appending matrix-1
	historyFile << "matrix 1: \n";
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			historyFile << *matone[i] << "	";
		}
		historyFile << "\n\n"; //using the standard \n as a delimeter
	}
	//appending matrix-2 & matrix-3(resultant)

	//this will only be for first 3 multi-matrix operations
	if (number > 0 && number < 4) {
		historyFile << "matrix 2: \n";

		for (int i = 0; i < r2; i++) {
			for (int j = 0; j < c2; j++) {
				historyFile << *mattwo[i] << "	";
			}
			historyFile << "\n\n";
		}
		//appending resultant matrix
		historyFile << "Resultant matrix: \n";
		for (int i = 0; i < r3; i++) {
			for (int j = 0; j < c3; j++) {
				historyFile << *matResult[i] << "	";
			}
			historyFile << "\n\n"; //using the standard \n as a delimeter

		}

		//result of single matrix operations
		if (number == 4 || number == 9 || number == 10 ) {

			historyFile << propertyCheck << "\n";
		}



	}

	historyFile << "_______________________________________________\n";
	historyFile.close();

}
void fileEraser() {
	fstream historyFile;

	historyFile.open("history.txt", ios::out);
	historyFile.close();

}
