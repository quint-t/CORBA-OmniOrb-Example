#include "CRequestServiceA.h"
#include <iostream>

int main(int argc, char **argv)
{
    // В конструкторе устанавливается связь с сервером CORBA
    CRequestServiceA requestServiceA(argc, argv);
    // Отправка запросов, получение и вывод ответов
    auto responseHelloWorld = requestServiceA.RequestHelloWorld("Hello");
    auto responseDiv = requestServiceA.RequestDiv(10, 5);
    auto responseCaesarCipher = requestServiceA.RequestCaesarCipher("Hello, world!", 3);
    std::cout << "Response (HelloWorld): " << responseHelloWorld << std::endl;
    std::cout << "Response (Div, 10/2): " << responseDiv.first << " (div error: " << !responseDiv.second << ')' << std::endl;
    std::cout << "Response (CaesarCipher): " << responseCaesarCipher << std::endl;
    return 0;
}