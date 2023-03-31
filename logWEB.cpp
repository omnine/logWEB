// logWEB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "httplib.h"

#include "LogCollector.h"

int main()
{
    std::cout << "Hello World!\n";

    LogCollector q(5);
    q.enqueue("10");
    q.enqueue("20");
    q.enqueue("30");
    q.enqueue("40");
    q.enqueue("50");
    q.enqueue("60");
    q.dequeue();
    q.enqueue("70");
    q.dequeue();
    q.enqueue("80");
    q.display();


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

    svr.Get("/packets", [&](const httplib::Request&, httplib::Response& res) {
        // using chunk provider to transfer large buffer?
        std::vector<string> bucket;
        q.fetch(bucket);
        res.set_chunked_content_provider(
            "text/html",
            [bucket](size_t offset, httplib::DataSink& sink) {
            for (int i = 0; i < bucket.size(); i++)
            {
                string message = bucket[i];
                sink.write("<p>", 3);
                sink.write(message.c_str(), message.size());
                sink.write("</p>", 4);
            }
            sink.done(); // No more data
            return true; // return 'false' if you want to cancel the process.
        }
        );


//        res.set_content("Hello World!", "text/plain");
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
