# include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include<fstream>
#include <sstream>
#include <vector>
#include "md5.h"

using namespace std;
	
string combinare(const vector<string>& combinare)
{
	int index = 0; 
	stringstream output;

	while (1)
	{
		bool este=false;
		for (int i = 0; i < combinare.size();i++)
		{
			const string& cuvant = combinare[i];
			if ( index < cuvant.size()  )
			{
				output << cuvant[index];
				este = true; 
			}
			
		}
		if (este == false)
		{
			break;
		}
		index++;
	}
	//output <<
	return output.str();
}

int main(int argc, char *argv[])
{ 

	int  my_rank;      
	int  nrprocs;
	string cautare;
	ifstream myReadFile("D:\\Facultate\\andul3\\Semestrul2\\APD-Tavi\\google-10000-english-master\\google-10000-english-no-swears.txt");
	int offset = 0; 
	int offset1 = 0;
	string line;
	string has1 = "e04b86583a42a056d37aa1dce541542f";
	//	"be6115fee122da57ec46f2bfa6841053";
	//;
	//string	 w[10000];
	
	vector <string> w;
	vector <string> v;
	bool flag = true; 
//	string	 v[10000];
	int str; 
	vector<string> p;
	
	//MPI_Init(&argc, &argv);
	

	while (!myReadFile.eof())
	{

		myReadFile >> line;
		if (line.size() > 4)
		{
			
				w.push_back(line);
	
				
			//w[offset] = line;
			//offset++;
		}
		if (line.size() == 15)
		{
			
				v.push_back(line);
			
		
			//v[offset1] = line;
			//offset1++;
		}

	}
	myReadFile.close();

	for(int a = 0; a < w.size(); a++ ){
		for(int b = 0 ; b < w.size();b++) {
			for( int c = 0; c < v.size(); c++)
			{
				
				if (w[a] != w[b] && w[b] != v[c] && w[a] != v[c])

				{

					string combined = combinare({w[a], w[b], v[c]});
					//	cout << combined;
					MD5_CTX ctx;
					stringstream ss; 
					ss << hex;
					MD5_Init(&ctx);
					MD5_Update(&ctx, combined.c_str(), combined.size());
					unsigned char hash[17];
					MD5_Final(hash, &ctx);
					hash[16] = 0;
					for (int i = 0; i < 16; i++)
					{
						ss << (int)hash[i];
					}
					
					//cout << w[a] << w[b] << v[c] << combined << " " << ss.str();
					cout << w[a]  << combined << " " << ss.str();
					if (has1 == ss.str())
					{
						
						cout << "MERGE"<<endl;
						
						flag = false;
						//break;
					}
					
					cout << "\n";
					
				}
				if (flag == false)
				{
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		if (flag == false)
		{
			break;
		}

	}


	
				
	



	//c_str
	//string combined = combinare({ "abcd", "efghcb", "si" });
	
		//vector<string> threeWords;

		
	


	
		
		
		
		

		
 	return 0;

}

