#ifndef CSERVICEARUNNER_H
#define CSERVICEARUNNER_H

#include "../Data.hh"
#include "CServiceA.h"

class CServiceARunner
{
public:
    CServiceARunner(int argc, char **argv);
    ~CServiceARunner();
    void run();
    CORBA::String_var get_ior();

private:
    // Брокер объектных запросов (Object Request Broker, ORB)
    CORBA::ORB_var m_orb;
    // Сервант
    PortableServer::Servant_var<CServiceA_i> m_c_service_a;
    // Строковая IOR ссылка на объект-сервант
    CORBA::String_var m_ior;
    // POA
    PortableServer::POA_var m_poa;
    // RootPOA
    CORBA::Object_var m_root_poa_obj;
    // POA менеджер
    PortableServer::POAManager_var poa_manager;
    // ObjectID
    PortableServer::ObjectId_var m_c_service_a_oid;
};

#endif // CSERVICEARUNNER_H