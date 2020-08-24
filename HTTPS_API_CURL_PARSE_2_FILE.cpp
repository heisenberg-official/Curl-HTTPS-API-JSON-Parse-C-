/*
** Author: Vineet Kumar
** Just A Simple Tech
*/

#include<iostream>
#include<Windows.h>

std::string GetStdoutFromCommand(std::string cmd)
{
    std::string data;
    FILE* stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = _popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        _pclose(stream);
    }
    return data;
}

std::string MaskToJson(std::string cmd_data)
{
    int x = -1;
    for (int i = 0; i < cmd_data.length(); i++)
    {
        x++;
        if (cmd_data[i] == '{')
            break;
    }
    cmd_data.erase(0, x);
    return cmd_data;
}

int main()
{
	std::string MainCMD = "curl -H \"Content-Type: application/x-www-form-urlencoded\" -H \"XF-Api-Key: XYZHEADERAPI\" -d \"login=HEiSENBERG&password=YourPassword\" https://YourWebsite.XYZ/api/auth";
	std::string StdOut = MaskToJson(GetStdoutFromCommand(MainCMD));
	std::cout << StdOut;
	return 0;
}
