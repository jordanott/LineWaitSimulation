#include "RegistrarSimulation.h"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
using namespace std;

RegistrarSimulation::RegistrarSimulation(string fileName){
	findNumStudents(fileName);
}
void RegistrarSimulation::findNumStudents(string fileName){
	ifstream reader(fileName.c_str());
	numStudents = 0;
	string line;
	int line_num = 0;
	int counter = 1;
	int nextLine = 3;
	while(getline(reader,line)){
		line_num = atoi(line.c_str());

		if (counter == 1)
		{
			// sets how many windows there are
			numWindows = line_num;
			window_ary = new int[numWindows];
			window_wait = new int[numWindows];
			for (int i = 0; i < numWindows; ++i)
			{
				window_ary[i] = 0;
				window_wait[i] = 0;

			}
		}
		else if(nextLine == counter){
			numStudents += line_num;
			
			nextLine += (line_num+2);
		}
		counter++;
	}
	reader.close();
	// Sets student array for how many students will show up 
	student_ary = new int[numStudents];
	for (int i = 0; i < numStudents; ++i)
	{
		student_ary[i] = 0;
	}
	// putting all numbers in file to an array
	file_numbers = new int[counter-1];
	counter = 0;
	ifstream reader2(fileName.c_str());
	while(getline(reader2,line)){
		line_num = atoi(line.c_str());
		file_numbers[counter] = line_num;
		counter++;
	}
	
	reader2.close();
}
void RegistrarSimulation::simulation(){
	bool condition = true;
	int num_arrived = 0;
	int counter = 1;
	int index = 1;
	int window_in_use = 0;
	int student_wait_index = 0;
	quee = new Queue<int>();
	while(num_arrived != numStudents || condition){
		
		if (num_arrived != numStudents)
		{	

			if (file_numbers[index]==counter)
			{
				index++;
				int loop = file_numbers[index];
				for (int i = 0; i <loop; ++i)
				{
					quee->insert(file_numbers[++index]);
					
				}
				index++;
			}
		}

		window_in_use = 0;
		for (int i = 0; i < numWindows; ++i)
		{
			if(window_ary[i] == 0){
				if (!quee->isEmpty())
				{
					window_ary[i] = quee->remove();
					num_arrived++;	
					student_wait_index++;
				}else{

					window_wait[i]++;
				}
			}else{
				window_in_use++;
				
				window_ary[i]--;
			}
		}
		if (window_in_use == numWindows)
		{
			for (int i = 0; i < quee->size; ++i)
			{
				student_ary[student_wait_index+i]++;
			}
		}
		if (num_arrived == numStudents)
		{
			window_in_use = 0;
			for (int i = 0; i < numWindows; ++i)
			{
				if (window_ary[i] == 0)
				{
					window_in_use++;

				}
			}
			if (window_in_use == numWindows)
			{
				condition = false;
			}
		}
		counter++;
	}

	sort(file_numbers, file_numbers + 8);
	sort(window_wait, window_wait + numWindows);	
	calculateStuff();
	cout << "Time: " << counter << endl;
}
void RegistrarSimulation::calculateStuff(){
	// Mean Student Wait Time
	mean_SWT = 0;
	meadian_SWT = 0;
	longest_SWT = 0;
	num_SOver10 = 0;
	mean_WIT = 0;
	longest_WIT = 0;
	num_WOver5 = 0;

	longest_SWT = student_ary[numStudents-1];
	if (!isdigit(numStudents/2))
		meadian_SWT = student_ary[numStudents/2];
	else {
		int medianA = numStudents/2;
		int medianB = (numStudents/2) + 1;
		meadian_SWT = (medianA + medianB)/2;
	}
	for (int i = 0; i < numStudents; ++i)
	{
		mean_SWT += student_ary[i];
		if (student_ary[i] > 10)
			num_SOver10++;
	}
	mean_SWT /= numStudents;

	longest_WIT = window_wait[numWindows-1];
	for (int i = 0; i < numWindows; ++i)
	{
		mean_WIT += window_wait[i];
		if (window_ary[i] > 5)
			num_WOver5++;
	}
	mean_WIT /= numWindows;
	cout << endl;
	// print out stats
	cout << "Mean student wait time: " << mean_SWT << endl;
	cout << "Median student wait time: " << meadian_SWT << endl;
	cout << "Longest student wait time: " << longest_SWT << endl;
	cout << "Number of students with a wait time over 10: " << num_SOver10 << endl;;
	cout << "Mean window idle time: " << mean_WIT << endl;
	cout << "Longest window idle time: " << longest_WIT << endl;
	cout << "Number of windows with an idle time over 5: " << num_WOver5 << endl;
	cout << endl;
}
RegistrarSimulation::~RegistrarSimulation(){
	delete [] student_ary;
	delete [] window_ary;
	delete [] file_numbers;
	delete [] window_wait;
	delete quee;
}