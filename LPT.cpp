/*
 Created by Sahar Kausar (Fall 2015 COP3530 - Data Structures with C++)
 Please do not copy or redistribute without permission.
 
 Assignment: Longest Processing Time
 */

/**
 What the program does:
 
Scheduling is an NP-hard optimization problem. However, it is applicable in a vast number of fields and situations. An often used heuristic for this problem is the Longest Processing Time algorithm. The Longest Processing Time algorithm is implemented as follows. The algorithm will be implemented in two versions using two different representations of a minimum priority queue. The first implementation will use an array-based  min-heap. The second implementation will use a pointer-based min height-biased leftist tree.
 
 For both implementations of the Min Priority Queue data structure, the following is implemented: a constructor, destructor, empty, size, push, top, and pop functions.
 -	The meld function of the leftist heap implementation is recursive.
 -	The empty function returns a bool of whether or not the priority queue is empty.
 -	The size function returns the current number of elements in the priority queue.
 -	The push function inserts an element into the priority queue.
 -	The top function returns the element with the min priority.
 -	The pop function removes the element with the min priority.
 When running the dataset on each version, the finishing time is outputted.
 The program will also print the schedule.

 
 Example Run:
 
 OUTPUT>> Enter number of job(s):
 USER INPUT >> 7
 OUTPUT>> Enter number of machine(s):
 USER INPUT >> 3
 OUTPUT>> Enter Processing Time(s):
 USER INPUT >> 14
 USER INPUT >> 7
 USER INPUT >> 10
 USER INPUT >> 6
 USER INPUT >> 2
 USER INPUT >> 3
 USER INPUT >> 5
 
 OUTPUT>> Min Heap Finishing Time: 16
 OUTPUT>> Schedule:
 OUTPUT>> Machine 1: 14, 2
 OUTPUT>> Machine 2: 10, 5
 OUTPUT>> Machine 3: 7, 6, 3
 OUTPUT>> Time Elapsed: 3.882e-06
 
 OUTPUT>> Height Biased Leftist Tree Finishing Time: 16
 OUTPUT>> Schedule:
 OUTPUT>> Machine 1: 14, 2
 OUTPUT>> Machine 2: 10, 5
 OUTPUT>> Machine 3: 7, 6, 3
 OUTPUT>> Time Elapsed: 3.927e-06
 
 USER INPUT >> Note: Your elapsed times will likely differ from these.

 
 **/

/**
 How to Compile and Execute:
 
 Download the file to your desired root folder on your computer. Open the terminal or executable IDE program to compile and run the file. Enter the following in the quotes (make sure to omit the quotes): "g++ -o (desiredNameOfFile) LPT.cpp"
 
 For example, you may enter the following: "g++ -o LPT LPT.cpp"
 
 The program will then compile. Run the program by typing "./(desiredNameOfFile)"
 
 In the above example, you may have entered: "./LPT"
 
 The program will then run and the user may follow the prompt. Enjoy!
 
 **/

#include <iostream>
#include <algorithm>
#include <functional>
#include <ctime>
#include <vector>

using namespace std;

template<class T>
class ArrayMinHeap {
private:
	int jobNumber;
	int machineNumber;
	vector<T> processingTimesArray;

	int *priorityQueue;
	int heapSize;
	int arrayLength;

	int *tempQueue;

	T **machineLength;

	int *rowSums;

	//Used for Inserting
	int LeftChildPosition(int position) {
		//return 2 * position;
		return 2 * position + 1;
	}

	int RightChildPosition(int position) {
		//return 2 * position + 1;
		return 2 * position + 2;
	}

	int ParentPosition(int position) {
		//int x = (position) / 2;
		int x = (position - 1) / 2;
		return x;
	}

	void moveDown(int position);
	
	int lowestValue(vector<vector<int> > sum);

	int lowRowSum(); //Returns machineLength row with lowest sum to use as 
	int largeRowSum(); //Returns Heap Finish Time
	void swap();


public:
	ArrayMinHeap(int jobs, int machines, int *processingTimes); //Constructor	
	bool empty(); //Returns a bool of whether or not the priority queue is empty
	int size(); //Returns the current number of elements in the priority queue
	void push(int value); //Inserts an element into the priroty queue
	int top(); //Returns the element with the min priority
	void pop(); //Removes the element with the min priority
	void simulate(); //Run LPT simulation
	~ArrayMinHeap(); //Destructor
};

//Array MinHeap Constructor
template <class T>
ArrayMinHeap<T>::ArrayMinHeap(int jobs, int machines, int *processingTimes) {

	//Initialize private variables
	jobNumber = jobs;
	machineNumber = machines;

	for (int i = 0; i < jobNumber; i++)
	{
		processingTimesArray.push_back(processingTimes[i]);
	}

	heapSize = 0;

	//Sort jobs in descending order for LPT
	sort(processingTimesArray.begin(), processingTimesArray.end());
	//reverse(processingTimesArray.begin(), processingTimesArray.end());



	arrayLength = machineNumber;





	simulate();

}

//Returns a bool of whether or not the priority queue is empty
template <class T>
bool ArrayMinHeap<T>::empty() {
	return (heapSize == 0);
}

//Returns the current number of elements in the priority queue
template <class T>
int ArrayMinHeap<T>::size() {
	return heapSize;
}


template <class T>
void ArrayMinHeap<T>::swap() {
		
	int tempPos = 0;

	for (int i = 0; i < machineNumber; i++)
	{
		for (int j = 0; j < machineNumber - i -1; j++)
		{
			if (priorityQueue[j] > priorityQueue[j+1])
			{
				tempPos = priorityQueue[j];
				priorityQueue[j] = priorityQueue[j + 1];
				priorityQueue[j + 1] = tempPos;
			}
		}
	}

	//for (int i = 0; i < machineNumber; i++)
	//{
	//	cout << priorityQueue[i] << ' ';
	//}

	//cout << endl;

}


//Inserts an element into the priroty queue
template <class T>
void ArrayMinHeap<T>::push(int value) {

	int parentPos;
	int position;

	heapSize++;
	position = heapSize - 1;
	priorityQueue[position] = value;

	//Find place for new value

	//No need to find place if first element
	while (position != 0) {
		parentPos = ParentPosition(position);
		if (priorityQueue[parentPos] > priorityQueue[position])
		{
			//Move Element up
			int tempPos = priorityQueue[parentPos];
			priorityQueue[parentPos] = priorityQueue[position];
			priorityQueue[position] = tempPos;
		}
		//Set to next position to check
		position = parentPos;
	}

	//swap();

	
}

//Returns the element with the min priority
template <class T>
int ArrayMinHeap<T>::top() {

	return priorityQueue[0];
}

template <class T>
void ArrayMinHeap<T>::moveDown(int position) {

	int leftChildPos = LeftChildPosition(position);
	int rightChildPos = RightChildPosition(position);
	int pos;

	if (rightChildPos >= heapSize) {
		if (leftChildPos >= heapSize) {
			return; //Return as new root has been moved to correct position
		}
		else {
			pos = leftChildPos; //Position to move down from
		}
	}
	else {
		//Check children to see where new root is
		if (priorityQueue[leftChildPos] <= priorityQueue[rightChildPos])
		{
			pos = leftChildPos;
		}
		else {
			pos = rightChildPos;
		}
	}

	//Check to see if previous position is greater than next position
	//If yes, move down
	if (priorityQueue[position] > priorityQueue[pos])
	{
		//Move element down
		int tempPos = priorityQueue[pos];
		priorityQueue[pos] = priorityQueue[position];
		priorityQueue[position] = tempPos;
		moveDown(pos); //Repeat until in correct position
	}
}

//Removes the element with the min priority
template <class T>
void ArrayMinHeap<T>::pop() {

	if (!empty())
	{
		int position = heapSize - 1;
		priorityQueue[0] = priorityQueue[position];
		heapSize--;
		if (heapSize > 0) {
			moveDown(0);
		}

		//Copy priority queue to temp and back to remove last element
		//tempQueue = new int[heapSize];

		//for (int i = 0; i < heapSize; i++)
		//{
		//	tempQueue[i] = priorityQueue[i];
		//}

		//priorityQueue = tempQueue;
	}
}

template<class T>
int ArrayMinHeap<T>::lowRowSum() {
	
	int row = 0;
	int lowestSum = 0;
	int tempSum = 0;

	rowSums = new int[machineNumber];

	//Get all sums
	for (int i = 0; i < machineNumber; i++)
	{
		int tempSum = 0;
		for (int j = 0; j < jobNumber; j++)
		{
			tempSum += machineLength[i][j];
		}

		rowSums[i] = tempSum;
	}

	//Print rowSums

	//for (int i = 0; i < machineNumber; i++)
	//{
	//	cout << rowSums[i] << ',';
	//}
	//cout << endl;

	//Determine lowestSum
	lowestSum = rowSums[0];

	for (int i = 0; i < machineNumber; i++)
	{
		int tempSum = rowSums[i];
		if (tempSum < lowestSum)
		{
			lowestSum = tempSum;
			row = i;
		}

		//if (tempSum == lowestSum)
		//{
		//	lowestSum = tempSum;
		//	//row = i;
		//}
	}

	delete[] rowSums;
	
	return row;
}

template<class T>
int ArrayMinHeap<T>::largeRowSum() {

	int largestSum = 0;
	for (int i = 0; i < machineNumber; i++)
	{
		int sum = 0;
		for (int j = 0; j < jobNumber; j++)
		{
			sum += machineLength[i][j];
		}

		if (sum > largestSum)
		{
			largestSum = sum;
		}
	}

	return largestSum;
}

template<class T>
void ArrayMinHeap<T>::simulate() {
	
	int jobIndex = 0;
	int machineIndex = 0;

	double duration;
	clock_t start;
	//Initialize priorityQueue to number of machines
	priorityQueue = new int[machineNumber];

	//Create machine Length Matrix with all 0 values
	machineLength = new T*[machineNumber];	

	//Create array with all 0 values
	for (int i = 0; i < machineNumber; i++) {
		//Initialize each row
		machineLength[i] = new T[jobNumber];
	
		for (int j = 0; j < jobNumber; j++)
		{
			machineLength[i][j] = 0;
		}
	}

	
	start = clock();

	while (processingTimesArray.size() > 0)
	{
		for (int i = 0; i < machineNumber; i++)
		{
			if (processingTimesArray.size() > 0)
			{
				//cout << processingTimesArray.back() << endl;
				push(processingTimesArray.back());
				processingTimesArray.pop_back();
			}
		}
		swap();
		//cout << size() << endl;
		reverse(priorityQueue, priorityQueue + size());
		//if (size() == machineNumber)
		//{
		//	//pop in reverse to get min
		//	reverse(priorityQueue, priorityQueue + machineNumber);
		//}

		for (int i = 0; i < size(); i++)
		{
			int index = lowRowSum();
			machineLength[index][machineIndex] = priorityQueue[i];
			machineIndex++;
		}
		for (int i = 0; i < machineNumber; i++)
		{
			pop();
		}
	}

	cout << "Min Heap Finishing Time: " << largeRowSum() << endl;
	cout << "Schedule:" << endl;
	
	for (int i = 0; i < machineNumber; i++)
	{
		cout << "Machine " << i + 1 << ":";
	
		for (int j = 0; j < jobNumber; j++)
		{
			if (machineLength[i][j] != 0)
			{
				cout << " " << machineLength[i][j] << ",";
			}
		}
	
		cout << "\b" << " " << endl;;
	}
	
	duration = (clock() - start) / ((double) CLOCKS_PER_SEC);
	
	cout << "Time Elapsed: " << (duration * 1000) << " ms" << endl;

}

//Array MinHeap Destructor
template <class T>
ArrayMinHeap<T>::~ArrayMinHeap() {

	delete[] priorityQueue;

	for (int i = 0; i < machineNumber; i++)
	{
		//Delete machineLength matrix row by row
		delete[] machineLength[i];
	}
}

//*****************************************************************************************************************//
//*****************************************************************************************************************//
//**************************                 Leftist                     ******************************************//

template<class T>
class minHeightLeftistTree_Node {
	// Node Structure for the Leftist Tree
	// Can be accessed outside of class for usage

public:
	T storeElement;
	minHeightLeftistTree_Node * leftValue; // points at the left value
	minHeightLeftistTree_Node * rightValue; // points at the right value
	int balance; // Keeps track of the balancing or s-factor of the trees for melding purposes
	int indexVal;

};

template<class T>
class minHeightLeftistTree {
	// Conducts the methods for the pointer-based min height-biased leftist tree
private:
	minHeightLeftistTree_Node<T> * treeRoot; // points at the root value for the tree
	int treeSize; // stores the size of the tree
	int jobNumber;
	int machineNumber;
	vector<T> processingTimesArray;
	T **machineCount;

	int largeRowSum(int machineNumber, int jobNumber);

public:



	minHeightLeftistTree(int jobs, int machines, int *processingTimes); //Constructor
	bool empty(); //Returns a bool of whether or not the priority queue is empty
	int size(); //Returns the current number of elements in the priority queue
	void push(T, int); //Inserts an element into the priority queue
	T top(); //Returns the element with the min priority
	T pop(); //Removes the element with the min priority
	int topIndex(); //Returns the element with the min priority's index
	//void printTree(); //Print Current tree
	void simulate(int machineNumber, int jobNumber); //Run LPT simulation
	minHeightLeftistTree_Node<T> * meld(minHeightLeftistTree_Node<T> * &first, minHeightLeftistTree_Node<T> * &second); // Melds/merges the two trees as a recursive function implementation
	~minHeightLeftistTree(); //Destructor

};

//Pointer Leftist Tree Constructor
template<class T>
minHeightLeftistTree<T>::minHeightLeftistTree(int jobs, int machines, int *processingTimes)
{
	int jobNumber = jobs;
	int machineNumber = machines;

	treeSize = 0; // number of elements
	treeRoot = NULL; // starts with an empty tree

	//Push values into heap
	for (int i = 0; i < jobNumber; i++)
	{
		push(processingTimes[i],i);
	}

	simulate(machineNumber, jobNumber);
}

//Returns a bool of whether or not the priority queue is empty (empty)
template<class T>
bool minHeightLeftistTree<T>::empty()
{
	return treeRoot == NULL;
}

//Returns the current number of elements in the priority queue (size)
template<class T>
int minHeightLeftistTree<T>::size()
{
	return treeSize;
}

//Inserts an element into the priority queue (push)
template<class T>
void minHeightLeftistTree<T>::push(T data, int indexVal)
{
	minHeightLeftistTree_Node<T> * temp = new minHeightLeftistTree_Node<T>();
	temp->leftValue = NULL;
	temp->rightValue = NULL;
	temp->storeElement = data;
	temp->indexVal = indexVal;

	if (empty())
		treeRoot = temp;
	else
		treeRoot = meld(treeRoot, temp);
	++treeSize;
}

//Returns the element with the min priority (top)
template<class T>
T minHeightLeftistTree<T>::top()
{
	return treeRoot->storeElement;
}

//Removes the element with the min priority (pop)
template<class T>
T minHeightLeftistTree<T>::pop()
{
	T popped = treeRoot->storeElement;
	treeRoot = meld(treeRoot->leftValue, treeRoot->rightValue);
	--treeSize;

	return popped;
}

//Returns the element with the min priority's index (top's index)
template<class T>
int minHeightLeftistTree<T>::topIndex()
{
	return treeRoot->indexVal;
}

//Melds/merges the two trees as a recursive function implementation (meld) textbook ref
template<class T>
minHeightLeftistTree_Node<T>* minHeightLeftistTree<T>::meld(minHeightLeftistTree_Node<T> * &first, minHeightLeftistTree_Node<T> * &second)
{
	// Melds the leftist trees
	if (first == NULL)
		return second;
	if (second == NULL)
	{
		return first;
	}

	// If neither are empty , swap
	if (first->storeElement > second->storeElement)
	{
		// perform the swap
		//swap (first, second);
		minHeightLeftistTree_Node<T> * var = first;
		first = second;
		second = var;
	}

	first->rightValue = meld(first->rightValue, second); // Melds recursively

														 // If there's nothing in the left subtree, we switch

	if (!first->leftValue)
	{
		first->leftValue = first->rightValue;
		first->rightValue = NULL;
	}
	else // Checks the balancing factor, if the right value is greater, we switch
	{
		if (first->leftValue->balance < first->rightValue->balance)
		{
			minHeightLeftistTree_Node<T> * temp = first->leftValue;
			first->leftValue = first->rightValue;
			first->rightValue = temp;
		}

		first->balance = first->rightValue->balance + 1;
	}

	return first;
}

////Print Current Tree
//template<class T>
//void minHeightLeftistTree<T>::printTree()
//{
//	minHeightLeftistTree_Node<T> * temp = treeRoot;
//	while (size() != 0)
//	{
//		cout << pop() << ' ';
//		
//		//if (temp->leftValue != NULL)
//		//{
//		//	temp = temp->leftValue;
//		//}
//		//else {
//		//	temp = temp->rightValue;
//		//}
//
//	}
//	cout << endl;
//}

template<class T>
int minHeightLeftistTree<T>::largeRowSum(int machineNumber, int jobNumber) {

	int largestSum = 0;
	for (int i = 0; i < machineNumber; i++)
	{
		int sum = 0;
		for (int j = 0; j < jobNumber; j++)
		{
			sum += machineCount[i][j];
		}

		if (sum > largestSum)
		{
			largestSum = sum;
		}
	}

	return largestSum;
}

//Run LPT simulation (simulate)
template<class T>
void minHeightLeftistTree<T>::simulate(int machineNumber, int jobNumber) {

	int jobIndex = 0;
	int machineIndex = 0;

	double duration;
	clock_t start;

	//cout << machineNumber << endl;
	//cout << jobNumber << endl;

	//Create machine Length Matrix with all 0 values
	machineCount = new T*[machineNumber];

	//Create array with all 0 values
	for (int i = 0; i < machineNumber; i++) {
		//Initialize each row
		machineCount[i] = new T[jobNumber];

		for (int j = 0; j < jobNumber; j++)
		{
			machineCount[i][j] = 0;
		}
	}


	start = clock();


	//Pop min item into queue vector
	while (size() != 0)
	{
		processingTimesArray.push_back(pop());
	}

	//for (unsigned int i = 0; i < processingTimesArray.size(); i++)
	//{
	//	cout << processingTimesArray[i] << ' ';
	//}
	//cout << endl;


	while (processingTimesArray.size() > 0)
	{
		//Find current execution time of every machine
		vector<int> rowSums;

		for (int i = 0; i < machineNumber; i++)
		{
			int sum = 0;
			for (int j = 0; j < jobNumber; j++)
			{
				sum += machineCount[i][j];
			}

			rowSums.push_back(sum);
		}
				
		//Find row with lowest execution time
		int execTime = rowSums[0];
		jobIndex = 0;
		for (int i = 0; i < machineNumber; i++)
		{
			int tempExecTime = rowSums[i];

			if (tempExecTime < execTime)
			{
				execTime = tempExecTime;
				jobIndex = i;
			}

		}
		
		//cout << processingTimesArray.back() << endl;

		machineCount[jobIndex][machineIndex] = processingTimesArray.back();
		processingTimesArray.pop_back();
		machineIndex++;
	}

	cout << "Height Biased Leftist Tree Finishing Time: " << largeRowSum(machineNumber, jobNumber) << endl;
	cout << "Schedule:" << endl;

	for (int i = 0; i < machineNumber; i++)
	{
		cout << "Machine " << i + 1 << ":";

		for (int j = 0; j < jobNumber; j++)
		{
			if (machineCount[i][j] != 0)
			{
				cout << " " << machineCount[i][j] << ",";
			}
		}

		cout << "\b" << " " << endl;;
	}

	duration = (clock() - start) / ((double)CLOCKS_PER_SEC);

	cout << "Time Elapsed: " << (duration * 1000) << " ms" << endl;

}

//Destructor
template<class T>
minHeightLeftistTree<T>::~minHeightLeftistTree()
{
	delete treeRoot; // If delete the tree root, it deletes the tree

	for (int i = 0; i < machineNumber; i++)
	{
		//Delete machineLength matrix row by row
		delete[] machineCount[i];
	}
}


//*****************************************************************************************************************//
//*****************************************************************************************************************//


int main() {

	//Declare user input variables 
	int jobs;
	int machines;

	int jobLeft;
	int machineLeft;

	cout << "Enter number of job(s):" << endl;
	cin >> jobs;
	jobLeft = jobs;

	//Create array of dyanmic size based on user input for processing times

	int* processingTimes = new int[jobs];


	cout << "Enter number of machine(s)" << endl;
	cin >> machines;
	machineLeft = machines;

	cout << "Enter Processing Time(s)" << endl;

	for (int jobNumber = 0; jobNumber < jobs; jobNumber++) {

		cin >> processingTimes[jobNumber];
	}

	cout << endl;

	
	ArrayMinHeap<int> arrayMinHeap = ArrayMinHeap<int>(jobs, machines, processingTimes);
	

	//Call Min Heap function	
	//arrayMinHeap.simulate();
		
	//Leftist Heap
	cout << endl;
	minHeightLeftistTree<int> mHL = minHeightLeftistTree<int>(jobLeft, machineLeft, processingTimes);
	//mHL.simulate();

	//mHL.push(14, 0);
	//mHL.push(7, 1);
	//mHL.push(10, 2);
	//mHL.push(6, 3);
	//mHL.push(2, 4);
	//mHL.push(3, 5);
	//mHL.push(5, 6);
	


	cin.get();
	cin.get();
}