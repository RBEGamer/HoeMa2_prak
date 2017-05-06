//
// Created by Marcel Ochsendorf on 06.05.17.
//

#include "vec.h"

vec::vec(const u_int16_t _size){
    size = _size;
    data_storage.clear();
    data_storage.reserve(VEC_INIT_SITE);
std::cout <<"size "<< _size <<std::endl;
    for (int i = 0; i < _size; ++i) {
    data_storage.push_back(VEC_INIT_VALUE);
    }
}


vec::vec(const char* _fmt,...){
    data_storage.reserve(VEC_INIT_SITE);
    data_storage.clear();
    va_list args;
    va_start(args, _fmt);
    int counter = 0;
    while (*_fmt != '\0') {
        VEC_TYPE d = va_arg(args, VEC_TYPE);
            data_storage.push_back(d);
        ++_fmt;
        counter++;
    }
    va_end(args);
    size = data_storage.size();
}


void vec::print(){
    std::cout << " { ";
    for (int i = 0; i < data_storage.size(); ++i) {
std::cout << data_storage[i] << ", ";
    }
    std::cout << "}" << std::endl;
}

int vec::set_value(u_int16_t _pos, const VEC_TYPE _val){
    //cehck size
    if(data_storage.size() == 0){
#ifdef VEC_WARNING
        std::cout << __FILE__ << ":" << __LINE__ << "->" << "set_val empty vector" << std::endl;
#endif
        throw "out of range";
        return  -1;}
    int s =data_storage.size();
if(_pos >= data_storage.size()){
#ifdef VEC_WARNING
    std::cout << __FILE__ << ":" << __LINE__ << "->" << "set_val out of range" << std::endl;
#endif
    throw "out of range";
    return -1;
}
    data_storage.at(_pos) = _val;
return 0;
}

//Call set_row_values("ddd",1.0,2.0,3.0f);
int vec::set_row_values(const char* _fmt,...){
    va_list args;
    va_start(args, _fmt);
    int counter = 0;
    while (*_fmt != '\0') {
        if (*_fmt == 'd') {
            double d = va_arg(args, double);
            data_storage.at(counter) = d;
            printf("%f\n", d);
        }else if (*_fmt == 'f') {
            float d = va_arg(args, float);
            data_storage.at(counter) = (VEC_TYPE)d;
            printf("%f\n", d);
        }else{
                #ifdef VEC_WARNING
                std::cout << __FILE__ << ":" << __LINE__ << "->" << "not implemented set row_val" << std::endl;
                #endif
                throw "this type is not implemented";
                //return  -1;
            }
        ++_fmt;
        counter++;
    }
    va_end(args);
    return 0;
}

VEC_TYPE vec::get_val(u_int16_t _pos){
    //cehck size
    if(_pos >= data_storage.size()){
#ifdef VEC_WARNING
        std::cout << __FILE__ << ":" << __LINE__ << "->" << "get_val out of range" << std::endl;
#endif
        throw "out of range";
    }
return data_storage.at(_pos);
}

std::vector<VEC_TYPE> vec::get_val_row(){
return data_storage;
}

VEC_TYPE& vec::at(u_int16_t _pos){
    if(_pos >= data_storage.size()){
#ifdef VEC_WARNING
        std::cout << __FILE__ << ":" << __LINE__ << "->" << "get_val out of range" << std::endl;
#endif
        throw "out of range";
    }
return data_storage.at(_pos);
}

vec vec::operator+ (vec& _other){
    uint16_t  si = this->gsize();
    if(si > _other.gsize()){
        si = _other.gsize();
    }
    vec tmp(si);

    for (int i = 0; i < tmp.gsize(); ++i) {
     tmp.set_value(i,this->get_val(i) + _other.get_val(i));
    }

    return tmp;
}

vec vec::operator* (VEC_TYPE _lam){
    vec tmp(this->gsize());
    for (int i = 0; i < tmp.gsize(); ++i) {
    tmp.set_value(i, this->get_val(i)*_lam);
    }
    return  tmp;
}

VEC_TYPE vec::operator[] (u_int16_t _pos){
    if(_pos >= data_storage.size()){
#ifdef VEC_WARNING
        std::cout << __FILE__ << ":" << __LINE__ << "->" << "op[] out of range" << std::endl;
#endif
       throw "out of range";

    }

    return data_storage.at(_pos);
}

u_int16_t vec::gsize(){
return size;
}

VEC_TYPE vec::length(){
    VEC_TYPE sum = 0.0f;
    for (int i = 0; i < data_storage.size(); ++i) {
        sum += pow(data_storage.at(i),2.0);
    }
    return sqrt(sum);
}