#include <iostream>
#include <vector>
// ADD ANY OTHER INCLUDES YOU DEEM NECESSARY

using namespace std;

// THE SKELETON BELOW HAS BEEN PROVIDED TO GIVE YOU IDEAS
// YOU CAN ADD ANY OTHER COMPONENT YOU WISH TO ADD

class File{
    //YOUR CODE GOES HERE
};
class Directory{
    // YOUR CODE GOES HERE
    public:
    vector<Directory*> files;
    Directory* fdirpointer;
    string fpath;
    string contents;
    string fname;
    static bool flag;

    vector<Directory*> subfolders;
    string dirpath;
    string name;
    Directory* parentdirpointer;

    Directory()
    {
        if(flag==false)
        {
            this->subfolders;
            this->files;
        }
        else
        {
            this->dirpath="/";
            this->subfolders={};
            this->parentdirpointer=NULL;
            this->name="/";
            this->files={};
        }
        flag=false;
    }
    void newfile(string filename, Directory* parentdir)
    {
        Directory* parentdirectory=parentdir;
        Directory* file=new Directory();
        file->fname=filename;
        vector<Directory*> vectortemp=parentdirectory->files;
        int counter=0;
        while(counter<vectortemp.size())
        {
            if(vectortemp[counter]->fname==filename)
            {
                cout<<"A file with that name already exists!"<<endl;
                return;
            }
            counter++;
        }
        parentdirectory->files.push_back(file);
        file->fdirpointer=parentdirectory;
    }
    void newsubdir(string dirname, Directory* prevpointer)
    {
        Directory* subdirectory=new Directory();
        subdirectory->name=dirname;
        Directory* parentpointer=prevpointer;
        if(prevpointer->parentdirpointer!=NULL)
        {
            subdirectory->dirpath=prevpointer->dirpath+"/"+subdirectory->name;
        }
        else
        {
            subdirectory->dirpath=prevpointer->dirpath+subdirectory->name;
        }
        vector<Directory*> directorychildren=prevpointer->subfolders;
        int counter=0;
        while(counter<directorychildren.size())
        {
            if(directorychildren[counter]->name==dirname)
            {
                cout<<"A directory with that name already exists!"<<endl;
                return;
            }
            counter++;
        }
        parentpointer->subfolders.push_back(subdirectory);
        subdirectory->parentdirpointer=prevpointer;
    }
    string getPath()
    {
        return dirpath;
    }
    void createnano(string filename, string filecont, Directory* directorycurrent);
    void coutfilenames(Directory* directorycurrent);
    void coutdirs(Directory* directorycurrent);
};
bool Directory::flag=true;
void Directory::coutfilenames(Directory* directorycurrent)
{
    int counter=0;
    while(counter<directorycurrent->files.size())
    {
        if(directorycurrent->files[counter]!=NULL)
        {
            if(counter==files.size()-1)
            {
                cout<<directorycurrent->files[counter]->fname;
            }
            else
            {
                cout<<directorycurrent->files[counter]->fname<<" ";
            }
        }
        else
        {
            counter++;
            continue;
        }
        counter++;
    }
}
void Directory::coutdirs(Directory* directorycurrent)
{
    int counter=0;
    while(counter<directorycurrent->subfolders.size())
    {
        if(directorycurrent->subfolders[counter]==NULL)
        {
            counter++;
            continue;
        }
        else
        {
            if(counter==subfolders.size()-1)
            {
                cout<<directorycurrent->subfolders[counter]->name<<"(d)";
            }
            else
            {
                cout<<directorycurrent->subfolders[counter]->name<<"(d) ";
            }
        }
        counter++;
    }
}
void Directory::createnano(string filename, string filecont, Directory* directorycurrent)
{
    int counter=0;
    Directory* file=new Directory();
    file->contents=filecont;
    file->fname=filename;
    Directory* dirpointer=directorycurrent;
    vector<Directory*> filesvect=dirpointer->files;
    while(counter<filesvect.size())
    {
        if(filesvect[counter]->fname==filename)
        {
            cout<<"A file with that name already exists!"<<endl;
            return;
        }
        counter++;
    }
    dirpointer->files.push_back(file);
    file->fdirpointer=dirpointer;
}

Directory * runCommand(Directory * pwd, vector<string> args)
{
    // YOUR CODE GOES HERE
    if(args[0] == "ls")
    {
        pwd->coutdirs(pwd);
        pwd->coutfilenames(pwd);
        return pwd;
    }
    else if(args[0] == "mkdir")
    {
        if(args.size()==2)
        {
            pwd->newsubdir(args[1], pwd);
        }
        else if(args.size()>=3)
        {
            int counter=1;
            while(counter<args.size())
            {
                pwd->newsubdir(args[counter], pwd);
                counter++;
            }
        }
        else if(args.size()==1)
        {
            cout<<"mkdir: operand missing!";
        }
        return pwd;
    }
    else if(args[0] == "touch")
    {
        if(args.size()==2)
        {
            pwd->newfile(args[1], pwd);
        }
        else if(args.size()>=3)
        {
            int counter=1;
            while(counter<args.size())
            {
                pwd->newfile(args[counter], pwd);
                counter++;
            }
        }
        if (args.size()==1)
        {
            cout<<"touch: operand missing!";
        }
        return pwd;
    }
    else if(args[0] == "nano")
    {
        if(args.size()==2)
        {
            pwd->createnano(args[1], args[1], pwd);
        }
        else
        {
            pwd->createnano(args[1], args[2], pwd);
        }
        return pwd;
    }
    else if(args[0] == "display")
    {
        int counter=0;
        while(counter<pwd->files.size())
        {
            if(pwd->files[counter]->fname==args[1])
            {
                break;
            }
            counter++;
        }
        cout<<pwd->files[counter]->contents;
        return pwd;
    }
    else if(args[0] == "cd")
    {
        if(args.size()==1)
        {
            cout<<"cd: operand missing!";
        }
        else if(args[1]=="/")
        {
            while(pwd->parentdirpointer!=NULL)
            {
                pwd=pwd->parentdirpointer;
            }
        }
        else if(args[1]=="..")
        {
            if(pwd->parentdirpointer!=NULL)
            {
                pwd=pwd->parentdirpointer;
            }
        }
        else
        {
            bool invalid=true;
            Directory* tpointer;
            vector<Directory*> subdirectories=pwd->subfolders;
            if(!subdirectories.empty())
            {
                for(int counter=0; counter<subdirectories.size(); counter++)
                {
                    if(subdirectories[counter]->name==args[1])
                    {
                        invalid=false;
                        tpointer=subdirectories[counter];
                        break;
                    }
                }

            }
            else
            {
                invalid=true;
            }
            if(invalid==false)
            {
                pwd=tpointer;
            }
            else
            {
                cout<<"No such subdirectory!";
            }
        }
        return pwd;
    }
    else if(args[0] == "delete")
    {
        int counter1, counter2;
        counter1=0;
        counter2=0;
        bool flag=false;
        if(args.size()==1)
        {
            cout<<"delete: operand missing!";
        }
        else if(args[1]=="*")
        {
            pwd->subfolders={};
            pwd->files={};
        }
        else
        {
            while(counter1<pwd->subfolders.size())
            {
                if(pwd->subfolders[counter1]->name==args[1])
                {
                    flag=true;
                    pwd->subfolders[counter1]=NULL;
                    break;
                }
                counter1++;
            }
            while(counter2<pwd->files.size())
            {
                if(pwd->files[counter2]->fname==args[1])
                {
                    pwd->files[counter2]=NULL;
                    flag=true;
                    break;
                }
                counter2++;
            }
            if(flag==false)
            {
                cout<<"No such subdirectory or file!";
            }
        }
        return pwd;
    }
    else
    {
      cout<<"No such command!"<<endl;
      return pwd;
    }
}
