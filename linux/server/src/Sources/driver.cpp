#include <stdafx.h>
#include "server.h"

/* MUST FREE MEMORY ALLOCATED TO GENERATED LIST */
/* Will only include arguments, excluding program name */
std::vector<std::string*>* CreateArgumentList(const int NumArgs, const char** const Arguments);
/* WILL ONLY DELETE ELEMENTS IN LIST; LIST WILL REMAIN ALLOCATED */
void ClearArgumentList(std::vector<std::string*>* const ArgumentList);
bool ConvertToInt(std::string* const Str, int* const ConvertedNum);
void Printer(const std::string& Msg);

int main(int argc, char** argv)
{
    bool ArgListCreated = false;
    bool PortNumParsed = false;
    bool BacklogSizeParsed = false;
    
    std::vector<std::string*>* ArgumentList;
    int PortNum = 0;
    int BacklogSize = 0;
    CPPServer::Server* mServer;
    
    if(argc >= 3)
    {
        ArgumentList = CreateArgumentList(argc, (const char**)argv);
        ArgListCreated = true;
    }
    if(ArgListCreated == true)
    {
        PortNumParsed = ConvertToInt((*ArgumentList)[0], &PortNum);
    }
    if(PortNumParsed == true)
    {
        BacklogSizeParsed = ConvertToInt((*ArgumentList)[1], &BacklogSize);
    }
    if(BacklogSizeParsed == true)
    {
        mServer = new CPPServer::Server();
        if(mServer->Initialize(PortNum, Printer) == true)
        {
            mServer->Operate(BacklogSize, std::string("halt"), Printer);
        }
        delete mServer;
    }
    else
    {
        Printer(std::string("Failed to process arguments"));
    }
    
    if(ArgListCreated == true)
    {
        ClearArgumentList(ArgumentList);
        delete ArgumentList;
        ArgumentList = nullptr;
    }
    return 0;
}

std::vector<std::string*>* CreateArgumentList(const int NumArgs, const char** const Arguments)
{
    std::vector<std::string*>* ArgList = new std::vector<std::string*>();
    std::string* NextArg;
    for(int i = 1; i < NumArgs; i++)
    {
        NextArg = new std::string(*(Arguments+i));
        ArgList->push_back(NextArg);
    }
    return ArgList;
}

void ClearArgumentList(std::vector<std::string*>* const ArgumentList)
{
    std::string* LastArg;
    while(ArgumentList->empty() == false)
    {
        LastArg = ArgumentList->back();
        ArgumentList->pop_back();
        delete LastArg;
        LastArg = nullptr;
    }
}

bool ConvertToInt(std::string* const Str, int* const ConvertedNum)
{
    bool ConvertSuccess = false;
    std::string::size_type Size;
    try
    {
        *ConvertedNum = std::stoi(*Str, &Size);
        ConvertSuccess = true;
    }
    catch(std::exception& e)
    {
        
    }
    return ConvertSuccess;
}

void Printer(const std::string& Msg)
{
    std::cout << Msg << std::endl;
}
