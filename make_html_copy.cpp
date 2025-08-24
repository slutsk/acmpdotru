#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<ctime>
#include<iomanip>
using namespace std;

struct ZADACHA{
    int number; //nomer zadachi na acmp
    int procent; //uroven
    string link; //ssilka na zadachu
};

//postroenie massiva so vsemi zadachami
void build_zadacha(vector<ZADACHA> & vc, int a[]){
    ifstream readLinks("links.txt");
    int number = 1;
    int procent;
    while(readLinks >> procent)
    {
        string tmp;
        readLinks >> tmp;
        if(procent < 100)
        {
          vc.push_back({number, procent, tmp});
          a[number] = procent;
        }
        ++number;
    }
    readLinks.close();
}

struct PERSON{
   string name;
   bool flag[2500] = {false};
   vector<int> cnt_procent;
   int rang = 0;
   int solved_problems = 0;
   int k;//
};

void build_person(vector<PERSON> &vc, int procent[])
{
    ifstream readFile("person.txt");
    string c;
    while(readFile >> c)
    {
        if(c=="*")
        {
            string name;
            getline(readFile, name);
            PERSON P;
            P.name = name;
            vc.push_back(P);
        }
        else{
            int number = stoi(c);
            if(!vc.back().flag[number]){
                vc.back().solved_problems++;
                vc.back().rang += procent[number];
                vc.back().flag[number] = true;
                vc.back().cnt_procent.push_back(procent[number]);
            }

        }
    }

    readFile.close();
}

void build_page(vector<PERSON> &vc, vector <ZADACHA> &zadacha)
{
     ifstream readFile("header.html");
     ofstream writeFile("index.html");
     string str;
     time_t t = time(nullptr);
	 tm *now = localtime(&t);
		  
     while(getline(readFile, str))
     {
         if (str.find("lastUpdate") != std::string::npos)
                writeFile << "<div class = \"lastUpdate\">" << "\nLatest website update: "
                    <<setfill('0') << setw(2) << (now->tm_mday) << '.'
                    <<setfill('0') << setw(2) << (now->tm_mon+1) <<'.'
                    <<setfill('0') << setw(2) << (now->tm_year+1900) <<' '
                    <<setfill('0') << setw(2) << (now->tm_hour+3) <<':'
                    <<setfill('0') << setw(2) << (now->tm_min)
                    << "</div>"<< "\n";

         else if (str.find("<thead>") != std::string::npos)
         {
             writeFile << str << "\n";
             writeFile << "<tr>" << "\n";
             for(auto x: vc)
             {
                writeFile << "<th class = \"";
                if(x.rang < 500) writeFile << "B0";
                else if(x.rang < 3000) writeFile << "B1";
                else if(x.rang < 7000) writeFile << "B9";
                else if(x.rang < 13000) writeFile << "B2";
                else if(x.rang < 23000) writeFile << "B3";
                else if(x.rang < 33000) writeFile << "B4";
                else if(x.rang< 43000) writeFile << "B5";
                else if(x.rang < 53000) writeFile << "B6";
                else if(x.rang < 63000) writeFile << "B7";
                else if(x.rang < 100000) writeFile << "B8";

                writeFile << "\">";

                 writeFile << x.name;
                 writeFile << "<br>" << x.solved_problems;
                 writeFile << "<br>" << x.rang; 
                 writeFile << "<br>" << x.k << "</th>" << "\n";
             }
             writeFile << "</tr></thead>" << "\n";
             writeFile << "<tr>"  << "\n";
             for(auto x: vc)
             {
                 writeFile << "<td class=\"second_table\">\n";

                 for(auto z: zadacha)
                 {
                    if(!x.flag[z.number]){
                        writeFile << "<div class = \"circle ";
                        if(z.procent < 10) writeFile << "cl01\">";
                        else if(z.procent < 20) writeFile << "cl02\">";
                        else if(z.procent < 30) writeFile << "cl03\">";
                        else if(z.procent < 40) writeFile << "cl04\">";
                        else if(z.procent < 50) writeFile << "cl05\">";
                        else if(z.procent < 60) writeFile << "cl06\">";
                        else if(z.procent < 70) writeFile << "cl07\">";
                        else if(z.procent < 80) writeFile << "cl08\">";
                        else if(z.procent < 100) writeFile << "cl09\">";
                        writeFile << "<a href = \'" << z.link  << "\' >"
                                  << z.number << "<br>"
                                  << z.procent << "%"<< "</a></div>" << "\n";
                    }
                 }

                 writeFile << "</td>\n";
             }
             writeFile << "</tr>" << "\n" << "</thed>";
         }
         else  writeFile << str << "\n";
     }

     writeFile.close();
     readFile.close();
}


int main()
{
	int array_of_procents[2500] = {0};
	vector<ZADACHA> zadacha;
	build_zadacha(zadacha, array_of_procents);
	sort(zadacha.begin(), zadacha.end(), [](ZADACHA x, ZADACHA y){return x.procent < y.procent;});

    vector<PERSON> person;
    build_person(person, array_of_procents);
    for(auto &x: person)
    {
        int n = 100;
        int mn = min((int)n, (int)x.cnt_procent.size());
        int sum = 0;
        sort(x.cnt_procent.rbegin(), x.cnt_procent.rend());
        //std::cout <<x.name << " ";  
        for(int i = 0; i < mn ; i++){
           sum += x.cnt_procent[i];
        }
        x.k = sum/mn;
        //cout << " " << x.k << "\n";
    }
    sort(person.begin(), person.end(), [](PERSON a, PERSON b){
             if(a.rang != b.rang) return a.rang > b.rang;
             return a.solved_problems > b.solved_problems;
         });
	build_page(person, zadacha);


    return 0;
}






