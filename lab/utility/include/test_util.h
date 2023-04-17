#include <string>

class Status{
    public:
        bool bPass;
        std::string msg;

    public:
        Status();
        void init();
        void update(bool bPass, const char* msg);
};