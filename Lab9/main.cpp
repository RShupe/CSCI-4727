#include <iostream>
#include <sys/stat.h>

struct stat st;

int main( int argc, char * argv[])
{
    using namespace std;

    if(argc != 2)
    {
        cout << "need argument" << endl;
        _Exit(1);
    }
    if(stat(argv[1], &st) == -1){
        cout << "something went wrong xD" << endl;
        _Exit(1);
    }

    cout <<"Size: "<< st.st_size << endl;
    cout <<"Blocks: " << st.st_blocks << endl;

    string filetype = "File type: ";

    if((st.st_mode & S_IFMT) == S_IFREG)
    {
        filetype += "Regular File";
    }
    else if((st.st_mode & S_IFMT) == S_IFBLK)
    {
        filetype += "Block Device";
    }
    else if((st.st_mode & S_IFMT) == S_IFDIR)
    {
        filetype += "Directory";
    }
    else if((st.st_mode & S_IFMT) == S_IFLNK)
    {
        filetype += "Symbolic Link";
    }
    else if((st.st_mode & S_IFMT) == S_IFIFO)
    {
        filetype += "FIFO Pipe";
    }
    else if((st.st_mode & S_IFMT) == S_IFCHR)
    {
        filetype += "Character Device";
    }
    else
    {
        filetype += "????? might have missed something";
    }

    cout << filetype << endl;
    cout << "Inode: " << st.st_ino << endl;
    cout <<"Mode: "<< st.st_mode << endl;
    cout <<"Links: "<< st.st_nlink << endl;
    cout <<"UID: "<< st.st_uid << endl;
    cout <<"GID: "<< st.st_gid << endl;
    cout <<"Access: " << ctime(&st.st_atime);
    cout <<"Modify: " << ctime(&st.st_mtime);
    cout <<"Change: " << ctime(&st.st_ctime);

    return 0;
}
