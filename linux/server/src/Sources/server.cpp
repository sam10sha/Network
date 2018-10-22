#include "stdafx.h"
#include "server.h"


// Public member functions
bool CPPServer::Server::Initialize(const int PortNum, const int BacklogSize, void (*Output)(const std::string&))
{
    bool SocketCreated = false;
    bool SocketBound = false;
    bool InitSuccess = false;
    
    struct sockaddr_in ServerAddr;
    
    Output(std::string("Initializing..."));
    
    mSockFD = socket(AF_INET, SOCK_STREAM, 0);
    SocketCreated = mSockFD > 0;
    if(SocketCreated == true)
    {
        SocketBound = bind(mSockFD, (const struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == 0;
    }
    if(SocketBound == true)
    {
        InitSuccess = listen(mSockFD, BacklogSize) < 0;
    }
    return InitSuccess;
}

void CPPServer::Server::Operate(const std::string& HaltMsg, void (*Output)(const std::string&)) const
{
    Output(std::string("Operating..."));
    int ClientFD = 0;
    struct sockaddr_in ClientAddr;
    socklen_t ClientAddrLen = sizeof(ClientAddr);
    std::string IncomingMsg;
    std::string ResponseMsg;
    while(IncomingMsg.compare(HaltMsg) != 0)
    {
        ClientFD = accept(mSockFD, (sockaddr*)&ClientAddr, &ClientAddrLen);
        if(ClientFD > 0)
        {
            ReadIncomingMsg(ClientFD, IncomingMsg);
            DetermineClientIP(ClientAddr, ResponseMsg);
            SendResponseMsg(ClientFD, ResponseMsg);
        }
    }
}




// Private member functions
void CPPServer::Server::CreateAddrStruct(struct sockaddr_in* const ServerAddr, const int PortNum) const
{
    ServerAddr->sin_family = AF_INET;
    ServerAddr->sin_port = htons(PortNum);
    ServerAddr->sin_addr.s_addr = INADDR_ANY;
}

bool CPPServer::Server::ReadIncomingMsg(const int ClientFD, std::string& Msg) const
{
    bool MsgSizeReceived = false;
    bool MsgReceived = false;
    int MsgSize = 0;
    char* MsgBytes = nullptr;
    
    Msg.clear();
    
    MsgSizeReceived = recv(ClientFD, &MsgSize, sizeof(int), 0) > 0;
    if(MsgSizeReceived == true)
    {
        SwitchEndianFormat(&MsgSize, sizeof(int));
        MsgBytes = new char[MsgSize + 1];
        std::memset(MsgBytes, 0, MsgSize + 1);
        MsgReceived = recv(ClientFD, &MsgBytes, MsgSize, 0) > 0;
        Msg.append(MsgBytes);
        delete[] MsgBytes;
    }
    return MsgReceived;
}

bool CPPServer::Server::SendResponseMsg(const int ClientFD, const std::string& ResponseMsg) const
{
    bool ResponseSizeSent = false;
    bool ResponseSent = false;
    int MsgSize = 0;
    
    MsgSize = ResponseMsg.size();
    SwitchEndianFormat(&MsgSize, sizeof(int));
    ResponseSizeSent = send(ClientFD, &MsgSize, sizeof(int), 0) > 0;
    if(ResponseSizeSent == true)
    {
        ResponseSent = send(ClientFD, ResponseMsg.c_str(), ResponseMsg.size(), 0) > 0;
    }
    return ResponseSent;
}

void CPPServer::Server::DetermineClientIP(const struct sockaddr_in& ClientAddr, std::string& ClientIP) const
{
    const size_t IP_BUF_LEN = 32;
    char IPBuffer[IP_BUF_LEN];
    ClientIP.clear();
    inet_ntop(AF_INET, &ClientAddr.sin_addr, IPBuffer, IP_BUF_LEN);
    ClientIP.append(IPBuffer);
}

void CPPServer::Server::SwitchEndianFormat(void* const Buffer, const size_t BufSize) const
{
    char CurrentByte;
    for(size_t i = 0; i < BufSize / 2; i++)
    {
        CurrentByte = *((char*)Buffer + i);
        *((char*)Buffer + i) = *((char*)Buffer + BufSize - i - 1);
        *((char*)Buffer + BufSize - i - 1) = CurrentByte;
    }
}




