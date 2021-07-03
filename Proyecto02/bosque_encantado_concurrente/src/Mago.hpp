#ifndef MAGO_H
#define MAGO_H

#include<vector>
#include<string>
class Mago{
    
    public:
        Mago();
        ~Mago();
        int start(int argc,char* argv[]);
    private:
        int analyze_arguments(int argc, char* argv[]);
        std::vector<std::string> get_mapas();


    private:

        std::string job_order;
};

#endif