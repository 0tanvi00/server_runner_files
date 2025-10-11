#include "crow.h"
#include <cstdlib>
#include <iostream>

void callPythonScript() {
    int ret = std::system("python test.py");
    std::cout << "Python script exited with code " << ret << std::endl;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        callPythonScript();
        return "C++ (Crow) server is running!\n";
    });

    app.port(3000).multithreaded().run();
}
