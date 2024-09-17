// Your First C++ Program
#include <SDKDDKVer.h>

#include <iostream>
#include <boost/asio.hpp>
#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;

string read_(tcp::socket &socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}
void send_(tcp::socket &socket, const string &message)
{
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}

int main()
{
    while (true)
    {
        boost::asio::io_service io_service;
        // listen for new connection
        tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
        // socket creation
        tcp::socket socket_(io_service);
        // waiting for connection
        acceptor_.accept(socket_);
        // read operation
        string message = read_(socket_);
        if (message.c_str()[0] == 'r')
        {
            HANDLE hToken;
            TOKEN_PRIVILEGES tkp;

            // Get a token for this process.

            if (!OpenProcessToken(GetCurrentProcess(),
                                  TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
                return (1);

            // Get the LUID for the shutdown privilege.

            LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
                                 &tkp.Privileges[0].Luid);

            tkp.PrivilegeCount = 1; // one privilege to set
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            // Get the shutdown privilege for this process.

            AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
                                  (PTOKEN_PRIVILEGES)NULL, 0);

            if (GetLastError() != ERROR_SUCCESS)
                return 1;

            // Shut down the system and force all applications to close.

            if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
                               SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
                                   SHTDN_REASON_MINOR_UPGRADE |
                                   SHTDN_REASON_FLAG_PLANNED))
                return FALSE;

            // shutdown was successful
            return 0;
        }
        else
        {
            cout << message;
            // write operation
            send_(socket_, "Invalid command!");
        }
    }
    return 0;
}