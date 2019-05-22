# include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include<fstream>
#include <sstream>
#include <vector>
#include "md5.h"
#include "mpi.h"

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
	return output.str();
}

int main(int argc, char *argv[])
{ 

	int  my_rank;      
	int  nrproces;
	string cautare;
	ifstream myReadFile("D:\\Facultate\\andul3\\Semestrul2\\APD-Tavi\\google-10000-english-master\\google-10000-english-no-swears.txt");
	int offset = 0; 
	int offset1 = 0;
	int n = 0;
	string line;
	int x , low, high ;
	string has1 = "be6115fee122da57ec46f2bfa6841053";

	
	vector <string> w;
	vector <string> v;
	bool flag = true; 
	int str; 
	vector<string> p;
	
	MPI_Init(&argc, &argv); // start mpi
	
	MPI_Comm_size(MPI_COMM_WORLD, &nrproces); // cate has-uri cauta fiecare proces 
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // rangul procesului 
	while (!myReadFile.eof())
	{

		myReadFile >> line;
		if (line.size() > 4)
		{
			
				w.push_back(line);
	
				

		}
		if (line.size() == 15)
		{
			
				v.push_back(line);
			
		

		}

	}
	myReadFile.close();

	MPI_Bcast(w.data(), w.size(), MPI_CHAR, 0, MPI_COMM_WORLD); // trimite vectorul de la root la celalalte procese  
	
	
	if (my_rank < 2)
	{
		x = w.size() / nrproces - 1 ; // marimea vectorului / procese adica 4 =  portiune de vector 
		low = my_rank * x; // rangul procesului 0,1,2,3 * portiunea de vector  = inceputul ariei de cautare 
		high = low + x; // inceputul ariei + lungimea unei portiuni = finalul ariei de cautat 
	}
	n = n + x;
	if (my_rank > 1)
	{	
		n = w.size() / nrproces + 2 + n  ; // marimea vectorului / procese adica 4 =  portiune de vector 
		low = my_rank * n; // rangul procesului 0,1,2,3 * portiunea de vector  = inceputul ariei de cautare 
		high = low + n; // inceputul ariei + lungimea unei portiuni = finalul ariei de cautat 
	}
//	x = w.size() / nrproces; // marimea vectorului / procese adica 4 =  portiune de vector 
//	low = my_rank * x; // rangul procesului 0,1,2,3 * portiunea de vector  = inceputul ariei de cautare 
//	high = low + x; // inceputul ariei + lungimea unei portiuni = finalul ariei de cautat 
	for (int a = low; a < high; a++) {
		for(int b = 0 ; b < w.size();b++) {
			for( int c = 0; c < v.size(); c++)
			{
				
				if (w[a] != w[b] && w[b] != v[c] && w[a] != v[c])

				{

					string combined = combinare({w[a], w[b], v[c]});
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
					
					
					cout << w[a]  << combined << " " << ss.str();
					if (has1 == ss.str())
					{
						
						cout << "S-a gasit hash-ul"<<endl;
						
						flag = false;
						
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


	
				
	


		

	
		
	MPI_Finalize();
		
		
	//7714 / 4 = 1928,5
	// proc 0 ,1 = lungimea lui w ( 7714 ) / 4 - 1 = 1927
	//proc 2,3 = lungimea lui w (7714 ) / 4 + 2 = 1930 
	// 1927 ,1927 , 1930 , 1930
		
 	return 0;

}

