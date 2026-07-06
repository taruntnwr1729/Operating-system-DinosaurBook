#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main(){
    string source_path;
    string dest_path;

    cout<<"enter the source file: ";
    cin>> source_path;
    cout<< "enter the destination file: ";
    cin>> dest_path;


    int src_fd = open(source_path.c_str(), O_RDONLY);

    if (src_fd < 0){
        cerr<<"error: source file"<<source_path<<" does not exist. \n";
        return 1;
    }
    int dest_fd = open(dest_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dest_fd < 0){
        cerr<<"error not able to create destination file. \n";
        close(src_fd);
        return 1;
    }

    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE))>0){
        ssize_t bytes_written = write(dest_fd, buffer, bytes_read);

        

        if(bytes_written != bytes_read){

            cerr<<"Critical error, failed in writing data. \n";
            close(src_fd);
            close(dest_fd);

            return 1;

        }


    }

        if(bytes_read<0){
            cerr<<"ERROR OCCURED WHILE READING. \n";
        }

        close(src_fd);
        close(dest_fd);

        cout<<"Sucess! File copied sucessfully. \n";


        return 0;

}