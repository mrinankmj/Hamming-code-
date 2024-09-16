#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Function to convert a string IP address to an integer
int stringToIP(const string &ip)
{
    int ipAddr = 0;
    int pos = 0;
    int count = 0;
    for (int i = 0; i < ip.length(); i++)
    {
        if (ip[i] == '.')
        {
            ipAddr = (ipAddr << 8) + stoi(ip.substr(pos, i - pos));
            pos = i + 1;
            count++;
        }
    }
    ipAddr = (ipAddr << (8 * (3 - count))) + stoi(ip.substr(pos));
    return ipAddr;
}

// Function to find the IP class
string findIPClass(int ipAddr)
{
    if ((ipAddr & 0x80000000) == 0)
    {
        return "Class A";
    }
    else if ((ipAddr & 0xC0000000) == 0x80000000)
    {
        return "Class B";
    }
    else if ((ipAddr & 0xE0000000) == 0xC0000000)
    {
        return "Class C";
    }
    else
    {
        return "Invalid IP address";
    }
}

// Function to find the subnet mask based on the IP class
int findSubnetMask(const string &ipClass)
{
    if (ipClass == "Class A")
    {
        return 0xFF000000;
    }
    else if (ipClass == "Class B")
    {
        return 0xFFFF0000;
    }
    else if (ipClass == "Class C")
    {
        return 0xFFFFFF00;
    }
    return 0;
}

// Function to find the broadcast network address
int findBroadcastAddress(int ipAddr, int subnetMask)
{
    return ipAddr | (~subnetMask);
}

// Function to find the first and last IP addresses of the block
pair<int, int> findFirstLastIP(int ipAddr, int subnetMask)
{
    int firstIP = ipAddr & subnetMask;
    int lastIP = ipAddr | (~subnetMask);
    lastIP = (lastIP == 0xFFFFFFFF) ? lastIP : lastIP - 1;
    return make_pair(firstIP, lastIP);
}

int main()
{
    string ipAddress;
    cout << "Enter an IP address: ";
    cin >> ipAddress;

    int ipAddr = stringToIP(ipAddress);
    string ipClass = findIPClass(ipAddr);
    int subnetMask = findSubnetMask(ipClass);
    int broadcastAddr = findBroadcastAddress(ipAddr, subnetMask);
    pair<int, int> firstLastIP = findFirstLastIP(ipAddr, subnetMask);

    cout << "IP Class: " << ipClass << endl;
    cout << "Subnet Mask: " << bitset<32>(subnetMask).to_string() << endl;
    cout << "Broadcast Network Address: " << bitset<32>(broadcastAddr).to_string() << endl;
    cout << "First IP Address: " << bitset<32>(firstLastIP.first).to_string() << endl;
    cout << "Last IP Address: " << bitset<32>(firstLastIP.second).to_string() << endl;

    return 0;
}