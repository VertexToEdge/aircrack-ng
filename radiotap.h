#include <iostream>
#include <cstring>
#include <map>
#include <struct_radiotap.h>
#include <boost/any.hpp>

#ifndef RADIOTAP_H
#define RADIOTAP_H


using std::cout;
using std::endl;
class radiotap
{
private:
    radiotap_header header;
    std::map<uint8_t, boost::any> elements;
public:
    radiotap(const u_char *data);
    radiotap_header getHeader(){
        return header;
    }
    ~radiotap(){
        delete[] header.present;

    }
};

#endif // RADIOTAP_H
