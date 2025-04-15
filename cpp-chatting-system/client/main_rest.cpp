#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>

using namespace utility;                  // string conversions
using namespace web;                      // common features like URIs
using namespace web::http;                // HTTP client features
using namespace web::http::client;        // HTTP client

int main() {
	try {
		http_client client(U("http://httpbin.org/get"));

		uri_builder builder(U("/"));
		http_response response = client.request(methods::GET).get();

		std::wcout << L"Status Code: " << response.status_code() << std::endl;
		std::wcout << L"Response: " << response.extract_string().get() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}