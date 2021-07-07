#include <stdexcept>
#include <iostream>
#include <utility>

#include "CRequestServiceA.h"
#include "../Data.hh"

CRequestServiceA::CRequestServiceA(int argc, char **argv)
{
    // Инициализация брокера объектных запросов (Object Request Broker, ORB)
    m_orb = CORBA::ORB_init(argc, argv);
    if (CORBA::is_nil(m_orb))
    {
        throw std::runtime_error("CORBA::ORB_init failed.");
    }
    // Получение корневого контекста именования
    CORBA::Object_var ns_obj = m_orb->resolve_initial_references("NameService");
    if (CORBA::is_nil(ns_obj))
    {
        throw std::runtime_error("CORBA::ORB->resolve_initial_references failed.");
    }
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(ns_obj);
    if (CORBA::is_nil(nc))
    {
        throw std::runtime_error("CosNaming::NamingContext::_narrow failed.");
    }
    // Получение доступа к серверу
    CosNaming::Name name;
    name.length(1);
    name[0].id = "DataService";
    name[0].kind = "Context";
    CORBA::Object_var obj = nc->resolve(name);
    if (CORBA::is_nil(obj))
    {
        throw std::runtime_error("CosNaming::NamingContext->resolve failed.");
    }
    // Получение доступа к запрашиваемому объекту
    m_obj = Data::ServiceA::_narrow(obj);
    if (CORBA::is_nil(obj))
    {
        throw std::runtime_error("Data::ServiceA::_narrow failed.");
    }
}

CRequestServiceA::~CRequestServiceA()
{
    try
    {
        m_orb->destroy(); // Уничтожение объекта ORB
    }
    catch (...)
    {
        std::cerr << "Orb destroy exception occurred." << std::endl;
    }
}

CORBA::String_var CRequestServiceA::RequestHelloWorld(CORBA::String_var message_svar)
{
    return m_obj->HelloWorld(message_svar);
}

std::pair<CORBA::Long, bool> CRequestServiceA::RequestDiv(CORBA::Long a, CORBA::Long b)
{
    CORBA::Long c = 0;
    CORBA::Boolean response = m_obj->Div(a, b, c);
    return {c, response};
}

CORBA::String_var CRequestServiceA::RequestCaesarCipher(CORBA::String_var message_svar, CORBA::Short k)
{
    CORBA::String_INOUT_arg str(message_svar);
    m_obj->CaesarCipher(str, k);
    return CORBA::string_dup(str);
}
