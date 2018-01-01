#include <iostream>
#include <string>
#include <vector>

static void command_loop();


int main(int argc, char *argv[])
{
    std::cout << "Welcome to the fracc CLI. Type 'help' for a list of supported commands.\n";
    command_loop();
}


static void command_loop()
{
    bool quit = false;

    std::string cmd;
    std::vector<std::string> tokens;

    while (!quit)
    {
        std::cout << "> ";

        std::getline(std::cin, cmd);
        for (char& c : cmd) { c = std::tolower(c); }

        // tokenize by spaces
        size_t i = 0;
        tokens.clear();
        while (i < cmd.size())
        {
            for (; (i < cmd.size()) && std::isspace(cmd[i]); ++i);
            if (i < cmd.size())
            {
                size_t prev_i = i;
                for (; (i < cmd.size()) && !std::isspace(cmd[i]); ++i);
                tokens.push_back(cmd.substr(prev_i, i - prev_i));
            }
        }
        if (!tokens.size()) continue;

        if (tokens[0] == "q")
        {
            quit = true;
        }

        else if (tokens[0] == "mbot" || tokens[0] == "mandelbrot")
        {
            // syntax: mbot [re_min im_min re_width im_width]
            double re_min, im_min, re_width, im_width;

            if (tokens.size() == 1)
            {
                re_min = -2.0;
                im_min = -1.0;
                re_width = 3.0;
                im_width = 2.0;
            }
            else if (tokens.size() == 5)
            {
                try
                {
                    re_min   = std::stod(tokens[1]);
                    im_min   = std::stod(tokens[2]);
                    re_width = std::stod(tokens[3]);
                    im_width = std::stod(tokens[4]);
                }
                catch (const std::exception& exc)
                {
                    std::cout << "invalid parameter(s) :(\n";
                    continue;
                }
            }
            else
            {
                std::cout << "wrong number of parameters :(\n";
                continue;
            }

            
        }
    }
}
