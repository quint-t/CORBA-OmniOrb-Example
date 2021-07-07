#include "CServiceARunner.h"
#include "CServiceA.h"
#include "../Data.hh"

#include <utility>
#include <iostream>

CServiceARunner::CServiceARunner(int argc, char **argv)
{
    // Инициализация брокера объектных запросов
    // (Object Request Broker, ORB)
    m_orb = CORBA::ORB_init(argc, argv);
    if (CORBA::is_nil(m_orb))
    {
        throw std::runtime_error("CORBA::ORB_init failed.");
    }
    // Получение доступа к переносимому объектному адаптеру по умолчанию
    // (Root Portable Object Adapter, RootPOA)
    m_root_poa_obj = m_orb->resolve_initial_references("RootPOA");
    if (CORBA::is_nil(m_root_poa_obj))
    {
        throw std::runtime_error("CORBA::ORB->resolve_initial_references(\"RootPOA\") failed.");
    }
    m_poa = PortableServer::POA::_narrow(m_root_poa_obj);
    if (CORBA::is_nil(m_poa))
    {
        throw std::runtime_error("PortableServer::POA::_narrow failed.");
    }
    PortableServer::POAManager_var poa_manager = m_poa->the_POAManager();
    if (CORBA::is_nil(poa_manager))
    {
        throw std::runtime_error("PortableServer::POA->the_POAManager() failed.");
    }
    // Создание серванта
    m_c_service_a = new CServiceA_i();
    // Активация серванта в RootPOA (переносимом объектном адаптере по умолчанию)
    m_c_service_a_oid = m_poa->activate_object(m_c_service_a);
    // Запоминание строковой IOR ссылки на объект-сервант
    // (Interoperable Object Reference, IOR)
    m_ior = m_orb->object_to_string(m_c_service_a->_this());
    // Получение корневого контекста именования
    CORBA::Object_var name_service_obj = m_orb->resolve_initial_references("NameService");
    if (CORBA::is_nil(name_service_obj))
    {
        throw std::runtime_error("CORBA::ORB->resolve_initial_references(\"NameService\") failed.");
    }
    CosNaming::NamingContext_var naming_context = CosNaming::NamingContext::_narrow(name_service_obj);
    if (CORBA::is_nil(naming_context))
    {
        throw std::runtime_error("CosNaming::NamingContext::_narrow failed.");
    }
    // Привязка к службе имен CORBA
    CosNaming::Name name;
    name.length(1);
    name[0].id = "DataService";
    name[0].kind = "Context";
    naming_context->rebind(name, m_c_service_a->_this());
    // Активация POA Manager
    poa_manager->activate();
}

CServiceARunner::~CServiceARunner()
{
    try
    {
        m_orb->destroy(); // Уничтожение объекта ORB
    }
    catch (...)
    {
        std::cerr << "CORBA::ORB->destroy exception occurred." << std::endl;
    }
}

void CServiceARunner::run()
{
    m_orb->run();
}

CORBA::String_var CServiceARunner::get_ior()
{
    return m_ior;
}
