#ifndef SERVER_H
#define SERVER_H

namespace CPPServer {
    class Server {
    // Private member variables
    private:
        int mSockFD;
    
    // Public member functions
    public:
        bool Initialize(const int PortNum, const int BacklogSize, void (*Output)(const std::string&));
        void Operate(const std::string& HaltMsg, void (*Output)(const std::string&)) const;
    
    // Private member functions
    private:
        void CreateAddrStruct(struct sockaddr_in* const ServerAddr, const int PortNum) const;
        bool ReadIncomingMsg(const int ClientFD, std::string& Msg) const;
        bool SendResponseMsg(const int ClientFD, const std::string& ResponseMsg) const;
        void DetermineClientIP(const struct sockaddr_in& ClientAddr, std::string& ClientIP) const;
        void SwitchEndianFormat(void* const Buffer, const size_t BufSize) const;
    };
}

#endif // SERVER_H
