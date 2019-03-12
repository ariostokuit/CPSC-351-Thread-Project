//
//  main.cpp
//  ThreadProject
//
//  Created by Ariosto Kuit on 3/11/19.
//  Copyright © 2019 Ariosto Kuit. All rights reserved.
//

#include <iostream>
#include <thread>//will be used to create threads
#include <string>
#include <fstream> //will be used for printing onto log file
#include <mutex> //this is needed to use mutex lock
using namespace std;

const int ALPHABETSIZE = 26; //global constant variable
const int NUMBERSIZE = 26;
mutex mtx1,mtx2; //mutex lock object

void threadA(ostream &outputLogText){//function is called to print 1-26 ten times
   lock(mtx1,mtx2);
    for(int a = 0; a < 10;a++){
        for(int i = 1; i <= NUMBERSIZE;i++){
        outputLogText << i << " ";
        }
        outputLogText << endl;
    }
    outputLogText << "...(10 total times)\n";
    mtx1.unlock();
    mtx2.unlock();
}

void threadB(ostream &outputLogText){ //will print out the alphabet 10 times

    lock(mtx2,mtx1);
    for(int i = 0; i < 10; i++){
        for(int j = 65; j < (65+ALPHABETSIZE);j++){
            outputLogText << char(j) << " ";
        }
        outputLogText << endl;
    }
    outputLogText << "...(10 total times)\n";
    mtx2.unlock();
    mtx1.unlock();
}

int main(int argc, const char * argv[]) {
    
    ofstream outputLogText;
   
    outputLogText.open("Akuit.log");
    
    outputLogText << "Ariosto's Project 2 started\n";
    
    
    thread first(threadA,ref(outputLogText));
    thread second(threadB,ref(outputLogText));
    
    thread::id threadA_ID = first.get_id();
    thread::id threadB_ID = second.get_id();
    outputLogText << "Thread A " << "(" << threadA_ID << ") created\n";
    outputLogText << "Thread B " << "(" << threadB_ID << ") created\n";
 
    //synchronize the threads:
    first.join();
    second.join();
    
    outputLogText << "Thread A " << "(" << threadA_ID << ") terminated\n";
    outputLogText << "Thread B " << "(" << threadB_ID << ") terminated\n";
    outputLogText << "Ariosto's Project 2 ended\n";
    
    return 0;
}

