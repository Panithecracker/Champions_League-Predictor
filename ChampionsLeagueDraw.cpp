
#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<fstream>

using namespace std;
class Team{
	private:
		string name;
		string country;
		string past;
	public:
		//default constructor...
		 Team(){
			name = "";
			country = "";
			past = "";
		}
		//parameterized constructor
		Team(string n, string c,string ps){
			name = n;
			country = c;
			past = ps;
		}
		//setters and getters for objects of this class
		void SetName(string n){
			name = n;
		}
		void SetCountry(string c){
			country = c;
		}
		void SetPast(string pa){
			past = pa;
		}
		string GetName(){
			return name;
		}
		string GetCountry(){
			return country;
		}
		string GetPast(){
			return past;
		}
		//special function that determines which teams can the team object face (not same country, not faced already nor picked at a previous stage of the draw)
		vector<class Team> SearchForRivals(vector<class Team> Box){
			vector<class Team> Rivals;
			for(int i = 0; i<Box.size(); ++i){
				//check conditions for the i-th possible rival inside the box given...
				if((GetCountry() != Box[i].GetCountry()) && (GetPast()!=Box[i].GetName())){
					//then this could perfectly be a rival, so we store it inside the Rivals vector...
					Rivals.push_back(Box[i]);
				}
			}
			return Rivals;
		} 		
};

//this program will record data regarding the different results of various draws made, emulating the real one 
void DisplayBox(vector<class Team> B){
	cout << "" << B.size() << " different teams in this box!" << endl;
	for(int i = 0; i<B.size();i++){
		cout << i+1 << "(" <<  B[i].GetName() <<"," << B[i].GetCountry() << ")" << endl;
 	}
}
int FindTeam(string tname, vector<class Team> Box);
void ReadTournament(int participants, vector<class Team> &T1, vector<class Team> &T2){
	//function that fills up the two boxes with the respective teams
	ifstream vfile;
	vfile.open("Teams.txt");
	if(!vfile){
		string info;
		class Team T;
		vector<class Team> Box1;
		vector<class Team> Box2;
		for(int i = 0; i<(participants/2); ++i){ //filling box1
			getline(vfile,info);
			Box1[i].SetName(info);
			getline(vfile,info);
			Box1[i].SetCountry(info);
			getline(vfile,info);
			Box1[i].SetPast(info);
		}
		for(int i = 0; i<(participants/2); ++i){ //filling box2
			getline(vfile,info);
			Box2[i].SetName(info);
			getline(vfile,info);
			Box2[i].SetCountry(info);
			getline(vfile,info);
			Box2[i].SetPast(info);
		}
		vfile.close();
	}else{
		cout << "Error when trying to open the text file!";
	}
}
int main(){
	//step 1: register all the teams
	int amount;
	cout << "Enter the total amount of teams that are participating :";
	cin >> amount;
	vector <class Team> Box1;
	vector <class Team> Box2;
	class Team T;
	string input;
	
	//get the tournament teams info to two boxes by reading the information on the txt file.
	ReadTournament(amount, Box1, Box2);
	DisplayBox(Box1);
	
	cout << "TIME FOR THE DRAWING SIMULATION \n" << endl;
	cout << "How many times would you like to simulate? ";
	double rounds;
	cin >> rounds;
	vector<class Team> B1;
	vector<class Team> B2;
	int size = amount/2;
	double Ocurrences[size][size]; //matrix of results after n-draws have been made
	//initialize it with all zeros
	for(int a=0; a<size;a++){
		for(int b=0; b<size;b++){
			Ocurrences[a][b] = 0;
		}
	}
	class Team T1;
	class Team T2;
	vector<class Team> Rivals;
	int num;
	for(int i= 0; i<rounds; ++i){ //do the draws for "rounds" times
		//now, we will draw all the teams in Box1(winner box) with the respective possible teams on Box2
		B1 = Box1;
		B2 = Box2;
		cout << "-----DRAW " << i+1 << endl;
		for(int j = 0; j<size; ++j){
			//from the current B1 content, grab a random team inside it...
		    num = rand() % B1.size(); //must be an integer inside [0,B1.size())
			T1 = B1[num];	
			//now, to draw a rival we first need to get a Box (from B2) that only contains the possible rivals...
			Rivals = T1.SearchForRivals(B2);
			if (Rivals.empty() == 1){
				//cancel draw... impossible draw case!
				//to not count it as a valid draw and not have spent the iteration, we decrement the value of i
				i = i-1;
			}else{			
			num = rand() % Rivals.size();
			T2 = Rivals[num]; //T1 will face T2, valid game 
			//now, print it on screen:
			cout << j+1 << ": " << T1.GetName() << "_VS_" << T2.GetName() << endl;
			//most importantly, keep track of what just happened inside the matrix where rows are teams in Box1 and columns are teams in Box2
			Ocurrences[FindTeam(T1.GetName(),Box1)][FindTeam(T2.GetName(),Box2)] += 1;
			//Now, erase T1 from B1 and T2 from B2...
			B1.erase(B1.begin() + FindTeam(T1.GetName(),B1));
			B2.erase(B2.begin() + FindTeam(T2.GetName(),B2));
			//done... keep drawing ...
			cout << endl;
		}
		}	
	}
	//now, print the corresponding matrix of ocurrences after the simultation of n (big ideally) draws done...
	double p;
	for(int m = 0; m<size;++m){
		//row by row
		for(int n = 0; n<size; ++n){
		cout <<	(Ocurrences[m][n])/(rounds) << "\t";
		}
		cout << endl;
	}
	return 0;
}
//function that returns the index in a vector containing a specific team name...
int FindTeam(string tname, vector<class Team> Box){
	for(int k = 0; k<Box.size();++k){
		if(tname == Box[k].GetName()){
			return k;
		}
	}
}
