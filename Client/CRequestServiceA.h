#ifndef CREQUESTSERVICEA_H
#define CREQUESTSERVICEA_H

#include <utility>
#include "../Data.hh"

class CRequestServiceA
{
public:
    CRequestServiceA(int argc, char **argv);
    ~CRequestServiceA();
    CORBA::String_var RequestHelloWorld(CORBA::String_var);
    std::pair<CORBA::Long, bool> RequestDiv(CORBA::Long, CORBA::Long);
    CORBA::String_var RequestCaesarCipher(CORBA::String_var, CORBA::Short);

private:
    // Объект, связанный с брокером объектных запросов (Object Request Broker, ORB)
    CORBA::ORB_var m_orb;
    // Объект посредством которого осуществляются запросы
    Data::ServiceA_var m_obj;
};

#endif // CREQUESTSERVICEA_H