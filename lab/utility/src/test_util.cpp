#include "test_util.h"

Status::Status(){
    init();
}

void Status::init(){
    this->bPass=false;
    this->msg="n/a";
}

void Status::update(bool bPass, const char* msg){
    this->bPass = bPass;
    this->msg = std::string(msg);
}
