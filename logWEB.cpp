// logWEB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "httplib.h"

int main()
{
    std::cout << "Hello World!\n";

    // HTTP
    httplib::Server svr;

    // Mount /public to ./www directory
    auto ret = svr.set_mount_point("/livelog", "./www");
    if (!ret) {
        // The specified base directory doesn't exist...
    }

    svr.Get("/hi", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 9074);





    // Remove mount /public
    ret = svr.remove_mount_point("/public");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
