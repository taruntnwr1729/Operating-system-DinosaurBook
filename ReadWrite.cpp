#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
//we first imported POSIX API TO COMMUNICATE WITH KERNEL
using namespace std;

int main(){
    //SIMPLY DEFINED THE DATA TYPES
    string source_path;
    string dest_path;
    //TOOK INPUT OF FILES TO WHICH CHANGES WILL BE MADE
    cout<<"enter the source file: ";
    cin>> source_path;
    cout<< "enter the destination file: ";
    cin>> dest_path;

    //WE OPENED THE FILE
    int src_fd = open(source_path.c_str(), O_RDONLY);
    //WE CHECKED IF THE OPEN FUNCTION RETURNED -1 TO US WE WILL DO ERROR HANDLING
    if (src_fd < 0){
        cerr<<"error: source file"<<source_path<<" does not exist. \n";
        return 1;
    }
    //SIMILARLIY HERE
    int dest_fd = open(dest_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dest_fd < 0){
        cerr<<"error not able to create destination file. \n";
        close(src_fd);
        return 1;
    }
    //THIS IS THE MAIN LOGIC TO COPY DATA
    const int BUFFER_SIZE = 4096; //WE DEFINED HERE SIZE OF THE PAGE (4KB) WHICH WE WILL BE USING
    char buffer[BUFFER_SIZE]; //HERE READ FUNCTION WILL DUMP DATA SO THAT WRITE FUN CAN GRAB IT 
    ssize_t bytes_read; //DATA TYPE FOR NO. OF BYTES THAT ARE READ

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE))>0){
        //IN THIS LOOP WE CHECK IF THERE IS ANY BYTE THAT HAS BEEN READ
        ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
        //BY THIS WE WRITE IT INTO THE DESTINATION FILE

        

        if(bytes_written != bytes_read){
            //CONDITION TO CHECK IF EVERYTHING HAS BEEN WRITTEN OR NOT

            cerr<<"Critical error, failed in writing data. \n";//IF NOT THEN GIVE ERROR
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