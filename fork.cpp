#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    cout<<"fork duplicated memory of parent process and makes a child process"<<endl;
    cout<<"Before fork we only have 1 process. \n";
    pid_t pid = fork();

    if(pid<0){
        cout<<"ERROR, fork failed"<<endl;
        return 1;

    }else if (pid == 0){
        //CHILD PROCESS CODE GOES HERE    

        cout<<"Hello World, this is Child program"<<endl;
        cout<<"Process ID: "<< getpid()<<endl;
        //WE DO CHILD WORK HERE

        return 0;
    }else{
        //Parent work

        cout<<"Hello Parent here"<<endl;
        cout<<"PID is: "<<getpid()<<endl;

        wait(NULL);
        cout<<"Parent process exiting after child finished. \n";

    }

    return 0;
}
