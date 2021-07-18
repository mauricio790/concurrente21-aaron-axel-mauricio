#ifndef MAGO_H
#define MAGO_H

#include<vector>
#include<string>
class Mago{
 public:
  Mago();
  ~Mago();
  int start(int argc, char* argv[]);
 private:
  void send_maps();
  void receive_maps();
  int analyze_arguments(int argc, char* argv[]);
  std::vector<std::string> get_mapas();
 private:
  std::string job_order;
  int num_threads;

};

#endif
