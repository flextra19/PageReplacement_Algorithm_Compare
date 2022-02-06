
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

bool isExistsOL(vector <string> frameList, string page)//func_lru,func_opt
{
    for(int i=0; i < frameList.size(); i++) {
        if(frameList.at(i)==page)
        {
            return true;
        }
    }
    return false;
}

int func_fifo(deque <string> pageList, int frameSize){
    list <string> frameList;
    list<string>::iterator iter;
    int faults = 0;
    
    while(pageList.size()!=0){
        // if set holds less pages than capacity.
        // insert page into the set one by one until the size of set reaches capacity or all page requests are processed.
        if(frameList.size()<frameSize){   
            // check current page if in memory
            bool flag = false;
            for(list<string>::iterator iter=frameList.begin(); iter!=frameList.end(); iter++){
                if(*iter==pageList.front()){
                    flag = true;
                    break;
                }
            }
            if(flag==false){ // if not exist, increase fault
                frameList.push_back(pageList.front());
                pageList.pop_front();   // next page
                faults++;
            }
            else {
                pageList.pop_front();   // next page
            }
        }
        else if(frameList.size()==frameSize){
            // if current page is present in set, do nothing.
            bool flag = false;
            for(iter=frameList.begin(); iter!=frameList.end(); iter++) {
                if(pageList.front()==*iter){
                    flag=true;
                    break;
                }
            }
            if(flag==true)
                pageList.pop_front();
            else {
                // remove the first page from the queue as it was the first to be entered in the memory
                // push back the current page into the set
                frameList.pop_front();
                frameList.push_back(pageList.front());
                pageList.pop_front();
                faults++;
            }
        }
    }
    frameList.clear();
    return faults;
}

int func_lru(deque <string> pageList, int frameSize){
    int faults = 0;
    vector<string> frameList;
    vector <string> popedList;
    vector<string>::iterator iter;
    int decNum;

    while(pageList.size()!=0){   
        // if set holds less pages than capacity.
        // maintain the recent occurred page in a map called popedList
        if(frameList.size()<frameSize){
            if(isExistsOL(frameList,pageList.front())==false) { // check if the current page in memory
                frameList.push_back(pageList.front());
                popedList.push_back(pageList.front());
                pageList.pop_front();
                faults++;  // increment page fault
            }
            else {
                popedList.push_back(pageList.front());
                pageList.pop_front();
            }
        }
        else if (frameList.size()==frameSize){
            // if current page is present in set, do nothing
            if(isExistsOL(frameList,pageList.front())){
                popedList.push_back(pageList.front());
                pageList.pop_front();
            }
            else {
                // find the page in the set that was least recently used. 
                // find it using popedList array.
                // basically need to replace the page with minimum index.
                int cnt=(totalPage-pageList.size()-1); 
                string changePage;
                decNum=frameSize;
                while(decNum>0&&cnt>=0){
                    for(cnt=totalPage-pageList.size()-1; cnt>=0; cnt--) { // looping popedList upside down
                        if(isExistsOL(frameList, popedList[cnt])) // if exist in frameList
                        {
                            bool flag = true;
                            int num1 = totalPage-pageList.size()-1; // overalled page count
                            // find the page in the set
                            for(int i=num1; i<=cnt; i++)
                                if(popedList[i]==popedList[cnt]){
                                    flag = false;
                                    break;
                                }

                            // find the page in the set
                            if(flag) { 
                                decNum--;
                                changePage=popedList[cnt];
                            }
                            else
                                continue;
                        }
                    }
                }
                // exchange the frameSize
                // replace the found page with current page.
                for(iter=frameList.begin(); iter!=frameList.end(); iter++){
                    if(changePage==*iter){
                        frameList.erase(iter);
                        frameList.insert(iter,pageList.front());

                    }
                }
                popedList.push_back(pageList.front());
                pageList.pop_front();
                faults++;
            }
        }
    }
    frameList.clear();
    popedList.clear();
    return faults;
}

int func_opt( deque <string> pageList, int frameSize){
    int faults = 0;
    vector <string> frameList;
    vector<string>::iterator iter;
    deque<string>::iterator iter1;
    int decNum;

    while(pageList.size()!=0){
        // if set holds less pages than capacity.
        // insert page into the set one by one until the size of set reaches capacity or all page requests are processed.
        if(frameList.size()<frameSize)
            if(isExistsOL(frameList, pageList.front())==false){
                string temp;
                temp=pageList.front();
                frameList.push_back(temp);
                pageList.pop_front();
                faults++;
            }
            else
                pageList.pop_front();
        else{
            string changePage;
            if(isExistsOL(frameList, pageList.front())==true)
                pageList.pop_front();
            else  //find the best one suit func_opt
            {
                // find if a page that is never referenced in future.
                // if such a page exists, replace this page with new page. (1)
                // if no such page exists, find a page that is referenced farthest in future. (2)
                string changePage;
                decNum=frameSize;
                bool referFlag = true;

                while(decNum>0&&referFlag==true){
                    for(iter1=pageList.begin(); iter1!=pageList.end(); iter1++)
                    {
                        if(isExistsOL(frameList, *iter1)){ // (2)
                            int num = pageList.size();
                            // check if page in memory
                            int it=0;
                            for(int i=(num-1); i<totalPage; i++) 
                                if(pageList[i]==*iter1){
                                    it++;
                                    break;
                                }
                            if(it==1){
                                decNum--;
                                changePage=*iter1;
                            }
                        }
                        else{ // (1)
                            changePage=*iter1;
                            referFlag = false;
                            break;
                        }
                    }
                }
              //exchange the frameSize
                for(iter=frameList.begin(); iter!=frameList.end(); iter++){
                    if(changePage==*iter){
                        frameList.insert(iter,pageList.front());
                        frameList.erase(iter);
                    }
                }
                pageList.pop_front();
                faults++;
            }
        }
    }
    frameList.clear();
    return faults;
}

int func_clock(deque <string> pageList, int frameSize) {
	int frames[frameSize], use_flag[frameSize], fault, cnt, found, i, j;
	for(i=0; i<frameSize; i++) { // initialize array into 0
		frames[i]=0;
		use_flag[i]=0;
	}
	fault=0;
	cnt=0;
	for(i=0; i<totalPage; i++) {
        // if the page already exists, simply set its corresponding element in use to true.
		found=0; // reset 
		for(j=0; j<frameSize; j++) { // check if page is in memory 
			if(atoi(pageList[i].c_str())==frames[j]) {
				found=1;
				use_flag[j]=1;
			}
		}
        // if the page doesn’t exist, check whether the space pointed to by pointer is empty (indicating cache isn’t full yet) 
        // if so, we will put the element there.
        // else we’ll traverse the array frames one by one (cyclically using the value of cnt), marking all corresponding use elements as false, till we find a one that’s already false. 
        // that is the most suitable page for replacement, so we do so.
		if(found==0) {
			do { /* if bit is 0 or NULL, load in page */
				if(use_flag[cnt]==0) {
					frames[cnt]=atoi(pageList[i].c_str());
					use_flag[cnt]=1;
					found=1;
					fault++;
				}
				else { /* reset use bit */
					use_flag[cnt]=0;
				}
				cnt++; /* Move pointer */
				if(cnt==frameSize) { cnt=0; } /* Reset */
			} while (found!=1);
		}
	}
	return fault;
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
        deque <string> pageList; //store the randomly generated pages
        for (int j=0; j<totalPage; ++j){
            string str = to_string(distribution(generator));
            pageList.push_back(str);
        }

        for (int frameSize = 2; frameSize < 21; frameSize ++) {
            fifo[frameSize] += func_fifo(pageList, frameSize);
 
            lru[frameSize] += func_lru(pageList, frameSize);

            opt[frameSize] += func_opt(pageList, frameSize);

            clock[frameSize] += func_clock(pageList,frameSize);
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
