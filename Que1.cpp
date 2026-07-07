#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(){
    pid_t pid = fork();
    
    int x = 1;

    if(pid==0){
        cout<<"Child has x = "<< ++x <<endl;

    }else if(pid>0){
        cout<<"Parent has x = "<<--x <<endl;
        wait(NULL);

    }else{
        cout<<"FORK FAILED"<<endl;
    }

    return 0;
}