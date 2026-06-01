#include "../generated/proto/warehouse.pb.h"

#include <iostream>

int main() {
    warehouse::LoginRequest req;
    req.set_username("admin");
    req.set_password("123456");
    std::string data;
    req.SerializeToString(&data);
    std::cout << "Serialized Size: " << data.size() << std::endl;

    warehouse::LoginRequest copy;
    copy.ParseFromString(data);

    std::cout << copy.username() << std::endl << copy.password() << std::endl;

    return 0;
}