#include "iniFile.h"
#include "value.h"

using namespace louis::value;
using namespace louis::ini;

int main(int argc, char const* argv[]) {
    IniFile ini;
    ini.load("./main.ini");

    // const string& ip = ini.get("server", "ip");
    // int port = ini.get("server", "port");

    const string& ip = ini["server"]["ip"];
    int port = ini["server"]["port"];

    ini.set("server", "flag", true);
    ini.set("server", "timeout", 1000);

    ini["server"]["flag"] = false;
    ini["server"]["timeout"] = 2000;

    bool flag1 = ini.has("server");
    bool flag2 = ini.has("serve");

    bool flag3 = ini.has("server", "ip");
    bool flag4 = ini.has("server", "ipp");

    ini.show();

    ini.save("./tmp.ini");
    return 0;
}
