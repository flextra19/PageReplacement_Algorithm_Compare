
// Main function
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <deque>
#include <chrono>
#include <random>

using namespace std;

int totalExp = 1000;
int totalPage = 1000;

int FIFO( deque <string>, int);
int LRU( deque <string>, int);
int OPT( deque <string>, int);
int clockPRA(deque <string>, int);
bool isExists(list <string> , string);//FIFO
bool isExists(vector <string> , string);//LRU,OPT
bool isAppearOnce(vector <string> &, string, int,int);//lRU
bool isAppearOnce(deque <string> &, string, int);//OPT

int FIFO(deque <string> myList, int pageFrame)
{
    int countPageFaults = 0;
    list <string> pageFrameList;
    list<string>::iterator iter;

    while(myList.size()!=0)
    {
        // if set holds less pages than capacity.
        // insert page into the set one by one until the size of set reaches capacity or all page requests are processed.
        if(pageFrameList.size()<pageFrame)
        {
            if(isExists(pageFrameList,myList.front())==false)
            {
                pageFrameList.push_back(myList.front());
                myList.pop_front();
                countPageFaults++;
            }
            else
            {
                myList.pop_front();
            }
        }
        else if(pageFrameList.size()==pageFrame)
        {
            // if current page is present in set, do nothing.
            bool inPageFrame = false;
            for(iter=pageFrameList.begin(); iter!=pageFrameList.end(); iter++)
            {
                if(myList.front()==*iter)
                    inPageFrame=true;
            }
            if(inPageFrame==true)
            {
                myList.pop_front();
            }
            // remove the first page from the queue as it was the first to be entered in the memory
            // push back the current page into the set
            else 
            {
                pageFrameList.pop_front();
                pageFrameList.push_back(myList.front());
                myList.pop_front();
                countPageFaults++;
            }
        }
    }
    pageFrameList.clear();
    return countPageFaults;
}

int LRU(deque <string> myList, int pageFrame)
{
    int countPageFaults = 0;
    vector<string> pageFrameList;
    vector <string> popedMyList;
    vector<string>::iterator iter;
    int tempNum;

    while(myList.size()!=0)
    {   
        // if set holds less pages than capacity.
        // maintain the recent occurred page in a map called popedMyList
        if(pageFrameList.size()<pageFrame)
        {
            if(isExists(pageFrameList,myList.front())==false)
            {
                pageFrameList.push_back(myList.front());
                popedMyList.push_back(myList.front());
                myList.pop_front();
                countPageFaults++;  // increment page fault
            }
            else 
            {
                popedMyList.push_back(myList.front());
                myList.pop_front();
            }
        }
        else if (pageFrameList.size()==pageFrame)
        {
            // if current page is present in set, do nothing
            if(isExists(pageFrameList,myList.front()))
            {
                popedMyList.push_back(myList.front());
                myList.pop_front();
            }
            else //find the best one suit LRU
            {
                // find the page in the set that was least recently used. 
                // find it using popedMyList array.
                // basically need to replace the page with minimum index.
                int i=(totalPage-myList.size()-1); 
                string changePage;
                tempNum=pageFrame;
                while(tempNum>0&&i>=0)
                {
                    for(i=totalPage-myList.size()-1; i>=0; i--) // looping popedMyList upside down
                    {
                        if(isExists(pageFrameList, popedMyList[i])) // if exist in pageFrameList
                        {
                            int num1 = totalPage-myList.size()-1; // overalled page count
                            if(isAppearOnce(popedMyList, popedMyList[i], num1, i)) // find the page in the set
                            {
                                tempNum--;
                                changePage=popedMyList[i];
                            }
                            else
                                {
                                    continue;
                                }
                        }
                        else
                        {
                             continue;
                        }
                    }
                }
                // exchange the pageFrame
                // replace the found page with current page.
                for(iter=pageFrameList.begin(); iter!=pageFrameList.end(); iter++)
                {
                    if(changePage==*iter)
                    {
                        pageFrameList.erase(iter);
                        pageFrameList.insert(iter,myList.front());

                    }
                }
                popedMyList.push_back(myList.front());
                myList.pop_front();
                countPageFaults++;
            }
        }
    }
    pageFrameList.clear();
    popedMyList.clear();
    return countPageFaults;
}

int OPT( deque <string> myList, int pageFrame)
{
    int countPageFaults = 0;
    vector <string> pageFrameList;
    vector<string>::iterator iter;
    deque<string>::iterator iter1;
    int tempNum;

    while(myList.size()!=0)
    {
        // if set holds less pages than capacity.
        // insert page into the set one by one until the size of set reaches capacity or all page requests are processed.
        if(pageFrameList.size()<pageFrame)
        {
            if(isExists(pageFrameList, myList.front())==false)
            {
                string temp;
                temp=myList.front();
                pageFrameList.push_back(temp);
                myList.pop_front();
                countPageFaults++;
            }
            else
            {
                myList.pop_front();
            }
        }
        else
        {
            string changePage;
            if(isExists(pageFrameList, myList.front())==true)
            {
                myList.pop_front();
            }
            else  //find the best one suit OPT
            {
                // find if a page that is never referenced in future.
                // if such a page exists, replace this page with new page. (1)
                // if no such page exists, find a page that is referenced farthest in future. (2)
                string changePage;
                tempNum=pageFrame;
                bool uselessPage = true;

                while(tempNum>0&&uselessPage==true)
                {
                    for(iter1=myList.begin(); iter1!=myList.end(); iter1++)
                    {
                        if(isExists(pageFrameList, *iter1)) // (2)
                        {
                            int num = myList.size();
                            if(isAppearOnce(myList,*iter1, num))
                            {
                                tempNum--;
                                changePage=*iter1;
                            }
                        }
                        else // (1)
                        {
                            changePage=*iter1;
                            uselessPage = false;
                            break;
                        }
                    }
                }
              //exchange the pageFrame
                for(iter=pageFrameList.begin(); iter!=pageFrameList.end(); iter++)
                {
                    if(changePage==*iter)
                        {pageFrameList.insert(iter,myList.front());
                        pageFrameList.erase(iter);
                        }
                }
                myList.pop_front();
                countPageFaults++;
            }
        }
    }
    pageFrameList.clear();
    return countPageFaults;
}

int clockPRA(deque <string> myList, int pageFrame) {
	int frames[pageFrame], use[pageFrame], fault, locat, found, i, j;
	for(i=0; i<pageFrame; i++) { /* Initialize all array elements to 0 */
		frames[i]=0;
		use[i]=0;
	}
	fault=0;
	locat=0;
	for(i=0; i<totalPage; i++) {
        // if the page already exists, simply set its corresponding element in use to true.
		found=0; /* Reset */
		for(j=0; j<pageFrame; j++) { /* Check if page is in memory */
			if(atoi(myList[i].c_str())==frames[j]) {
				found=1;
				use[j]=1;
			}
		}
        // if the page doesn’t exist, check whether the space pointed to by pointer is empty (indicating cache isn’t full yet) 
        // if so, we will put the element there.
        // else we’ll traverse the array frames one by one (cyclically using the value of locat), marking all corresponding use elements as false, till we find a one that’s already false. 
        // that is the most suitable page for replacement, so we do so.
		if(found==0) {
			do { /* if bit is 0 or NULL, load in page */
				if(use[locat]==0) {
					frames[locat]=atoi(myList[i].c_str());
					use[locat]=1;
					found=1;
					fault++;
				}
				else { /* reset use bit */
					use[locat]=0;
				}
				locat++; /* Move pointer */
				if(locat==pageFrame) { locat=0; } /* Reset */
			} while (found!=1);
		}
	}
	return fault;
}

bool isExists(list <string> tempList, string iter1)
{
    list<string>::iterator iter;
    for(iter=tempList.begin(); iter!=tempList.end(); iter++)
    {
        if(*iter==iter1)
            return true;
    }
    return false;
}

bool isExists(vector <string> tempList, string iter1)//LRU,OPT
{
    vector<string>::iterator iter;
    for(int i=0; i < tempList.size(); i++)
    {
        if(tempList.at(i)==iter1)
        {
            return true;
        }
    }
    return false;
}

bool isAppearOnce(vector <string> &tempList, string iter1, int num, int curNum )//LRU will use this function
{
    for(int i=num; i<=curNum; i++)
    {
        if(tempList[i]==iter1)
        {
            return false;
        }
    }
        return true;
}

bool isAppearOnce(deque <string> &tempList, string iter1, int num)//OPT will use this function
{
    int n=0;
    for(int i=(num-1); i<totalPage; i++)
    {
        if(tempList[i]==iter1)
        {
            n++;
        }
    }
    if(n==1)
        return true;
    return false;
}

int main(int Argc,char* Args[])
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::poisson_distribution<int> distribution (10);

    std::cout << "some Poisson-distributed results (mean=10)" << endl;
    
    float fifo[21] = {0};
    float lru[21] = {0};
    float opt[21] = {0};
    float clock[21] = {0};

    for (int i=0; i<totalExp; ++i){
    	cout<<"- Experience number is "<<(i+1)<<endl;
        deque <string> myList; //store the randomly generated pages
        for (int j=0; j<totalPage; ++j){
            string str = to_string(distribution(generator));
            myList.push_back(str);
        }

        for (int pageFrame = 2; pageFrame < 21; pageFrame ++) {
            fifo[pageFrame] += FIFO(myList, pageFrame);
 
            lru[pageFrame] += LRU(myList, pageFrame);

            opt[pageFrame] += OPT(myList, pageFrame);

            clock[pageFrame] += clockPRA(myList,pageFrame);
        }
    }
    fstream fp;
    string file_cmd="output.txt";
	fp.open(file_cmd.c_str(), ios::out);
    fp<<"no : FIFO : LRU : OPT : CLOCK"<<endl;
    cout<<"no : FIFO : LRU : OPT : CLOCK"<<endl;
    for (int i = 2; i < 21; i ++){
        string str_i = to_string(i);
        fp<<str_i<<" : "<<fifo[i]/float(totalExp)<<" : "<<lru[i]/float(totalExp)<<" : "<<opt[i]/float(totalExp)<<" : "<<clock[i]/float(totalExp)<<endl;
        cout<<str_i<<" : "<<fifo[i]/float(totalExp)<<" : "<<lru[i]/float(totalExp)<<" : "<<opt[i]/float(totalExp)<<" : "<<clock[i]/float(totalExp)<<endl;
    }
    return 0;
}
